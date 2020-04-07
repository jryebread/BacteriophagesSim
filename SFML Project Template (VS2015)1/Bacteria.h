#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include "Cell.h"

constexpr int windowWidth{ 2000 }, windowHeight{ 800};
class Bacteria
{
public:
	Bacteria();
	Bacteria(float x, float y, bool bacteriaAlliegance);
	//copy constructor
	Bacteria(float x, float y, bool bacteriaAlliegance, float radius, Bacteria parent);
	sf::CircleShape shape;
	void update(std::unordered_set<int> &idsToDelete, std::vector<Bacteria> &bacV, std::vector<Cell> &cells, std::unordered_map<int, Cell> &bacToCell,
		std::unordered_map<int, std::unordered_set<int>> &mapCellsToBac, std::unordered_map<int, Bacteria> &idToBacMap);
	int health;
	int id;
private:

	

	int frames{ 0 };
	float bacSpeed{ 2.f };
	sf::Vector2f velocity{ -bacSpeed, -bacSpeed };
	bool isBad;
	float m_radi = 6.0f;
	
	//property methods
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }

};

