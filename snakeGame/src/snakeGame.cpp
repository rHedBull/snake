// snakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Game.h"
#include "Util.h"



void test() {
    
}

void gameLoop() {

    Game game(600, 600, 70, "Snake Game");
    

    logger(1, "game loop starts");

    while (game.running())
    {
        
        //update
        game.update();

        //render
        game.render();

    }
    logger(1, "game loop ended");
}

int main()
{   
    //initialize random seed
    srand(static_cast<unsigned>(time(0)));

    //test();
    gameLoop();
    return 0;
}
