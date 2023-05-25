#pragma once
#include <ncurses.h>

//미션을 표시할 윈도우 클래스
class Missionboard
{
    WINDOW *mission_win;
public : 
    Missionboard()
    {

    }

    Missionboard(int y, int x)
    {
        mission_win = newwin(7, 20, y, x);
    }

   void initialize(int goalB, int goalApple, int goalPoison, int goalGate)
    {
        clear();
        box(mission_win, 0, 0);
        mvwprintw(mission_win, 1, 5, "Mission");
        mvwprintw(mission_win, 2, 5, "B: %i", goalB);
        mvwprintw(mission_win, 3, 5, "+: %i", goalApple);
        mvwprintw(mission_win, 4, 5, "-: %i", goalPoison);
        mvwprintw(mission_win, 5, 5, "Gate: %i", goalGate);
        refresh();
    }

    //미션을 만족했을 시 목표 달성 여부를 어떻게 표시할지 구현해야 함

    void clear()
    {
        wclear(mission_win);
    }

    void refresh()
    {
        wrefresh(mission_win);
    }
};