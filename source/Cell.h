#pragma once
#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>
#include<math.h>

class Cell
{
public:
	sf::RectangleShape shape;
	int id;
	Cell(int id, sf::RectangleShape shape) {
		(*this).id = id;
		(*this).shape = shape;
	}
	Cell() {

	}

	
};

