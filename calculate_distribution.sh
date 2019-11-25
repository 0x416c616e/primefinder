#!/usr/bin/env bash
#calculates the number of primes per 50k csv
#makes a new csv with the offset (0, 50k, 100k, 150k, etc)
#along with the number of primes
#so you can graph the number of primes over time per 50k

./prime_distribution.sh > prime_distribution.csv
