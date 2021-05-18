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

float GameObj::getCurrentMovementSpeed()
{
	return this->movementSpeed;
}
void GameObj::setCurrentMovementSpeed(float s)
{
	this->movementSpeed = s;
}