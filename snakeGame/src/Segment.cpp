#include "Segment.h"
#include "Util.h"
#include <string>

//constructor
Segment::Segment()
{

}
/*
create instance of segment class
parameters:
float startPoint;
float endPoint;
int direction;
int id;
*/
Segment::Segment(float startPoint, float endPoint, int direction, int id)
{
	this->setStartPoint(startPoint);
	this->setEndPoint(endPoint);
	this->setDirection(direction);
	this->setId(id);
	logger(1, "segment "+ to_string(id) + " created; dir = " + to_string(this->getDirection()) + ", EndPoint at:" + to_string(this->getEndPoint()));
}

//destructor
Segment::~Segment()
{

}


//accessors
float Segment::getEndPoint()
{
	return this->endPoint;
}
void Segment::setEndPoint(float eP)
{
	this->endPoint = eP;
}

float Segment::getStartPoint()
{
	return this->startPoint;
}
void Segment::setStartPoint(float sP)
{
	this->startPoint = sP;
}

int Segment::getDirection()
{
	return this->direction;
}
void Segment::setDirection(int dir)
{
	this->direction = dir;
}

int Segment::getId()
{
	return this->id;
}
void Segment::setId(int id)
{
	this->id = id;
}

bool Segment::hasPassed(int numb)
{
	int i;
	for (i = 0; i < passedBalls.size(); i++)
	{
		if (numb == passedBalls[i])
		{
			return true;
		}
	}

	return false;
}
void Segment::addPassedBall(int numb)
{
	this->passedBalls.push_back(numb);
}