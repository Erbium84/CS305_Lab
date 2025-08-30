#include <bits/stdc++.h>
using namespace std;

string encrypt(const string &pt, int key) {
    string ct = pt;
    for (int i = 0; i < pt.size(); i++) {
        if (pt[i] >= 'a' && pt[i] <= 'z')
            ct[i] = 'a' + ((pt[i] - 'a' + key) % 26);
        else if (pt[i] >= 'A' && pt[i] <= 'Z')
            ct[i] = 'A' + ((pt[i] - 'A' + key) % 26);
        else
            ct[i] = pt[i]; // non-alphabetic stays same
    }
    return ct;
}

string decrypt(const string &ct, int key) {
    string pt = ct;
    for (int i = 0; i < ct.size(); i++) {
        if (ct[i] >= 'a' && ct[i] <= 'z')
            pt[i] = 'a' + ((ct[i] - 'a' - key + 26) % 26);
        else if (ct[i] >= 'A' && ct[i] <= 'Z')
            pt[i] = 'A' + ((ct[i] - 'A' - key + 26) % 26);
        else
            pt[i] = ct[i]; 
    }
    return pt;
}

int main() {
    int key;
    string plaintext;

    cout << "Enter Caesar key: ";
    cin >> key;
    cin.ignore(); // clear buffer after reading int

    cout << "Enter message: ";
    getline(cin, plaintext);

    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted message: " << ciphertext << endl;

    string decryptedtext = decrypt(ciphertext, key);
    cout << "Decrypted message: " << decryptedtext << endl;

    return 0;
}