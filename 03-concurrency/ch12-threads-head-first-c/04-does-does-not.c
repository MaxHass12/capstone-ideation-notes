#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

// Function prototypes
void* does_not(void* a);
void* does_too(void* a);
void error(char* message);

int main(void)
{
    pthread_t t0;
    pthread_t t1;

    // Open the first thread
    if (pthread_create(&t0, NULL, does_not, NULL) != 0)
        error("Could not open first thread");

    // Open the second thread
    if (pthread_create(&t1, NULL, does_too, NULL) != 0)
        error("Could not open second thread");

    // Wait for the threads to finish
    void* result;
    if (pthread_join(t0, &result) != 0)
        error("Could not join the first thread");
    if (pthread_join(t1, &result) != 0)
        error("Could not join the second thread");

    return 0;
}

void* does_not(void* a)
{
    for (int i = 0; i < 5; i++)
    {
        usleep(10000);  // 0.1 second = 100000 microseconds
        puts("1");
    }
    return NULL;
}

void* does_too(void* a)
{
    for (int i = 0; i < 5; i++)
    {
        usleep(10000);  // 0.1 second = 100000 microseconds
        puts("0");
    }
    return NULL;
}

void error(char* message)
{
    fprintf(stderr, "%s: %s\n", message, strerror(errno));  // Fixed format string
    exit(1);
}
