#ifndef Segment_H
#define Segment_H

#include <vector>

class Segment
{
	/*
	a straight line from one turn point to another,
	tells the balls on the segment where to travel until thei reach the segment's endPoint
	*/
private:
	float endPoint;
	float startPoint;
	int direction;
	int id;

	std::vector <int> passedBalls;

public:
	//constructor
	Segment();
	Segment(float startPoint, float endPoint, int direction, int id);

	//destructor
	~Segment();


	//accessor
	float getEndPoint();
	void setEndPoint(float eP);

	float getStartPoint();
	void setStartPoint(float sP);

	int getDirection();
	void setDirection(int dir);

	int getId();
	void setId(int id);

	bool hasPassed(int numb);
	void addPassedBall(int numb);
};

#endif