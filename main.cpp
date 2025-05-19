#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
using namespace std;

// Simple random number generator (very basic)
int simpleRand(int max) {
    static unsigned long seed = time(0);
    seed = (8253729 * seed + 2396403);  // Linear congruential generator
    return seed % max;
}

// Manual uppercase conversion
char toUpperManual(char ch) {
    if (ch >= 'a' && ch <= 'z')
        return ch - ('a' - 'A');
    return ch;
}

// Display piles
void displayPiles(const int piles[], int size) {
    char label = 'A';
    for (int i = 0; i < size; ++i) {
        cout << label++ << ": ";
        for (int j = 0; j < piles[i]; ++j)
            cout << "O ";
        cout << endl;
    }
}

// Check if game is over
bool isGameOver(const int piles[], int size) {
    for (int i = 0; i < size; ++i) {
        if (piles[i] > 0)
            return false;
    }
    return true;
}

// User turn
void userTurn(string playerName, int piles[], int size) {
    displayPiles(piles, size);
    cout << playerName << "'s turn (e.g., A2 or B 1): ";
    char pileChar;
    int count;
    cin >> pileChar >> count;

    int pileIndex = toUpperManual(pileChar) - 'A';

    if (pileIndex < 0 || pileIndex >= size || (count != 1 && count != 2) || piles[pileIndex] < count) {
        cout << "Invalid move. Try again.\n";
        userTurn(playerName, piles, size);
    } else {
        piles[pileIndex] -= count;
    }
}

// Simple PC logic
void pcTurn(int piles[], int size) {
    cout << "Computer's turn:\n";
    for (int i = 0; i < size; ++i) {
        if (piles[i] >= 1) {
            int take = (piles[i] >= 2) ? 2 : 1;
            piles[i] -= take;
            char pileChar = 'A' + i;
            cout << "Computer took " << take << " from pile " << pileChar << "\n";
            break;
        }
    }
}

// Distribution function
int calculateTokens(int i) {
    double exponent = -1.0 * ((i - 5) * (i - 5)) / 10.89;
    return static_cast<int>(10 * exp(exponent));
}

// Initialize piles
void initializePiles(int piles[], int size, int totalTokens, bool useFunction) {
    int assigned = 0;

    if (useFunction) {
        for (int i = 0; i < size; ++i) {
            piles[i] = calculateTokens(i + 1);
            assigned += piles[i];
        }
        while (assigned < totalTokens) {
            int r = simpleRand(size);
            piles[r]++;
            assigned++;
        }
    } else {
        for (int i = 0; i < size; ++i) {
            piles[i] = 1;
            assigned++;
        }
        while (assigned < totalTokens) {
            int r = simpleRand(size);
            piles[r]++;
            assigned++;
        }
    }
}

// Recursive gameplay
void playGameRecursively(string player1, string player2, int piles[], int size, bool vsComputer, bool turn = true) {
    if (isGameOver(piles, size)) {
        cout << (turn ? player2 : player1) << " wins!\n";
        return;
    }

    if (turn) {
        userTurn(player1, piles, size);
    } else {
        if (vsComputer)
            pcTurn(piles, size);
        else
            userTurn(player2, piles, size);
    }

    playGameRecursively(player1, player2, piles, size, vsComputer, !turn);
}

// Main game logic
void playNimGame() {
    int mode;
    cout << "Select mode:\n1. User vs User\n2. User vs Computer\n> ";
    cin >> mode;

    string player1, player2 = "Computer";
    cout << "Enter Player 1 name: ";
    cin >> player1;

    bool vsComputer = (mode == 2);
    int heaps = vsComputer ? 0 : 5;
    int totalTokens;

    if (vsComputer) {
        cout << "Enter number of heaps (2-10): ";
        cin >> heaps;
        while (heaps < 2 || heaps > 10) {
            cout << "Invalid. Enter between 2 and 10: ";
            cin >> heaps;
        }
        cout << "Enter total number of tokens: ";
        cin >> totalTokens;
        while (totalTokens < heaps) {
            cout << "Must be >= number of heaps. Try again: ";
            cin >> totalTokens;
        }
    } else {
        cout << "Enter Player 2 name: ";
        cin >> player2;
        cout << "Enter total number of tokens (>=5): ";
        cin >> totalTokens;
        while (totalTokens < 5) {
            cout << "Try again. Must be >= 5: ";
            cin >> totalTokens;
        }
    }

    int piles[10];
    initializePiles(piles, heaps, totalTokens, vsComputer);
    playGameRecursively(player1, player2, piles, heaps, vsComputer);
}

// Main
int main() {
    playNimGame();
    return 0;
}

