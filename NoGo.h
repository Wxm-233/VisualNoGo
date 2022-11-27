#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 9


#define BLACK       0x1
#define WHITE       0x2
#define BLANK       0x4


#define BLACK_WIN   0x1
#define WHITE_WIN   0x2
#define GAME_ON     0x4
#define UNDEFINED   0x8
//BLACK_WIN == BLACK
//WHITE_WIN == WHITE

signed char**   noGo_Initialize();
void            free_Board(signed char** Board);
void            clear_Board(signed char** Board);
signed char     opposite_Color(signed char color);
signed char     board_Process(signed char x, signed char y, signed char** Board, signed char color);
bool            qi_Search(signed char x, signed char y, signed char** Board, unsigned int* searchMap, signed char color);

signed char** noGo_Initialize()
{
    signed char** Board = (signed char**)malloc(BOARD_SIZE * sizeof(signed char*));
    if (Board == NULL)
        return NULL;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        Board[i] = (signed char*)malloc(BOARD_SIZE * sizeof(signed char));
        if (Board[i] == NULL)
            return NULL;

        memset(Board[i], BLANK, BOARD_SIZE * sizeof(signed char));
    }

    return Board;
}

void clear_Board(signed char** Board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
        memset(Board[i], BLANK, BOARD_SIZE * sizeof(signed char));
}

void free_Board(signed char** Board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
        free(Board[i]);

    free(Board);
}

signed char opposite_Color(signed char color)
{
    switch (color)
    {
    case BLACK:return WHITE;
    case WHITE:return BLACK;
    default: return UNDEFINED;
    }
}

signed char board_Process(signed char x, signed char y, signed char** Board, signed char color)
{
    unsigned int* searchMap = (unsigned int*)malloc(BOARD_SIZE * sizeof(unsigned int));

    Board[x][y] = color;

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (!qi_Search(x, y, Board, searchMap, color))                                                                                           return opposite_Color(color);//OPPOSITE_COLOR_WIN

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (x - 1 >= 0 && Board[x - 1][y] == opposite_Color(color) && !qi_Search(x - 1, y, Board, searchMap, opposite_Color(color)))          return opposite_Color(color);

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (x + 1 < BOARD_SIZE && Board[x + 1][y] == opposite_Color(color) && !qi_Search(x + 1, y, Board, searchMap, opposite_Color(color)))          return opposite_Color(color);

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (y - 1 >= 0 && Board[x][y - 1] == opposite_Color(color) && !qi_Search(x, y - 1, Board, searchMap, opposite_Color(color)))          return opposite_Color(color);

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (y + 1 < BOARD_SIZE && Board[x][y + 1] == opposite_Color(color) && !qi_Search(x, y + 1, Board, searchMap, opposite_Color(color)))          return opposite_Color(color);

    return GAME_ON;
}

bool qi_Search(signed char x, signed char y, signed char** Board, unsigned int* searchMap, signed char color)
{
    if (searchMap[x] & 1 << y)
        return false;

    searchMap[x] |= 1 << y;

    bool qi = false;

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return false;

    if (Board[x][y] == opposite_Color(color))
        return false;

    if (Board[x][y] == BLANK)
        return true;

    qi += qi_Search(x - 1, y, Board, searchMap, color);
    qi += qi_Search(x + 1, y, Board, searchMap, color);
    qi += qi_Search(x, y - 1, Board, searchMap, color);
    qi += qi_Search(x, y + 1, Board, searchMap, color);

    return qi;
}