//*********************************************************
//
// James Stewart and Will Taylor
// Operating Systems
// Project 2c
//
// Due: Monday, Feb. 22 at Midnight
//
// This multithreaded program uses PThreads to determine whether or
// not a given sudoko puzzle is a valid solution or not. The program
// uses a total of 11 threads to perform the calculations. 1 thread
// checks the rows, 1 thread checks the columns, and 9 threads
// check the 9 boxes in the board.
//
//  Input: A series of 81 integers delimited by spaces from standard input.
//
//  Output: 0 if the board is not a valid solution
//          1 if the board is a valid solution
//
//  To input a file from the command line, run ./a.out < INPUT_FILE_NAME.TXT
//
//*********************************************************

#include <iostream>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;

void *checkColumns( void *ptr );
void *checkRows( void *ptr );
void *checkBox( void *ptr );

bool arrayIsValid(int rowOrColumn[9]);
int getCenterPosition(int center);

int board[81]; //= malloc(81 * sizeof(int));

bool rowsCorrect, columnsCorrect, box1Correct, box2Correct, box3Correct, box4Correct, box5Correct, box6Correct,
      box7Correct, box8Correct, box9Correct = false;

int main(int argc, char* argv[]) {

  // ---------------------- Declarations ----------------------
  pthread_t rowThread, columnThread, box1Thread, box2Thread, box3Thread, box4Thread, box5Thread, box6Thread,
    box7Thread, box8Thread, box9Thread;

  // ---------------------- Initializations ----------------------
  columnsCorrect = true;
  rowsCorrect = true;
  // Initialize board from stdin

  for(int ii = 1; ii < 82; ii++){
    int token;
    cin >> token;
    board[ii - 1] = token;
  }

  //assert(argc == 82);


  // Create and run threads
  pthread_create( &columnThread, NULL, checkColumns, (void*) argv);
  pthread_create( &rowThread, NULL, checkRows, (void*) argv);

  int parameter = 0;
  pthread_create( &box1Thread, NULL, checkBox, (void*) &parameter);
  int parameter1 = 1;
  pthread_create( &box2Thread, NULL, checkBox, (void*) &parameter1);
  int parameter2 = 2;
  pthread_create( &box3Thread, NULL, checkBox, (void*) &parameter2);
  int parameter3 = 3;
  pthread_create( &box4Thread, NULL, checkBox, (void*) &parameter3);
  int parameter4 = 4;
  pthread_create( &box5Thread, NULL, checkBox, (void*) &parameter4);
  int parameter5 = 5;
  pthread_create( &box6Thread, NULL, checkBox, (void*) &parameter5);
  int parameter6 = 6;
  pthread_create( &box7Thread, NULL, checkBox, (void*) &parameter6);
  int parameter7 = 7;
  pthread_create( &box8Thread, NULL, checkBox, (void*) &parameter7);
  int parameter8 = 8;
  pthread_create( &box9Thread, NULL, checkBox, (void*) &parameter8);

  // Join with threads
  pthread_join(columnThread, NULL);
  pthread_join(rowThread, NULL);
  pthread_join(box1Thread, NULL);
  pthread_join(box2Thread, NULL);
  pthread_join(box3Thread, NULL);
  pthread_join(box4Thread, NULL);
  pthread_join(box5Thread, NULL);
  pthread_join(box6Thread, NULL);
  pthread_join(box7Thread, NULL);
  pthread_join(box8Thread, NULL);
  pthread_join(box9Thread, NULL);

  // Determine whether or not puzzle is valid
 if(rowsCorrect && columnsCorrect && box1Correct && box2Correct && box3Correct && box4Correct &&
     box5Correct && box6Correct && box7Correct && box8Correct && box9Correct){
    cout << "1\n";
  } else {
    cout << "0\n";
  }

  return 0;
}

void *checkBox( void *ptr ){
  // Representation of each box:
  //
  // A|B|C
  // -----
  // D|E|F
  // -----
  // G|H|I
  //
  // If we know the board value, of center, we can
  // deduce the board value of the entire box:
  //
  // A = cen - 10   B = cen - 9   C = cen - 8
  // D = cen - 1    E = cen       F = cen + 1
  // G = cen + 8    H = cen + 9   I = cen + 10

  int center = *((int *) ptr);
  int temp;

  int boxToCheck[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  int oldCenter = center;
  center = getCenterPosition(center);

  // Check for the value in each of 9 sections of box and mark
  // the numbers we find

  temp = board[center - 10];    // A
  boxToCheck[temp - 1] = 1;

  temp = board[center - 9];     // B
  boxToCheck[temp - 1] = 1;

  temp = board[center - 8];     // C
  boxToCheck[temp - 1] = 1;

  temp = board[center - 1];     // D
  boxToCheck[temp - 1] = 1;

  temp = board[center];         // E
  boxToCheck[temp - 1] = 1;

  temp = board[center + 1];     // F
  boxToCheck[temp - 1] = 1;

  temp = board[center + 8];     // G
  boxToCheck[temp - 1] = 1;

  temp = board[center + 9];     // H
  boxToCheck[temp - 1] = 1;

  temp = board[center + 10];    // I
  boxToCheck[temp - 1] = 1;


  // Check to see if box is correct
  bool boxIsCorrect = arrayIsValid(boxToCheck);



  switch(oldCenter){
    case 0:
      box1Correct = boxIsCorrect;
    case 1:
      box2Correct = boxIsCorrect;
    case 2:
      box3Correct = boxIsCorrect;
    case 3:
      box4Correct = boxIsCorrect;
    case 4:
      box5Correct = boxIsCorrect;
    case 5:
      box6Correct = boxIsCorrect;
    case 6:
      box7Correct = boxIsCorrect;
    case 7:
      box8Correct = boxIsCorrect;
    case 8:
      box9Correct = boxIsCorrect;
    }
  pthread_exit(0);
}

int getCenterPosition(int center){

  // Function to return the board value of the
  // center of one of the nine sub boxes.

  switch(center){
    case 0:
      return 10;
    case 1:
      return 13;
    case 2:
      return 16;
    case 3:
      return 37;
    case 4:
      return 40;
    case 5:
      return 43;
    case 6:
      return 64;
    case 7:
      return 67;
    case 8:
      return 70;
    }
    pthread_exit(0);
}

void *checkColumns( void *ptr ){
  int columnStart = 0;
  int currentSpot = 0;

  int columnToCheck[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  int ii, jj;

  for(ii = 0; ii < 9; ii++){
    // For each column

    // Reset columnToCheck array
    for(int aa = 0; aa < 9; aa++){
      columnToCheck[aa] = 0;
    }


    // Record what numbers we have
    for(jj = 0; jj < 9; jj++){

      // Find where to check in the column
      if(jj == 0){
        currentSpot = columnStart;
      } else {
        currentSpot = currentSpot + 9;
      }

      // Get the spot in the board
      int temp = board[currentSpot];
      // Record that we have gotten that int
      columnToCheck[temp - 1] = 1;

    }
    // Check to see if row is corerct

    bool columnIsCorrect = arrayIsValid(columnToCheck);

    if(!columnIsCorrect){
      columnsCorrect = false;
      break;
    }

    columnStart = columnStart + 1;

  }

  pthread_exit(0);

}

void *checkRows( void *ptr ){
  int rowStart = 0;
  int currentSpot = 0;

  int rowToCheck[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  int ii, jj;

  for(ii = 0; ii < 9; ii++){
    // For each column

    // Reset rowToCheck array
    for(int aa = 0; aa < 9; aa++){
      rowToCheck[aa] = 0;
    }

    // Record what numbers we have
    for(jj = 0; jj < 9; jj++){

      // Find where to check in the column
      if(jj == 0){
        currentSpot = rowStart;
      } else {
        currentSpot = currentSpot + 1;
      }

      // Get the spot in the board
      int temp = board[currentSpot];
      // Record that we have gotten that int
      rowToCheck[temp - 1] = 1;

    }
    // Check to see if row is corerct

    bool rowIsCorrect = arrayIsValid(rowToCheck);

    if(!rowIsCorrect){
      rowsCorrect = false;
      break;
    }

    rowStart = rowStart + 9;

  }

  pthread_exit(0);
}

bool arrayIsValid(int rowOrColumn[9]){
  int ii;

  for(ii = 0; ii < 9; ii++){

    if(rowOrColumn[ii] == 0 ){
      return false;
    }
  }

  return true;
}
