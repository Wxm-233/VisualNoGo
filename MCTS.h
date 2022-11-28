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
    for(int i = 0; i < node->childNode.size(); i++)
    {
        int currentUCB = UCB(N, node->childNode[i]->n, node->childNode[i]->value);
        if(currentUCB > maxUCB)
        {
            maxUCB = currentUCB;
            maxValueOne = i;
        }
    }
    return node->childNode[i];
}

void Expansion(Node *node, int* addressofN, signed char** Board)
{
    for(signed char i = 0; i < BOARD_SIZE; i++)
    {
        for(signed char j = 0; j < BOARD_SIZE; j++)
        {
            if(Board[i][j] == BLANK)
            {
                Node* newNode = new(sizeof(Node));
                newNode->n = 0;
                newNode->value = 0;
                node->childNode.push(newNode);
                (node->n)++;
            }
        }
    }
}

int RollOut(Node *node)
{
    int value;
    
    return value;
}