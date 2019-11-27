#include <iostream>
#include <fstream>

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
	//finds primes in the first 100,000 positive natural numbers
	ofstream outputFile;
	outputFile.open("output.dat");
	for (unsigned long long i = 2; i < 100000; i++) {
		if (numIsPrime(i)) {
			outputFile << i << endl;
		}
	}
	return 0;
}
