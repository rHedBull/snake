#ifndef GameObj_H
#define GameObj_H

#include <SFML/Graphics.hpp>


class GameObj 
{
private:

	//position
	float xPos;
	float yPos;


	//movement
	float movementSpeed;//movement per frame for all objects always the same
	int movementDirection; //
	/*
	 1 = to the right -->
	 2 = downwards
	 3 = to the left <--
	 4 = upwards
	*/

	
public:

	//constructor
	GameObj();

	//destructor
	~GameObj();


	//accessors
	int getMovementDirection();
	void setMovementDirection(int dir);

	float getCurrentMovementSpeed();
	void setCurrentMovementSpeed(float s);
};

#endif