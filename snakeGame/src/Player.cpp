#include "Player.h"
#include "Util.h"
#include "Game.h"

//private functions
void Player::initShape()
{
	// create the rectangle
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->shape.setPosition(this->getInitX(), this->getInitY());
	logger(1, "player shape initialized at x:" + std::to_string(this->initX) + ", y:" + std::to_string(this->initY));

}

void Player::initVariables(float iX, float iY, float w, float h)
{
	this->setInitX(iX);
	this->setInitY(iY);
	this->setWidth(w);
	this->setHeight(h);
	this->setMovementSpeed(1.f);

	// set random start direction
	int r = (rand() % 4) + 1;
	this->setMovementDirection(r);
}

void Player::moving()
{
	// moves the player every time the function is called in the movementDirection
	// 	   so that he moves continuously

	//left
	if(this->getMovementDirection() == 3)
		this->shape.move(-this->getMovementSpeed(), 0.f);
	//right
	else if (this->getMovementDirection() == 1)
		this->shape.move(this->getMovementSpeed(), 0.f);
	//down
	else if (this->getMovementDirection() == 2)
		this->shape.move(0.f, this->getMovementSpeed());
	//up
	else if (this->getMovementDirection() == 4)
		this->shape.move(0.f , -this->getMovementSpeed());
}


//constructor
Player::Player()
{

}
Player::Player(float iX, float iY, float w, float h)
{
	this->initVariables( iX,  iY,  w,  h);
	this->initShape();
}

//destructor
Player::~Player()
{
	logger(1, "player destroyed");
}


//public functions
void Player::update(sf::RenderTarget* targetWindow) //sf::RenderTarget* targetWindow
{
	//get keystrokes
	this->updateInput();

	//move player in direction
	this->moving();

	//window bounds collision
	//targetWindow->getSize();
	this->updateWindowBoundsCollision(targetWindow);

	//update the players collected balls
	int i = 0;
	while (i < this->getCollectedBallsLength())
	{
		this->collectedBalls[i].update();

		i++;
	}

}

void Player::updateCollectedBalls()
{

}

void Player::updateInput() {
	//keypoard input collects the change of directions by ASWD and arrow keys

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->setMovementDirection(3); // to the left
		

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D ) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->setMovementDirection(1); // to the right
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->setMovementDirection(4); // upward

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->setMovementDirection(2); // downwards
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//checks continuously for collision with game Window borders
	//Up
	if (shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(shape.getGlobalBounds().left, 0.f);
	//Down
	if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);

	//Left
	if (shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, shape.getGlobalBounds().top);
		//Right
	if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);
	

	
}

void Player::render(sf::RenderTarget * targetWindow)
{
	//render player shape to game window
	targetWindow->draw(this->shape);

	//rendering of the collected balls
	int i = 0;
	while (i < this->getCollectedBallsLength())
	{
		this->collectedBalls[i].render(targetWindow);

		i++;
	}
}

const sf::RectangleShape & Player::getShape() const
{
	//returns the player's shape
	return this->shape;
}

//accesors
void Player::setMovementDirection(int d)
{
	this->movementDirection = d;
}
int Player::getMovementDirection()
{
	return this->movementDirection;
}

void Player::setMovementSpeed(float s)
{
	this->movementSpeed = s;
}
float Player::getMovementSpeed()
{
	return this->movementSpeed;
}

void Player::setWidth(float w)
{
	this->width = w;
}
float Player::getWidth()
{
	return this->width;
}

void Player::setHeight(float h)
{
	this->height = h;
}
float Player::getHeight()
{
	return this->height;
}

void Player::setInitX(float iX)
{
	this->initX = iX;
}
float Player::getInitX()
{
	return this->initX;
}

void Player::setInitY(float iY)
{
	this->initY = iY;
}
float Player::getInitY()
{
	return this->initY;
}

void Player::addBall(Ball b)
{
	this->collectedBalls.push_back(b); // pushes Ball into player's collection of balls vector
	logger(1, "added ball to vector collectedBalls.");

	//give the newly added ball direction and speed of player to follow him
	this->collectedBalls.back().setMovementDirection(this->getMovementDirection());
	this->collectedBalls.back().setMovementSpeed(this->getMovementSpeed());
}
int Player::getCollectedBallsLength()
{
	return collectedBalls.size();
}

