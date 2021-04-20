#include "TurnPoint.h"
#include "Util.h"

//private functions
void TurnPoint::initVars(float x, float y)
{
	this->setXPos(x);
	this->setYPos(y);
	this->setRadius(5); // define accuracy of turn point here
}

void TurnPoint::initShape()
{
	//create the circle shape
	this->circ.setFillColor(sf::Color::White);
	this->circ.setRadius(this->getRadius());
	this->circ.setPosition(this->getXPos(), this->getYPos());
	logger(1, "turnPoint (radius:" + std::to_string(this->getRadius()) + " ) shape initialized at x:" + std::to_string(this->getXPos()) + ", y:" + std::to_string(this->getYPos()));

}

//constructor
TurnPoint::TurnPoint()
{

}
TurnPoint::TurnPoint(float x, float y)
{
	this->initVars(x, y);
	this->initShape();
}

//destructor
TurnPoint::~TurnPoint()
{

}

//public functions
void TurnPoint::update()
{

}

void TurnPoint::render(sf::RenderTarget* targetWindow)
{
	//render circle to game window
	targetWindow->draw(this->circ);
}

//accessors
float TurnPoint::getXPos()
{
	return this->x_pos;
}
void TurnPoint::setXPos(float x)
{
	this->x_pos = x;
}

float TurnPoint::getYPos()
{
	return this->y_pos;
}
void TurnPoint::setYPos(float y)
{
	this->y_pos = y;
}

int TurnPoint::getRadius()
{
	return this->radius;
}
void TurnPoint::setRadius(int r)
{
	this->radius = r;
}

int TurnPoint::getNewDirection()
{
	return this->newDirection;
}
void TurnPoint::setNewDirection(int dir)
{
	this->newDirection = dir;
}