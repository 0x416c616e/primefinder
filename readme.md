# Prime Gap Finder

This project can find prime numbers, gaps between prime numbers, distributions of prime numbers per 50k positive natural numbers, and graph prime gaps. I eventually want to add functionality for graphing the prime distributions too, and maybe even a prime gap histogram too. 

This program uses "checkpoints" which mean that it periodically saves its state to files on your hard drive or SSD, but it doesn't do it too often, because that would cause wear and tear on your hardware, not to mention it would make the program slower. So I currently have it set so that it will do 50k iterations, then save its status.

Not only do the checkpoints reduce the amount of times the program needs to write to storage, but it also makes it so that, if the program gets quit unexpectedly (such as closing the window or hitting ctrl+c in the middle of a run, or your power going out, or rebooting your computer), you can still recover from it.

Another benefit of the checkpoint system is how it breaks up the data into smaller files. Each .dat file only has 50,000 natural numbers' worth of x,y pairs in it. That means far fewer than 50,000 per file (and in fact, as the numbers are higher, there are fewer entries per file because of the nature of prime distribution). The pairs consist of the prime number itself and the difference between it and the previous prime number.

The .dat file is structured much like a .csv file. I started making this program with comma-separated values, as it is easy to work with in C++ and I didn't feel like using a local database or some more advanced format like XML or JSON, which are easy to deal with in newer languages, but might require a third party or a DIY parser on an older language like C++. gnuplot apparently usually uses spaces or tabs to differentiate between values, but the shell script for creating a gnusplot script has a line that specifies commas as the delimiter. 

My previous prime number software would restart every time you opened it, but this time, it will revert back to its last checkpoint.

So it you go through 110k numbers and then quit, the next time you start, it will start at 100k again, because it only saves in multiples of 50,000. Like I said, this is to reduce the amount of times it has to write to the drive/SSD.

If you run primegaps.exe, it will do a single 50k number run. If you want to run it continuously, use the shellscript called run_continuously.

run_continuously will not only run the primegaps.exe program again and again, it will also run a shell script which creates a gnuplot script, and then it runs the gnuplot script to create a graph, which in this case is an 800x800 .png image called primegaps.png.

The best way to run this program is with run_continuously, such as chmod +x run_continuously; ./run_continuously. 


