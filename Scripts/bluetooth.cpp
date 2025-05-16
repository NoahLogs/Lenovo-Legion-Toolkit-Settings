#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "Bthprops.lib")

// Function to check if Bluetooth is enabled and return both the status and handle
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
     searchParams.fReturnAuthenticated = TRUE;
     searchParams.fReturnRemembered = FALSE;
     searchParams.fReturnUnknown = FALSE;
     searchParams.fIssueInquiry = FALSE;

     // Retrieve the first connected Bluetooth device
     BLUETOOTH_DEVICE_INFO deviceInfo = {sizeof(BLUETOOTH_DEVICE_INFO)};
     HBLUETOOTH_DEVICE_FIND hDeviceFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);

     BluetoothFindDeviceClose(hDeviceFind);

     if (hDeviceFind == NULL)
     {
          cout << "No connected Bluetooth devices found." << endl;
          return false;
     }

     cout << "Connected Bluetooth device found" << endl;
     return true;
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

     if (CheckConnectedBluetoothDevices(hBluetooth))
     {
          cout << "Connected Bluetooth devices found." << endl;
     }
     else
     {
          cout << "No connected Bluetooth devices found." << endl;
     }

     CloseHandle(hBluetooth);

     Sleep(2000); // Sleep for 2 seconds
}
