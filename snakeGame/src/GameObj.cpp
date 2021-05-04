#include "GameObj.h"


//constructor
GameObj::GameObj()
{

}

GameObj::~GameObj()
{

}


//accessors
int GameObj::getMovementDirection()
{
	return this->movementDirection;
}
void GameObj::setMovementDirection(int dir)
{
	this->movementDirection = dir;
}

float GameObj::getMovementSpeed()
{
	return this->movementSpeed;
}
void GameObj::setMovementSpeed(float s)
{
	this->movementSpeed = s;
}