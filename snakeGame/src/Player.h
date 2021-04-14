#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
	//private variables
	sf::RectangleShape shape;
	int movementSpeed;

	//private functions
	void initVariables();
	void initShape();

public:

	//constructor
	Player();

	//destructor
	~Player();

	//public functions
	void update();
	void updateInput();
	void render(sf::RenderTarget* targetWindow);

};

