#pragma once
#include <ncurses.h>
#include<cstdlib> //rand(), srand()
#include<ctime> //time()

class Mission{
    //현재 나의 상태를 나타내는 변수들
    int b;
    int apple;
    int poison;
    int gate;
    bool game_clear;

    //목표
    int goalB;
    int goalApple;
    int goalPoison;
    int goalGate;

public : 
    //생성하면서 초기화해줍니다
    Mission():b(0), apple(0), poison(0), gate(0)
    {   
        //무작위로 목표를 설정합니다
        srand((unsigned int)time(NULL));
        goalB = rand() % 10 + 1;
        goalApple = rand() % 10 + 1;
        goalPoison = rand() % 10 + 1;
        goalGate = rand() % 5 + 1;
    }

    int getGoalB(){return goalB;}
    int getGoalApple(){return goalApple;}
    int getGoalPoison(){return goalPoison;}
    int getGoalGate(){return goalGate;}

    //apple과 poison 업데이트
    //이부분은 gate, b에 대하여 추가 수정 필요
    void updateGoalApple(int n)
    {
        apple = n;
    }

    void updateGoalPoison(int n)
    {
        poison = n;
    }

    //클리어 조건 확인
    bool isClear()
    {
        if(goalApple <= apple && goalPoison <= poison)
        {
            return true;
        }
        return false;
    }
};