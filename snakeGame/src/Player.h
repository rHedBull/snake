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
	float movementSpeed;
	int movementDirection;
	/*
	 1= to the right -->
	 2 = downwards 
	 3 = to the left <--
	 4 = upwards
	*/

	//private functions
	void initVariables();
	void initShape();
	void moving();

public:

	//constructor
	Player();

	//destructor
	~Player();

	//accesors
	void setMovementDirection(int d);
	int getMovementDirection();

	void setMovementSpeed(float s);
	float getMovementSpeed();

	//public functions
	void update(sf::RenderTarget* targetWindow);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* targetWindow);

};

