#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Shared resource
int beers = 2000000;
pthread_mutex_t lock;  // Mutex declaration

// Function prototype
void* drink_lots(void* a);

int main() {
    pthread_t threads[20];

    printf("%d bottles of beer on the wall\n%d bottles of beer\n", beers, beers);

    pthread_mutex_init(&lock, NULL);  // Initialize mutex

    // Create threads
    for (int t = 0; t < 20; t++) {
        if (pthread_create(&threads[t], NULL, drink_lots, NULL) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    // Correct loop for joining threads
    for (int t = 0; t < 20; t++) {  // ✅ Match the number of created threads
      if (pthread_join(threads[t], NULL) != 0) {
          perror("Error joining thread");
          exit(EXIT_FAILURE);
      }
    }


    printf("Final beer count: %d\n", beers);

    pthread_mutex_destroy(&lock);  // Destroy mutex
    return 0;
}

// Function for drinking beers (Thread-safe)
// void* drink_lots(void* a) {
//     for (int i = 0; i < 100000; i++) {
//         pthread_mutex_lock(&lock);  // Lock before modifying shared data
//         beers -= 1;
//         pthread_mutex_unlock(&lock);  // Unlock after modification
//     }
//     printf("beers = %i\n", beers);
//     return NULL;
// }

void* drink_lots(void* a) {
  pthread_mutex_lock(&lock);  // Lock before modifying shared data
  for (int i = 0; i < 100000; i++) {
      beers -= 1;
  }
  pthread_mutex_unlock(&lock);  // Unlock after modification
  printf("beers = %i\n", beers);
  return NULL;
}

