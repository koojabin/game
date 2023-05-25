#include <ncurses.h>
#include <iostream>
#include "SnakeGame.hpp"
#include "Board.hpp"
#include "Drawable.hpp"


#define BOARD_DIM 15
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM *  2.5

int main(int argc, char **agrv){

    initscr();
    refresh();
    noecho();
    curs_set(0);
    
    //+맵3개를 어떻게 구현할지 생각이 필요함
    //게임 시작 전 화면, 게임 오버 후 화면 gui 구현하면 좋을듯
    SnakeGame game(BOARD_ROWS,BOARD_COLS);

    while(!game.isOver()){
        
        game.processInput();

        game.updateState();

        game.redraw();

        if (game.isClear()){
            break;
        }
    }

    endwin();
    if (game.isOver()) std::cout << "Gameover" << std::endl;
    else if (game.isClear()) std::cout << "Game clear" << std::endl;


    return 0;

} 