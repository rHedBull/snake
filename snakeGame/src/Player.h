#ifndef Player_H
#define Player_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "TurnPoint.h"
#include "Ball.h"
#include "GameObj.h"


class Player: public GameObj
{
private:
	//private variables
	sf::RectangleShape shape;
	float width;
	float height;

	
	std::vector <Ball> collectedBalls; // keeps track of all the balls in the game not collected by player
	std::vector <TurnPoint> turnPoints;
	//std::vector <Segment> segments;


	//private functions
	void initVariables(float w, float h);
	void initShape(float ix, float iy);
	void moving();
	void updateCollectedBalls();
	void updateTurnPointCollision();
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	bool checkTPDist(int movementDirection);
	void updateVariables(float speed);

	
public:
	//constructor
	Player();
	Player(float iX, float iY, float w, float h);

	//destructor
	~Player();


	//public functions
	void update(sf::RenderTarget* targetWindow, float newSpeed);
	void render(sf::RenderTarget* targetWindow);


	//accesors
	void setWidth(float w);
	float getWidth();

	void setHeight(float h);
	float getHeight();

	float getXPos();
	float getYPos();

	void addBall(Ball b);
	int getCollectedBallsLength();

	void addTurnPoint(TurnPoint tP);
	int getTurnPointsLength();

	const sf::RectangleShape& getShape() const;


};

#endif