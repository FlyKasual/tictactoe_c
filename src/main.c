#include <stdlib.h>
#include <stdio.h>

#define SIZE 9

enum player {
    NONE = -1,
    X,
    O
};

typedef enum player* game;

void printGame(game);
int getAndValidateUserInput(game);

int main(void) {
    enum player currentPlayer = X;
    enum player _game[SIZE] = {
        NONE, NONE, NONE,
        NONE, NONE, NONE,
        NONE, NONE, NONE
    };

    printGame(_game);

    int choice = getAndValidateUserInput(_game);
    _game[choice] = currentPlayer;
    currentPlayer = 1 - currentPlayer;
    return EXIT_SUCCESS;
}

void printGame(game _game) {
    int i = 0;
    printf("   \u2502   \u2502   \n");
    for (; i < SIZE / 3; ++i) {
        if (_game[i] == NONE)
            printf(" %d ", i + 1);
        else
            printf(" %c ", _game[i] == X ? 'X' : 'O');
        if (i % 3 == 2)
            printf("\n");
        else
            printf("\u2502");
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
    return _i;
}
