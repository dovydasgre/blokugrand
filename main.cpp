#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

using namespace std;

// SHA-256 initial hash values (H0-H7)
const uint32_t SHA256_INITIAL_HASH[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

void readFile(string input) {
    string pav, hash;
    cout << "Parasykite failo pavadinima (be .txt galunes):" << endl;
    cin >> pav;
    ifstream rf("./tests/"+pav+".txt");
    stringstream my_buffer;
    my_buffer.clear();
    if (rf.is_open()) {
        my_buffer << rf.rdbuf();
        input = my_buffer.str();
        rf.close();
    } else {
        cout << "Nepavyko atidaryti failo." << endl;
        exit;
    }
}

// SHA-256 mixing function
uint32_t sha256Mix(uint32_t a, uint32_t b, uint32_t c) {
    uint32_t temp1 = b >> 6 | b << (32 - 6);
    uint32_t temp2 = b >> 11 | b << (32 - 11);
    uint32_t temp3 = b >> 25 | b << (32 - 25);
    uint32_t s1 = temp3 ^ temp2 ^ b;

    temp1 = a >> 2 | a << (32 - 2);
    temp2 = a >> 13 | a << (32 - 13);
    temp3 = a >> 22 | a << (32 - 22);
    uint32_t s0 = temp3 ^ temp2 ^ temp1;

    return a + s0 + b + s1 + c;
}

// Simple hash function that returns a 256-bit (64 hex characters) hash
std::string customHash(const std::string& input) {
    uint32_t hash[8];

    // Initialize the hash with SHA-256 initial hash values
    std::memcpy(hash, SHA256_INITIAL_HASH, sizeof(SHA256_INITIAL_HASH));

    for (char c : input) {
        // Perform mixing operations using the sha256Mix function for demonstration
        for (int i = 0; i < 8; ++i) {
            hash[i] = sha256Mix(hash[i], hash[(i + 1) % 8], static_cast<uint32_t>(c));
        }
    }

    char result[65];
    snprintf(result, sizeof(result),
             "%08x%08x%08x%08x%08x%08x%08x%08x",
             hash[0], hash[1], hash[2], hash[3],
             hash[4], hash[5], hash[6], hash[7]);

    return result;
}

int main () {
    bool choice;
    string input, hash;
    cout << "Skaityti faila (1), ivesti (0): ";	cin >> choice;
    if (choice) {
        readFile(input);
    } else {
        getline(cin >> ws, input);
    }
    hash = customHash(input);
    cout << hash << endl;
}