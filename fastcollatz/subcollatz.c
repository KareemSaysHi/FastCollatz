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

void biggestCollatz(size_t howLow, size_t howHigh, size_t *maxLen, size_t *maxNum ) {
    size_t resultingcalc;
    for (size_t i = howLow; i < howHigh + 1; i++) {

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
    size_t min = 0;
    size_t max = 0;
    size_t maxLen = 0;
    size_t maxNum = 0;
    FILE *fptr;
    
    if(argc != 4) {
        printf("unexpected number of arguments\n");
        return -1;
    }

    min = atoi(argv[2]);
    max = atoi(argv[3]);

    biggestCollatz(min, max, &maxLen, &maxNum);

    fptr = fopen(argv[1], "w");
    fprintf(fptr, "For min %lu and max %lu, we found number %lu with length %lu\n", min, max, maxNum, maxLen);
    fclose(fptr);

    return 0;
    
}