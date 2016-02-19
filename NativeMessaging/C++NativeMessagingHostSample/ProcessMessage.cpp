// ////////////////////////////////////////////////////////////////////////////
// Carestream Health RESTRICTED INFORMATION - for internal use only
// ////////////////////////////////////////////////////////////////////////////
// 
// File:    ProcessMessage.cpp
// Author:  Forrest Feng
// Date:    2016.02.18
// Remark:  Process message received from chromium with JsonCpp librar.
//
// Copyright 2016, All Rights Reserved.
// 
// ////////////////////////////////////////////////////////////////////////////

#include "ProcessMessage.h"
#include "json\json.h"
#include "Windows.h" //ExitWindowsEx

// Edit this file to handle more request message from chromium browser

void ProcessMessage(char* jsonMsg)
{
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(jsonMsg, root);
	if (!parsingSuccessful)
	{
		return;
	}

	std::string request = root.get("request", "").asString();
	if (request == "logoff_windows")
	{
		ExitWindowsEx(EWX_LOGOFF, 0);
	}
}

