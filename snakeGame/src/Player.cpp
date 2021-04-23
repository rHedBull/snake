#include "Player.h"
#include "Util.h"
#include "TurnPoint.h"


//private functions
void Player::initShape()
{
	// create the rectangle
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->shape.setPosition(this->getInitX(), this->getInitY());
	logger(1, "player shape initialized at x:" + std::to_string(this->initX) + ", y:" + std::to_string(this->initY));

}

void Player::initVariables(float iX, float iY, float w, float h)
{
	this->setInitX(iX);
	this->setInitY(iY);
	this->setWidth(w);
	this->setHeight(h);
	this->setMovementSpeed(1.f);

	// set random start direction
	int r = (rand() % 4) + 1;
	this->setMovementDirection(r);
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
		this->shape.move(0.f , -this->getMovementSpeed());
}

void Player::updateTurnPointCollision()
{

	//check for collisions between all collected balls and all existing turnpoints!
	int i = 0;
	int x = 0;
	while(i < this->getCollectedBallsLength())
	{
		x = 0;
		while (x < this->getTurnPointsLength())
		{
			if (this->collectedBalls[i].getShape().getGlobalBounds().intersects(this->turnPoints[x].getShape().getGlobalBounds()))
			{
				logger(1, "ball:" + to_string(collectedBalls[i].getBallNumb()) + " collided with turn point");

				// place ball centered behind player
				//get player's position
				float x_pos = this->getShape().getGlobalBounds().left;
				float y_pos = this->getShape().getGlobalBounds().top;
				float offset = ((this->getWidth()) * 1.5) * ((float)i + 1.0);

				int dir = this->turnPoints[x].getNewDirection();

				if (dir == 1) // to the right
				{
					this->collectedBalls[i].align(x_pos - offset, y_pos);
				}
				else if (dir == 2) // downwards
				{
					this->collectedBalls[i].align(x_pos, y_pos - offset);
				}
				else if (dir == 3) // to the left
				{
					this->collectedBalls[i].align(x_pos + offset, y_pos);
				}
				else if (dir == 4) // upwards
				{
					this->collectedBalls[i].align(x_pos, y_pos + offset);
				}
				logger(1, "ball:" + to_string(collectedBalls[i].getBallNumb()) + " is realigned");

				//assign new movement direction saved in turn point to collided ball
				this->collectedBalls[i].setMovementDirection(dir);
				logger(1, "ball:" + to_string(collectedBalls[i].getBallNumb()) + " changed movemenDirection to:" + to_string(dir));

				// if this is the last collected ball the turn point can disappear
				if (this->collectedBalls[i].getBallNumb() == this->collectedBalls.back().getBallNumb())
				{
					this->turnPoints.pop_back();

					logger(1, "turn point deleted");
				}
				
			}
			x++;
		}
		i++;
	}
	
}

void Player::updateCollectedBalls()
{
	int i = 0;
	while (i < this->getCollectedBallsLength())
	{
		this->collectedBalls[i].update();

		i++;
	}
}

void Player::updateInput() {
	//keypoard input collects the change of directions by ASWD and arrow keys


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == false)
		{
			this->setMovementDirection(3); // to the left
		}
		else
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == true)
			{
				this->setMovementDirection(3); // to the left

				//define new turnpoint
				TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
				tp.setNewDirection(3);
				// push created tp into turnPoints vector

				this->addTurnPoint(tp);
			}
			else
			{
				// check if turn point is not overlapping
				bool t = this->checkTPDist(this->getMovementDirection());

				if (t) {

					this->setMovementDirection(3); // to the left

					//define new turnpoint
					TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
					tp.setNewDirection(3);
					// push created tp into turnPoints vector

					this->addTurnPoint(tp);
				}
			}
			
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == false)
		{
			this->setMovementDirection(1); // to the right
		}
		else
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == true)
			{
				this->setMovementDirection(1); // to the right

				//define new turnpoint
				TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
				tp.setNewDirection(1);
				// push created tp into turnPoints vector

				this->addTurnPoint(tp);
			}
			else
			{
				// check if turn point is not overlapping
				bool t = this->checkTPDist(this->getMovementDirection());

				if (t) {

					this->setMovementDirection(1); // to the right

					//define new turnpoint
					TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
					tp.setNewDirection(1);
					// push created tp into turnPoints vector

					this->addTurnPoint(tp);
				}
			}

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == false)
		{
			this->setMovementDirection(4); // upwards
		}
		else
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == true)
			{
				this->setMovementDirection(4); // upwards

				//define new turnpoint
				TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
				tp.setNewDirection(4);
				// push created tp into turnPoints vector

				this->addTurnPoint(tp);
			}
			else
			{
				// check if turn point is not overlapping
				bool t = this->checkTPDist(this->getMovementDirection());

				if (t) {

					this->setMovementDirection(4); // upwards

					//define new turnpoint
					TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
					tp.setNewDirection(4);
					// push created tp into turnPoints vector

					this->addTurnPoint(tp);
				}
			}

		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// check if there are already any balls collected
		bool collected = !this->collectedBalls.empty();

		if (collected == false)
		{
			this->setMovementDirection(2); // downwards
		}
		else
		{
			// check if there are already any turn points
			bool empty = this->turnPoints.empty();

			if (empty == true)
			{
				this->setMovementDirection(2); // downwards

				//define new turnpoint
				TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
				tp.setNewDirection(2);
				// push created tp into turnPoints vector

				this->addTurnPoint(tp);
			}
			else
			{
				// check if turn point is not overlapping
				bool t = this->checkTPDist(this->getMovementDirection());

				if (t) {

					this->setMovementDirection(2); // downwards

					//define new turnpoint
					TurnPoint tp = TurnPoint(this->getXPosition(), this->getYPosition());
					tp.setNewDirection(2);
					// push created tp into turnPoints vector

					this->addTurnPoint(tp);
				}
			}

		}
	}



}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//checks continuously for collision with game Window borders
	//Up
	if (this->getYPosition() <= 0.f)
		this->shape.setPosition(shape.getGlobalBounds().left, 0.f);
	//Down
	if (this->getYPosition() + shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);

	//Left
	if (this->getXPosition() <= 0.f)
		this->shape.setPosition(0.f, shape.getGlobalBounds().top);
	//Right
	if (this->getXPosition() + shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);

}

bool Player::checkTPDist(int mDir)
{
		//check for enough distance between 2 turn points
		float dist; // distance between last turnPoint and wanted new one at current Player's position
		if (mDir == 1) // to the right
		{
			dist = this->getXPosition() - this->turnPoints.back().getXPos();
		}
		else if (mDir == 2) //downwards
		{
			dist = this->getYPosition() - this->turnPoints.back().getYPos();
		}
		else if (mDir == 3) // to the left
		{
			dist = this->turnPoints.back().getXPos() - this->getXPosition();
		}
		else if (mDir == 4) //upwards
		{
			dist = this->turnPoints.back().getYPos() - this->getYPosition();
		}

		bool space = (dist > this->getWidth() + 5);

		if (space == true)
		{
			return true;
		}
}


//constructor
Player::Player()
{

}
Player::Player(float iX, float iY, float w, float h)
{
	this->initVariables( iX,  iY,  w,  h);
	this->initShape();
}

//destructor
Player::~Player()
{
}


//public functions
void Player::update(sf::RenderTarget* targetWindow) //sf::RenderTarget* targetWindow
{
	//get keystrokes
	this->updateInput();

	//move player in direction
	this->moving();

	//window bounds collision
	//targetWindow->getSize();
	this->updateWindowBoundsCollision(targetWindow);

	//update the players collected balls
	this->updateCollectedBalls();

	//if collected ball collides with turn point
	this->updateTurnPointCollision();

}

void Player::render(sf::RenderTarget * targetWindow)
{
	//render player shape to game window
	targetWindow->draw(this->shape);

	//rendering of the collected balls
	int i = 0;
	while (i < this->getCollectedBallsLength())
	{
		this->collectedBalls[i].render(targetWindow);

		i++;
	}

	//render turnpoints
	i = 0;
	while (i < this->getTurnPointsLength())
	{
		this->turnPoints[i].render(targetWindow);

		i++;
	}
}


//accesors
void Player::setMovementDirection(int d)
{
	this->movementDirection = d;
}
int Player::getMovementDirection()
{
	return this->movementDirection;
}

void Player::setMovementSpeed(float s)
{
	this->movementSpeed = s;
}
float Player::getMovementSpeed()
{
	return this->movementSpeed;
}

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

void Player::setInitX(float iX)
{
	this->initX = iX;
}
float Player::getInitX()
{
	return this->initX;
}

void Player::setInitY(float iY)
{
	this->initY = iY;
}
float Player::getInitY()
{
	return this->initY;
}

float Player::getXPosition()
{
	return  this->getShape().getGlobalBounds().left;
}
float Player::getYPosition()
{
	return this->getShape().getGlobalBounds().top;
}

void Player::addBall(Ball b)
{
	this->collectedBalls.push_back(b); // pushes Ball into player's collection of balls vector
	logger(1, "added ball to vector collectedBalls.");

	//give the newly added ball direction and speed of player to follow him
	this->collectedBalls.back().setMovementDirection(this->getMovementDirection());
	this->collectedBalls.back().setMovementSpeed(this->getMovementSpeed());
}
int Player::getCollectedBallsLength()
{
	return collectedBalls.size();
}

void Player::addTurnPoint(TurnPoint tP)
{
	this->turnPoints.push_back(tP);
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

