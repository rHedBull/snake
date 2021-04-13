// snakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include "Rectangle.h"
#include "Game.h"

string logger(int level, string message)
{
    string text;
    string l;
    string m = message;

    // generate log message
    switch (level)
    {
    case 1:
        l = "INFO";
    case 2:
        l = "Warning";
    case 3:
        l = "Failure";
    }

    // generate date and time
    time_t currenTime = time(0);

#pragma warning(suppress : 4996)
    tm* t = localtime(&currenTime);

    string year = std::to_string((t->tm_year) + 1900);
    string month = std::to_string((t->tm_mon) + 1);
    string day = std::to_string(t->tm_mday);
    string hour = std::to_string(t->tm_hour);
    string min = std::to_string(t->tm_hour);
    string sec = std::to_string(t->tm_sec);

    string dateTime = '[' + year + "." + month + "." + day + "--" + hour + ":" + min + ":" + sec + "]";

    text = dateTime + "  [" + l + "]" + "  " + m;
    cout << text << endl;

    ofstream logfile;
    logfile.open("logs.txt", std::ios_base::app);
    logfile << text << " \n";
  
    for (int i = 1; i <= 150; i++)
    {
        logfile << "*";
    }
    logfile << " \n";

    logfile.close();

    return text;
}

void test() {
    logger(1, "loger started nominal");
    logger(2, " hohpefully this still works fine ?");
 
}

void gameLoop() {

    Game game;

    while (game.running())
    {
        

        //update
        game.update();

        //render
        game.render();


        //window.draw(rec);
        //window.display();
    }
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
