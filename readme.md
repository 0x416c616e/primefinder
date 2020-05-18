# Prime Finder

This project can find and graph prime numbers, gaps between successive prime numbers, and how frequently primes occur. It was written in C++, Bash, and gnuplot script.

![prime gap graph](https://github.com/0x416c616e/primefinder/blob/master/primegaps.png "Prime Gap Graph")
![prime distribution graph](https://github.com/0x416c616e/primefinder/blob/master/primedistribution.png "Prime Distribution Graph")


This program uses "checkpoints" which mean that it periodically saves its state to files on your hard drive or SSD, but it doesn't do it too often, because that would cause wear and tear on your hardware, not to mention it would make the program slower. So I currently have it set so that it will do 50k iterations, then save its status.

## How to run it 

Here's how to run this program:

Firstly, you will need to compile the `src/primegaps.cpp` file and then put it in the main directory.

Then run this:

    ./run_continuously.sh

The output files will be prime_distribution.dat and gaps_0.dat, gaps_1.dat, gaps_2.dat, and so on.

The graphs are saved to primegaps.png (differences between successive primes) and primedistribution.png (number of prime numbers per 50 natural numbers).

To quit the program, press and hold ctrl+c for a few seconds. 

## Dependencies

You need C++, Bash, and gnuplot. If you're on Windows, you will need to make sure you added gnuplot to your PATH variable. 

## chmod +x

Make sure you do chmod +x for all of the shell scripts and the executable.

## macOS and Linux

If you're on macOS or Linux, then compile the primegaps.cpp file within the src folder. The compiled executable will need to be in into the main project folder, such as primefinder.

## Simplified prime finder

A simpler prime-finding program is simple_prime_finder.exe, which only finds primes for the first 100,000 positive natural numbers and then saves them to a file called output.dat. It's much faster for finding primes than the main program, but that's because all it's doing is finding primes, not prime differences, graphing, etc.


