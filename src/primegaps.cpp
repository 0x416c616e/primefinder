#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
bool numIsPrime(unsigned long long argNum){
    for (unsigned long long x = 2; x < argNum; x++) {
        if (argNum % x == 0) {
            return false;
        }
    }
    return true;
}
int main() {
    string filename = "gaps.csv";
    ifstream appendFileExists;
    appendFileExists.open(filename);
    bool fileExists = appendFileExists.good();
    appendFileExists.close();
    if (fileExists){
        ofstream appendFile;
        appendFile.open(filename, ios_base::app);
        cout << "file exists, appending prime gaps..." << endl;
        unsigned long long old_prime;
        unsigned long long current_prime = 2;
        unsigned long long num = 3;
        unsigned long long gap = 1;
        for (unsigned long long i = num; i < 1000000; i++) {
            if (numIsPrime(i)) {
                old_prime = current_prime;
                current_prime = i;
                gap = current_prime - old_prime;
                appendFile << gap;
                appendFile << ",";
            }
        }
        appendFile.close();
    } else {
        cout << "file doesn't exist" << endl;
    }
    return 0;
}
