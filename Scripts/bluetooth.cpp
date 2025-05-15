#include <windows.h>
#include <bluetoothapis.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "Bthprops.lib")

bool ToogleBluetooth()
{
     // Initialize a generic Windows system handle
     HANDLE hBluetooth;

     // Initialize a struct to hold Bluetooth radio information with its proper size
     BLUETOOTH_FIND_RADIO_PARAMS btfrp = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};

     // Look for the first Bluetooth radio device and store its handle in hBluetooth
     HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hBluetooth);

     // Check if a Bluetooth radio was found
     if (hFind == NULL)
     {
          cout << "No Bluetooth radio found." << endl;
          return false;
     }
     else
     {
          cout << "Bluetooth radio found." << endl;
     }

     return true;
}

int main()
{
     ToogleBluetooth();

     Sleep(2000); // Sleep for 2 seconds
}
