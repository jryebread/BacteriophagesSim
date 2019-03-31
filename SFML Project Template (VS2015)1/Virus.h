#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>
#include<math.h>

class Virus
{
public:
	Virus(float x, float );
	sf::Vector2f velocity{ -vSpeed, -vSpeed };
	sf::Sprite sprite;
	void update(std::vector<Virus> &virusVector, float time);
private:
	int windowWidth{ 1280 }, windowHeight{ 720 };
	int rng = 1;
	int frameCount = 0;
	float vSpeed{ 2.f };
	//property methods
	float x() { return sprite.getPosition().x; }
	float y() { return sprite.getPosition().y; }
	float left() { return x() - sprite.getScale().x / 2.f; }
	float right() { return x() + sprite.getScale().x / 2.f; }
	float top() { return y() - sprite.getScale().y / 2.f; }
	float bottom() { return y() + sprite.getScale().y / 2.f; }
	
};

