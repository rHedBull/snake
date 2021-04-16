#include "Game.h"
#include "Util.h"


//private functions:
void Game::initVariables() 
{
	//initialize game variables
	this->window = nullptr;
	logger(1, "game variables initialized");
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
	Ball ball;
	addBall(ball); // pushes the newly created ball into the Game classes vector newBall
}


//constructor:
Game::Game(int width, int height, int frameRate, string name)
{
	this->setFrameRate(frameRate);
	this->setHeight(height);
	this->setWidth(width);
	this->setName(name);


	logger(1, "intialize game");
	this->initVariables();
	this->initWindow();
	this->ballSpawn();
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
	this->player.render(this->window);
	this->newBall[0].render(this->window);
	
	//draw game:
	this->window -> display();
}

void Game::update()
{
	// poll for newest events(keypress, ...)
	this->pollEvents();

	//update different objects
	this->player.update(this->window); //only one instance of player
	this->newBall[0].update();
	
	//update interactions between multiple objects
	this->updateCollision();
}

void Game::updateCollision()
{
	// updates collision between player and newest ball
		if (this->player.getShape().getGlobalBounds().intersects(this->newBall[0].getShape().getGlobalBounds()))
		{
			logger(1, "collision occured!");
			this->player.addBall(this->newBall[0]); // moves newest ball to player's ball collection
			this->deleteBall(); // deletes Ball from Game classes vector newBall
			//this->newBall.~Ball();
			this->ballSpawn(); // creates new ball
		}
}


//accessors:
const bool Game::running() const
{
	// test if the game window still is opened
	return this->window->isOpen();
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

void Game::setName(string n)
{
	this->name = n;
}
string Game::getName()
{
	return this->name;
}

void Game::addBall(Ball b)
{
	//add ball to vector newBall of the Game class
	this->newBall.push_back(b); // vector newBall always has only one element so at index = 0
}
void Game::deleteBall()
{
	//delete ball from the vector newBall from this instance's Game class
	this->newBall.pop_back();
}