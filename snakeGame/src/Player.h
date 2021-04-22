#ifndef Player_H
#define Player_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "TurnPoint.h"
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
	void updateTurnPointCollision();

	std::vector <Ball> collectedBalls; // keeps track of all the balls in the game not collected by player
	std::vector <TurnPoint> turnPoints;


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

	float getXPosition();
	float getYPosition();

	void addBall(Ball b);
	int getCollectedBallsLength();

	void addTurnPoint(TurnPoint tP);
	int getTurnPointsLength();


};

#endif