#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"

#define SIZE 4

int array[SIZE];

// add any global declarations here
pthread_mutex_t locks[SIZE];

// inputs: integer indices in range 0 to SIZE-1 in either argument
// outputs: none
// Must call update_entry(int indx) with the lower of the two indices before
// incrementing the larger index array value by the updated lower index array 
// value.
void update_two(int idx1, int idx2) {
  // Access/update shared data as specified.   Synchronize it!
  int lower = idx1;
  int higher = idx2;
  if (idx1 > idx2) {
    // Swap the values
    lower = idx2;
    higher = idx1;
  }
  // Suppose idx1 < idx2, then:
  Pthread_mutex_lock(&locks[lower]);
  Pthread_mutex_lock(&locks[higher]);

  update_entry(lower);
  array[higher] += array[lower];
  // These two lines should execute atomically: no updates to array[idx1] and array[idx2]
  // by other threads while this code section executes.
  Pthread_mutex_unlock(&locks[higher]);
  Pthread_mutex_unlock(&locks[lower]);
}

// create 4 threads, passing to each one a unique integer id in the range 0-3
// each thread should be created with thread_worker as the function to execute
// wait for all 4 threads to complete before returning.
// this routine will be called many times from main.
void create_and_wait_threads() {
  // fill in this portion to initialize locks and create 4 threads 
  // that call thread_worker with a unique integer id in the range 0-3
  // use join to wait for all four threads to finish before returning
  pthread_t threads[4];
  int thread_ids[4] = {0, 1, 2, 3};
  for (int i = 0; i < 4; i++) {
    Pthread_create(&threads[i], NULL, thread_worker, (void *)&thread_ids[i]);
  }
  for (int j = 0; j < 4; j++) {
    Pthread_join(threads[j], NULL);
  }
}

int main (int argc, char **argv)
{

  // run some number of trials defined in mythreads.h
  for (int k = 0; k < TRIALS; k++) {
    // set the array values
   for (int i = 0; i < SIZE; i++) {
      array[i] = 0;
   }

    // call an internal init routine, used by prof
    my_threads_init();

    // create the threads and wait for completion
    create_and_wait_threads();

    my_threads_end();

    // main finish up code, compute a sum of the array values
    int sum = 0;
    for (int i =0; i < SIZE; i++) {
      if (array[i]) {
        printf("%d: %d\n",i,array[i]);
        sum += array[i];
      } 
    }
    printf("main: trial %d result %d\n",k,sum);
  }

  return(0);
}
