#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t id = fork();

    if (id < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (id == 0) {
        // Child process
        printf("Child process executing ls command:\n");
        system("ls");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish

        printf("Parent process executing ps command:\n");
        char *const ps_args[] = {"ps", NULL};
        execv("/bin/ps", ps_args);

        // execv will only return if an error occurs
        perror("execv failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}