#include "ciphers.hpp"
using namespace std;


void Cipher::caesar() {
    string text;
    int key;
    cout << "\nEnter text for Caesar Cipher: ";
    getline(cin, text);
    cout << "Enter key: ";
    cin >> key;
    cin.ignore();

    string enc = caesarEncrypt(text, key);
    string dec = caesarDecrypt(enc, key);

    cout << "Encrypted: " << enc << endl;
    cout << "Decrypted: " << dec << endl;
}

string Cipher::caesarEncrypt(string text, int key) {
    for (char &ch : text) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = (ch - base + key) % 26 + base;
        }
    }
    return text;
}

string Cipher::caesarDecrypt(string text, int key) {
    return caesarEncrypt(text, 26 - key);
}


void Cipher::vigenere() {
    string text, key;
    cout << "\nEnter text for Vigenere Cipher: ";
    getline(cin, text);
    cout << "Enter key (letters only): ";
    getline(cin, key);

    string enc = vigenereEncrypt(text, key);
    string dec = vigenereDecrypt(enc, key);

    cout << "Encrypted: " << enc << endl;
    cout << "Decrypted: " << dec << endl;
}

string Cipher::vigenereEncrypt(string text, string key) {
    string result;
    for (int i = 0; i < text.size(); i++) {
        char text_num = text[i];
        char key_num = key[i % 26];
        if (isalpha(text_num)) {
            //char keyletter = isupper(text_num) ? 'A' : 'a';
            result += ((text_num + key_num)) % 26;
        } else result += text_num;
    }
    return result;
}

string Cipher::vigenereDecrypt(string text, string key) {
    string result;
    for (int i = 0; i < text.size(); i++) {
        char text_num = text[i];
        char key_num = key[i % 26];
        if (isalpha(text_num)) {
            //char keyletter = isupper(text_num) ? 'A' : 'a';
            result += ((text_num - key_num) + 26) % 26;
        } else result += text_num;
    }
    return result;
}

void Cipher::hill() {
    string text;
    cout << "\nEnter text for Hill Cipher (in uppercase, multiple of 2): ";
    getline(cin, text);

    vector<vector<int>> key = {{3, 3}, {2, 5}}; 
    string enc = hillEncrypt(text, key);
    string dec = hillDecrypt(enc, key);

    cout << "Encrypted: " << enc << endl;
    cout << "Decrypted: " << dec << endl;
}

string Cipher::hillEncrypt(string text, vector<vector<int>> key) {
    string result;
    for (int i = 0; i < text.size(); i += 2) {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int x = (key[0][0]*a + key[0][1]*b) % 26;
        int y = (key[1][0]*a + key[1][1]*b) % 26;
        result += char(x + 'A');
        result += char(y + 'A');
    }
    return result;
}

int Cipher::modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

string Cipher::hillDecrypt(string text, vector<vector<int>> key) {
    int det = (key[0][0]*key[1][1] - key[0][1]*key[1][0]) % 26;
    if (det < 0) det += 26;
    int invDet = modInverse(det, 26);

    vector<vector<int>> inv(2, vector<int>(2));
    inv[0][0] = key[1][1];
    inv[1][1] = key[0][0];
    inv[0][1] = -key[0][1];
    inv[1][0] = -key[1][0];

    
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv[i][j] = (invDet * ((inv[i][j] % 26 + 26) % 26)) % 26;

    string result;
    for (int i = 0; i < text.size(); i += 2) {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int x = (inv[0][0]*a + inv[0][1]*b) % 26;
        int y = (inv[1][0]*a + inv[1][1]*b) % 26;
        result += char(x + 'A');
        result += char(y + 'A');
    }
    return result;
}

