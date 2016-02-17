#include <pthread.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//Functions
void *printString(void *ptr);
bool isConsonant(string x);
bool isVowel(string x);
bool isOther(string x);

//Global variables
string token;
const char** input;
int totalInput;

int main(int argc, char const *argv[]) {

  pthread_t cThread, vThread, oThread;
  char firstChar;
  input = argv;
  totalInput = argc;

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
  string firstChar;
  int id = *((int *) ptr);
  printf("%d\n", id);

  for (ii = 1; ii < totalInput; ii++) {

    token = input[ii];
    firstChar = token.at(0);

    while(true) {
      if (isConsonant(firstChar) && id == 0) {
        cout << token << endl;
        sched_yield();
        break;
      }
      else if(isVowel(firstChar) && id == 1) {
        cout << token << endl;
        sched_yield();
        break;
      }
      else if (isOther(firstChar) && id == 2) {
        cout << token << endl;
        sched_yield();
        break;
      }
    }
  }
  pthread_exit(0);
}

bool isConsonant(string x) {
  string consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
  int numberOfConsonants = 42;
  string consonant;
  int ii;

  for(ii = 0; ii < numberOfConsonants; ii++) {
    consonant = consonants.at(ii);
    if (x.compare(consonant) == 0) {
      return true;
    }
  }
  return false;
}

bool isVowel(string x) {
  string vowels = "aeiouAEIOU";
  int numberOfVowels = 10;
  string vowel;
  int ii;

  for(ii = 0; ii < numberOfVowels; ii++) {
    vowel = vowels.at(ii);
    if(x.compare(vowel) == 0) {
      return true;
    }
  }
  return false;
}

bool isOther(string x) {
  string others = "0123456789.,!@#$^&*()[]{};:/?<>`~|";
  int numberOfOthers = 34;
  string other;
  int ii;

  for(ii = 0; ii < numberOfOthers; ii++) {
    other = others.at(ii);
    if(x.compare(other) == 0) {
      return true;
    }
  }
  return false;
}
