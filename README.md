# Smallest-Number-Compute
 C program that computes the kth smallest number in a sequence of n integers. 

- This program will apply counting sort up to 9 times, once for each of the digit positions. 
- The first sort will operate on the "hundred millinos" digits. 
- The last sort will operate on the "ones" digits (MSD radix sort inspired). 
- Each sort may eliminate a significant fraction of the remaining values. This may also decrease n and k for the next counting sort. 
- The program will also indicate teh number of remaining values after each counting sort. 
