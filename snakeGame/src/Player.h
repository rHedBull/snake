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
	float width;
	float height;
	float initX;
	float initY;

	/*
	 1= to the right -->
	 2 = downwards 
	 3 = to the left <--
	 4 = upwards
	*/

	

	//private functions
	void initVariables(float iX, float iY, float w, float h);
	void initShape();
	void moving(); 
	void updateCollectedBalls();

	std::vector <Ball> collectedBalls; // keeps track of all the balls in the game not collected by player
	
public:

	//constructor
	Player();
	Player(float iX, float iY, float w, float h);

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

	void setWidth(float w);
	float getWidth();

	void setHeight(float h);
	float getHeight();

	void setInitX(float iX);
	float getInitX();

	void setInitY(float iY);
	float getInitY();

	void addBall(Ball b);
	int getCollectedBallsLength();


};

