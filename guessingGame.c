/*
 * guessingGame.c
 *
 *  Created on: Feb 10, 2024
 *      Author: alyssaditroia
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEADERBOARD "leaderboard.txt"
#define MAX_LEADERS 5

typedef struct {
  char userName[50];
  int numberOfGuesses;
} User;

typedef enum { FALSE = 0, TRUE = 1 } Bool;

void createLeaderboard();
void playGuessingGame();
void getUserName(User *currentUser);
int getNumberToGuess();
int getUserGuess(int numberToGuess);
void updateLeaderboard(User leaderboard[], User currentUser);

int main() {
  createLeaderboard();
  playGuessingGame();
  return 0;
}



// creates a new leader board if one does not exist
void createLeaderboard() {
  FILE *file = fopen(LEADERBOARD, "r");
  if (file == NULL) {
    file = fopen(LEADERBOARD, "w");
    fclose(file);
  }
  fclose(file);
}



// play game function scans if player will continue playing
void playGuessingGame() {
  char playerInput;

  printf("Welcome, press 'q' to quit or any other key to continue:\n");
  scanf(" %c", &playerInput);

  while (playerInput != 'q') {
    User currentUser;
    getUserName(&currentUser);

    int numberToGuess = getNumberToGuess();
    currentUser.numberOfGuesses = getUserGuess(numberToGuess);

    User leaderboard[MAX_LEADERS];
    updateLeaderboard(leaderboard, currentUser);

    printf("Press 'q' to quit or any other key to continue:\n");
    scanf(" %c", &playerInput);
  }
}


// assigns user's name to the User struct
void getUserName(User *currentUser) {
  printf("Enter your name: ");
  scanf("%s", currentUser->userName);
}



// generates the number for the user to guess
int getNumberToGuess() {
  srand((unsigned int)time(NULL));
  int numberToGuess = rand() % 91 + 10;
  double squareRoot = sqrt(numberToGuess);
  printf("%.8f is the square root of what number?\n", squareRoot);
  return numberToGuess;
}



// scans for users guess and counts the number of guesses
int getUserGuess(int numberToGuess) {
  int guess;
  int numberOfGuesses = 0;
  printf("Enter your guess: ");
  // checks for valid input
  while (scanf("%d", &guess) != TRUE || getchar() != '\n') {
    printf("Invalid input. Please enter an integer: \n");
    while (getchar() != '\n');// Clear current input due to invalid input
  }

  while (guess != numberToGuess) {
    numberOfGuesses++;

    if (guess < numberToGuess) {
      printf("Too low, guess again:\n");

    }
    else if (guess > numberToGuess) {
      printf("Too high, guess again:\n");
    }
    // checks for valid input
    while (scanf("%d", &guess) != TRUE || getchar() != '\n') {
      printf("Invalid input. Please enter an integer: \n");
      while (getchar() != '\n'); // Clear current input due to invalid input
    }
  }
  numberOfGuesses++;
  printf("You got it, baby!\n");
  printf("Your guesses: %d\n", numberOfGuesses);
  return numberOfGuesses;
}



void updateLeaderboard(User leaderboard[], User currentUser) {
  FILE *file = fopen(LEADERBOARD, "r+");
  // error checking in case file doesn't exist
  if (file == NULL) {
    printf("Unable to open file.\n");
    return;
  }

  // Read leader board and count the number of leaders
  int leaderCount = 0;
  while (leaderCount < MAX_LEADERS &&
         fscanf(file, "%s %d", leaderboard[leaderCount].userName,
                &leaderboard[leaderCount].numberOfGuesses) == 2) {
    leaderCount++;
  }

  fclose(file);

  // Check if the users score is less than someone on the leader board
  int insertIdx = leaderCount;
  for (int i = 0; i < leaderCount; i++) {
    if (currentUser.numberOfGuesses < leaderboard[i].numberOfGuesses) {
      insertIdx = i;
      break;
    }
  }
  // Insert the new leader into the leader board array
  if (insertIdx < MAX_LEADERS) {
    for (int j = leaderCount - 1; j >= insertIdx; j--) {
      leaderboard[j + 1] = leaderboard[j];
    }
    leaderboard[insertIdx] = currentUser;
    leaderCount = (leaderCount < MAX_LEADERS) ? leaderCount + 1 : MAX_LEADERS;
  }

  // Write the leader board back to the file
  file = fopen(LEADERBOARD, "w");
  if (file == NULL) {
    printf("Unable to open file for writing.\n");
    return;
  }
  for (int i = 0; i < leaderCount; i++) {
    fprintf(file, "%s %d\n", leaderboard[i].userName,
            leaderboard[i].numberOfGuesses);
  }
  fclose(file);
}

