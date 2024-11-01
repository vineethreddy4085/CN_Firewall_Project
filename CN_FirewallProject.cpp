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


int main()
{
	cout << "hello world";
	return 0;
}