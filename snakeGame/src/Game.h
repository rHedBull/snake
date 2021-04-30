#ifndef Game_H
#define Game_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

#include "Ball.h"
#include "Player.h"


class Game
{
private:

	//private variables
	float movementSpeed;

	//window variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	int width;
	int height;
	int frameRate;
	std::string name;


	// Game objects
	// player object is created as part of game init
	Player player;  
	std::vector <Ball> newBall; // always just one element, the newest spanned ball

	int ballCount = 1;

	//private functions
	void initVariables(int width, int height, int frameRate, float speed, std::string name);
	void initWindow();
	void ballSpawn();
	void reassignBall();
	void updateCollision();
	

public:
	//constructor
	Game(int width, int height, int frameRate, float speed, std::string name);

	//destructor
	~Game();
	
	
	// public functions
	void pollEvents();
	void update();
	void render();


	//accessors:
	const bool running() const;

	float getMovementSpeed();
	void setMovementSpeed(float s);

	void setBallCount(int c);
	int getBallCount() const;

	void setWidth(int w);
	int getWidth();

	void setHeight(int h);
	int getHeight();

	void setFrameRate(int fR);
	int getFrameRate();

	void setName(std::string n);
	std::string getName();
};

#endif