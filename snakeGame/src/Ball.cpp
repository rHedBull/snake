#include "Ball.h"
#include "Util.h"


//private functions
// ---------- init player instance --------------------------------------------------------------------------
/*
initialize the ball's variables
parameters:
float w; 
int numb;
*/
void Ball::initVars(float w, int numb) {
	//initialize variables
	this->setBallNumb(numb);
	this->setRadius(w/30); // set radius relative to width of window
}

/*
initialize the ball's circle shape
parameters:
int windowWidth;
int windowHeight;
*/
void Ball::initShape(float windowWidth, float windowHeight)
{
	int r = this->getRadius();
	int x_max = (int) (0.5 + windowWidth - 1.5 * r);
	int y_max = (int)(0.5 + windowHeight - 1.5 * r);

	float x_pos = (rand() % x_max) + 1;
	float y_pos = (rand() % y_max) + 1;

	this->shape.setFillColor(sf::Color::Red);
	this->shape.setRadius(r);
	this->shape.setPosition(x_pos, y_pos);
	logger(1, "ball (radius:" + std::to_string(r) + " ) shape initialized at x:" + std::to_string(x_pos) + ", y:" + std::to_string(y_pos));
}
// ------------------------------------------------------------------------------------------------------
/*
update the ball's variables
parameters:
float newSpeed;
*/
void Ball::updateVariables(float newSpeed)
{
	this->setCurrentMovementSpeed(newSpeed);
}

/*
move the ball in current movementDirection
*/
void Ball::moving()
{
	// moves the ball every time the function is called in the movementDirection
	// 	   so that he moves continuously
	
	//left
	if (this->getMovementDirection() == 3)
		this->shape.move(-this->getCurrentMovementSpeed(), 0.f);
	//right
	else if (this->getMovementDirection() == 1)
		this->shape.move(this->getCurrentMovementSpeed(), 0.f);
	//down
	else if (this->getMovementDirection() == 2)
		this->shape.move(0.f, this->getCurrentMovementSpeed());
	//up
	else if (this->getMovementDirection() == 4)
		this->shape.move(0.f, -this->getCurrentMovementSpeed());
}
// ------------------------------------------------------------------------------------------------------


//constructor
Ball::Ball()
{

}

/*
create instance of the ball class
parameters:
float w;
float h;
int numb;
*/
Ball::Ball(float w, float h, int numb)
{
	this->initVars(w, numb);
	this->initShape(w, h); // here enter dimensions of game window
}

//destructor
Ball::~Ball()
{
}
// ------------------------------------------------------------------------------------------------------


//public functions
/*
update the ball  it's variables and moves it
parameters:
float newSpeed;
*/
void Ball::update(float newSpeed)
{
	this->updateVariables(newSpeed);
	this->moving();

}

/*
render this ball to the targetWindow
parameters:
sf::RenderTarget* targetWindow;

*/
void Ball::render(sf::RenderTarget* targetWindow)
{
	//render ball to game window
	targetWindow->draw(this->shape);
}

/*
align the ball at position (x, y)
parameters:
float x;
float y;
*/
void Ball::align(float x, float y)
{
	this->shape.setPosition(x, y); //repositions ball
	logger(1, "Ball has been repositioned at x:" + to_string(x) + ", y:" + to_string(y));
}

/*
	return whether ball has reached segment endPoint an the next segment is needed
	true == segment finished, next one needed
	false == segment not yet finished, set movementDirection according to segment
	parameters:
	Segment s;
*/
bool Ball::updateSegmentPath(Segment seg)
{
	int dir = seg.getDirection();

	//check if this ball has already passed this segment
	if (seg.hasPassed(this->getBallNumb()))
	{
		//ball has already finished this segment
		return true;
	}

	bool finishedSegment = false;

	if (dir == 1) // to the right
	{
		if (this->getXPos() >= seg.getEndPoint())
		{
			finishedSegment = true;
		}
	}
	else if (dir == 2) //downwards
	{
		if (this->getYPos() >= seg.getEndPoint())
		{
			finishedSegment = true;
		}
	}
	else if (dir == 3) //to the left
	{
		if (this->getXPos() <= seg.getEndPoint())
		{
			finishedSegment = true;
		}

	}
	else if (dir == 4)//upwards
	{
		if (this->getYPos() <= seg.getEndPoint())
		{
			finishedSegment = true;
		}
	}

	if (finishedSegment == true)
	{
		//ball has finished segment, add it to passedBalls vector of the segment
		seg.addPassedBall(this->getBallNumb());
		return true;
	}
	else {
		// ball still has to finish this segment
		this->setMovementDirection(seg.getDirection());
		return false;
	}
}
// ------------------------------------------------------------------------------------------------------


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

float Ball::getXPos()
{
	return  this->getShape().getPosition().x;
}
float Ball::getYPos()
{
	return this->getShape().getGlobalBounds().top;
}

/*
returns the ball's shape
*/
const sf::CircleShape Ball::getShape() const
{
	// returns the shape of this ball
	return this->shape;
}