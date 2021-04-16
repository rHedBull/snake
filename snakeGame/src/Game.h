#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Util.h"
#include "Ball.h"

class Game
{
private:

	//private variables
	
	//window variables
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	int width;
	int height;
	int frameRate;
	string name;


	// Game objects
	Player player;  // player object is created as part of game init
	std::vector <Ball> newBall; // always just one element, the newest spanned ball
	

	//private functions
	void initVariables();
	void initWindow();
	void ballSpawn();
	

public:
	//constructor
	Game(int width, int height, int frameRate, string name);

	//destructor
	~Game();
	
	
	// public functions
	void pollEvents();
	void update();
	void render();
	void updateCollision();


	//accessors:
	const bool running() const;

	void setWidth(int w);
	int getWidth();

	void setHeight(int h);
	int getHeight();

	void setFrameRate(int fR);
	int getFrameRate();

	void setName(string n);
	string getName();

	void addBall(Ball b);
	void deleteBall();
};

