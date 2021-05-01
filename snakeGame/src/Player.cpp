#include "Player.h"
#include "Util.h"


//private functions
//--------------------------- init Player------------------------------------------------------------
/*
initializes the player object's variables
parameters:
float width;
float height;
*/
void Player::initVariables( float width, float height)
{
	this->setWidth(width);
	this->setHeight(height);

	// set random start direction
	int r = (rand() % 4) + 1;
	this->setMovementDirection(r);
}

/*
initializes the player object's shape
parameters:
float initialX;
float initialY;
*/
void Player::initShape(float initialX, float initialY)
{
	// create the rectangle
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->shape.setPosition(initialX, initialY);
	logger(1, "player shape initialized at x:" + std::to_string(initialX) + ", y:" + std::to_string(initialY));

}
// ------------------------------------------------------------------------------------------------------

/*
update the Player's variables
parameters:
float speed;
*/
void Player::updateVariables(float speed)
{
	this->setMovementSpeed(speed);
}

/*
moves the player in the current movementDirection
*/
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
		this->shape.move(0.f, -this->getMovementSpeed());
}

/*
update all the from the player collected balls
*/
void Player::updateCollectedBalls()
{
	int i = 0;
	while (i < this->collectedBalls.size())// iterate through all collected balls
	{
		
		this->collectedBalls[i].update(this->getMovementSpeed());// update the overall game variables

		int s = 0;
		while(s < this->segments.size())
		{
			Segment seg = this->segments[s];
			// send segment an find out if this ball has already finished it
			bool obsoleteSegment = this->collectedBalls[i].updateSegmentPath(seg); 
			if (obsoleteSegment == false) {
				// not yet finished, right settings assigned to ballbreak this segment's loop
				break; 
			}
			else if (obsoleteSegment == true && this->collectedBalls[i].getBallNumb() == this->collectedBalls.back().getBallNumb())
			{
				//last collected ball has finished the segment

				segments.erase(this->segments.begin());// delete finished segment
				logger(1, "segment: " + to_string(seg.getId()) + " finished and deleted");
			}
		}

		i++;
	}
}

/*
checks if enough space to last segment
parameters:
int oldDirection; 
*/
bool Player::segmentSpacing(int oldDirection)
{
	bool space = false;

	if (oldDirection == 1) // to the right -->
	{
		// check if enough space between current player position and last segment start
		space = (this->getXPos() - segments.back().getStartPoint()) > this->getWidth();

	}
	else if (oldDirection == 3) // to the left <--
	{
		// check if enough space between current player position and last segment start
		space = (segments.back().getStartPoint() - this->getXPos()) > this->getWidth();

	}
	else if (oldDirection == 4) // upwards
	{
		// check if enough space between current player position and last segment start
		space = (segments.back().getStartPoint() - this->getYPos()) > this->getHeight();

	}
	else if (oldDirection == 2) //downwards
	{
		// check if enough space between current player position and last segment start
		space = (this->getYPos() - segments.back().getStartPoint()) > this->getHeight();
	}

	return space;
}

/*
keypoard input collects the change of directions by ASWD and arrow keys
*/
void Player::updateInput() {
	
	bool leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	bool rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	bool upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

	int newDir = this->getMovementDirection();

	

	

	if (leftKey || rightKey || upKey || downKey)// check if any of the keys is pressed
	{
		//assign right int to newDirection, according to keysPressed
		if (leftKey)
		{
			newDir = 3;

		}
		else if (rightKey)
		{
			newDir = 1;

		}

		if (upKey)
		{
			newDir = 4;

		}
		else if (downKey)
		{
			newDir = 2;

		}

		if (newDir == this->getMovementDirection()) // if there would be no change in direction
		{
			return; // exit this method without any further action
		}


		if (this->collectedBalls.empty() == false) // checks if any balls have already been collected
		{
			if (this->segments.empty() == false) //checks if there are already any segments
			{
				if (segmentSpacing(this->getMovementDirection()) == true) // checks if enough space to last segment
				{
					this->updateSegments();
				}
				else {
					return; // exit this method without any further action
				}

			}

			this->createPreliminarySegment(newDir);
			
		}

		this->setMovementDirection(newDir);

	}

}

/*
checks continuously for collision with game Window borders
parameters:
const sf::RenderTarget* target;
*/
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Up
	if (this->getYPos() <= 0.f)
		this->shape.setPosition(shape.getGlobalBounds().left, 0.f);
	//Down
	if (this->getYPos() + shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);

	//Left
	if (this->getXPos() <= 0.f)
		this->shape.setPosition(0.f, shape.getGlobalBounds().top);
	//Right
	if (this->getXPos() + shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);

}

/*
bool Player::checkOverlappingTP(int mDir)
{
		//check for enough distance between 2 turn points
		float dist = 0; // distance between last turnPoint and wanted new one at current Player's position
		if (mDir == 1) // to the right
		{
			dist = this->getXPos() - this->turnPoints.back().getXPos();
		}
		else if (mDir == 2) //downwards
		{
			dist = this->getYPos() - this->turnPoints.back().getYPos();
		}
		else if (mDir == 3) // to the left
		{
			dist = this->turnPoints.back().getXPos() - this->getXPos();
		}
		else if (mDir == 4) //upwards
		{
			dist = this->turnPoints.back().getYPos() - this->getYPos();
		}

		bool space = (dist > this->getWidth() + 5);

		if (space == true)
		{
			return false;
		}
		else {
			return true;
		}
}*/

/*
update the last preliminary segment
*/
void Player::updateSegments()
{
	if (this->getMovementDirection() == 1 || this->getMovementDirection() == 3) // last movement was horizontal
	{
		//set new Endpoint for last segment
		this->segments.back().setEndPoint(this->getXPos());
	}
	else 
	{	// last movement was vertical
		//set new Endpoint for last segment
		this->segments.back().setEndPoint(this->getYPos());
	}

	logger(1, "segment " + to_string(segments.back().getId()) + " endPoint updated to: " + to_string(this->segments.back().getEndPoint()));
}


//constructor
Player::Player()
{

}

/*
creates instance of Player class
paramters:
float initialX;
float initialY;
float width;
float height;
*/
Player::Player(float initialX, float initialY, float width, float height)
{
	this->initVariables(width, height);
	this->initShape(initialX, initialY);
}

//destructor
Player::~Player()
{
}


//public functions
void Player::update(sf::RenderTarget* targetWindow, float newSpeed)
{
	//update the player's variables
	this->updateVariables(newSpeed);

	//get keystrokes
	this->updateInput();

	//move player in direction
	this->moving();

	//window bounds collision
	this->updateWindowBoundsCollision(targetWindow);

	//update the players collected balls
	this->updateCollectedBalls();

}

/*
render all the Player's shapes to the target window
parameters:
sf::RenderTarget * targetWindow;
*/
void Player::render(sf::RenderTarget * targetWindow)
{
	//render player shape to game window
	targetWindow->draw(this->shape);

	//rendering of the collected balls
	int i = 0;
	while (i < this->collectedBalls.size())
	{
		this->collectedBalls[i].render(targetWindow);

		i++;
	}

	//render turnpoints, only for debugging!
	i = 0;
	while (i < this->turnPoints.size())
	{
		this->turnPoints[i].render(targetWindow);

		i++;
	}
}

/*
creates preliminary segment according to new movementDirection and pushes it into players segments vector
parameters:
int direction;
*/
void Player::createPreliminarySegment(int direction)
{
	float preEndPoint = 0;
	float sPoint = 0;

	//assign start point and preliminary endPoints to variables
	//horizontal
	if (direction == 3)
	{
		preEndPoint = -10.0;   //preliminary endPoint
		sPoint = this->getXPos();
	}
	else if (direction == 1)
	{
		preEndPoint = 100000.0;//preliminary endPoint
		sPoint = this->getXPos();
	}

	//vertical
	if (direction == 4)
	{
		preEndPoint = -10.0;   //preliminary endPoint
		sPoint = this->getYPos();
	}
	else if (direction == 2)
	{
		preEndPoint = 100000.0;//preliminary endPoint
		sPoint = this->getYPos();
	}

	// create new segment for balls, endPoint is only perliminary
	Segment seg = Segment(sPoint, preEndPoint, direction, this->getSegmentCount());
	this->segments.push_back(seg); //push created segment into segments vector
	this->setSegmentCount(this->getSegmentCount() + 1); //count segmentCounter one up
}


//accesors
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

float Player::getXPos()
{
	return  this->getShape().getGlobalBounds().left;
}
float Player::getYPos()
{
	return this->getShape().getGlobalBounds().top;
}

void Player::setSegmentCount(int c)
{
	this->segmentCount = c;
}
int Player::getSegmentCount()
{
	return this->segmentCount;
}

void Player::addBall(Ball b)
{
	this->collectedBalls.push_back(b); // pushes Ball into player's collection of balls vector
	logger(1, "added ball to vector collectedBalls.");

	//give the newly added ball direction and speed of player to follow him
	this->collectedBalls.back().setMovementDirection(this->getMovementDirection());
}
int Player::getCollectedBallsLength()
{
	return collectedBalls.size();
}
int Player::getTurnPointsLength()
{
	return turnPoints.size();
}

const sf::RectangleShape& Player::getShape() const
{
	//returns the player's shape
	return this->shape;
}

