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

int main()
{
     HANDLE hBluetooth = IsBluetoothEnabled();

     // Finish program if Bluetooth is not enabled
     if (hBluetooth == NULL)
     {
          cout << "Exiting program." << endl;
          return 1;
     }
     else
     {
          cout << "Bluetooth is enabled." << endl;
     }

     Sleep(2000); // Sleep for 2 seconds
}
