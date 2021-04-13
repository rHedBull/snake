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

	void initVariables();
	void initShape();

public:

	//constructor && destructor
	Player();
	~Player();

	void update();
	void render(sf::RenderTarget* targetWindow);

};

