#include "Bacteria.h"



Bacteria::Bacteria(float x, float y, bool isBadBacteria)
{
	shape.setPosition(x, y);
	shape.setRadius(m_radi);
	isBad = isBadBacteria;
	isBad ? shape.setFillColor(sf::Color::Red) : shape.setFillColor(sf::Color::Green);
	shape.setOrigin(m_radi, m_radi);

}

void Bacteria::update(std::vector<Bacteria> &bacV)
{
	++frames;

	if (this->isBad)
	{
		shape.move(sf::Vector2f(rand() % 4, (rand() % 2)));
	}
	else	shape.move(sf::Vector2f(rand() % 4, rand() % 5));
	shape.move(velocity);
	//IN SFML, 0,0 is the top left corner of the screen which is we check if < 0, 
	//If its leaving toward the left, we need to set the horizontal velocity to a positive value(towards the right)
	if (left() < 0) velocity.x = bacSpeed;

	//Otherwise if its leaving toward the right, we need to set horizontal velocity to a negative value (left)
	else if (right() > windowWidth) velocity.x = -bacSpeed;

	//same idea can be applied for top/bottom collisions
	if (top() < 0) velocity.y = bacSpeed;

	else if (bottom() > windowHeight) velocity.y = -bacSpeed;
	int v1 = rand() % 10;
	if (v1 == 5);
	{
		
	}

	//Reproduce
		
		
		if (frames > 1000 && (rand() % 100) == 42 && bacV.size() <= 5000)
		{
			frames = 0;
			if (this->isBad)
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, true); //spawn bad bac
				bacV.push_back(newBacteria);
			}
			else
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, false); //spawn good bac
				bacV.push_back(newBacteria);
			}
			
			
		}
		

	
}

