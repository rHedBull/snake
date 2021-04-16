#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Ball
{
private:
	//private variables
	sf::CircleShape shape;

	int radius;


	//private functions
	void initVars();
	void initShape(int x, int y);


public:
	//constructor
	Ball();

	//destructor
	virtual ~Ball();


	//public functions
	void update();
	void render(sf::RenderTarget* targetWindow);


	//accesors
	void setRadius(int r);
	int getRadius();

	const sf::CircleShape getShape() const;
};

