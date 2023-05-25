#pragma once
#include <ncurses.h>
#include <queue>
#include "Drawable.hpp"

enum Direction
{
    up = 1,
    down = -1,
    left = 2,
    right = -2,
    f = 0
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->x = this-> y = 0;
        this->icon = '#';
    }
    SnakePiece(int y, int x)
    {
        this->x = x;
        this->y = y;
        this->icon = '#';
    }
};

class Snake 
{   
    //큐를 이용하여 이전 피스들을 저장합니다
    std::queue<SnakePiece> prev_pieces;
    //현재 이동할 디렉션
    Direction cur_direction;

public: 
    static int length;

    Snake()
    {
        cur_direction = down;
    }

    void addPiece(SnakePiece piece)
    {
        prev_pieces.push(piece);
    }

    void removePiece()
    {
        prev_pieces.pop();
    }

    //이전 피스들을 모아놓은 큐(FIFO)의 제일 앞부분이 꼬리가 됩니다
    SnakePiece tail()
    {
        return prev_pieces.front();
    }

    //이전 피스들을 모아놓은 큐의 제일 끝이 머리가 됩니다
    SnakePiece head()
    {
        return prev_pieces.back();
    }

    Direction getDirection()
    {
        return cur_direction;
    }

    void setDirection(Direction d){
        //현재 디렉션과 앞으로 설정할(갈) 디렉션의 합이 0이면 내 진행방향과 바로 반대의 방향으로 간다는 뜻입니다(ex.왼쪽으로 가고 있는데 오른쪽으로 진행하려고 함)
        //0이 아니면 진행시키고
        if (cur_direction + d != 0){
        cur_direction = d;}

        //0이면 f를 설정해줍니다. 이건 handleNextPiece(snakeGame)에서 게임오버가 될 것입니다..
        else{
            cur_direction = f;
        }
    }

    SnakePiece nextHead()
    {
        int row = head().getY();
        int col = head().getX();

        switch(cur_direction)
        {
            case down:
                row++;
                break;
            case up:
                row--;
                break;
            case left:
                col--;
                break;
            case right:
                col++;
                break;
        }
        return SnakePiece(row,col);
    }
};

int Snake :: length = 4;
