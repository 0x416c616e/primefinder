#include <iostream>
#include <fstream>
#include <climits>
#include <chrono>
#include <ctime>

using namespace std;

//function takes a potentially huge integer and then returns
//whether it's prime or not
bool numIsPrime(unsigned long long argNum){
    for (unsigned long long x = 2; x < argNum; x++) {
        if (argNum % x == 0) {
            return false;
        }
    }
    return true;
}

void aMillionDigits(){
	//put stuff from main here
	//so that later I can have it all loop
}

int main() {

	//this determines how many results to put into one file
	unsigned long long sizeOfFile = 50000;
	//file size stays the same for every run,
	//but ceiling changes based on how many previous runs
	//have been done
    unsigned long long ceiling = sizeOfFile;


	auto startingTime = chrono::system_clock::now();
    time_t startTimeValue = chrono::system_clock::to_time_t(startingTime);
    cout << "Started at: " << ctime(&startTimeValue);
    //check that count.txt file exists
    string countname = "count.txt";
    ifstream countFileExists;
    countFileExists.open(countname);
    bool countExists = countFileExists.good();
    countFileExists.close();

    int leftOffAtInt = -1; //here for scope
    					   //do not use later if -1

    bool fileExists = false;

    string filename = "";
    if (countExists) {
    	//get checkpoint count from count.txt
    	ifstream leftOffCount;
		leftOffCount.open(countname);
		string leftOffAtStr;
		getline(leftOffCount, leftOffAtStr);
		leftOffAtInt = stoi(leftOffAtStr);
		cout << "number of previously completed runs: " << leftOffAtInt << endl;
		leftOffCount.close();

		//check that gaps.csv file exists
	    filename += "gaps_";
	    filename += leftOffAtStr;
	    filename += ".csv";
	    cout << "filename: " << filename << endl;

	    //check if the program has completed at least one 1M CSV file
	    if (leftOffAtInt == 0) {
	    	//append to gaps_0.csv when it has never been made before
	    	ifstream appendFileExists;
			appendFileExists.open(filename);
			fileExists = appendFileExists.good();
			appendFileExists.close();
		//the else block here is for making new files once one has already been completed
	    } else {
	    	//make new csv files, such as for gaps_1.csv, gaps_2.csv, etc.
	    	ifstream myFile;
			myFile.open(filename);
			if (myFile.good()) {
				cout << "can't make new file with filename: " << filename << endl;
			} else {
				cout << "making new file: " << filename << endl;
				ofstream newFile;
				newFile.open(filename);
				newFile << "";
				fileExists = newFile.good();
				newFile.close();

			}
			myFile.close();
	    }
    }

    //proceed if relevant .csv file exists, count file exists, and count stuff was good
    //and if the filename was made successfully
    bool canProceed = fileExists && countExists && (leftOffAtInt != -1) && (filename != "");

    if (canProceed){

        ofstream appendFile;
        appendFile.open(filename.c_str(), ios_base::app);
        cout << "file exists, calculating prime gaps..." << endl;
        unsigned long long old_prime;
        unsigned long long current_prime = 2;
        unsigned long long num = 3;
        unsigned long long gap = 1;

        if (leftOffAtInt > 0) {
        	//TO DO: get last prime from previous CSV and store as current_prime
        	ceiling += (leftOffAtInt * ceiling);
        	num = ceiling - sizeOfFile;
        	ifstream getLastPrime;
        	getLastPrime.open("lastprime.txt");
        	string currentPrimeStr;
        	getline(getLastPrime, currentPrimeStr);
        	cout << "currentPrimeStr: " << currentPrimeStr << endl;
        	current_prime = stoull(currentPrimeStr);
        	getLastPrime.close();
        	cout << "current prime: " << current_prime << endl;
        }

    	cout << "File size: " << sizeOfFile << endl;
    	cout << "num: " << num << endl;
    	cout << "ceiling: " << ceiling << endl;

        //putting prime gaps into a CSV
        cout << "Progress:" << endl;
             //  [========================================]
        cout << "0                   50                   100" << endl;
        cout << "v                   v                    v";
        cout << "\r[";
        cout.flush();

        for (unsigned long long i = num; i < ceiling; i++) {
            if (numIsPrime(i)) {
                old_prime = current_prime;
                current_prime = i;
                gap = current_prime - old_prime;
                //each line contains x,y coordinates to be graphed
                appendFile << gap;
                appendFile << ",";
                appendFile << current_prime << endl;
            }
            if (i % (sizeOfFile/40) == 0) {
            	cout << "=";
            	cout.flush();
			}
        }
        cout << "=]" << endl;
        cout.flush();
        ofstream changeCount;
        changeCount.open("count.txt");
        changeCount << leftOffAtInt + 1;
        changeCount.close();
        ofstream changeLastPrime;
        //lastprime means the last prime from the previous checkpoint
        changeLastPrime.open("lastprime.txt");
        changeLastPrime << current_prime;
        appendFile.close();
        auto endingTime = chrono::system_clock::now();
        time_t endTimeValue = chrono::system_clock::to_time_t(endingTime);
        cout << "Finished at: " << ctime(&endTimeValue);
        cout << "----------------------------------------" << endl;
        //TO-DO: indicate if was completed fully
        //make a text file called run_completed.txt
        //and at the beginning of the program, it will need to
        //check if the last run was completed or not
        //because it could be interrupted before being finished, or
        //the device it's on could be rebooted, or there could be
        //a power outage or something

        //TO-DO:
        //make a separate shell script or cpp program that can just tell if the program wasn't completed in its last run
        //and then fixes it accordingly

        //TO-DO:
        //make the shell script run either a finite number of times if the user passes an argument to it
        //or infinitely if they don't
    } else {
        cout << "error: missing file" << endl;
    }
    return 0;
}
