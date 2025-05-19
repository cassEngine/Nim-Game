# Nim Game (C++)

This is a terminal-based implementation of the classic **Nim Game**, written in C++. It supports two modes:
1. **User vs User**
2. **User vs Computer (PC)**

The game is recursive and demonstrates clean handling of user input, token removal, and win conditions.

---

##  Game Rules

- There are multiple **heaps** (or piles) of tokens.
- Each player can pick **1 or 2 tokens** from a **single heap per turn**.
- The player who takes the **last token wins**.
- Tokens are displayed visually like this:
  
A: O O

B: O O O

A: O (...)

## Game Features

- Recursive turn-based gameplay
- Two game modes:
- Player vs Player (5 heaps)
- Player vs PC (2–10 heaps)
- Input format like `B2 or B 2 (pile letter + number of tokens)
- Automatically declares the winner

## 📷 Sample Output

Choose Game Mode:

Player vs Player

Player vs Computer

Enter number of tokens (min 5): 15

Initial Token Setup:

A: O O

B: O O O

C: O O

D: O O O O

E: O

Player1's turn (X), choose your move (e.g., B 2)... and so on.

## How to Compile and Run

Use any C++ compiler like g++:

```bash
g++ nim_game.cpp -o nim
./nim
