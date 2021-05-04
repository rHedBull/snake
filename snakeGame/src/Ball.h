#ifndef Ball_H
#define Ball_H

#include <SFML/Graphics.hpp>
#include "GameObj.h"
#include "Segment.h"

class Ball: public GameObj 
{
private:
	//private variables
	
	//shape
	sf::CircleShape shape;
	int radius;
	int ballNumb;


	//private functions
	void initVars(float w, int numb);
	void updateVariables(float newSpeed);
	void initShape(int x, int y);
	void moving();
	


public:
	//constructor
	Ball();
	Ball(float w, float h, int numb);

	//destructor
	virtual ~Ball();


	//public functions
	void update(float newSpeed);
	void render(sf::RenderTarget* targetWindow);
	bool updateSegmentPath(Segment s);
	void align(float x, float y);



	//accesors
	int getBallNumb() const;
	void setBallNumb(int n);

	void setRadius(int r);
	int getRadius();

	float getXPos();
	float getYPos();

	const sf::CircleShape getShape() const;
};

#endif