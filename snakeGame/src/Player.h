#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Ball.h"

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
	void updateCollectedBalls();

	std::vector <Ball> collectedBalls; // keeps track of all the balls in the game not collected by player

public:

	//constructor
	Player();

	//destructor
	~Player();


	//public functions
	const sf::RectangleShape& getShape() const;

	void update(sf::RenderTarget* targetWindow);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* targetWindow);


	//accesors
	void setMovementDirection(int d);
	int getMovementDirection();

	void setMovementSpeed(float s);
	float getMovementSpeed();

	void addBall(Ball b);
	int getPlayerBallsLength();
};

