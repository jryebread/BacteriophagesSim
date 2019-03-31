#include "Virus.h"


//constructs virus and takes in position (mouse pos)
Virus::Virus(float x, float y)
{
	sprite.setPosition(x, y);
	sprite.setScale(sf::Vector2f(0.1f, 0.1f));
	sprite.setOrigin(sprite.getScale().x / 2, sprite.getScale().y / 2);
	
}

void Virus::update(std::vector<Virus>& virusVector, float time)
{
	//if(badBacNearby())
	//	velocity.x = 
	++frameCount;
	rng = rand() % 10;
	if (frameCount > 100)
	{

		velocity.x += frameCount % 2 == 0 ? rng : time - sin(time) * rng;
		velocity.y += frameCount % 2 == 0 ? rng : time - cos(time) * rng;
		frameCount = 0;
	}
	
	sprite.move(velocity);
	
	
	// std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
	// SFML's y-axis is flipped: flip our y-component
	auto angleRads = std::atan2(-velocity.y, velocity.x);
	auto angleDegs = angleRads * 180.0 / 3.14;
	sprite.rotate(angleDegs);
	//IN SFML, 0,0 is the top left corner of the screen which is we check if < 0, 
	//If its leaving toward the left, we need to set the horizontal velocity to a positive value(towards the right)
	if (left() < 0) velocity.x = this->vSpeed;

	//Otherwise if its leaving toward the right, we need to set horizontal velocity to a negative value (left)
	else if (right() > windowWidth) velocity.x = -vSpeed;

	//same idea can be applied for top/bottom collisions
	if (top() < 0) velocity.y = vSpeed;

	else if (bottom() > windowHeight) velocity.y = -vSpeed;

	
	
}

