#pragma once
#include <ncurses.h>

class Drawable{
public :
    Drawable(){
        y = x = 0;
        icon = ' ';
    }

    Drawable(int y, int x, chtype ch){
        this->y = y;
        this->x = x;
        this->icon = ch;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    chtype getIcon(){
        return icon;
    }

protected :
    int y, x;
    chtype icon;
};