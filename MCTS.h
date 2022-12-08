#pragma once

#include <iostream>
#include <vector>
#include "NoGo.h"
#include <Windows.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
//odd round is for black while even round is for white



struct Node
{
    std::vector<Node*> childNode;
    int value = 0;
    int n = 0;
    POINT Point;
};


POINT randomPoint(signed char** Board, int currentRound)
{
    signed int color = Round2Color(currentRound);
    POINT point = { 0, 0 };
    for (int i = 0; i < 50; i++)
    {
        point.x = rand() % BOARD_SIZE;
        point.y = rand() % BOARD_SIZE;

        if (Board[point.x][point.y] == BLANK && Check_Board(point.x, point.y, Board, color) != opposite_Color(color))
        {
            if(currentRound != 1 || (point.x != BOARD_SIZE / 2 && point.y != BOARD_SIZE / 2))
                return point;
        }
    }
    return { -1, -1 };
}

double UCB(int N, int n, int v)
{
    return (double)v / (n + 0.01) + 2 * sqrt(log(N + 1) / (n + 0.0001));
}

Node* Selection(Node* node, int N)
{
    
    int maxUCBOne = rand() % node->childNode.size();
    double maxUCB = UCB(N, node->childNode[maxUCBOne]->n, node->childNode[maxUCBOne]->value);
    for (int i = 0; i < node->childNode.size(); i++)
    {
        double currentUCB = UCB(N, node->childNode[i]->n, (node->childNode[i]->value));
        if (currentUCB > maxUCB)
        {
            maxUCB = currentUCB;
            maxUCBOne = i;
        }
    }
    return node->childNode[maxUCBOne];
}

void Expansion(Node* node, signed char** Board, int currentRound, signed int color)
{
    for (signed char i = 0; i < BOARD_SIZE; i++)
    {
        for (signed char j = 0; j < BOARD_SIZE; j++)
        {
            if (Board[i][j] == BLANK)
            {
                Node* newNode = new Node;
                newNode->Point.x = i;
                newNode->Point.y = j;
                signed int result = Check_Board(i, j, Board, Round2Color(currentRound));
                if (result == color)
                {
                    newNode->value += 1;
                }

                node->childNode.push_back(newNode);
            }
        }
    }
}

void RollOut(Node* node, signed char** Board, int currentRound, signed char color)
{
    Expansion(node, Board, currentRound, color);
    if (node->childNode.empty())
    {
        if (Round2Color(currentRound) != color)
            node->value = 1;
        return;
    }

    for (int i = 0; i < 100; i++) 
    {
        signed char** BoardCopy = Board_Copy(Board);

        signed char result = GAME_ON;
        int thisRound = currentRound;
        do {
            int ChosenOrder = rand() % node->childNode.size();
            POINT ChosenPoint = node->childNode[ChosenOrder]->Point;
            delete node->childNode[ChosenOrder];
            node->childNode.erase(node->childNode.begin() + ChosenOrder);

            result = board_Process(ChosenPoint.x, ChosenPoint.y, BoardCopy, Round2Color(thisRound));
            thisRound++;
        } while (result == GAME_ON);

        if (result == color)
            node->value += 1;

        free_Board(BoardCopy);
        for (int i = 0; i < node->childNode.size(); i++)
            delete node->childNode[i];

        node->childNode.shrink_to_fit();
        node->childNode.clear();
        Expansion(node, Board, currentRound, color);
    }
    for (int i = 0; i < node->childNode.size(); i++)
        delete node->childNode[i];
    node->childNode.clear();
}

int Node_Process(signed char** Board, int currentRound, signed char color, Node* CurrentNode, int* addressofN)
{
    if (CurrentNode->childNode.empty())
    {
        if (CurrentNode->n == 0)
        {
            (CurrentNode->n)++;
            (*addressofN)++;
            RollOut(CurrentNode, Board, currentRound, color);
            return CurrentNode->value;
        }
        else {
            Expansion(CurrentNode, Board, currentRound, color);
            return 0;
        }
    }
    else {
        Node* NodeSelected = Selection(CurrentNode, *addressofN);
        signed char** Copy = Board_Copy(Board);
        Copy[NodeSelected->Point.x][NodeSelected->Point.y] = Round2Color(currentRound);
        int valueAdded = Node_Process(Copy, currentRound + 1, color, NodeSelected, addressofN);
        CurrentNode->value += valueAdded;

        (CurrentNode->n)++;
        free_Board(Copy);

        return valueAdded;
    }
}

void deleteNode(Node* node)
{
    if (node->childNode.empty())
    {
        delete node;
    }
    else {
        int size = node->childNode.size();
        for (int i = 0; i < size; i++)
        {
            deleteNode(node->childNode[i]);
        }
        node->childNode.clear();
        node->childNode.shrink_to_fit();
        delete node;
    }
}

POINT MCTS_AI(signed char** Board, int currentRound)
{
    if (currentRound < 5)
    {
        POINT rdmpt = randomPoint(Board, Round2Color(currentRound));
        if (rdmpt.x != -1)
            return rdmpt;
    }

    Node* MainNode = new Node;
    int N = 0;
    signed int color = Round2Color(currentRound);
    Expansion(MainNode, Board, currentRound, color);
    for (int i = 0; i < 80; i++)
    {
        Node_Process(Board, currentRound, color, MainNode, &N);
    }

    for (int i = MainNode->childNode.size() - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (MainNode->childNode[j]->value < MainNode->childNode[j + 1]->value)
            {
                std::swap(MainNode->childNode[j], MainNode->childNode[j + 1]);
            }
        }
    }
    for (int i = 0; i < MainNode->childNode.size(); i++)
    {
        POINT point = MainNode->childNode[i]->Point;
        if (Check_Board(point.x, point.y, Board, color) != opposite_Color(color))
        {
            deleteNode(MainNode);
            return point;
        }
    }
    POINT point = MainNode->childNode[0]->Point;
    deleteNode(MainNode);
    return point;
}