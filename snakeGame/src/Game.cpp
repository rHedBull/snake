#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.h"
#include "Util.h"


//private functions:
// ---------- init game --------------------------------------------------------------------------
/*
intialize all the game's variables and the player object
parameters:
int width;
int height;
int frameRate;
float speed;
std::string name;
*/
void Game::initVariables(int width, int height, int frameRate, float speed, std::string name)
{
	//initialize game variables
	this->window = nullptr;
	this->setFrameRate(frameRate);
	this->setHeight(height);
	this->setWidth(width);
	this->setName(name);
	this->setInitialMovementSpeed(speed);
	this->setCurrentMovementSpeed(this->getInitialMovementSpeed());
	this->setBallCount(0);
	this->setGameState(0); // game has not yet started
	logger(1, "game variables initialized");

	//define Player
	this->player = Player(this->getHeight()/2, this->getWidth()/2, this->getWidth()/20, this->getHeight()/20);
}

/*
initialize the game window
*/
void Game::initWindow()
{
	//initialize window
	this->videoMode.height = (this->height);
	this->videoMode.width = (this->width);
	this->window = new sf::RenderWindow(this->videoMode, this->name , sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(this->frameRate);
	logger(1, "window \'" + this->name + "\' initialized. height:" + std::to_string(this->height) + ", width:"+ std::to_string(this->width));
	
}

/*
initialize and load the used fonts
*/
void Game::initFont()
{
	if (!this->font.loadFromFile("res/arial.ttf"))
	{
		logger(3, "Game initFont() could not load \"arial.ttf\" ");
	}
}

/*
initialize the text
*/
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setFillColor(sf::Color::Green);
	this->uiText.setCharacterSize(25);
	this->uiText.setString("None");
}
//------------------------------------------------------------------------------------------------
//----------- update and render running game -----------------------------------------------------
/*
spawns newBall at random position within game window
*/
void Game::ballSpawn()
{
	//spawn the newest ball
	Ball ball = Ball(this->getWidth(), this->getHeight(), this->getBallCount());
	this->setBallCount(this->getBallCount() + 1);
	this->newBall.push_back(ball); // pushes the newly created ball into the Game classes vector newBall
}

/*
*	places collisioned ball behind player or the last collected ball
	moves  collisioned ball from Game to player
	deletes old newest ball
*/
void Game::reassignBall() 
{
	int dir = 0;

	// if no ball collected yet
	if (this->player.getCollectedBallsLength() == 0)
	{
		dir = this->player.getMovementDirection();// get movement direction from the player

		//place ball behind the player
		//get player's position
		float x_pos = this->player.getXPos();
		float y_pos = this->player.getYPos();
		float offset = (this->newBall.front().getRadius() * 2.7); // to place ball behind player depends on direction
		if (dir == 1) // to the right
		{
			this->newBall.front().align(x_pos - offset, y_pos);
		}
		else if (dir == 2) // downwards
		{
			this->newBall.front().align(x_pos, y_pos - offset);
		}
		else if (dir == 3) // to the left
		{
			this->newBall.front().align(x_pos + offset, y_pos);
		}
		else if (dir == 4) // upwards
		{
			this->newBall.front().align(x_pos, y_pos + offset);
		}
	}
	else // if already collected balls
	{
		//place newly collected ball behind last collected ball
		dir = this->player.getCollectedBalls().back().getMovementDirection();

		float x_pos = this->player.getCollectedBalls().back().getXPos();
		float y_pos = this->player.getCollectedBalls().back().getYPos();
		float offset = (this->player.getCollectedBalls().back().getRadius() * 2.7);// to place ball behind player depends on direction

		if (dir == 1) // to the right
		{
			this->newBall.front().align(x_pos - offset, y_pos);
		}
		else if (dir == 2) // downwards
		{
			this->newBall.front().align(x_pos, y_pos - offset);
		}
		else if (dir == 3) // to the left
		{
			this->newBall.front().align(x_pos + offset, y_pos);
		}
		else if (dir == 4) // upwards
		{
			this->newBall.front().align(x_pos, y_pos + offset);
		}

	}
	
	//assign new movementDirection to ball
	this->newBall.front().setMovementDirection(dir);
	
	this->player.addBall(this->newBall.front()); // moves newest ball to player's ball collection

	this->newBall.clear(); // deletes Ball from Game classes vector newBall
	logger(1, "old \"newBall\" \'ball\' has been deleted");
}

/*
updates collisions
- between player and newest ball
- between player and his collected balls
- between player and the window edges
*/
void Game::updateCollision()
{
	//collision between player and newly created balls
	if (this->player.getShape().getGlobalBounds().intersects(this->newBall[0].getShape().getGlobalBounds()))
	{
		logger(1, "collision with new ball occured!");
		this->reassignBall(); //configure new ball handling
		if (this->player.getCollectedBallsLength() == 1)
		{
			//create new segment extra for newly collected ball
			this->player.createPreliminarySegment(this->player.getMovementDirection());
			logger(1, "extra segment for ball created");
		}

		this->ballSpawn(); // creates new ball
		return;
	}

	// update collision between player and his collected balls
	int i = 1;
	while (i < this->player.getCollectedBallsLength())
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->player.getCollectedBalls()[i].getShape().getGlobalBounds()))
		{
			this->endGame();
		}
		i++;
	}

	//check for collision between window edges and player
	const sf::RenderTarget* target = this->window;
		if (this->player.getYPos() <= 0.f || this->player.getYPos() + this->player.getShape().getGlobalBounds().height >= target->getSize().y || this->player.getXPos() <= 0.f || this->player.getXPos() + this->player.getShape().getGlobalBounds().width >= target->getSize().x)
		{
			this->endGame();
		}	
}

/*
updates the text depending on the current gameState
*/
void Game::updateUI()
{
	stringstream sStream;
	if (this->getGameState() == 0) //game has not started yet
	{
		sStream << "press any Key to start the game";
		this->uiText.setPosition((this->getWidth()/2) - 150, this->getHeight()/2);

	}else if (this->getGameState() == 1)//game is running
	{
		sStream << "score: " << (this->player.getCollectedBallsLength());
		this->uiText.setPosition(5, 5);
	}
	else if (this->getGameState() == 2)// game ended
	{
		sStream << "Game Over! your final score: " << (this->player.getCollectedBallsLength()) << "\n" << "\n" << "or Esc to exit the Game";
		this->uiText.setPosition((this->getWidth() / 2) - 150, this->getHeight() / 2);
	}
	this->uiText.setString(sStream.str());	
}

/*
renders the text to the RenderTarget window
parameters:
sf::RenderTarget& target;
*/
void Game::renderUI(sf::RenderTarget* target)
{
	target->draw(this->uiText);
}

/*
restarts the game by setting many variables to their initial value
*/
void Game::restartGame()
{
	this->setCurrentMovementSpeed(this->getInitialMovementSpeed());
	this->newBall.clear();
	this->setBallCount(0);
	this->ballSpawn();
	this->setGameState(1);

	//reset the player
	this->player.restart(this->getHeight() / 2, this->getWidth() / 2);
	logger(1, "game restarted");
}
//--------------------------------------------------------------------------------------------------


//constructor:
/*
constructs instance of game class
parameters:
int width;
int height;
int frameRate;
float speed;
std::string name;
*/
Game::Game(int width, int height, int frameRate, float speed, std::string name)
{
	logger(1, "intialize game");
	this->initVariables(width, height, frameRate, speed,  name);
	this->initWindow();

	this->initFont();
	this->initText();

	this->ballSpawn(); //create first ball commented out while new Movement scheme is developed

	logger(1, "game initialized");
}

//destructor:
/*
called when this instance of the game class is destroyed
*/
Game::~Game()
{
	delete this->window;
	logger(1, "window deleted");
}
// ------------------------------------------------------------------------------------------------------


//public functions:
/*
collecteds all the Events that happen
*/
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

/* render the game objects
- clear old frame
- render objects
- display new frame in window
*/
void Game::render()
{
	this->window->clear(); //clear

	if (this->getGameState() == 1)
	{
		//render objects
		this->player.render(this->window);     // also calls rendering for the collected balls!

		//render the newBall
		this->newBall[0].render(this->window);
	}

	this->renderUI(this->window);

	//draw game:
	this->window -> display();
}

/*
update all the game's variables and objects as well as the ui
*/
void Game::update()
{
	// poll for newest events(keypress, ...)
	this->pollEvents();

	if (this->getGameState() == 0)
	{
		bool leftKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool rightKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		if (leftKey || rightKey || upKey || downKey)
		{
			this->setGameState(1);
		}

	}else if (this->getGameState() == 1) // if game is running
	{
		//only one instance of player, also calls updating the collected balls
		this->player.update(this->getCurrentMovementSpeed());

		//update collision between player and newBall
		this->updateCollision();
	}
	else if (this->getGameState() == 2)
	{
		// check for restart of game
		bool enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

		if (enterKey)
		{
			this->restartGame();
		}
	}

		//update what should be printed as text
		this->updateUI();
}

/*
defines what happens when condition for ending the game are met
*/
void Game::endGame()
{
	this->setGameState(2);
	logger(1, "game ended");
}
// ------------------------------------------------------------------------------------------------------


//accessors:
const bool Game::running() const
{
	// test if the game window still is opened
	return this->window->isOpen();
}

float Game::getCurrentMovementSpeed()
{
	return this->currentMovementSpeed;
}
void Game::setCurrentMovementSpeed(float s)
{
	this->currentMovementSpeed = s;
}

float Game::getInitialMovementSpeed()
{
	return this->initialMovementSpeed;
}
void Game::setInitialMovementSpeed(float iS)
{
	this->initialMovementSpeed = iS;
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

void Game::setGameState(int gS)
{
	this->gameState = gS;
}
int Game::getGameState()
{
	return this->gameState;
}

void Game::setName(std::string n)
{
	this->name = n;
}
std::string Game::getName()
{
	return this->name;
}