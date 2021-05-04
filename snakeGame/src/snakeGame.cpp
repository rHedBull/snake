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
    sf::Font font;
    if (!font.loadFromFile("./arial.ttf"))
    {
        //logger(1, "error loading the ARCADECLASSIC.TTF font file at relative position: \"..\res\ARCADECLASSIC.TTF\"");
        EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("this works so far");
    text.setCharacterSize(10);

    sf::VideoMode vm = sf::VideoMode::VideoMode(400, 400);
    sf::RenderWindow* window;
    window = new sf::RenderWindow(vm, "test space" , sf::Style::Titlebar | sf::Style::Close);

    while (true)
    {
        window->clear();
        window->draw(text);
    }
   
    
}

void gameLoop() {

    Game game(600, 600, 70, 1.0, "Snake Game");

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
