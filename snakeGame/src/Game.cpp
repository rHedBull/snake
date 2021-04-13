#include "Game.h"
#include "Util.h"

//constructor:
Game::Game()
{
	logger(1, "intialize game");
	this->initVariables();
	this->initWindow();
	this->init_enemies();
	logger(1, "game initialized");
}

//destructor:
Game::~Game() 
{
	delete this->window;
	logger(1, "window deleted");
}

//private functions:

void Game::initVariables() 
{
	this->window = nullptr;
	logger(1, "game variables initialized");
}

void Game::initWindow()
{
	
	this->videoMode.height = (600);
	this->videoMode.width = (600);
	this->window = new sf::RenderWindow(this->videoMode, "SnakeGame", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(70);
	logger(1, "window initialized");
	
}

void Game::init_enemies() {
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
	logger(1, "enemies initialized");
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
	
	this->window->clear();

	this->window->draw(this->enemy);

	//draw game:
	this->window -> display();
}

void Game::update()
{
	this->pollEvents();

}