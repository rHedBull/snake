#include "Player.h"
#include "Util.h"


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

void Player::update()
{
	//window bounds collision
	
	updateInput();
	
}

void Player::updateInput() {
	//keypoard input
	this->movementSpeed = 10;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);

	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}

}

void Player::render(sf::RenderTarget * targetWindow)
{
	targetWindow->draw(this->shape);
}

Player::Player()
{
	//this->shape.setPosition(pos_x, pos_y);

	this->initShape();
	this->initVariables();
	//logger(1, "player created at x:" + std::to_string(pos_x) + ", y:" + std::to_string(pos_y));
}

Player::~Player()
{
	logger(1, "player destroyed");
}