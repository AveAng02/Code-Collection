#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    int pipefd[2];
    pid_t child_pid;
    char buffer[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process (receiver)

        printf("Inside Child Process\n");

        close(pipefd[1]); // Close write end of the pipe in the child process

        // Read from the pipe
        ssize_t bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Print the received message
        printf("Child received: %s\n", buffer);

        close(pipefd[0]); // Close read end of the pipe in the child process
    } else {
        // Parent process (sender)

        printf("Inside Parent Process\n");

        close(pipefd[0]); // Close read end of the pipe in the parent process

        // Write to the pipe
        char message[] = "Operating Systems Lab";
        ssize_t bytes_written = write(pipefd[1], message, strlen(message) + 1);
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close write end of the pipe in the parent process
    }

    return 0;
}
