#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>
constexpr int windowWidth{ 1280 }, windowHeight{ 720};
class Bacteria
{
public:
	Bacteria(float x, float y, bool bacteriaAlliegance);
	sf::CircleShape shape;
	void update(std::vector<Bacteria> &bacV);
private:
	int frames{ 0 };
	float bacSpeed{ 2.f };
	sf::Vector2f velocity{ -bacSpeed, -bacSpeed };
	bool isBad;
	float m_radi = 6.0f;
	int health;
	//property methods
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }

};

