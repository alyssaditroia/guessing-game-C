# Guessing Game

## Description

This project is a simple number guessing game implemented in C. The game challenges players to guess a randomly generated number based on its square root. The program keeps track of the number of guesses each player takes and updates a leaderboard to store the top 5 scores.

## Features

- **Random Number Generation:** The game generates a random number between 10 and 100, and the player is asked to guess the number based on its square root.
- **Leaderboard:** The game maintains a leaderboard of the top 5 players with the fewest guesses.
- **User-Friendly Interface:** Players are prompted to continue or quit the game and can easily input their guesses.

## How to Play

1. **Start the Game:**
   - Run the program.
   - You will be prompted to press any key to start or 'q' to quit.

2. **Enter Your Name:**
   - Enter your name when prompted.

3. **Guess the Number:**
   - The program will provide the square root of a random number.
   - Enter your guesses until you find the correct number.
   - The program will inform you if your guess is too high or too low.

4. **View the Leaderboard:**
   - If your number of guesses is among the top 5, your name and score will be added to the leaderboard.
   - The leaderboard is saved to a file (`leaderboard.txt`).

5. **Repeat or Quit:**
   - After each game, you can choose to play again or quit by entering 'q'.

## Code Overview

- **Data Structures:**
  - `User`: A structure that holds a player's name and the number of guesses they made.
  - `Bool`: An enumeration representing boolean values (`TRUE` and `FALSE`).

- **Key Functions:**
  - `createLeaderboard()`: Initializes the leaderboard file if it does not already exist.
  - `playGuessingGame()`: Manages the game loop, including prompting the player to continue or quit.
  - `getUserName(User *currentUser)`: Prompts the player to enter their name.
  - `getNumberToGuess()`: Generates the random number and provides its square root to the player.
  - `getUserGuess(int numberToGuess)`: Handles user input for guessing the number and counts the number of attempts.
  - `updateLeaderboard(User leaderboard[], User currentUser)`: Updates the leaderboard with the player's score if it qualifies for the top 5.

## Requirements

- **C Compiler:** Any standard C compiler (e.g., GCC).
- **Operating System:** Linux, macOS, or any system that supports `system("clear")` for screen clearing.

## How to Compile and Run

1. **Compile:**
   ```sh
   gcc -o guessingGame guessingGame.c
