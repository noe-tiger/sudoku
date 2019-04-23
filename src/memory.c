#include <stdlib.h>

#include "board.h"

void free_board(board_t *board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                free(board->cell[i][j].holder[k]);
            }
            free(board->cell[i][j].holder);
        }
        free(board->cell[i]);
    }
    free(board->cell);
    free(board);
}

char **new_cell() {
    char **tab;

    if (!(tab = malloc(sizeof(char *) * 3))) {
        return (NULL);
    }
    for (int i = 0; i < 3; i++) {
        if (!(tab[i] = malloc(sizeof(char) * 3))) {
            free(tab);
            return (NULL);
        }
        for (int j = 0; j < 3; j++) {
            tab[i][j] = 0;
        }
    }
    return (tab);
}

board_t *get_board() {
    board_t *board;

    if (!(board = malloc(sizeof(board_t))))
        return (NULL);
    if (!(board->cell = malloc(sizeof(cell_t *) * 3))) {
        free(board);
        return (NULL);
    }
    for (int i = 0; i < 3; i++) {
        if (!(board->cell[i] = malloc(sizeof(cell_t *) * 3))) {
            free(board->cell);
            free(board);
            return (NULL);
        }
        for (int j = 0; j < 3; j++) {
            if (!(board->cell[i][j].holder = new_cell())) {
                for (int x = 0; x <= i; x++) {
                    free(board->cell[x]);
                }
                free(board->cell);
                free(board);
                return (NULL);
            }
        }
    }
    return (board);
}
