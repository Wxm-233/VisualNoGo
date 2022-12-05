#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 9


#define BLACK_PIECE         'B'
#define WHITE_PIECE         'W'
#define BLANK               '~'


#define BLACK_WIN   'B'
#define WHITE_WIN   'W'
#define GAME_ON     '~'
#define UNDEFINED   NULL
//BLACK_WIN == BLACK_PIECE
//WHITE_WIN == WHITE_PIECE

signed char**   noGo_Initialize();
void            free_Board(signed char** Board);
void            clear_Board(signed char** Board);
signed char     opposite_Color(signed char color);
signed char     board_Process(signed char x, signed char y, signed char** Board, signed char color);
bool            qi_Search(signed char x, signed char y, signed char** Board, unsigned int* searchMap, signed char color);
signed char**   Board_Copy(signed char** Board);
signed char     Round2Color(int round);
signed char     Check_Board(signed char x, signed char y, signed char** Board, signed char color);

signed char** noGo_Initialize()
{
    signed char** Board = (signed char**)malloc(BOARD_SIZE * sizeof(signed char*));
    if (Board == NULL)
        return NULL;

    signed char* Area = (signed char*)malloc(BOARD_SIZE * BOARD_SIZE * sizeof(signed char));
    if (Area == NULL)
        return NULL;

    memset(Area, BLANK, BOARD_SIZE * BOARD_SIZE * sizeof(signed char));

    for (int i = 0; i < BOARD_SIZE; i++)
        Board[i] = Area + i * BOARD_SIZE;

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
    case BLACK_PIECE:return WHITE_PIECE;
    case WHITE_PIECE:return BLACK_PIECE;
    default: return UNDEFINED;
    }
}

signed char Check_Board(signed char x, signed char y, signed char** Board, signed char color)
{
    signed int result = board_Process(x, y, Board, color);
    Board[x][y] = BLANK;
    return result;
}

signed char board_Process(signed char x, signed char y, signed char** Board, signed char color)
{
    Board[x][y] = color;

    unsigned int* searchMap = NULL;

    do {
        searchMap = (unsigned int*)malloc(BOARD_SIZE * sizeof(unsigned int));
    } while (searchMap == NULL);

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (!qi_Search(x, y, Board, searchMap, color))
    {
        free(searchMap);
        return opposite_Color(color);//OPPOSITE_COLOR_WIN
    }

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (x - 1 >= 0 && Board[x - 1][y] == opposite_Color(color) && !qi_Search(x - 1, y, Board, searchMap, opposite_Color(color)))          
    {
        free(searchMap);
        return opposite_Color(color);
    }

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (x + 1 < BOARD_SIZE && Board[x + 1][y] == opposite_Color(color) && !qi_Search(x + 1, y, Board, searchMap, opposite_Color(color)))          
    {
        free(searchMap);
        return opposite_Color(color);
    }

    memset(searchMap, 0 , BOARD_SIZE * sizeof(unsigned int));
    if (y - 1 >= 0 && Board[x][y - 1] == opposite_Color(color) && !qi_Search(x, y - 1, Board, searchMap, opposite_Color(color)))          
    {
        free(searchMap);
        return opposite_Color(color);
    }

    memset(searchMap, 0, BOARD_SIZE * sizeof(unsigned int));
    if (y + 1 < BOARD_SIZE && Board[x][y + 1] == opposite_Color(color) && !qi_Search(x, y + 1, Board, searchMap, opposite_Color(color)))          
    {
        free(searchMap);
        return opposite_Color(color);
    }

    free(searchMap);
    return GAME_ON;
}

bool qi_Search(signed char x, signed char y, signed char** Board, unsigned int* searchMap, signed char color)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return false;

    if (searchMap[x] & 1 << y)
        return false;

    searchMap[x] |= 1 << y;

    if (Board[x][y] == opposite_Color(color))
        return false;

    if (Board[x][y] == BLANK)
        return true;

    bool qi = false;

    qi += qi_Search(x - 1, y, Board, searchMap, color);
    qi += qi_Search(x + 1, y, Board, searchMap, color);
    qi += qi_Search(x, y - 1, Board, searchMap, color);
    qi += qi_Search(x, y + 1, Board, searchMap, color);

    return qi;
}

signed char** Board_Copy(signed char** Board)
{
    signed char** Copy = noGo_Initialize();
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Copy[i][j] = Board[i][j];
        }
    }
    return Copy;
}

signed char Round2Color(int round)
{
    if (round % 2)
        return BLACK_PIECE;
    else return WHITE_PIECE;
}