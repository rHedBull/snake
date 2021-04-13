#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include "Player.h"

class Game
{
private:

	// window variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	void initVariables();
	void initWindow();

	// Game objects
	Player player;
	//sf::RectangleShape enemy;

	//private functions

	void init_enemies();

public:
	//constructors && destructors
	Game();
	~Game();
	
	//accessors:
	const bool running() const;

	//Functions
	void pollEvents();
	void update();
	void render();

};

