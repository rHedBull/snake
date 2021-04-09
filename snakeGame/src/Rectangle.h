#ifndef Rectangle_H
#define Rectangle_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Rectangle : public sf::RectangleShape
{
//private
	
public:
	int x = 10;

	Rectangle(int x_pos, int y_pos);

	void position(int x_pos, int y_pos);

	int getX();

	void setX(int x);
};
#endif
