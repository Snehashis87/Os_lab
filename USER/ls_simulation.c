#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to search and print lines containing the pattern
void search_in_file(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[1024];  // Buffer to hold each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains the pattern
        if (strstr(line, pattern)) {
            printf("%s", line);  // Print the line containing the pattern
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    // Check if correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <pattern>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *pattern = argv[2];

    // Search for the pattern in the file
    search_in_file(filename, pattern);

    return 0;
}

