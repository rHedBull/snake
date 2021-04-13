// snakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include "Rectangle.h"
#include "Game.h"
#include "Util.h"


void test() {

    logger(1, "loger started nominal");
    logger(2, " hohpefully this still works fine ?");
 
}

void gameLoop() {

    Game game;
    logger(1, "game loop starts");

    while (game.running())
    {
        

        //update
        game.update();

        //render
        game.render();


        //window.draw(rec);
        //window.display();
    }
    logger(1, "game loop ended");
}

int main()
{   
    
    test();
    //gameLoop();
    return 0;
}

void grid(int width, int height) {
    int rows = width / 30;

    
}

/* next: get rectangle actually displayed
 finish rectangle class
    - getters/ setters for position
    - let object be drawn
    - move object
    - let object disappear
 */
