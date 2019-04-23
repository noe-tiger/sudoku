#ifndef MEMORY_H_
# define MEMORY_H_

# include "board.h"

board_t *get_board();
void free_board(board_t *board);

#endif