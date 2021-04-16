#include "Player.h"
#include "Util.h"
#include "Game.h"

//private functions
void Player::initShape()
{
	float x_pos = 100.f;
	float y_pos = 100.f;

	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(100.f, 100.f));
	this->shape.setPosition(x_pos, y_pos);
	logger(1, "player shape initialized at x:" + std::to_string(x_pos) + ", y:" + std::to_string(y_pos));

}

void Player::initVariables()
{
	this->setMovementSpeed(1.f);
	this->setMovementDirection(1);
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
	//this->shape.setPosition(pos_x, pos_y);

	this->initShape();
	this->initVariables();
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
	//updateCollectedBalls();

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

void Player::addBall(Ball b)
{
	this->collectedBalls.push_back(b); // pushes Ball into player's collection of balls vector
	logger(1, "added ball to vector collectedBalls");
}
int Player::getPlayerBallsLength()
{
	return sizeof(this->collectedBalls);
}