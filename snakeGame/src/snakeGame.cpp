// snakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rectangle.h"

void test() {
    
    
 
}

void gameLoop() {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    Rectangle rec(100, 200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    

        window.clear();
        window.draw(rec);
        window.display();
    }
}

int main()
{   
    gameLoop();
    return 0;
}

void grid(int width, int height) {
    int rows = width / 30;

    
}
