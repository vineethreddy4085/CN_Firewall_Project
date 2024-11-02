#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/sha.h>

// maintain the order of the below commands. causes issues with byte redefinition
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used parts of Windows headers
#include <windows.h>          // Prevent Windows from defining `min` and `max`
       


using namespace std;

class Auth {
private:
    string username;
    string password;

    string getHiddenPath(const string& filename);
    string hashPassword(const string& password);

public:
    bool authVerify();
    bool authenticate();
};

