#ifndef TurnPoint_H
#define TurnPoint_H

#include <SFML/Graphics.hpp>

class TurnPoint
{
private:
	//private variables
	//shape variables
	float x_pos;
	float y_pos;
	int radius;
	
	sf::CircleShape circ;

	//functional variables
	int newDirection; // the direction in which the balls should move after colliding with this shape
	/*
	 1= to the right -->
	 2 = downwards
	 3 = to the left <--
	 4 = upwards
	*/

	//private functions
	void initVars(float x, float y);
	void initShape();

public:

	//constructor
	TurnPoint();
	TurnPoint(float x, float y);

	//destructor
	~TurnPoint();

	//public functions
	void update();
	void render(sf::RenderTarget* targetWindow);


	//accessors
	float getXPos();
	void setXPos(float x);

	float getYPos();
	void setYPos(float y);

	int getRadius();
	void setRadius(int r);

	int getNewDirection();
	void setNewDirection(int dir);
};

#endif