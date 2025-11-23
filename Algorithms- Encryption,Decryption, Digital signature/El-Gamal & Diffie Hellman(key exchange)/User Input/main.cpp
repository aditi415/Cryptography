#include "eldh.hpp"

int main() {
    ElGamalDH elgdh;
    int choice;
    cout << "1. Diffie-Hellman Key Exchange" << endl;
    cout << "2. ElGamal Encryption & Decryption" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        elgdh.diffieHellman();
    else if (choice == 2)
        elgdh.elGamal();
    else
        cout << "Invalid choice!" << endl;

    return 0;
}
