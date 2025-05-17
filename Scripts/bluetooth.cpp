#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "User32.lib")

HANDLE IsBluetoothEnabled()
{
     // Initialize a generic Windows system handle
     HANDLE hBluetooth = NULL;

     // Initialize a struct to hold Bluetooth radio information with its proper size
     BLUETOOTH_FIND_RADIO_PARAMS btfrp = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};

     // Look for the first Bluetooth radio device and store its handle in hBluetooth
     HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hBluetooth);

     // Check if a Bluetooth radio was found
     if (hFind == NULL)
     {
          cout << "Bluetooth is disabled." << endl;
          return NULL;
     }

     cout << "Bluetooth is enabled." << endl;
     return hBluetooth;
}

bool CheckConnectedBluetoothDevices(HANDLE hBluetooth)
{
     // Initialize a struct to hold Bluetooth device search parameters with its proper size
     BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = {sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS)};

     // Set the search parameters for Bluetooth devices, including what status devices to return
     searchParams.hRadio = hBluetooth;
     searchParams.fReturnConnected = TRUE;
     searchParams.fReturnAuthenticated = FALSE;
     searchParams.fReturnRemembered = FALSE;
     searchParams.fReturnUnknown = FALSE;
     searchParams.fIssueInquiry = FALSE;

     // Retrieve the first connected Bluetooth device
     BLUETOOTH_DEVICE_INFO deviceInfo = {sizeof(BLUETOOTH_DEVICE_INFO)};
     HBLUETOOTH_DEVICE_FIND hDeviceFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);

     // Validate if at least one connected Bluetooth device was found
     BluetoothFindDeviceClose(hDeviceFind);
     if (hDeviceFind == NULL)
     {
          cout << "No connected Bluetooth devices found." << endl;
          return false;
     }

     cout << "Connected Bluetooth device found." << endl;
     return true;
}

void ToogleBluetooth()
{
     INPUT submenu_inputs[4] = {0};

     // Press Windows key
     submenu_inputs[0].type = INPUT_KEYBOARD;
     submenu_inputs[0].ki.wVk = VK_LWIN;

     // Press A key
     submenu_inputs[1].type = INPUT_KEYBOARD;
     submenu_inputs[1].ki.wVk = 'A';

     // Release A key
     submenu_inputs[2].type = INPUT_KEYBOARD;
     submenu_inputs[2].ki.wVk = 'A';
     submenu_inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

     // Release Windows key
     submenu_inputs[3].type = INPUT_KEYBOARD;
     submenu_inputs[3].ki.wVk = VK_LWIN;
     submenu_inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

     // Send the inputs
     SendInput(ARRAYSIZE(submenu_inputs), submenu_inputs, sizeof(INPUT));

     Sleep(1000);

     INPUT movement_inputs[2] = {0};

     // Press left arrow key
     movement_inputs[0].type = INPUT_KEYBOARD;
     movement_inputs[0].ki.wVk = VK_RIGHT;

     // Release left arrow key
     movement_inputs[1].type = INPUT_KEYBOARD;
     movement_inputs[1].ki.wVk = VK_RIGHT;
     movement_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     SendInput(ARRAYSIZE(movement_inputs), movement_inputs, sizeof(INPUT));

     INPUT enter_inputs[2] = {0};

     // Press Enter key
     enter_inputs[0].type = INPUT_KEYBOARD;
     enter_inputs[0].ki.wVk = VK_RETURN;

     // Release Enter key
     enter_inputs[1].type = INPUT_KEYBOARD;
     enter_inputs[1].ki.wVk = VK_RETURN;
     enter_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     // Send the inputs
     SendInput(ARRAYSIZE(enter_inputs), enter_inputs, sizeof(INPUT));

     Sleep(1000);

     INPUT close_submenu_inputs[2] = {0};

     // Press Escape key
     close_submenu_inputs[0].type = INPUT_KEYBOARD;
     close_submenu_inputs[0].ki.wVk = VK_ESCAPE;

     // Release Escape key
     close_submenu_inputs[1].type = INPUT_KEYBOARD;
     close_submenu_inputs[1].ki.wVk = VK_ESCAPE;
     close_submenu_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

     // Send the inputs
     SendInput(ARRAYSIZE(close_submenu_inputs), close_submenu_inputs, sizeof(INPUT));
}

int main()
{
     HANDLE hBluetooth = IsBluetoothEnabled();

     // Finish program if Bluetooth is not enabled
     if (hBluetooth == NULL)
     {
          cout << "Exiting program." << endl;
          return 1;
     }

     if (CheckConnectedBluetoothDevices(hBluetooth) == false)
     {
          cout << "No connected Bluetooth devices found. Exiting program." << endl;
          ToogleBluetooth();
          return 1;
     };

     CloseHandle(hBluetooth);

     Sleep(2000);
}
