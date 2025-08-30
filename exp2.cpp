#include <bits/stdc++.h>
using namespace std;

// Remove duplicates and create Playfair key table
vector<vector<char>> generateMatrix(string key) {
    string filtered = "";
    bool seen[26] = {false};

    // Replace J with I
    for (char &ch : key) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !seen[ch - 'A']) {
            filtered += ch;
            seen[ch - 'A'] = true;
        }
    }

    // Add remaining alphabets
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // skip J
        if (!seen[ch - 'A']) {
            filtered += ch;
            seen[ch - 'A'] = true;
        }
    }

    // Fill 5x5 matrix
    vector<vector<char>> matrix(5, vector<char>(5));
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = filtered[k++];
        }
    }
    return matrix;
}

// Find position of a character in matrix
pair<int, int> findPosition(vector<vector<char>> &matrix, char ch) {
    if (ch == 'J') ch = 'I'; // treat J as I
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) return {i, j};
        }
    }
    return {-1, -1};
}

// Prepare plaintext into digraphs with "X" inserted for repeats
string preparePlaintext(string plaintext) {
    string prepared = "";
    for (char &ch : plaintext) {
        if (isalpha(ch)) prepared += toupper(ch);
    }

    string result = "";
    for (int i = 0; i < prepared.size(); i++) {
        result += prepared[i];
        if (i + 1 < prepared.size() && prepared[i] == prepared[i + 1]) {
            result += 'X'; // insert X after first repeating char
        }
    }

    if (result.size() % 2 != 0) result += 'X'; // pad if odd length
    return result;
}

// Encrypt using Playfair rules
string encrypt(string plaintext, vector<vector<char>> &matrix) {
    string cipher = "";
    for (int i = 0; i < plaintext.size(); i += 2) {
        auto p1 = findPosition(matrix, plaintext[i]);
        auto p2 = findPosition(matrix, plaintext[i + 1]);

        if (p1.first == p2.first) {
            // Same row → shift right
            cipher += matrix[p1.first][(p1.second + 1) % 5];
            cipher += matrix[p2.first][(p2.second + 1) % 5];
        } 
        else if (p1.second == p2.second) {
            // Same column → shift down
            cipher += matrix[(p1.first + 1) % 5][p1.second];
            cipher += matrix[(p2.first + 1) % 5][p2.second];
        } 
        else {
            // Rectangle rule → swap columns
            cipher += matrix[p1.first][p2.second];
            cipher += matrix[p2.first][p1.second];
        }
    }
    return cipher;
}

int main() {
    string plaintext, key;

    cout << "Enter the key: ";
    getline(cin, key);

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    auto matrix = generateMatrix(key);

    cout << "\nPlayfair Matrix:\n";
    for (auto &row : matrix) {
        for (auto &ch : row) cout << ch << " ";
        cout << endl;
    }

    string prepared = preparePlaintext(plaintext);
    string cipher = encrypt(prepared, matrix);

    cout << "\nPrepared Plaintext: " << prepared;
    cout << "\nCipher Text: " << cipher << endl;

    return 0;
}
