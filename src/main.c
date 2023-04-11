#include <stdlib.h>
#include <stdio.h>

#define SIZE 9
#define COLUMNS 3

enum player {
    NONE = -1,
    X,
    O,
    draw
};

typedef enum player* game;

void printGame(game);
void printRow(game, int);
int getAndValidateUserInput(game);
enum player determineWinner(game, enum player);

int main(void) {
    enum player currentPlayer = X;
    enum player _game[SIZE] = {
        NONE, NONE, NONE,
        NONE, NONE, NONE,
        NONE, NONE, NONE
    };
    enum player gameState = NONE;

    printGame(_game);
    for (;gameState == NONE; gameState = determineWinner(_game, currentPlayer), currentPlayer = 1 - currentPlayer) {
        printf("It's %c's turn\n", currentPlayer == X ? 'X' : 'O');
        int choice = getAndValidateUserInput(_game);
        _game[choice] = currentPlayer;
        printGame(_game);
    }
    if (gameState == draw)
        printf("It's adraw!\n");
    else
        printf("%c has won!\n", gameState == X ? 'X' : 'O');
    return EXIT_SUCCESS;
}

void printGame(game _game) {
    printf("   |   |   \n");
    printRow(_game, 0);
    printf("   |   |   \n");
    printf("–––+–––+–––\n");
    printf("   |   |   \n");
    printRow(_game, 3);
    printf("   |   |   \n");
    printf("–––+–––+–––\n");
    printf("   |   |   \n");
    printRow(_game, 6);
    printf("   |   |   \n");
}

void printRow(game _game, int startingPosition) {
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
}

int getAndValidateUserInput(game _game) {
    int _i = 0;
    printf("Select position: ");
    while(scanf("%d", &_i) != 1 || _i < 1 || _i > 9 || _game[_i - 1] != NONE ) {
        printf("This is not a valid choice! Please try again: ");
        int tmp = '\0';
        while((tmp = getchar()) != '\n' && tmp != EOF);
    }
    return _i - 1;
}

enum player determineWinner(game _game, enum player currentPlayer) {
    int numberOfFreeFields = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (_game[i] == NONE)
            ++numberOfFreeFields;
    }
    if (numberOfFreeFields < 5) {
        if (_game[0] == currentPlayer && _game[1] == currentPlayer && _game[2] == currentPlayer)
            return currentPlayer;
        if (_game[0] == currentPlayer && _game[3] == currentPlayer && _game[6] == currentPlayer)
            return currentPlayer;
        if (_game[6] == currentPlayer && _game[7] == currentPlayer && _game[8] == currentPlayer)
            return currentPlayer;
        if (_game[2] == currentPlayer && _game[5] == currentPlayer && _game[8] == currentPlayer)
            return currentPlayer;
        if (_game[4] == currentPlayer) {
            if (
                (_game[0] == currentPlayer && _game[8] == currentPlayer)
                || (_game[2] == currentPlayer && _game[6] == currentPlayer)
                || (_game[3] == currentPlayer && _game[5] == currentPlayer)
                || (_game[1] == currentPlayer && _game[7] == currentPlayer)
            ) {
                return currentPlayer;
            }
        }
    }
    return numberOfFreeFields == 0 ? draw : NONE;
}
