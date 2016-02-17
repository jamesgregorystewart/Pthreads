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
int gindex;

int main(int argc, char const *argv[]) {

  pthread_t cThread, vThread, oThread;
  gargv = argv;
  gargc = argc;
  gindex = 1;

  int idConsonant = 0;
  int idVowel = 1;
  int idOther = 2;

  int iretC = pthread_create(&cThread, NULL, *printString, (void*) &idConsonant);
  int iretV = pthread_create(&vThread, NULL, *printString, (void*) &idVowel);
  int iretO = pthread_create(&oThread, NULL, *printString, (void*) &idOther);

  pthread_join(cThread, NULL);
  pthread_join(vThread, NULL);
  pthread_join(oThread, NULL);

  return 0;
}

void *printString(void *ptr) {
  int ii;
  string token;
  char firstChar;
  int id = *((int *) ptr);
  int allowed = 0;
  bool changeThread = false;


  while (gindex < gargc) {
    token = gargv[gindex];
    firstChar = token.at(0);

    //lines that are commented out will print the thread id and token
    if (isConsonant(firstChar) && id == 0) {
      // cout << id << " " << token << endl;
      cout << token << endl;
      gindex++;
    } else if (isVowel(firstChar) && id == 1) {
      // cout << id << " " << token <<endl;
      cout << token << endl;
      gindex++;
    } else if(isOther(firstChar) && id == 2) {
      // cout << id << " " << token << endl;
      cout << token << endl;
      gindex++;
    } else {
      //sched_yield();
    }
  }
  pthread_exit(0);
}

bool isConsonant(char x) {
  char consonants[] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
  if (strchr(consonants, x) != NULL) {
    return true;
  }
  return false;
}

bool isVowel(char x) {
  char vowels[] = "aeiouAEIOU";
  if (strchr(vowels, x) != NULL) {
    return true;
  }
  return false;
}

bool isOther(char x) {
  if (!isalpha(x)) {
    return true;
  }
  return false;
}
