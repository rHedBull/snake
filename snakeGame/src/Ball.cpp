#include "Ball.h"
#include "Util.h"
#include "Game.h"



//constructor
Ball::Ball()
{
	this->initVars();
	this->initShape(600, 600); // here enter dimensions of game window

}

//destructor
Ball::~Ball()
{
	
	logger(1, "Ball has been deleted");
}

//private variables


//private functions
void Ball::initVars() {
	this->setRadius(50);
}

void Ball::initShape(int x, int y)
{
	//random positions between 0 and 600/ width/ height of window
	int r = this->getRadius();
	int x_max = x - r;
	int y_max = y - r;

	float x_pos = (rand() % x_max) + 1;
	float y_pos = (rand() % y_max) + 1;

	this->shape.setFillColor(sf::Color::Red);
	this->shape.setRadius(r);
	this->shape.setPosition(x_pos, y_pos);
	logger(1, "ball (radius:"+ std::to_string(r) + " ) shape initialized at x:" + std::to_string(x_pos) + ", y:" + std::to_string(y_pos));
	
}

//accesors
void Ball::setRadius(int r)
{
	this->radius = r;
}
int Ball::getRadius()
{
	return this->radius;
}

const sf::CircleShape Ball::getShape() const
{
	return this->shape;
}

//public functions
void Ball::update()
{

}

void Ball::render(sf::RenderTarget* targetWindow)
{
	targetWindow->draw(this->shape);
}