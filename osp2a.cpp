//*********************************************************
//
// James Stewart and Will Taylor
// Operating Systems
// Project #2a
//
// Due: Monday, Feb. 22 at Midnight
//
// This multithreaded program uses PThreads to calculate the max,
// min, and mean of a set of integers. There are three threads,
// meanThread, maxThread, and minThread that perform these calculations.
// The main thread prints out the results after all three threads have
// exited.
//
//  Input: A series of n integers from the command line.
//
//  Output: The max, min, and mean of the series of integers.
//
//*********************************************************

#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;

void *calculateMean( void *ptr );
void *calculateMin( void *ptr );
void *calculateMax( void *ptr );

float average = -1;
int max, minimum, maximum;

int main(int argc, char* argv[]) {

  assert(argc > 1);

  pthread_t meanThread, maxThread, minThread;

  int  iret1, iret2, iret3;

  iret1 = pthread_create( &meanThread, NULL, calculateMean, (void*) argv);
  iret2 = pthread_create( &minThread, NULL, calculateMin, (void*) argv);
  iret2 = pthread_create( &maxThread, NULL, calculateMax, (void*) argv);

  pthread_join(meanThread, NULL);
  pthread_join(minThread, NULL);
  pthread_join(maxThread, NULL);

  cout.precision(2);

  std::cout << "MEAN: " << fixed << average << "\n";
  std::cout << "MIN: " << minimum << "\n";
  std::cout << "MAX: " << maximum << "\n";

  return 0;
}

void *calculateMean( void *ptr ){
  // Local variables
  char** args;
  int ii, sum, temp, count;

  // Initialize local variables
  args = (char**) ptr;
  sum = 0;
  count = 0;

  // Add together all numbers in set
  for(ii = 1; args[ii] != NULL; ii++){
    temp = atoi(args[ii]);
    sum += temp;
    count++;
  }

  // Set global average variable
  average = ( (float) sum / (float) count);

  pthread_exit(0);
}

void *calculateMin( void *ptr ){
  // Local variables
  char** args;
  int ii, min, temp;

  // Initialize local variables
  args = (char**) ptr;
  min = atoi(args[1]);

  // Find min
  for(ii = 1; args[ii] != NULL; ii++){
    temp = atoi(args[ii]);

    if(temp < min){
      min = temp;
    }
  }

  // Set global min variable
  minimum = min;

  pthread_exit(0);
}

void *calculateMax( void *ptr ){
  // Local variables
  char** args;
  int ii, max, temp;

  // Initialize local variables
  args = (char**) ptr;
  max = atoi(args[1]);

  // Find min
  for(ii = 1; args[ii] != NULL; ii++){
    temp = atoi(args[ii]);

    if(temp > max){
      max = temp;
    }
  }

  // Set global min variable
  maximum = max;

  pthread_exit(0);
}
