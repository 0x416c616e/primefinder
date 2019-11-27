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
		cout << "Number of previously completed runs: " << leftOffAtInt << endl;
		leftOffCount.close();

		//check that gaps.dat file exists
	    filename += "gaps_";
	    filename += leftOffAtStr;
	    filename += ".dat";
	    cout << "Filename: " << filename << endl;

	    //note: used to be .csv, but changed to .dat for the sake of gnuplot
	    //check if the program has completed at least one 50k .DAT file
	    if (leftOffAtInt == 0) {
	    	//append to gaps_0.dat when it has never been made before
	    	ifstream appendFileExists;
			appendFileExists.open(filename);
			fileExists = appendFileExists.good();
			appendFileExists.close();
		//the else block here is for making new files once one has already been completed
	    } else {
	    	//make new .dat files, such as for gaps_1.dat, gaps_2.dat, etc.
	    	ifstream myFile;
			myFile.open(filename);
			if (myFile.good()) {
				cout << "Can't make new file with filename: " << filename << endl;
			} else {
				cout << "Making new file: " << filename << endl;
				ofstream newFile;
				newFile.open(filename);
				newFile << "";
				fileExists = newFile.good();
				newFile.close();
			}
			myFile.close();
	    }
    }

    //proceed if relevant .dat file exists, count file exists, and count stuff was good
    //and if the filename was made successfully
    bool canProceed = fileExists && countExists && (leftOffAtInt != -1) && (filename != "");
    //the above has an issue if you start a run but don't finish it
    //the values will be 0, 1, 1, 1 for the booleans in that order

    //this handles if the user used the run_continuously.sh script
    //but then quit the program in the middle of a run
    if (!fileExists) {
        ifstream checkIfCompleted; //check if the last run was completed
        checkIfCompleted.open("last_was_completed.txt");
    	string completedStr;
    	getline(checkIfCompleted, completedStr);
    	checkIfCompleted.close();

    	//what to do if the program was interrupted during the last run
    	if (completedStr == "false") {
    		canProceed = true;
			ofstream newFile2;
			newFile2.open(filename);
			newFile2 << "";
			fileExists = newFile2.good();
			newFile2.close();
			cout << "The last run was interrupted." << endl;
			cout << "Program is now taking measures to resume from" << endl;
			cout << "the last good checkpoint." << endl;
    	} else {
    		cout << "something went wrong" << endl;
    		return 1;
    	}
    }

    //======================================



    //======================================

    if (canProceed){

        ofstream appendFile;
        appendFile.open(filename.c_str(), ios_base::app);
        cout << "Everything is fine" << endl;
        cout << "Calculating prime gaps..." << endl;
        unsigned long long old_prime;
        unsigned long long current_prime = 2;
        unsigned long long num = 3;
        unsigned long long gap = 1;

        if (leftOffAtInt > 0) {
        	ceiling += (leftOffAtInt * ceiling);
        	num = ceiling - sizeOfFile;
        	ifstream getLastPrime;
        	getLastPrime.open("lastprime.txt");
        	string currentPrimeStr;
        	getline(getLastPrime, currentPrimeStr);
        	current_prime = stoull(currentPrimeStr);
        	getLastPrime.close();
        	cout << "Biggest prime from previous run: " << current_prime << endl;
        }

    	cout << "File size: " << sizeOfFile << endl;
    	cout << "Num: " << num << endl;
    	cout << "Ceiling: " << ceiling << endl;



        //setting last_was_completed.txt to false
		ofstream changeRunStatus;
		changeRunStatus.open("last_was_completed.txt");
		changeRunStatus << "false";
		changeRunStatus.close();
        cout << "Current run in progress..." << endl;

    	//has an ASCII loading bar that moves to indicate progress
        cout << "Progress:" << endl;
             //  [========================================]
        cout << "0                   50                   100" << endl;
        cout << "v                   v                    v";
        cout << "\r[";
        cout.flush();

        //putting prime gaps into a .dat
		//main prime gap loop
        for (unsigned long long i = num; i < ceiling; i++) {
        	//EDGE CASE for 2 because 2 is the 1st prime
        	//meaning it doesn't have a previous prime
        	//to compare it to, so a prime gap is not possible
        	//in this case, I am just putting 0 as the prime gap
        	//because there is no previous value
        	if (i == 3) {
        		appendFile << 2;
        		appendFile << ",";
        		appendFile << 0 << endl;
        	}
            if (numIsPrime(i)) {
                old_prime = current_prime;
                current_prime = i;
                gap = current_prime - old_prime;
                //each line contains x,y coordinates to be graphed
                appendFile << current_prime;
                appendFile << ",";
                appendFile << gap << endl;
            }
            //moving the loading bar along
            //to denote progress with the current run/batch
            if (i % (sizeOfFile/40) == 0) {
            	cout << "=";
            	cout.flush();
			}
        }
        //closing the loading bar
        cout << "=]" << endl;
        cout.flush();
        //updating the text files that have status info
        //this is the "checkpoint" functionality
        //so the program can be run, quit abruptly, run again
        //so instead of starting from scratch, you can always
        //resume where you left off later
        //but instead of writing every single single change, it's only once every 50k
        //to reduce disk wear

        //update count.txt
        ofstream changeCount;
        changeCount.open("count.txt");
        changeCount << leftOffAtInt + 1;
        changeCount.close();

        //update lastprime.txt
        ofstream changeLastPrime;
        //lastprime means the last prime from the previous checkpoint
        changeLastPrime.open("lastprime.txt");
        changeLastPrime << current_prime;
        appendFile.close();

        //update last_was_completed.txt
        ofstream changeCompleted;
        changeCompleted.open("last_was_completed.txt");
        changeCompleted << "true";
        changeCompleted.close();

        //end time for run
        auto endingTime = chrono::system_clock::now();
        time_t endTimeValue = chrono::system_clock::to_time_t(endingTime);
        cout << "Finished at: " << ctime(&endTimeValue);

    } else {
        cout << "error: missing file" << endl;
        cout << "debugging-related info:" << endl;
        cout << "fileExists: " << fileExists << endl;
		cout << "countExists: " << countExists << endl;
		cout << "leftOffAtInt: " << (leftOffAtInt != -1) << endl;
		cout << "filename: " << (filename != "") << endl;
    }
    return 0;
}
