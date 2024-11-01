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

}

void addFirewallRule(vector<FirewallRule>& firewallRules)
{

}

void removeFirewallRule(vector<FirewallRule>& firewallRules)
{

}

void clearFirewallRules(vector<FirewallRule>& firewallRules)
{

}

void printFirewallRules(const vector<FirewallRule>& firewallRules)
{

}

void countFirewallRules(const vector<FirewallRule>& firewallRules)
{

}

void searchFirewallRules(const vector<FirewallRule>& firewallRules)
{

}

//Traffic operations


int main()
{
	cout << "hello world";
	return 0;
}