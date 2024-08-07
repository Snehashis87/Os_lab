#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  // For opendir, readdir, closedir
#include <string.h>  // For strcmp

int main() {
    // Step 4: Get directory name
    char dir_name[256];
    printf("Enter the directory name: ");
    scanf("%255s", dir_name);  // Safe input to avoid buffer overflow

    // Step 5: Open directory
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Step 6: Read content of directory
    struct dirent *entry;
    printf("Contents of directory '%s':\n", dir_name);
    while ((entry = readdir(dir)) != NULL) {
        // Print the name of the file/directory
        printf("%s\n", entry->d_name);
    }

    // Check for errors in reading directory
    if (closedir(dir) == -1) {
        perror("closedir");
        return EXIT_FAILURE;
    }

    // Step 7: Close directory
    printf("Directory closed successfully.\n");

    return EXIT_SUCCESS;
}

