#include "Ball.h"
#include "Util.h"


//private functions
void Ball::initVars(float w, int numb) {
	//initialize variables
	this->setBallNumb(numb);
	this->setRadius(w/30); // set radius relative to width of window
}

void Ball::updateVariables(float newSpeed)
{
	this->setMovementSpeed(newSpeed);
}

void Ball::initShape(int x, int y)
{
	//random positions between 0 and 600/ width/ height of window
	// here must somewhere be an error!, sometimes balls spawn partyl outside the game window
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

void Ball::moving()
{
	// moves the ball every time the function is called in the movementDirection
	// 	   so that he moves continuously
	
	//left
	if (this->getMovementDirection() == 3)
		this->shape.move(-this->getMovementSpeed(), 0.f);
	//right
	else if (this->getMovementDirection() == 1)
		this->shape.move(this->getMovementSpeed(), 0.f);
	//down
	else if (this->getMovementDirection() == 2)
		this->shape.move(0.f, this->getMovementSpeed());
	//up
	else if (this->getMovementDirection() == 4)
		this->shape.move(0.f, -this->getMovementSpeed());
}

//constructor
Ball::Ball()
{

}
Ball::Ball(float w, float h, int numb)
{
	this->initVars(w, numb);
	this->initShape(w, h); // here enter dimensions of game window
}

//destructor
Ball::~Ball()
{
}


//public functions
void Ball::update(float newSpeed)
{
	updateVariables(newSpeed);

	if (this->getMovementDirection() > 0)
	{
		this->moving();
	}


}

void Ball::render(sf::RenderTarget* targetWindow)
{
	//render ball to game window
	targetWindow->draw(this->shape);
}

void Ball::align(float x, float y)
{
	this->shape.setPosition(x, y); //repositions ball
	logger(1, "Ball has been repositioned at x:" + to_string(x) + ", y:" + to_string(y));
}


//accesors

int Ball::getBallNumb() const
{
	return this->ballNumb;
}
void Ball::setBallNumb(int n)
{
	this->ballNumb = n;
}

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
	// returns the shape of this ball
	return this->shape;
}