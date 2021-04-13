#include "Player.h"
#include "Util.h"


void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setSize(sf::Vector2f(100.f, 100.f));
	logger(1, "player shape initialized");

}

void Player::initVariables()
{

}

void Player::update()
{

}

void Player::render(sf::RenderTarget * targetWindow)
{
	targetWindow->draw(this->shape);
}

Player::Player()
{
	this->initShape();
	this->initVariables();
	logger(1, "player created");
}

Player::~Player()
{
	logger(1, "player destroyed");
}