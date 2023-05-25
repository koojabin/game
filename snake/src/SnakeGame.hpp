#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "Apple.hpp"
#include "Poison.hpp"
#include "Empty.hpp"
#include "Board.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"
#include "Scoreboard.hpp"
#include "Mission.hpp"
#include "Missionboard.hpp"


class SnakeGame
{
    //보드
    Board board;
    Missionboard missionboard;
    Scoreboard scoreboard;
    //게임의 상태
    bool game_over;
    bool game_clear;
    //아이템
    Apple *apple;
    Poison *poison;
    //뱀
    Snake snake;
    //미션
    Mission mission;

    //미션 달성을 위한 아이들
    int appleItem;
    int poisonItem;
    int appleCount;
    int poisonCount;
    int timeCount;
    int b;

    //Apple 생성 메소드
    void createApple()
    {
        int y, x;
        //보드의 y,x에서 빈 곳을 찾아 apple 포인터를 add해줌
        board.getEmptyCoordinates(y,x);
        apple = new Apple(y,x);
        board.add(*apple);
        appleCount = 0;
    }

    //poison생성 메소드.. 위의 apple 메소드와 동일한 logic
    void createPoison()
    {
        int y, x;
        board.getEmptyCoordinates(y,x);
        poison = new Poison(y,x);
        board.add(*poison); 
        poisonCount = 0;
    }

    //다음에 이동할 위치가 apple인지 poison인지 빈칸인지 벽인지 판단하는 메소드
    void handleNextPiece(SnakePiece next)
    {   
        if (apple != NULL && poison != NULL){
            //보드에서 다음에 이동할 위치 확인
            switch (board.getChatAt(next.getY(), next.getX())){
                case 'A' :
                    eatApple();
                    break;
                case ' ':
                {
                    pass();
                    break;
                }
                case 'P' :
                {
                    eatPoison();
                    break;
                }
                //벽
                default :
                    game_over = true;
                    break;
            }
        }

        board.add(next);
        snake.addPiece(next);
    }

    void eatApple()
    {
        //애플 포인터 해제, 애플 아이템(미션) 증가, 스네이크 길이 증가, 애플 카운트(리셋) 0으로 초기화 
        delete apple;
        appleItem++;
        snake.length++;
        appleCount = 0;
        //미션 업데이트, 스코어보드 업데이트
        mission.updateGoalApple(appleItem);
        scoreboard.updateScore(timeCount, b, appleItem,poisonItem);
        //다시 애플 생성
        createApple();
    }

    void eatPoison()
    {
        //잘은 모르겠지만 작동은 하는 코드.. 꼬리 삭제
        int emptyRow1 = snake.tail().getY();
        int emptyCol1 = snake.tail().getX();
        board.add(Empty(emptyRow1, emptyCol1));
        snake.removePiece();
        int emptyRow = snake.tail().getY();
        int emptyCol = snake.tail().getX();
        board.add(Empty(emptyRow, emptyCol));
        snake.removePiece();

        //eatApple과 동일
        delete poison;
        poisonItem++;
        snake.length--;
        poisonCount = 0;
        mission.updateGoalPoison(poisonItem);
        scoreboard.updateScore(timeCount, b, appleItem, poisonItem);
        createPoison();
    }

    void pass()
    {
        //이것도 작동하더군요..
        int emptyRow = snake.tail().getY();
        int emptyCol = snake.tail().getX();
        board.add(Empty(emptyRow, emptyCol));
        snake.removePiece();
        scoreboard.updateScore(timeCount, b, appleItem, poisonItem);
    }

public:
    
    SnakeGame(int height, int width, int speed = 300)
    {
        //보드들 초기화
        board = Board(height, width,speed);
        int sb_row = board.getStartRow();
        int sb_col = board.getStartCol() + width + 3;
        scoreboard = Scoreboard(sb_row, sb_col);
        missionboard = Missionboard(sb_row+8, sb_col);
        initialize();
    }

    //동적할당 해제해주는 소멸자
    ~SnakeGame()
    {
        delete apple;
        delete poison;
    }

    //초기화 메소드..
    void initialize()
    {
        apple = NULL;
        poison = NULL;
        board.initialize();
        appleItem = 0;
        poisonItem = 0;
        timeCount = 0;
        b = 0;
        missionboard.initialize(mission.getGoalB(), mission.getGoalApple(), mission.getGoalPoison(), mission.getGoalGate());
        scoreboard.initialize();
        game_over = false;
        game_clear = false;

        //맨 처음에 스네이크는 아래로 두번 갔다가 오른쪽으로 꺾습니다
        snake.setDirection(down);

        handleNextPiece(SnakePiece(1,1));
        handleNextPiece(snake.nextHead());
        handleNextPiece(snake.nextHead());
        snake.setDirection(right);
        handleNextPiece(snake.nextHead());

        if (apple == NULL){
            createApple(); 
        }

        if (poison == NULL){
            createPoison();
        }
    }

    //키보드 인풋을 받아옵니다
    void processInput()
    {
        chtype input = board.getInput();
        switch(input)
        {   //화살표, wasd 두 표현 모두 작동
            case KEY_UP:
            case 'w':
                snake.setDirection(up);
                break;
            case KEY_DOWN:
            case 's':
                snake.setDirection(down);
                break;
            case KEY_RIGHT:
            case 'd':
                snake.setDirection(right);
                break;
            case KEY_LEFT:
            case 'a':
                snake.setDirection(left);
                break;
            //p를 누르면 pause
            case 'p' :
                board.setTimeout(-1);
                while(board.getInput() != 'p'){}
                board.setTimeout(1000);
                break;
            default:
                break;
        }
    }

    //state를 업데이트해주는 메소드
    void updateState()
    {   
        //어디로 움직일지 (ex. 내가 마지막으로 down을 눌렀으면 나는 계속 down으로 가는 것)
        handleNextPiece(snake.nextHead());

        //apple과 poison을 일정시간이 되면 초기화
        if (appleCount >= 30){
            board.addAt(apple->getY(),apple->getX(),' ');
            delete apple;
            createApple(); 
        }

        if (poisonCount >= 30){
            board.addAt(poison->getY(),poison->getX(),' ');
            delete poison;
            createPoison();
        }

        //몸의 길이가 3 미만이면 게임 오버
        if (snake.length < 3){
            game_over = true;
        }

        //미션을 모두 클리어하면 게임 클리어
        if(mission.isClear())
        {
            game_clear = true;
        }

        //시간의 경과(반복의 경과)를 표현합니다
        appleCount++;
        poisonCount++;
        timeCount++;

    }

    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

    bool isClear()
    {
        return game_clear;
    }
};