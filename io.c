#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if at least one command-line argument is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    // Convert the command-line argument to an integer
    int number = atoi(argv[1]);

    // Print the number
    printf("The entered number is: %d\n", number);

    return 0;
}
