#ifndef BOARD_H_
# define BOARD_H_

typedef struct cell_s
{
    char **holder;
} cell_t;

typedef struct board_s
{
    cell_t **cell;
} board_t;

#endif