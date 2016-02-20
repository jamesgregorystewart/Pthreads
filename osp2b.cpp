//*********************************************************
//
// James Stewart and Will Taylor
// Operating Systems
// Project #2b
//
// Due: Monday, Feb. 22 at Midnight
//
// This multithreaded program uses PThreads to print out
// arguments entered by the user upon execution. Each of the
// three threads will take turns printing out strings that
// begin with a consonant, vowel, or other.
//
//  Input: A series of n strings entered as arguments to the
//  executable.
//
//  Output: The arguments entered by the user preceded with
//  what kind of character it starts with, where each argument
//  is printed on its own line.
//
//*********************************************************

#include <pthread.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

//Functions
void *printString(void *ptr);
bool isConsonant(char x);
bool isVowel(char x);
bool isOther(char x);

//Global variables
string token;
const char** gargv;
int gargc;
int gindex; //argument counter

/*****************************************************************************
    main() function

    Purpose - Assigns the values entered by the user to global variables and
              creates the threads that are then assigned to printString().

    Input - int as argc; const char array as argv.

    Output - None.

*****************************************************************************/

int main(int argc, char const *argv[]) {

  pthread_t cThread, vThread, oThread;
  gargv = argv;
  gargc = argc;
  gindex = 1; //start at 1 to skip executable

  //ids for the threads
  int idConsonant = 0;
  int idVowel = 1;
  int idOther = 2;

  //create the threads
  int iretC = pthread_create(&cThread, NULL, *printString, (void*) &idConsonant);
  int iretV = pthread_create(&vThread, NULL, *printString, (void*) &idVowel);
  int iretO = pthread_create(&oThread, NULL, *printString, (void*) &idOther);

  //make them wait for each other before exiting out
  pthread_join(cThread, NULL);
  pthread_join(vThread, NULL);
  pthread_join(oThread, NULL);

  return 0;
}

/****************************************************************************
*   printString() function
*
*   Purpose - Threads wait in a loop until it is their turn to print the
*              string that corresponds to the type of character they are
*              responsible for printing.
*
*    Input - Threads
*
*    Output - Strings printed out to the standard output that show what type
*             the first character is and the string the character belonged to.
*
*
****************************************************************************/

void *printString(void *ptr) {
  int ii;
  string token;
  char firstChar;
  int id = *((int *) ptr);
  int allowed = 0;
  bool changeThread = false;

  //while there is still another argument
  while (gindex < gargc) {
    token = gargv[gindex];
    firstChar = token.at(0);

    if (isConsonant(firstChar) && id == 0) {
      cout << "CONSONANT: " << token << endl;
      gindex++;
    } else if (isVowel(firstChar) && id == 1) {
      cout << "VOWEL: " << token << endl;
      gindex++;
    } else if(isOther(firstChar) && id == 2) {
      cout << "OTHER: " << token << endl;
      gindex++;
    } else {
      sched_yield();
    }
  }
  pthread_exit(0);
}

/**********************************************************************
*    isConsonant() function
*
*    Purpose - This function will return true if the character it is passed
*              begins with a consonant; otherwise it returns false.
*
*    Input - This function takes a character.
*
*    Output - Boolean.
*
**********************************************************************/

bool isConsonant(char x) {
  char consonants[] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

  // does the array contain x?
  if (strchr(consonants, x) != NULL) {
    return true;
  }
  return false;
}

/**********************************************************************
*    isVowel() function
*
*    Purpose - This function will return true if the character it is passed
*              begins with a vowel; otherwise it returns false.
*
*    Input - This function takes a character.
*
*    Output - Boolean.
*
**********************************************************************/

bool isVowel(char x) {
  char vowels[] = "aeiouAEIOU";

  // does the array contain x?
  if (strchr(vowels, x) != NULL) {
    return true;
  }
  return false;
}

/**********************************************************************
*    isOther() function
*
*    Purpose - This function will return true if the character it is passed
*              begins with a non-alpha character; otherwise it returns false.
*
*    Input - This function takes a character.
*
*    Output - Boolean.
*
**********************************************************************/

bool isOther(char x) {

  //is x an alpha character?
  if (!isalpha(x)) {
    return true;
  }
  return false;
}
