# Prime Gap Finder

This project can find prime numbers, gaps between prime numbers, distributions of prime numbers per 50k positive natural numbers, and graph prime gaps. I eventually want to add functionality for graphing the prime distributions too, and maybe even a prime gap histogram too. 

This program uses "checkpoints" which mean that it periodically saves its state to files on your hard drive or SSD, but it doesn't do it too often, because that would cause wear and tear on your hardware, not to mention it would make the program slower. So I currently have it set so that it will do 50k iterations, then save its status.

Here's how to run this program:
    ./run_continuously.sh

The output files will be prime_distribution.dat and gaps_0.dat, gaps_1.dat, gaps_2.dat, and so on.

The graphs are saved to primegaps.png (differences between successive primes) and primedistribution.png (number of prime numbers per 50 natural numbers).
