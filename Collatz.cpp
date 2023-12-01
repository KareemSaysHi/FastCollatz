#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/Users/colbyriley/Downloads/gmp-6.3.0/gmp.h"
//#include "/Users/colbyriley/Downloads/gmp-6.3.0/gmpxx.h"

// Apparently 530000000 is the limit for the amount of memory one can allocate at once before things start to explode, which is why it throws errors.
#define MAX_N 500000000 

/*
Things that could cause a seg-fault: 
    Going above the max for an unsigned long long
    Stack overflowing the while loop 
    Going past system memory limitations

Thing to ask Kareem about:
    Increasing my MAX_N by switching to dynamically allocated arrays rather than large static arrays

size_T


Idea for making sure we get all powers of 2
    Whenever we get a number which is equal and is less than half the thing, make sure we store twice that with 1+

*/



// Array to store memoized Collatz lengths
int memo[MAX_N] = {0};

int collatz_length2(unsigned long long num, unsigned long long start) {
        int length = 0; 
        while (num >= start) {
            if (num & 1) {
                num = 3 * num + 1;
                length++;
            }
            num >>= 1;
            length++;
        }
        length += memo[num];
        return length;
}

int collatz_length(unsigned long long num) {     //We cannot assume that this is only running below MAX_N, since the iteration will quickly go above it.
    if(num >= MAX_N) {
        int length = 0;
        while(num >= MAX_N) {
            if (num & 1) {
                num = 3 * num + 1;
                length++;
            }
            num >>= 1;
            length++;
        }
        return length + collatz_length(num);
    }
    if(memo[num] != 0) {return memo[num];} 
    int length = (num & 1) ? 2 + collatz_length( (3*num + 1) >> 1 ) : 1 + collatz_length(num >> 1);
    memo[num] = length;
    return length;
} 
//while loop (iteration) is faster than recursion, but recursion is needed to memoize all in the sequence, which is much faster. 
// We can augment the recursive loop with iteration -- For instance, if the number is too big, we do not have to recurse. 
//We can just while loop until it is memoizeable. 

// Function to find the maximum Collatz length for numbers less than n
unsigned long long max_collatz_length(unsigned long long n) {
    unsigned long long max_num = 1;
    int max_length = 1;

    // Ensure n is odd for more efficient iteration
    if (n % 2 == 0) {
        n--;
    }

    unsigned long long updateInterval = n / 100;  // Update every 10%

    // Skip even numbers, as they have longer Collatz sequences
    unsigned long long i = 3;

    unsigned long long midpoint = n;
    if(MAX_N * 2 <= n) {
        midpoint = MAX_N;
    } else {
        midpoint = n / 2;
    }

    // add 1 to the memo as the base case.
    memo[1]=1;
    int current_length=0;

    while (i <= midpoint) { 
        current_length = collatz_length(i);
        if (current_length > max_length) {
            max_length = current_length+1;
            max_num = i*2;
        } 
        // Print completion percentage
        if (i % updateInterval == 0) {
            double completion_percentage = ((double)(i - 1) / (n - 1)) * 100;
            printf("Completion: %.2f%%\n", completion_percentage);
        }
        i += 2;
    }
        
    while (i <= n) { 
        current_length = collatz_length2(i, midpoint);
        if (current_length > max_length) {
            max_length = current_length;
            max_num = i;
        } 
        // Print completion percentage
        if (i % updateInterval == 0) {
            double completion_percentage = ((double)(i - 1) / (n - 1)) * 100;
            printf("Completion: %.2f%%\n", completion_percentage);
        }
        i += 2;
    }

    printf("Number with maximum Collatz length below %lld is %lld with length %d.\n", n, max_num, max_length-1);

    return max_num;
}

int main() {
    unsigned long long n;

    printf("Enter the value of n: ");
    scanf("%lld", &n);

    clock_t start_time = clock(); 

    max_collatz_length(n);

    clock_t end_time = clock(); 
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Execution time: %.4f seconds\n", execution_time);

    return 0;
}


/*
Failed optimization attemps:
Moving the memo array to the end. Reason: Idk
    I think this could still work if we moved half the memo array to the beginning and half to the end? Or we could also just use two memo arrays.

Keeping a previous best tally, and immediately killing a cycle if we fell before it. Reason: too many checks in the loop.

*/
