#include "cipher.hpp"
int main() {
    string text, key;
    int shift;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "\n--- Caesar Cipher ---\n";
    cout << "Enter shift: ";
    cin >> shift;
    CaesarCipher caesar(shift);
    string encC = caesar.encrypt(text);
    string decC = caesar.decrypt(encC);
    cout << "Encrypted: " << encC << "\n";
    cout << "Decrypted: " << decC << "\n";

    cin.ignore(); 

    
    cout << "\n--- Vigenere Cipher ---\n";
    cout << "Enter key: ";
    getline(cin, key);
    VigenereCipher vigenere(key);
    string encV = vigenere.encrypt(text);
    string decV = vigenere.decrypt(encV);
    cout << "Encrypted: " << encV << "\n";
    cout << "Decrypted: " << decV << "\n";

    cout << "\n--- Hill Cipher (2x2) ---\n";
    HillCipher hill;
    string encH = hill.encrypt(text);
    string decH = hill.decrypt(encH);
    cout << "Encrypted: " << encH << "\n";
    cout << "Decrypted: " << decH << "\n";

    return 0;
}

