#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Ball
{
private:
	//private variables
	// 
	//shape
	sf::CircleShape shape;
	int radius;

	//movement
	float movementSpeed;
	int movementDirection;
	/*
	 1= to the right -->
	 2 = downwards
	 3 = to the left <--
	 4 = upwards
	*/


	//private functions
	void initVars();
	void initShape(int x, int y);


public:
	//constructor
	Ball();

	//destructor
	virtual ~Ball();


	//public functions
	void update();
	void render(sf::RenderTarget* targetWindow);
	void align(float x, float y);


	//accesors
	void setRadius(int r);
	int getRadius();
	
	void setMovementSpeed(int v)
	{
		this->movementSpeed = v;
	}
	int getMovementSpeed()
	{
		return this->movementSpeed;
	}

	void setMovementDirection(int r)
	{
		this->movementDirection = r;
	}
	int getMovementDirection()
	{
		return this->movementDirection;
	}

	const sf::CircleShape getShape() const;
};

