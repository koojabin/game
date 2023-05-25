#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Board
{
public:
    Board()
    {
        construct(0,0,300);
    }

    // Board 클래스의 생성자
    Board(int height, int width, int speed)
    {
        construct(height, width, speed);
    }

    void add(Drawable drawable)
    {
        addAt(drawable.getY(),drawable.getX(),drawable.getIcon());
    }

    // 특정 좌표에 문자 추가
    void addAt(int y, int x, chtype ch)
    {
        mvwaddch(board_win, y, x, ch);
    }

    // 사용자 입력 반환
    chtype getInput()
    {
        return wgetch(board_win);
    }

    chtype getChatAt(int y, int x)
    {
        return mvwinch(board_win, y, x);
    }

    // 보드를 초기화
    void initialize()
    {
        clear();
        refresh();
    }

    // 보드 주위에 경계 추가
    void addBorder()
    {
        //box(board_win, 0, 0);
        wborder(board_win, '1', '1', '1', '1', '2', '2', '2', '2');
    }

    void getEmptyCoordinates(int& y, int& x)
    {
        while(mvwinch(board_win, y = rand() % height, x = rand() % width) != ' ');
    }

    // 보드 지우기
    void clear()
    {
        wclear(board_win);
        addBorder();
    }


    // 보드 갱신
    void refresh()
    {
        wrefresh(board_win);
    }

    void setTimeout(int timeout){
        wtimeout(board_win, timeout);
    }

    int getStartRow(){
        return start_row;
    }

    int getStartCol(){
        return start_col;
    }
    
private:
    WINDOW *board_win; // 보드를 나타내는 윈도우 포인터
    int height, width, start_row, start_col;

    void construct(int height, int width, int speed)
    {
        // 터미널의 가로 세로 크기
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;
        start_row = (yMax / 2) - (height / 2);
        start_col =  (xMax / 2) - (width / 2);

        // 보드 윈도우를 생성, 중앙에 배치
        board_win = newwin(height, width, start_row, start_col);
        setTimeout(speed);
        keypad(board_win, true);
    }
};