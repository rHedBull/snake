#include "Player.h"
#include "Util.h"
#include "Game.h"

//constructor
Player::Player()
{
	//this->shape.setPosition(pos_x, pos_y);

	this->initShape();
	this->initVariables();
	//logger(1, "player created at x:" + std::to_string(pos_x) + ", y:" + std::to_string(pos_y));
}

//destructor
Player::~Player()
{
	logger(1, "player destroyed");
}

//private functions
void Player::initShape()
{
	float x_pos = 100.f;
	float y_pos = 100.f;

	this->shape.setFillColor(sf::Color::Red);
	this->shape.setSize(sf::Vector2f(100.f, 100.f));
	this->shape.setPosition(x_pos, y_pos);
	logger(1, "player shape initialized at x:" + std::to_string(x_pos) + ", y:" + std::to_string(y_pos));

}

void Player::initVariables()
{
	this->movementSpeed = 60;
}


//public functions
void Player::update(sf::RenderTarget* targetWindow) //sf::RenderTarget* targetWindow
{
	//get keystrokes
	this->updateInput();


	//window bounds collision
	//targetWindow->getSize();
	this->updateWindowBoundsCollision(targetWindow);
}

void Player::updateInput() {
	//keypoard input
	this->movementSpeed = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->shape.move(-this->movementSpeed, 0.f);

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D ) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->shape.move(0.f, -this->movementSpeed);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->shape.move(0.f, this->movementSpeed);
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();

	//Up
	if (playerBounds.top <= 0.f)
		this->shape.setPosition(playerBounds.left, 0.f);
	//Down
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);

	//Left
	if (playerBounds.left <= 0.f)
		this->shape.setPosition(0.f, playerBounds.top);
		//Right
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	

	
}

void Player::render(sf::RenderTarget * targetWindow)
{
	targetWindow->draw(this->shape);
}