# ChromeExtension
A sample of C++ version Chrome native messaging host.

This example show you how to click a button in the Chrome browser to sign off current user.

1. User click a button or a menu on the web page.
2. The click handler function send a logoff request message to a native executable via chrome.runtime.sendNativeMessage 
     NOTE: If the executable is not running chromium will start it automatically.
3. The client receives this message and run "shutdown.exe /l" (or call a similar windows API) to logoff current user.

Please ref to the chrome native messaging and sample.
https://developer.chrome.com/extensions/nativeMessaging
https://chromium.googlesource.com/chromium/src/+/master/chrome/common/extensions/docs/examples/api/nativeMessaging

