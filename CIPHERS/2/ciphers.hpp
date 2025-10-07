#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <iostream>
#include <string>
#include <vector>

class Cipher {
public:
    void caesar();
    void vigenere();
    void hill();

private:
  
    std::string caesarEncrypt(std::string text, int key);
    std::string caesarDecrypt(std::string text, int key);

  
    std::string vigenereEncrypt(std::string text, std::string key);
    std::string vigenereDecrypt(std::string text, std::string key);

  
    std::string hillEncrypt(std::string text, std::vector<std::vector<int>> key);
    std::string hillDecrypt(std::string text, std::vector<std::vector<int>> key);
    int modInverse(int a, int m);
};

#endif

