#include <iostream>

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
	//finds primes in the first 10,000 positive natural numbers
	for (unsigned long long i = 3; i < 10000; i++) {
		if (numIsPrime(i)) {
			cout << i << " is prime" << endl;
		}
	}
	return 0;
}
