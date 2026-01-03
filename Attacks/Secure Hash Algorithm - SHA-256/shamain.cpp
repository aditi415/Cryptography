#include <iostream>
#include <iomanip>
#include "sha256.hpp"

using namespace std;  

int main() {
    string msg;
    cout << "Enter a message: ";
    getline(cin, msg);

    SHA256 sha;
    sha.update(msg);

    vector<uint8_t> hash = sha.digest();

    cout << "\nSHA-256 Hash:\n";
    cout << SHA256::toHex(hash) << "\n";

    return 0;
}

