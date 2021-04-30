#include "Player.h"
#include "Util.h"
#include "TurnPoint.h"


//private functions
//--------------------------- init Player------------------------------------------------------------
void Player::initShape(float ix, float iy)
{
	// create the rectangle
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->shape.setPosition(ix, iy);
	logger(1, "player shape initialized at x:" + std::to_string(ix) + ", y:" + std::to_string(iy));

}

void Player::initVariables( float w, float h)
{
	this->setWidth(w);
	this->setHeight(h);

	// set random start direction
	int r = (rand() % 4) + 1;
	this->setMovementDirection(r);
}
// ------------------------------------------------------------------------------------------------------

void Player::updateVariables(float speed)
{
	this->setMovementSpeed(speed);
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
		this->shape.move(0.f, -this->getMovementSpeed());
}

void Player::updateCollectedBalls()
{
	int i = 0;
	while (i < this->collectedBalls.size())// iterate through all collected balls
	{
		
		this->collectedBalls[i].update(this->getMovementSpeed());// update the overall game variables

		int s;
		for (s = 0; s < segments.size(); s++) //update through all currently existing segments
		{
			Segment seg = this->segments[s];
			bool obsoleteSegment = this->collectedBalls[i].updateSegmentPath(seg); // send segment an find out if this ball has already finished it
			if (obsoleteSegment == false) {
				break; // not yet finished, ball moved, break this segment loop
			}
			else if (obsoleteSegment == true && this->collectedBalls[i].getBallNumb() == this->collectedBalls.back().getBallNumb())
			{
				//last collected ball has finished the segment

				segments.erase(this->segments.begin());// delete finished segment
				logger(1, "segment:" + to_string(seg.getId()) + "finished and deleted");
			}
		}

		i++;
	}
}

void Player::updateInput() {
	//keypoard input collects the change of directions by ASWD and arrow keys

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->setMovementDirection(3); // set players movementDirection to the left

		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == true)
		{

			//Segment seg = Segment(-10, this->getMovementDirection(), this->getSegmentCount());

			
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == false)
			{
				// check if turn point is not overlapping
				bool overlapping = this->checkOverlappingTP(this->getMovementDirection());

				if (overlapping == true)
				{
					return;
				}
				
			}
		
			//define new turnpoint
			TurnPoint tp = TurnPoint(this->getXPos(), this->getYPos());
			tp.setNewDirection(3);
			// push created tp into turnPoints vector

			this->turnPoints.push_back(tp);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->setMovementDirection(1); // set players movementDirection to the left

		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == true)
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == false)
			{
				// check if turn point is not overlapping
				bool overlapping = this->checkOverlappingTP(this->getMovementDirection());

				if (overlapping == true)
				{
					return;
				}
			}

			//define new turnpoint
			TurnPoint tp = TurnPoint(this->getXPos(), this->getYPos());
			tp.setNewDirection(1);
			// push created tp into turnPoints vector

			this->turnPoints.push_back(tp);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->setMovementDirection(4); // set players movementDirection to the left

		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == true)
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == false)
			{
				// check if turn point is not overlapping
				bool overlapping = this->checkOverlappingTP(this->getMovementDirection());

				if (overlapping == true)
				{
					return;
				}
			}

			//define new turnpoint
			TurnPoint tp = TurnPoint(this->getXPos(), this->getYPos());
			tp.setNewDirection(4);
			// push created tp into turnPoints vector

			this->turnPoints.push_back(tp);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->setMovementDirection(2); // set players movementDirection to the left

		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == true)
		{// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == false)
			{
				// check if turn point is not overlapping
				bool overlapping = this->checkOverlappingTP(this->getMovementDirection());

				if (overlapping == true)
				{
					return;
				}
			}

			//define new turnpoint
			TurnPoint tp = TurnPoint(this->getXPos(), this->getYPos());
			tp.setNewDirection(2);
			// push created tp into turnPoints vector

			this->turnPoints.push_back(tp);
		}
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//checks continuously for collision with game Window borders
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
}

void Player::updateSegments()
{
	//checks if 2 turnPoints exist in vector turnPoints and then creates a segment ending in the latter turnPoint
	if (this->turnPoints.size() >= 2)
	{
		/*
		int dir = turnPoints.front().getNewDirection();
		Segment segment;
		if (dir == 1 || dir == 3)
		{
			segment = Segment(turnPoints.back().getXPos(), dir, this->getSegmentCount());
			this->setSegmentCount(this->getSegmentCount() + 1);
		}
		else if (dir == 2 || dir == 4)
		{
			segment = Segment(turnPoints.back().getYPos(), dir, this->getSegmentCount());
			this->setSegmentCount(this->getSegmentCount() + 1);
		}
		turnPoints.erase(this->turnPoints.begin()); // destroys all turnPoints
		this->segments.push_back(segment); // add created segment to vector segments
		*/
		this->turnPoints.erase(this->turnPoints.begin());

	}else if (this->turnPoints.size() == 1) //if only one turnPoint exist, L shape player and balls, create segment from last collected ball to turnPoint
	{
		int dir = turnPoints.front().getNewDirection();
		Segment segment;
		if (dir == 1 || dir == 3)
		{
			segment = Segment(turnPoints.back().getXPos(), dir, this->getSegmentCount());
			this->setSegmentCount(this->getSegmentCount() + 1);
		}
		else if (dir == 2 || dir == 4)
		{
			segment = Segment(turnPoints.back().getYPos(), dir, this->getSegmentCount());
			this->setSegmentCount(this->getSegmentCount() + 1);
		}
		this->segments.push_back(segment); // add created segment to vector segments
	}
}


//constructor
Player::Player()
{

}
Player::Player(float iX, float iY, float w, float h)
{
	this->initVariables( w,  h);
	this->initShape(iX, iY);
}

//destructor
Player::~Player()
{
}


//public functions
void Player::update(sf::RenderTarget* targetWindow, float newSpeed)
{
	//update the player's variables
	updateVariables(newSpeed);

	//get keystrokes
	this->updateInput();

	//move player in direction
	this->moving();

	//window bounds collision
	this->updateWindowBoundsCollision(targetWindow);

	//update the players collected balls
	this->updateCollectedBalls();

	//update if new segments must be created
	this->updateSegments();

}

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

