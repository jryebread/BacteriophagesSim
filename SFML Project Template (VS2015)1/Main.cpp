#include <SFML/Graphics.hpp>
#include "Bacteria.h"
#include "Virus.h"
#include <vector>
#include <time.h>
//generic function that checks for intersection between two objects
template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.top() <= mB.bottom() && mA.bottom() >= mB.top();
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Bacteria Simulation");
	sf::Mouse::setPosition({ 1280, 720 }, window);
	srand(time(NULL));
	sf::Clock deltaClock;
	window.setFramerateLimit(60);
	///PIG TEXTURE AND SPRITE SETUP
	sf::Texture	virusT;
	virusT.loadFromFile("phage.png");
	if (!virusT.loadFromFile("phage.png")) {
		return EXIT_FAILURE;
	}
	std::vector<Virus> virusV;
	Bacteria goodBacteria(1280.f/2, 720.f/2, false);
	Bacteria badBacteria(1200.f / 2, 720.f / 2, true);
	//testBacteria.sprite.setTexture(bacT);
	std::vector<Bacteria> bacG;
	bacG.push_back(goodBacteria);
	std::vector<Bacteria> bacB;
	bacB.push_back(badBacteria);
	while (window.isOpen())
	{
		sf::Time time = deltaClock.restart();
		float dt = time.asSeconds();
		sf::Event event; //event buffer
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				Virus spawn(sf::Mouse::getPosition().x - 325.0f , sf::Mouse::getPosition().y - 200.f);
				spawn.sprite.setTexture(virusT);
				virusV.push_back(spawn);
			
			}
		
			/*
			
			Virus v;
			v.initialize();
			if(mouseClick)
			initialize virus at mouse click

			*/
			
				

		}
		
		window.clear();
		//window.draw(testBacteria.shape);
		int sizeG = bacG.size();
		for (int x = 0; x < sizeG; ++x)
		{
			window.draw(bacG[x].shape);
			bacG[x].update(bacG);
		}
		int sizeB = bacB.size();
		for (int x = 0; x < sizeB; ++x)
		{
			window.draw(bacB[x].shape);
			bacB[x].update(bacB);
		}
		int sizeV = virusV.size();
		for (int x = 0; x < sizeV; ++x)
		{
			window.draw(virusV[x].sprite);
			virusV[x].update(virusV, dt);
		}
		window.display();
	}

	return 0;
}