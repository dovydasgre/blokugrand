#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main () {
    string filename = "25k1000.txt";
    ofstream rf (filename);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int numSymbols = 1000;
    for (int x=0;x<25000;x++){
        for (int j = 0; j < 2; j++){
            for (int i = 0; i < numSymbols; ++i) {
                // Generate a random integer between 32 and 126 (ASCII values for printable characters)
                int randomInt = std::rand() % 95 + 32;

                // Convert the random integer to a character and print it
                char randomSymbol = static_cast<char>(randomInt);
                rf << randomSymbol;
            }
            rf << " ";
        }
        rf << endl;
    }
}