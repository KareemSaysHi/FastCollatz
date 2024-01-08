#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 1000  

FILE *fptr;

int check_power_of_two(int numtocheck) {
    while (numtocheck != 1 ) {
        if (numtocheck % 2 != 0) return 0;
        numtocheck /= 2;
    }
}

int main(int argc, char **argv) {
    size_t input1, input2;
    size_t searchupto = 0;
    int numforks = 0;
    size_t result2 = 0;
    char **command = NULL;
    pid_t pid;


    /* check inputs*/
    if(argc != 3) {
        printf("unexpected number of arguments\n");
        return -1;
    }
    
    searchupto = 1 << (atoi(argv[1]));
    numforks = atoi(argv[2]);

    
    printf("%zu\n", searchupto);
    printf("%d\n", numforks);

    if (!(check_power_of_two(numforks)) || (numforks > 8))   {
        printf("you need a forking number of 1, 2, 4, 8\n");
        return -1;
    }
    

    /* format the forking */

    command = malloc(numforks * sizeof(char*));

    for (int i = 0; i < numforks; i++) {
        command[i] = malloc(MAX_COMMAND_LENGTH);
        sprintf(command[i], "./subcollatz file%d %zu %zu", i, (searchupto*i)/numforks, (searchupto*(i+1))/numforks);
        printf("./subcollatz file%d %zu %zu\n", i, (searchupto*i)/numforks, (searchupto*(i+1))/numforks);

    }

    /* and now we do parallel */
    for (int i = 0; i < numforks; i++) {
        pid = fork();

        if (pid == 0) {
            //printf("running command %s\n", command[i]);
            system(command[i]);
            printf("done with %d\n", i);
            exit(0);
        }
    }

    for (int i = 0; i < numforks; i++) {
        wait(NULL);
    }
    
    system("cat file* > finalfile");

    return 0;
}