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

	//private variables
	
	//window variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	int width;
	int height;
	int frameRate;
	string name;

	// Game objects
	Player player;  // player object is created as part of game init

	//sf::RectangleShape enemy;
	

	//private functions
	void initVariables();
	void initWindow();

	void init_enemies();

public:
	//constructor
	Game(int width, int height, int frameRate, string name);

	//destructor
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

	// public functions
	void pollEvents();
	void update();
	void render();

};

