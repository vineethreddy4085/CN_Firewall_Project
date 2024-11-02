#include "Auth.h"


bool Auth::authVerify() {
    string enteredUsername, enteredPassword;
    cout << "Username: ";
    cin >> enteredUsername;
    cout << "Password: ";
    cin >> enteredPassword;
    while (cin.get() != '\n');  // Ignore the remaining newline character

    if (enteredUsername != username || enteredPassword != password) {
        cout << "Authentication failed. Exiting..." << endl;
        return false;
    }
    return true;
}

bool Auth::authenticate() {
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

string Auth::getHiddenPath(const string& filename) {
    string hiddenPath = "." + filename;
    return hiddenPath;
}

string Auth::hashPassword(const string& password) {
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
