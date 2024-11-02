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
#include <iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<openssl\evp.h>
#include<openssl\sha.h>
#include<sstream>
#include<limits>
#include<Windows.h>
#include <ios>
using namespace std;

//Firewall rule creation according to IP Address
struct FirewallRule
{
	string ipAddress;
	bool allow;
};

//FIrewall operations
bool isPacketAlowed(const string& ipAddress, const vector<FirewallRule>& firewallRules)
{
	for (const auto& rule : firewallRules)
	{
		if (rule.ipAddress == ipAddress)
			return rule.allow;
	}
	return false;
}

void addFirewallRule(vector<FirewallRule>& firewallRules)
{
	string ipAddress;
	char choice;

	cout << "Enter IP Address: ";
	cin >> ipAddress;

	cout << "Allow or Block (a or b): ";
	cin >> choice;

	bool allow = (choice == 'a' || choice == 'A');
	firewallRules.push_back({ ipAddress,allow });

	cout << "Firewall rule added successfully. \n";
}

void removeFirewallRule(vector<FirewallRule>& firewallRules)
{
	string ipAddress;

	cout << "Enter IP address to remove: ";
	cin >> ipAddress;

	for (auto it = firewallRules.begin(); it != firewallRules.end(); ++it) {
		if (it->ipAddress == ipAddress) {
			firewallRules.erase(it);
			cout << "Firewall rule removed successfully." << endl;
			return;
		}
	}

	cout << "Firewall rule not found for the given IP address." << endl;
}

void clearFirewallRules(vector<FirewallRule>& firewallRules)
{
	firewallRules.clear();
	cout << "All firewall rules cleared." << endl;
}

void printFirewallRules(const vector<FirewallRule>& firewallRules)
{
	cout << "Firewall Rules:" << endl;
	for (const auto& rule : firewallRules) {
		string action = rule.allow ? "Allow" : "Block";
		cout << "IP: " << rule.ipAddress << "  Action: " << action << endl;
	}
}

void countFirewallRules(const vector<FirewallRule>& firewallRules)
{
	cout << "Total firewall rules: " << firewallRules.size() << endl;

}

void searchFirewallRules(const vector<FirewallRule>& firewallRules)
{
	string ipAddress;

	cout << "Enter IP address to search: ";
	cin >> ipAddress;

	for (const auto& rule : firewallRules) {
		if (rule.ipAddress == ipAddress) {
			string action = rule.allow ? "Allow" : "Block";
			cout << "Firewall rule found for IP: " << rule.ipAddress << "  Action: " << action << endl;
			return;
		}
	}

	cout << "No firewall rule found for the given IP address." << endl;

}

//Traffic operations
void blockAllTraffic(vector<FirewallRule>& firewallRules)
{
	firewallRules.clear();
	firewallRules.push_back({ "0.0.0.0", false });
	cout << "All traffic blocked. Firewall rules updated." << endl;

}

void allowAllTraffic(vector<FirewallRule>& firewallRules)
{
	firewallRules.clear();
	firewallRules.push_back({ "0.0.0.0", true });
	cout << "All traffic allowed. Firewall rules updated." << endl;

}

//range based operations
void blockAllTrafficFromRange(vector<FirewallRule>& firewallRules)
{
	string startIp, endIp;

	cout << "Enter starting IP address: ";
	cin >> startIp;

	cout << "Enter ending IP address: ";
	cin >> endIp;

	firewallRules.push_back({ startIp, false });
	firewallRules.push_back({ endIp, false });

	cout << "Blocked traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << endl;

}

void allowAllTrafficFromRange(vector<FirewallRule>& firewallRules)
{
	string startIp, endIp;

	cout << "Enter starting IP address: ";
	cin >> startIp;

	cout << "Enter ending IP address: ";
	cin >> endIp;

	firewallRules.push_back({ startIp, true });
	firewallRules.push_back({ endIp, true });

	cout << "Allowed traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << endl;

}

//protocol based operations
void blockAllTrafficbyProtocol(vector<FirewallRule>& firewallRules)
{
	string protocol;

	cout << "Enter protocol to block: ";
	cin >> protocol;

	firewallRules.push_back({ protocol, false });

	cout << "Blocked traffic for protocol " << protocol << ". Firewall rules updated." << endl;

}

void allowAllTrafficbyProtocol(vector<FirewallRule>& firewallRules)
{
	string protocol;

	cout << "Enter protocol to allow: ";
	cin >> protocol;

	firewallRules.push_back({ protocol, true });

	cout << "Allowed traffic for protocol " << protocol << ". Firewall rules updated." << endl;

}

//port based operations
void blockAllTrafficbyPort(vector<FirewallRule>& firewallRules)
{
	string port;

	cout << "Enter port to block: ";
	cin >> port;

	firewallRules.push_back({ port, false });

	cout << "Blocked traffic for port " << port << ". Firewall rules updated." << endl;

}

void allowAllTrafficbyPort(vector<FirewallRule>& firewallRules)
{
	string port;

	cout << "Enter port to allow: ";
	cin >> port;

	firewallRules.push_back({ port, true });

	cout << "Allowed traffic for port " << port << ". Firewall rules updated." << endl;

}

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

//hashing using SHA 256
string hashPassword(const string& password)
{
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hashLength;

	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	const EVP_MD* md = EVP_sha256();

	EVP_DigestInit_ex(mdctx, md, nullptr);
	EVP_DigestUpdate(mdctx, password.c_str(), password.length());
	EVP_DigestFinal_ex(mdctx, hash, &hashLength);
	EVP_MD_CTX_free(mdctx);

	stringstream ss;
	for (unsigned int i = 0; i < hashLength; ++i) {
		ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
	}
	return ss.str();

}

//hidden path
string getHiddenPath(const string& filename)
{
	string hiddenPath = "." + filename; 
	return hiddenPath;
}

//authentication
bool authenticate(string& username, string& password)
{
	ifstream credentialsFile(getHiddenPath("credentials.txt"));
	if (credentialsFile.is_open()) {
		getline(credentialsFile, username);
		string encryptedPassword;
		getline(credentialsFile, encryptedPassword);
		credentialsFile.close();

		string inputPassword;
		cout << "Enter your password: ";
		getline(cin, inputPassword);

		if (hashPassword(inputPassword) == encryptedPassword) {
			return true;
		}
		else {
			cout << "Invalid password. Authentication failed." << endl;
			return false;
		}
	}
	else {
		ofstream newCredentialsFile(getHiddenPath("credentials.txt"));
		if (newCredentialsFile.is_open()) {
			cout << "Welcome! Let's set up your firewall credentials." << endl;
			cout << "Enter a username: ";
			getline(cin, username);
			string inputPassword;
			cout << "Enter a password: ";
			getline(cin, inputPassword);
			string encryptedPassword = hashPassword(inputPassword);
			newCredentialsFile << username << "\n" << encryptedPassword << endl;
			newCredentialsFile.close();

			// Hide the credentials file
			DWORD attributes = GetFileAttributesA(getHiddenPath("credentials.txt").c_str());
			SetFileAttributesA(getHiddenPath("credentials.txt").c_str(), attributes | FILE_ATTRIBUTE_HIDDEN);

			cout << "Credentials set successfully. Please restart the firewall." << endl;
		}
		else {
			cout << "Failed to create credentials file. Exiting..." << endl;
		}
		return false;
	}
}
bool authenticate(const string& username,const string& password)
{
	string enteredUsername, enteredPassword;
	cout << "Username: ";
	cin>>enteredUsername;
	cout << "Password: ";
	cin>>enteredPassword;
	while (cin.get() != '\n'); // Ignore the remaining newline character

	if (enteredUsername != username || enteredPassword != password) {
		cout << "Authentication failed. Exiting..." << endl;
		return false;
	}
	return true;
}

//main
int main()
{
	vector<FirewallRule> firewallRules;

	string username, password;
	if (!authenticate(username, password)) {
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
			addFirewallRule(firewallRules);
			break;
		case 2:
			removeFirewallRule(firewallRules);
			break;
		case 3:
			clearFirewallRules(firewallRules);
			break;
		case 4:
			printFirewallRules(firewallRules);
			break;
		case 5:
			countFirewallRules(firewallRules);
			break;
		case 6:
			searchFirewallRules(firewallRules);
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
					blockAllTraffic(firewallRules);
					break;
				case 2:
					allowAllTraffic(firewallRules);
					break;
				case 3:
					blockAllTrafficFromRange(firewallRules);
					break;
				case 4:
					allowAllTrafficFromRange(firewallRules);
					break;
				case 5:
					blockAllTrafficbyProtocol(firewallRules);
					break;
				case 6:
					allowAllTrafficbyProtocol(firewallRules);
					break;
				case 7:
					blockAllTrafficbyPort(firewallRules);
					break;
				case 8:
					allowAllTrafficbyPort(firewallRules);
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