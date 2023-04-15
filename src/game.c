/**
 * tictactoe_c
 * Copyright (C) 2023  Johannes Nielsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "customio.h"

static void printRow(game, int);

void printGame(game _game) {
    printRow(_game, 0);
    printf("–––+–––+–––\n");
    printRow(_game, 3);
    printf("–––+–––+–––\n");
    printRow(_game, 6);
}

static void printRow(game _game, int startingPosition) {
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
    int _tmp = -1;
    char command[7] = "";
    printf("Select position: ");
    while((_tmp = scanf("%d", &_i)) != 1 || _i < 1 || _i > SIZE || _game[_i - 1] != NONE) {
        if (_tmp != 1) {
            getCharacters(command, 6);
        }
        if (strcmp(command, "show w") == 0 || strcmp(command, "show c") == 0) {
            clrscr();
            switch(command[5]) {
                case 'w':
                    printf(
                        " * tictactoe_c\n"
                        " * Copyright (C) 2023  Johannes Nielsen\n\n"
                        " * This program is distributed in the hope that it will be useful,\n"
                        " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                        " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                        " * GNU General Public License for more details.\n"
                    );
                    break;
                case 'c':
                    printf(
                        " * tictactoe_c\n"
                        " * Copyright (C) 2023  Johannes Nielsen\n\n"
                        " * This program is free software: you can redistribute it and/or modify\n"
                        " * it under the terms of the GNU General Public License as published by\n"
                        " * the Free Software Foundation, either version 3 of the License, or\n"
                        " * (at your option) any later version.\n"
                    );
                    break;
            }
            clearInput();
            printGame(_game);
            return getAndValidateUserInput(_game);
        } else {
            printf("This is not a valid choice! Please try again: ");
            clearInput();
        }
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
