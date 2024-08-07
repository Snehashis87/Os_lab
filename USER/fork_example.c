#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For fork(), getpid(), exit()

int main() {
    // Step 2: Declare pid, pid1
    pid_t pid, pid1;

    // Step 3: Call fork()
    pid = fork();

    // Step 4: If fork() returns -1, exit
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Step 5: If fork() is successful
    // Print PID and Child PID
    if (pid == 0) {
        // This block is executed by the child process
        pid1 = getpid();
        printf("Child process PID: %d\n", pid1);
    } else {
        // This block is executed by the parent process
        pid1 = getpid();
        printf("Parent process PID: %d\n", pid1);
    }

    // Step 7: Close
    // Exit the program
    exit(EXIT_SUCCESS);
}

