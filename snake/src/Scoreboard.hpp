#pragma once
#include <ncurses.h>

//스코어보드는 스코어를 표현하는 윈도우를 표현
class Scoreboard
{
    WINDOW *score_win;
public : 
    Scoreboard()
    {

    }

    Scoreboard(int y, int x)
    {   
        score_win = newwin(8, 20, y, x);
    }

    void initialize()
    {
        clear();
        box(score_win, 0, 0);
        updateScore(0, 0, 0, 0);
        refresh();
    }

   void updateScore(int gametime, int b, int apple, int poison)
    {
        mvwprintw(score_win, 1, 5, "Score Board");
        mvwprintw(score_win, 2, 5, "Game Time: %i", gametime);
        mvwprintw(score_win, 3, 5, "B: %i" ,b); 
        mvwprintw(score_win, 4, 5, "+: %i ", apple); 
        mvwprintw(score_win, 5, 5, "-: %i ", poison);
        mvwprintw(score_win, 6, 5, "G: "); // gate구현시 이부분 수정
        refresh();
    }

    void clear()
    {
        wclear(score_win);
    }

    void refresh()
    {
        wrefresh(score_win);
    }
};