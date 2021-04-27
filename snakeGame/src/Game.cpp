#include "Game.h"
#include "Util.h"

//private functions:
void Game::initVariables(int width, int height, int frameRate, float speed, std::string name)
{
	//initialize game variables
	this->window = nullptr;
	this->setFrameRate(frameRate);
	this->setHeight(height);
	this->setWidth(width);
	this->setName(name);
	this->setMovementSpeed(speed);
	logger(1, "game variables initialized");

	//define Player
	this->player = Player(this->getHeight()/2, this->getWidth()/2, this->getWidth()/20, this->getHeight()/20);
}

void Game::initWindow()
{
	//initialize window
	this->videoMode.height = (this->height);
	this->videoMode.width = (this->width);
	this->window = new sf::RenderWindow(this->videoMode, this->name , sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(this->frameRate);
	logger(1, "window \'" + this->name + "\' initialized. height:" + std::to_string(this->height) + ", width:"+ std::to_string(this->width));
	
}

void Game::ballSpawn()
{
	//spawn the newest ball
	Ball ball = Ball(this->getWidth(), this->getHeight(), this->getBallCount());
	this->setBallCount(this->getBallCount() + 1);
	addBall(ball); // pushes the newly created ball into the Game classes vector newBall
}

void Game::reassignBall() {
	//moves newest collisioned ball from Game to player
	//deletes old newest ball

	int dir = this->player.getMovementDirection();// get movement direction from the player

	//place ball behind the player
	//get player's position
	float x_pos = this->player.getXPos();
	float y_pos = this->player.getYPos();
	float offset = ((this->player.getWidth()) * 1.5) * ((float) this->player.getCollectedBallsLength() + 1.0); // to place ball behind player depends on direction
	if (dir == 1) // to the right
	{
		this->newBall.front().align(x_pos - offset, y_pos);
	}
	else if (dir == 2) // downwards
	{
		this->newBall.front().align(x_pos, y_pos - offset);
	}else if (dir == 3) // to the left
	{
		this->newBall.front().align(x_pos + offset, y_pos);
	}
	else if (dir == 4) // upwards
	{
		this->newBall.front().align(x_pos, y_pos + offset);
	}	

	
	this->player.addBall(this->newBall.front()); // moves newest ball to player's ball collection

	this->emptyBall(); // deletes Ball from Game classes vector newBall
	logger(1, "old \"newBall\" \'ball\' has been deleted");
}

void Game::updateCollision()
{
	// updates collision between player and newest ball
	if (this->player.getShape().getGlobalBounds().intersects(this->newBall[0].getShape().getGlobalBounds()))
	{
		logger(1, "collision occured!");
		this->reassignBall(); //configere new ball handling
		this->ballSpawn(); // creates new ball
	}
}


//constructor:
Game::Game(int width, int height, int frameRate, float speed, std::string name)
{
	logger(1, "intialize game");
	this->initVariables(width, height, frameRate, speed,  name);
	this->initWindow();
	this->ballSpawn(); //create first ball commented out while new Movement scheme is developed
	logger(1, "game initialized");
}

//destructor:
Game::~Game()
{
	delete this->window;
	logger(1, "window deleted");
}


//public functions:
void Game::pollEvents()
{
	//Event polling
		while (this->window->pollEvent(this->ev))
		{
			switch (this->ev.type)
			{
				case sf::Event::Closed:
					this->window->close();
					break;

				case sf::Event::KeyPressed:
					if (this->ev.key.code == sf::Keyboard::Escape)
						this->window->close();
					break;
			}
		}
}

void Game::render()
{
	/* render the game objects
	*	- clear old frame
	*	- render objects
	*	- display new frame in window
	*/
	
	this->window->clear(); //clear

	//render objects
	this->player.render(this->window);     // also calls rendering for the collected balls!
	this->newBall[0].render(this->window); //commented out while new Movement scheme is developed
	
	
	
	//draw game:
	this->window -> display();
}

void Game::update()
{
	// poll for newest events(keypress, ...)
	this->pollEvents();

	this->player.update(this->window, this->getMovementSpeed()); //only one instance of player, also calls updating the collected balls
	
	//update interactions between multiple objects
	this->updateCollision(); //commented out while new Movement scheme is developed
}




//accessors:
const bool Game::running() const
{
	// test if the game window still is opened
	return this->window->isOpen();
}

float Game::getMovementSpeed()
{
	return this->movementSpeed;
}
void Game::setMovementSpeed(float s)
{
	this->movementSpeed = s;
}

void Game::setBallCount(int c)
{
	this->ballCount = c;
}
int Game::getBallCount() const
{
	return this->ballCount;
}

void Game::setWidth(int w)
{
	this->width = w;
}
int Game::getWidth()
{
	return this->width;
}

void Game::setHeight(int h)
{
	this->height = h;
}
int Game::getHeight()
{
	return this->height;
}

void Game::setFrameRate(int fR)
{
	this->frameRate = fR;
}
int Game::getFrameRate()
{
	return this->frameRate;
}

void Game::setName(std::string n)
{
	this->name = n;
}
std::string Game::getName()
{
	return this->name;
}

void Game::addBall(Ball b)
{
	//add ball to vector newBall of the Game class
	this->newBall.push_back(b); // vector newBall always has only one element so at index = 0
}
void Game::emptyBall()
{
	//delete ball from the vector newBall from this instance's Game class
	this->newBall.pop_back();

}