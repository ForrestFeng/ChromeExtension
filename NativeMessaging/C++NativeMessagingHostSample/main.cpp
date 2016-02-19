// ////////////////////////////////////////////////////////////////////////////
// Carestream Health RESTRICTED INFORMATION - for internal use only
// ////////////////////////////////////////////////////////////////////////////
// 
// File:    native.cpp
// Author:  Forrest Feng
// Date:    2016.02.18
// Remark:  This console program is used to process message sent from Chromium 
//          plugin. 
//          Example of useage:
//          1. User click logoff button or a menu on the web page.
//          2. The click handler function send a logoff request message to a 
//             native executable via chrome.runtime.sendNativeMessage
//             NOTE : If the executable is not running chromium will start it 
//             automatically.
//          3. The client receives this message and call windows API to logoff current user.
//
// Copyright 2016 All Rights Reserved.
// 
// ////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "ProcessMessage.h"

// Define union to read the message size easily
typedef union {
	unsigned long u32;
	unsigned char u8[4];
} U32_U8;

// On Windows, the default I / O mode is O_TEXT.Set this to O_BINARY
// to avoid unwanted modifications of the input / output streams.
int SetBinaryMode(FILE* file)
{
	int result;

	result = _setmode(_fileno(file), _O_BINARY);
	if (result == -1)
	{
		perror("Cannot set mode");
		return result;
	}
	// set do not use buffer
	result = setvbuf(file, NULL, _IONBF, 0);	
	if (result != 0)
	{
		perror("Cannot set zero buffer");
		return result;
	}

	return 0;
}

// main logic
int _tmain(int argc, _TCHAR* argv[])
{
	if (SetBinaryMode(stdin) != 0)
	{
		return -1;
	}
	if (SetBinaryMode(stdout) != 0)
	{
		return -1;
	}
				
	// The format of raw message received from the stdin
	// IIIISSSSS...SS
	// IIII is a 4bytes integer in binary format. It is the lenth of the following json message.
	// SSSSS...SS is the json message immidiatlly follows the 4 bytes header. 
	// Each message is serialized using JSON, UTF-8 encoded and is preceded with 32-bit message length in native byte order.
	// You can send message back to chromium plugin by writing the same formated IIIISSSSS...SS to stdout.

	size_t iSize = 0;
	U32_U8 lenBuf;
	lenBuf.u32 = 0;
	char* jsonMsg = NULL; // a json message encoded in utf-8 

	iSize = fread(lenBuf.u8, 1, 4, stdin);
	if (iSize == 4)
	{
		int iLen = (int)lenBuf.u32;
		// now read the message
		if (iLen > 0)
		{
			jsonMsg = (char*)malloc(8 * iLen);
			iSize = fread(jsonMsg, 1, iLen, stdin);

			// process message
			ProcessMessage(jsonMsg);

			// echo the message
			fwrite(lenBuf.u8, 1, 4, stdout);
			fwrite(jsonMsg, 1, iLen, stdout);
			fflush(stdout);	
		}
		
		
		//uncomment it to debug the messaging 
		/*FILE* log = fopen("D:\\native.txt", "w");
		fwrite((void*)lenBuf.u8, 1, 4, log);
		fwrite(utf8Buffer, 1, iLen, log);		
		fclose(log);*/
		

		// free resource
		if (jsonMsg != NULL)
			free(jsonMsg);
	}	
}

