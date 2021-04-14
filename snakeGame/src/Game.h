#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Player.h"
#include "Util.h"

class Game
{
private:

	// window variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	int width;
	int height;
	int frameRate;
	string name;

	void initVariables();
	void initWindow();

	// Game objects
	// player object is created as part of game init
	Player player;

	//sf::RectangleShape enemy;

	//private functions

	void init_enemies();

public:
	//constructors && destructors
	Game(int width, int height, int frameRate, string name);
	~Game();
	
	//accessors:
	const bool running() const;
	
	void setWidth(int w);
	int getWidth();

	void setHeight(int h);
	int getHeight();

	void setFrameRate(int fR);
	int getFrameRate();

	void setName(string n);
	string getName();

	//Functions
	void pollEvents();
	void update();
	void render();

};

