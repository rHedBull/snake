#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(int x_pos, int y_pos) {
	sf::RectangleShape line(sf::Vector2f(150.f, 5.f));
}

void Rectangle::position(int x_pos, int y_pos) {
	this->setPosition(sf::Vector2f(x_pos, y_pos));
}

	/*void Rectangle::print(string s) {
		std::cout << s << std::endl;
	}

	void Rectangle::func(string s) {
		Rectangle::x = 11;
		std::cout << s << std::endl;
		this->print("yap");
	}*/

	int Rectangle::getX() {
		return x;
	}

	void Rectangle::setX(int newX) {
		x = newX;
	}

