1. Problem Definition:
  Given an array 𝐴[1..𝑛] consisting of 𝑛 positive integers, the task is identifying majority element in the array. Majority element is defined as an element that passes more than n/2. If there is no such an element, output of algorithm should –1.
  There are several algorithms with different theoretical and practical performances for this problem called FindMajority. In the scope of this project, at least seven different algorithms will be implemented, tested, and compared for solve this problem. The methods to be used include brute force, ranking-based approaches, divide and conquer strategy, hashing, Boyer-Moore Voting algorithm, and an additional method selected from the literature or originally developed.
  The aim of the project is to evaluate the performance of these algorithms on various input scenarios (best case, worst case and average case) and to analyze the experimental results obtained by comparing them with the theoretical time and memory complexities.

2. Implementation Details:
  This program is designed to compare the performance and results of various algorithms that find the majority element in an array that appears more than half the time. It reads input arrays from a file, applies each algorithm, measures execution time, and prints the results.
  The program includes standard libraries (stdio.h, stdlib.h, string.h, time.h) and defines constants for array and line limits.
printArray(): Prints an array.
copyArray(): Duplicates one array into another.
countFrequency(): Counts how many times a given element appears.
printResult(): Nicely formats and prints each algorithm's result and timing.
time_diff_sec(): Calculates execution time in microseconds using clock_gettime().
parseLine(): Reads a line from the input file and converts it into an array of integers.
main(): The program opens a file named inputs.txt. For each line in the file; it parses the numbers into an array A, it prints the input array with its index and size, it copies the original array into B (so the original remains unchanged), it measures the execution time using clock_gettime(), it calls the corresponding function to find the majority element, it prints the algorithm name, the result, and the time taken in microseconds. After processing all inputs, the file is closed and the program ends.
A total of eight majority element algorithms are implemented.
![image](https://github.com/user-attachments/assets/268a0bb7-32c8-4ea2-a264-3326897f167f)
![image](https://github.com/user-attachments/assets/145629f7-6b5b-4bd8-95ef-c1cd7469b264)
