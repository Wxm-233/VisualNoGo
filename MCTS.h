#include <iostream>
#include <queue>
#include "NoGo.h"
#include <Windows.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>


POINT randomPoint();
bool isVaildPoint(int x, int y, signed char** Board);

struct Node
{
    std::queue<Node*> childNode;
    int value;
    int n;
};


POINT randomPoint()
{
    POINT point = {0, 0};
    point.x = rand() % BOARD_SIZE;
    point.y = rand() % BOARD_SIZE;
    return point;
}


bool isVaildPoint(signed char x, signed char y, signed char** Board)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && Board[x][y] == BLANK && ;
}

double UCB(int N, int n, double v)
{
    return v / n + 2 * sqrt(log(N) / n);
}

bool isLeafNode(Node *node)
{
    return node->childNode.empty();
}

Node* Selection(Node *node, int N)
{
    int maxUCB = 0;
    int maxValueOne = 0;
    for (int i = 0; i < node->childNode.size(); i++)
    {
        int currentUCB = UCB(N, node->childNode[i]->n, node->childNode[i]->value);
        if (currentUCB > maxUCB)
        {
            maxUCB = currentUCB;
            maxValueOne = i;
        }
    }
    return node->childNode[i];
}

void Expansion(Node *node, int* addressofN, signed char** Board)
{
    for (signed char i = 0; i < BOARD_SIZE; i++)
    {
        for (signed char j = 0; j < BOARD_SIZE; j++)
        {
            if (Board[i][j] == BLANK)
            {
                Node* newNode = new(sizeof(Node));
                newNode->n = 0;
                newNode->value = 0;
                node->childNode.push(newNode);
                (node->n)++;
                (*addressofN)++;
            }
        }
    }
}

void RollOut(Node *node, signed char** Board, int currentRound, signed int color)
{
    signed char** BoardCopy = noGo_Initialize();
    for (signed char i = 0; i < BOARD_SIZE; i++)
        for (signed char j = 0; j < BOARD_SIZE; j++)
            BoardCopy[i][j] = Board[i][j];
    
    signed int result = GAME_ON;
    do{
        POINT rdmpt = randomPoint();
        if (currentRound % 2)
            result = board_Process(rdmpt.x, rdmpt.y, BoardCopy, BLACK);
        else result = board_Process(rdmpt.x, rdmpt.y, BoardCopy, WHITE);
    }while (result == GAME_ON);

    if (result == color)
        node->value = 2;
    else node->value = 1;

    free_Board(BoardCopy);
}

POINT MCTS_AI(signed char** Board, int currentRound, signed char color)
{
    Node* MainNode = new(sizeof(Node));
    MainNode->n = 0;
    MainNode->value = 0;
    Node* CurrentNode = MainNode;
    int N = 0;
    for(int i = 0; i < 100; i++)
    {
        if (CurrentNode->childNode.empty())
        {
            if (CurrentNode->n == 0)
            {
                RollOut(CurrentNode, Board, currentRound, color);
            }
            else {
                Expansion(CurrentNode, &N, Board);
                CurrentNode = CurrentNode->childNode[0];
            }
        }
        else {
            CurrentNode = Selection(CurrentNode, N);
        }
    }
}