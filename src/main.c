#include "board.h"
#include "game.h"
#include "memory.h"

int main() {
    board_t *board = get_board();
    set_board(board);
    free_board(board);
    return 0;
}