#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t id = fork();

    if (id < 0) {
        printf("fork failed");
        exit(EXIT_FAILURE);
    } 
    
    else if (id == 0) {
        printf("Child process executing ls command:%d\n",id);
        char *args[] = {"ls", NULL};
        execv("/bin/ls", args);
        printf("\n");    
        
        printf("execv failed");
        exit(EXIT_FAILURE);
    } else {
        
        wait(NULL); 
        
        printf("\nParent process executing ps command:%d\n",id);
        char *ps_args[] = {"ps", NULL};
        execv("/bin/ps", ps_args);
        
        printf("execv failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
