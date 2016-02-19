This directory contains an example of chrome application that uses native
messaging API that allows to communicate with a native application.

In order for this example to work you must first install the native messaging
host from the host directory.

To install the host:

On Windows:
  Run install_host.bat script in the host directory.
  This script installs the native messaging host for the current user, by
  creating a registry key
  HKEY_CURRENT_USER\SOFTWARE\Google\Chrome\NativeMessagingHosts\com.google.chrome.example.echo
  and setting its default value to the full path to
  host\com.google.chrome.example.echo-win.json .
  If you want to install the native messaging host for all users, change HKCU to
  HKLM.
  Note that you need to have python installed.

On Mac and Linux:
  Run install_host.sh script in the host directory:
    host/install_host.sh
  By default the host is installed only for the user who runs the script, but if
  you run it with admin privileges (i.e. 'sudo host/install_host.sh'), then the
  host will be installed for all users. You can later use host/uninstall_host.sh
  to uninstall the host.


To start with the extension with the --app-id option
"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe"  --profile-directory=Default --app-id=knldjmfmopnpolahpmmgbagdohdnhkik

"H:\C\CS_LOCAL_CACHE\ThirdParty\Chromium\49.0.2580.0\chrome.exe"  --app-id=knldjmfmopnpolahpmmgbagdohdnhkik
