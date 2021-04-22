#ifndef Ball_H
#define Ball_H

#include <SFML/Graphics.hpp>

class Ball
{
private:
	//private variables
	// 
	//shape
	sf::CircleShape shape;
	int radius;
	int ballNumb;

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
	void initVars(float w, int numb);
	void initShape(int x, int y);
	void moving();


public:
	//constructor
	Ball();
	Ball(float w, float h, int numb);

	//destructor
	virtual ~Ball();


	//public functions
	void update();
	void render(sf::RenderTarget* targetWindow);
	void align(float x, float y);


	//accesors
	int getBallNumb() const;
	void setBallNumb(int n);

	void setRadius(int r);
	int getRadius();
	
	void setMovementSpeed(float v);
	float getMovementSpeed();

	void setMovementDirection(int r);
	int getMovementDirection();

	const sf::CircleShape getShape() const;
};

#endif