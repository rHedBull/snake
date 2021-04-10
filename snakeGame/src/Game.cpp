#include "Game.h"

//constructor:
Game::Game()
{

}

//destructor:
Game::~Game() 
{
	delete this->window;
}

//private functions:

void Game::initVariables() 
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = (600);
	this->videoMode.width = (600);
	this->window = new sf::RenderWindow(this->videoMode, "SnakeGame", sf::Style::Titlebar | sf::Style::Close);
}

//accessors:

const bool Game::running() const
{
	return this->window->isOpen();
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

	this->window->clear(sf::Color(255, 0, 0));

	//draw game:
	this->window -> display();
}

void Game::update()
{
	this->pollEvents();

}