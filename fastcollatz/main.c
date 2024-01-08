#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    size_t input;
    size_t max = 0;
    size_t result2 = 0;
    
    if(argc != 2) {
        printf("unexpected number of arguments\n");
        return -1;
    }

    max = atoi(argv[1]);

    system("./subcollatz file1 0 50000000");
    system("./subcollatz file2 50000000 100000000");
    
    system("cat file* > finalfile");

    return 0;
    
}