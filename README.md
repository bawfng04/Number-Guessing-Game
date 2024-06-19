# Number Guessing Game

This is a simple number guessing game implemented in C++. The game offers three modes: easy, medium, and hard. 

## How to Play

1. Compile and run the game.
2. Select a game mode by typing 'easy', 'medium', or 'hard'.
3. Guess the number.

## Game Modes

- **Easy Mode**: Guess a number between 1 and 100. There is no limit on the number of attempts and no hints are provided.
- **Medium Mode**: Guess a number between 1 and 200. You have 10 attempts and 1 hint.
- **Hard Mode**: Guess a number between 1 and 500. You have 9 attempts and 2 hints.

## Hints

Hints can be requested by typing 'hint'. The hints can be about whether the number is prime, or whether the last digit of the number is even or odd.

## Compilation

To compile the game, navigate to the project directory and run the following command:

```bash
g++ NumberGuessing.cpp -o NumberGuessing
