#include <stdlib.h>
#include <stdio.h>

#define SIZE 9
#define COLUMNS 3

enum player {
    NONE = -1,
    X,
    O
};

union gameState {
    enum player winner;
    enum { draw = 2, ongoing } state;
};

typedef enum player* game;

void printGame(game);
void printRow(game, int);
int getAndValidateUserInput(game);
union gameState determineWinner(game, enum player);
void clrscr(void);

int main(void) {
    enum player currentPlayer = X;
    enum player _game[SIZE] = {
        NONE, NONE, NONE,
        NONE, NONE, NONE,
        NONE, NONE, NONE
    };
    union gameState state = { ongoing };

    printGame(_game);
    for (;state.state == ongoing; state = determineWinner(_game, currentPlayer), currentPlayer = 1 - currentPlayer) {
        printf("It's %c's turn\n", currentPlayer == X ? 'X' : 'O');
        int choice = getAndValidateUserInput(_game);
        _game[choice] = currentPlayer;
        printGame(_game);
    }
    if (state.state == draw)
        printf("It's adraw!\n");
    else
        printf("%c has won!\n", state.winner == X ? 'X' : 'O');

    return EXIT_SUCCESS;
}

void printGame(game _game) {
    clrscr();
    printRow(_game, 0);
    printf("–––+–––+–––\n");
    printRow(_game, 3);
    printf("–––+–––+–––\n");
    printRow(_game, 6);
}

void printRow(game _game, int startingPosition) {
    printf("   |   |   \n");
    for (int i = startingPosition; i < (startingPosition + COLUMNS); ++i) {
        if (_game[i] == NONE)
            printf(" %d ", (i + 1));
        else
            printf(" %c ", _game[i] == X ? 'X' : 'O');
        if (i % COLUMNS == (COLUMNS - 1))
            printf("\n");
        else
            printf("|");
    }
    printf("   |   |   \n");
}

int getAndValidateUserInput(game _game) {
    int _i = 0;
    printf("Select position: ");
    while(scanf("%d", &_i) != 1 || _i < 1 || _i > SIZE || _game[_i - 1] != NONE ) {
        printf("This is not a valid choice! Please try again: ");
        int tmp = '\0';
        while((tmp = getchar()) != '\n' && tmp != EOF);
    }
    return _i - 1;
}

union gameState determineWinner(game _game, enum player currentPlayer) {
    int numberOfFreeFields = 0;
    union gameState state = { ongoing };
    for (int i = 0; i < SIZE; ++i) {
        if (_game[i] == NONE)
            ++numberOfFreeFields;
    }
    if (numberOfFreeFields < 5) {   // If 5 or more fields are still unset, no player has made more than 2 moves
        if (
            (_game[0] == currentPlayer && _game[1] == currentPlayer && _game[2] == currentPlayer)       // First row
            || (_game[0] == currentPlayer && _game[3] == currentPlayer && _game[6] == currentPlayer)    // First column
            || (_game[6] == currentPlayer && _game[7] == currentPlayer && _game[8] == currentPlayer)    // Last row
            || (_game[2] == currentPlayer && _game[5] == currentPlayer && _game[8] == currentPlayer)    // Last column
        ) {
            state.winner = currentPlayer;
            return state;
        }
        if (_game[4] == currentPlayer) {    // Player has the center
            if (
                (_game[0] == currentPlayer && _game[8] == currentPlayer)        // Top left to bottom right diagonal
                || (_game[2] == currentPlayer && _game[6] == currentPlayer)     // Top right to bottom left diagonal
                || (_game[3] == currentPlayer && _game[5] == currentPlayer)     // Center row
                || (_game[1] == currentPlayer && _game[7] == currentPlayer)     // center column
            ) {
                state.winner = currentPlayer;
                return state;
            }
        }
    }
    if (numberOfFreeFields == 0)
        state.state = draw;
    return state;
}

void clrscr(void) {
    system("@cls||clear");
}
