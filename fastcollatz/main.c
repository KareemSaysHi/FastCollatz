#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <time.h>

clock_t startClock;
clock_t endClock;
double cpuSecondsConsumed;

int main(int argc, char **argv) {
    size_t input;
    size_t forking = 0;
    size_t result2 = 0;
    FILE *fptr;
    
    if(argc != 2) {
        printf("unexpected number of arguments\n");
        return -1;
    }

    forking = atoi(argv[1]);
    if (forking == 0) {
        startClock = clock();
        system("./subcollatz file1 0 50000000");
        system("./subcollatz file2 50000000 100000000");
        endClock = clock();
        system("cat file* > finalfile");
        
        cpuSecondsConsumed = ((double)(endClock - startClock)) / CLOCKS_PER_SEC;
        fptr = fopen("finalfile", "a");
        fprintf(fptr, "Program took %f seconds without forking", cpuSecondsConsumed);
        fclose(fptr);
        return 0;

    } else  {
        startClock = clock();
        pid_t pid;
        pid = fork();

        if (pid == 0) {//child branch
            system("./subcollatz file1 0 50000000"); 
            exit(0);
        }

        else { //parent branch
            system("./subcollatz file2 50000000 100000000");
            wait(NULL);
        }
    endClock = clock();
    
    system("cat file* > finalfile");

    cpuSecondsConsumed = ((double)(endClock - startClock)) / CLOCKS_PER_SEC;
    fptr = fopen("finalfile", "a");
    fprintf(fptr, "Program took %f seconds with forking", cpuSecondsConsumed);
    fclose(fptr);

    return 0;
    
    }
}