#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Game
{
private:

	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	void initVariables();
	void initWindow();

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

