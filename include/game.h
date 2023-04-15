#ifndef GAME_H_1681571070
#define GAME_H_1681571070

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
int getAndValidateUserInput(game);
union gameState determineWinner(game, enum player);

#endif
