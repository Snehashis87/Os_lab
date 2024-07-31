#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024  // Define a maximum line length

int main(int argc, char *argv[]) {
    // Step 1: Start the program
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <pattern>\n", argv[0]);
        return 1;
    }

    // Step 2: Declare the variables
    char fline[MAX];        // Buffer to hold each line from the file
    int count = 0;          // To count lines read
    int occurrence = 0;    // To count lines containing the pattern
    const char *filename = argv[1];
    const char *pattern = argv[2];
    FILE *fp;
    char *newline;

    // Step 3: Open the file in read mode
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Step 4: Read the file line by line
    while (fgets(fline, MAX, fp) != NULL) {
        count++;  // Step 5: Increment the count value

        // Step 6: Check if the line contains a newline character
        newline = strchr(fline, '\n');
        if (newline) {
            *newline = '\0';  // Remove the newline character from the line
        }

        // Step 7: Check if the pattern is in the line
        if (strstr(fline, pattern)) {
            occurrence++;  // Increment the occurrence count
            printf("Line %d: %s\n", count, fline);  // Print the line
        }
    }

    // Step 8: Close the file and stop the program
    fclose(fp);
    printf("Total lines checked: %d\n", count);
    printf("Total lines containing pattern: %d\n", occurrence);

    return 0;
}

