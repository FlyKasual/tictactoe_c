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
#include <stdlib.h>
#include <stdio.h>
#include "customio.h"
#include "game.h"

int main(void) {
    enum player currentPlayer = X;
    enum player _game[SIZE] = {
        NONE, NONE, NONE,
        NONE, NONE, NONE,
        NONE, NONE, NONE
    };
    union gameState state = { ongoing };

    clrscr();
    printf(
        "\n\n"
        " * tictactoe_c  Copyright (C) 2023  Johannes Nielsen\n"
        " * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
        " * This is free software, and you are welcome to redistribute it\n"
        " * under certain conditions; type `show c' for details.\n\n"
    );
    printGame(_game);
    for (;state.state == ongoing; state = determineWinner(_game, currentPlayer), currentPlayer = 1 - currentPlayer) {
        printf("It's %c's turn\n", currentPlayer == X ? 'X' : 'O');
        int choice = getAndValidateUserInput(_game);
        _game[choice] = currentPlayer;
        clrscr();
        printGame(_game);
    }
    if (state.state == draw)
        printf("It's adraw!\n");
    else
        printf("%c has won!\n", state.winner == X ? 'X' : 'O');

    return EXIT_SUCCESS;
}
