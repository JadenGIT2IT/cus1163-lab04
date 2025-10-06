#include "executor.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Executes a given command with arguments using fork-exec-wait pattern
int execute_command(char *command, char *args[]) {
    pid_t pid;
    int status;

    // =============================
    // TODO 1: Fork the Child Process
    // =============================
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1;  // Return error to caller
    }

    // =============================
    // TODO 2: Child Process - Execute Command
    // =============================
    if (pid == 0) {
        // In child process: transform into new program
        execvp(command, args);

        // If execvp returns, it failed
        perror("execvp");
        exit(1); // Must call exit, not return
    }

    // =============================
    // TODO 3: Parent Process - Wait for Child
    // =============================
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return -1;
    }

    // Check if child exited normally
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        // Abnormal termination
        return -1;
    }
}
