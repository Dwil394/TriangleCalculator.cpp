/**
 * This program generates the Collatz (Hailstone) sequence for any positive integer
 * entered by the user. It displays the subsequence from the starting number until 
 * the next occurrence of 1, along with the sequence length and the sum of the terms.
 * If the user enters a non-positive integer, an error message is displayed.
 * 
 * @author Day'Quan Williams
 * <pre>
 * CSC 1253 Project #3 Section # YOUR_SECTION_NUMBER
 * DATE: October 21, 2025
 * File: CollatzSequencer.cpp
 * Instructor: Dr. Duncan
 * </pre>
 */

#include <iostream>
using namespace std;

int main() {
    cout << "The Collatz/Hailstone Sequence\n" << endl;

    long n;
    cout << "Enter the first term of the Collatz sequence-> ";
    cin >> n;

    // Check for valid input
    if (n < 1) {
        cout << "You must enter a positive integer." << endl;
        return 0;
    }

    // Initialize sequence variables
    long term = n;
    long sum = 0;
    int length = 0;

    cout << "The Collatz Subsequence from " << n << " to 1 is:" << endl;

    // Generate and display the Collatz sequence
    while (true) {
        cout << term;
        sum += term;
        length++;

        // Stop when we reach 1
        if (term == 1)
            break;

        cout << ", ";

        // Collatz rules
        if (term % 2 == 0)
            term = term / 2;
        else
            term = 3 * term + 1;
    }

    cout << endl;
    cout << "Length of Subsequence: " << length << endl;
    cout << "sum(collatz[" << n << ",...,1]) = " << sum << endl;

    return 0;
}
