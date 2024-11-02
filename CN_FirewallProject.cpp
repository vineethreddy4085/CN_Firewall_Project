/*

We are using CPP 20 set to x64.

To get this working download and install openssl from https://slproweb.com/products/Win32OpenSSL.html

then follow these steps
1. Under C/C++ > General, set the Additional Include Directories to include the path to the OpenSSL include folder:
	C:\OpenSSL-Win64\include do it exactly like this

2. Under Linker > General, set the Additional Library Directories to the path of the OpenSSL lib folder
	C:\OpenSSL-Win64\lib

3. Under Linker > Input, in the Additional Dependencies field, add the following
	libssl.lib;libcrypto.lib
*/

#include<iostream>
#include "firewall.h"
#include "auth.h"
using namespace std;

//print screen
void printMenu()
{
	cout << "=======================" << endl;
	cout << "Firewall Menu" << endl;
	cout << "=======================" << endl;
	cout << "1. Add Firewall Rule" << endl;
	cout << "2. Remove Firewall Rule" << endl;
	cout << "3. Clear All Firewall Rules" << endl;
	cout << "4. Print Firewall Rules" << endl;
	cout << "5. Count Firewall Rules" << endl;
	cout << "6. Search Firewall Rule" << endl;
	cout << "7. Block/Allow Traffic" << endl;
	cout << "8. Exit" << endl;
	cout << "=======================" << endl;
	cout << endl;
}

//main
int main()
{
	Firewall F;
	Auth A;
	
	if (!A.authenticate()) {
		return 0;
	}

	int choice;
	do {
		printMenu();
		cout << "Enter your choice (1-8): ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			F.addFirewallRule();
			break;
		case 2:
			F.removeFirewallRule();
			break;
		case 3:
			F.clearFirewallRules();
			break;
		case 4:
			F.printFirewallRules();
			break;
		case 5:
			F.countFirewallRules();
			break;
		case 6:
			F.searchFirewallRules();
			break;
		case 7:
			// Submenu for blocking/allowing traffic
			int submenuChoice;
			do {
				cout << "1. Block All Traffic" << endl;
				cout << "2. Allow All Traffic" << endl;
				cout << "3. Block Traffic by IP Range" << endl;
				cout << "4. Allow Traffic by IP Range" << endl;
				cout << "5. Block Traffic by Protocol" << endl;
				cout << "6. Allow Traffic by Protocol" << endl;
				cout << "7. Block Traffic by Port" << endl;
				cout << "8. Allow Traffic by Port" << endl;
				cout << "9. Go Back to Main Menu" << endl;
				cout << "Enter your choice (1-9): ";
				cin >> submenuChoice;
				cout << endl;

				switch (submenuChoice) {
				case 1:
					F.blockAllTraffic();
					break;
				case 2:
					F.allowAllTraffic();
					break;
				case 3:
					F.blockAllTrafficFromRange();
					break;
				case 4:
					F.allowAllTrafficFromRange();
					break;
				case 5:
					F.blockAllTrafficbyProtocol();
					break;
				case 6:
					F.allowAllTrafficbyProtocol();
					break;
				case 7:
					F.blockAllTrafficbyPort();
					break;
				case 8:
					F.allowAllTrafficbyPort();
					break;
				case 9:
					break;  // Go back to the main menu
				default:
					cout << "Invalid choice. Please try again." << endl;
					break;
				}
				cout << endl;
			} while (submenuChoice != 9);
			break;
		case 8:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
		cout << endl;
	} while (choice != 8);

	return 0;
}