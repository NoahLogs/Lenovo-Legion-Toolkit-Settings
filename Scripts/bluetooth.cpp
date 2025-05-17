#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "User32.lib")

HANDLE IsBluetoothEnabled()
{
     // Look for the Bluetooth radio device
     HANDLE handle_bluetooth = NULL;
     BLUETOOTH_FIND_RADIO_PARAMS radio_finder_params = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};
     HBLUETOOTH_RADIO_FIND handle_finder = BluetoothFindFirstRadio(&radio_finder_params, &handle_bluetooth);

     // Validate if a radio device was found
     if (handle_finder == NULL)
     {
          cout << "Bluetooth is disabled." << endl;
          return NULL;
     }

     cout << "Bluetooth is enabled." << endl;
     return handle_bluetooth;
}

bool CheckConnectedBluetoothDevices(HANDLE handle_bluetooth)
{
     // Set the search parameters for Bluetooth devices
     BLUETOOTH_DEVICE_SEARCH_PARAMS search_params = {sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS)};

     search_params.hRadio = handle_bluetooth;
     search_params.fReturnConnected = TRUE;
     search_params.fReturnAuthenticated = FALSE;
     search_params.fReturnRemembered = FALSE;
     search_params.fReturnUnknown = FALSE;
     search_params.fIssueInquiry = FALSE;

     // Retrieve the first connected Bluetooth device
     BLUETOOTH_DEVICE_INFO device_info = {sizeof(BLUETOOTH_DEVICE_INFO)};
     HBLUETOOTH_DEVICE_FIND device_finder = BluetoothFindFirstDevice(&search_params, &device_info);

     // Validate if at least one connected Bluetooth device was found
     BluetoothFindDeviceClose(device_finder);

     if (device_finder == NULL)
     {
          cout << "No connected Bluetooth devices found." << endl;
          return false;
     }

     cout << "Connected Bluetooth device found." << endl;
     return true;
}

void ToogleBluetooth()
{
     // Press and realese Windows key + A key
     INPUT submenu_inputs[4] = {0};

     submenu_inputs[0].type = INPUT_KEYBOARD;
     submenu_inputs[0].ki.wVk = VK_LWIN;

     submenu_inputs[1].type = INPUT_KEYBOARD;
     submenu_inputs[1].ki.wVk = 'A';

     submenu_inputs[2].type = INPUT_KEYBOARD;
     submenu_inputs[2].ki.wVk = 'A';
     submenu_inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

     submenu_inputs[3].type = INPUT_KEYBOARD;
     submenu_inputs[3].ki.wVk = VK_LWIN;
     submenu_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

     SendInput(ARRAYSIZE(submenu_inputs), submenu_inputs, sizeof(INPUT));

     Sleep(1000);

     // Press and realese right arrow key
     INPUT movement_inputs[2] = {0};

     movement_inputs[0].type = INPUT_KEYBOARD;
     movement_inputs[0].ki.wVk = VK_RIGHT;

     movement_inputs[1].type = INPUT_KEYBOARD;
     movement_inputs[1].ki.wVk = VK_RIGHT;
     movement_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     SendInput(ARRAYSIZE(movement_inputs), movement_inputs, sizeof(INPUT));

     // Press and release Enter key
     INPUT enter_inputs[2] = {0};

     enter_inputs[0].type = INPUT_KEYBOARD;
     enter_inputs[0].ki.wVk = VK_RETURN;

     enter_inputs[1].type = INPUT_KEYBOARD;
     enter_inputs[1].ki.wVk = VK_RETURN;
     enter_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     SendInput(ARRAYSIZE(enter_inputs), enter_inputs, sizeof(INPUT));

     Sleep(1000);

     // Press and release Escape key
     INPUT close_submenu_inputs[2] = {0};

     close_submenu_inputs[0].type = INPUT_KEYBOARD;
     close_submenu_inputs[0].ki.wVk = VK_ESCAPE;

     close_submenu_inputs[1].type = INPUT_KEYBOARD;
     close_submenu_inputs[1].ki.wVk = VK_ESCAPE;
     close_submenu_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     SendInput(ARRAYSIZE(close_submenu_inputs), close_submenu_inputs, sizeof(INPUT));
}

int main()
{
     HANDLE handle_bluetooth = IsBluetoothEnabled();

     if (handle_bluetooth == NULL)
     {
          cout << "Exiting program." << endl;
          return 1;
     }

     if (CheckConnectedBluetoothDevices(handle_bluetooth) == false)
     {
          cout << "No connected Bluetooth devices found. Exiting program." << endl;
          ToogleBluetooth();
          return 1;
     };

     CloseHandle(handle_bluetooth);

     Sleep(2000);
}
