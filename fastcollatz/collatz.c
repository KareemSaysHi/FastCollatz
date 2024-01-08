#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t collatzLength(size_t number) {
    size_t count = 0;
    while (number != 1) {
        if (number % 2 == 1) {
            number =( 3*number + 1) >> 1;
            count += 2;
        }
        else { 
            number = number >> 1;
            count += 1;
        }
    }
    return count;
}

void biggestCollatz(size_t howHigh, size_t *maxLen, size_t *maxNum ) {
    size_t resultingcalc;
    for (size_t i = howHigh / 2; i < howHigh + 1; i++) {
        if ((i % 1000000) == 0) {
            printf("Currently at %lu\n", i);
        }

        if (3*i % 4 == 0) {
            if (3 * i / 4 == *maxNum) {
                *maxLen = *maxLen +2;
                *maxNum = i;
            }
        }
        if (i % 2 != 0) {
            resultingcalc = collatzLength(i);
            if ((*maxLen) < resultingcalc) {
                *maxLen = resultingcalc;
                *maxNum = i;
            }
        } else if (i / 2 == *maxNum) {
            *maxLen = *maxLen +1;
            *maxNum = i;
        }
    }
}

int main(int argc, char **argv) {
    size_t input;
    size_t result1 = 0;
    size_t result2 = 0;
    
    if(argc != 2) {
        printf("unexpected number of arguments\n");
        return -1;
    }

    input = atoi(argv[1]);

    biggestCollatz(input, &result1, &result2);

    printf("The largest number is %lu with path length %lu", result2, result1);

    return 0;
    
}