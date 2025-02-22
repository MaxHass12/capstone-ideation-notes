#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Parent process (PID: %d) starts\n", getpid());
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running\n", getpid());
        sleep(1);  // Simulate quick work
        printf("Child process (PID: %d) is done\n", getpid());
        exit(0);  // Child exits before parent
    } else {
        // Parent process
        printf("Parent process (PID: %d) is running, waiting...\n", getpid());
        sleep(3);  // Delay parent execution
        printf("Parent process (PID: %d) finishing after child\n", getpid());
    }

    return 0;
}
