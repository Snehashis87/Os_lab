#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Step 1: Check if the program is called with the right number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Step 2: Declare the variables
    char ch;
    FILE *fp;
    int sc = 0; // Space count

    // Step 3: Open the file in read mode
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Step 4: Get the character and process it
    while ((ch = fgetc(fp)) != EOF) {
        // Step 5: If ch is a space, increment sc
        if (ch == ' ') {
            sc++;
        }
    }

    // Step 6: Print the number of spaces
    printf("Number of spaces: %d\n", sc);

    // Step 7: Close the file
    fclose(fp);

    return 0;
}

