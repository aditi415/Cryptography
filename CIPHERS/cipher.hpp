#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class CaesarCipher {
private:
    int shift;
public:
    CaesarCipher(int s = 3) { shift = s % 26; }
    string encrypt(const string &text);
    string decrypt(const string &text);
};

class VigenereCipher {
private:
    string key;
public:
    VigenereCipher(string k = "KEY") { key = k; }
    string encrypt(const string &text);
    string decrypt(const string &text);
};

class HillCipher {
private:
    vector<vector<int>> key;
public:
    HillCipher(vector<vector<int>> k = {{3,3},{2,5}}) { key = k; }
    string encrypt(const string &text);
    string decrypt(const string &text);
};

#endif
s
