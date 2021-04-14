#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class Player
{
private:
	sf::RectangleShape shape;
	int movementSpeed;

	void initVariables();
	void initShape();

public:

	//constructor && destructor
	Player();
	~Player();

	void update();
	void updateInput();
	void render(sf::RenderTarget* targetWindow);

};

