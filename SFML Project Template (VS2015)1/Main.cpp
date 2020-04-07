#include <SFML/Graphics.hpp>
#include "Bacteria.h"
#include "Virus.h"
#include <vector>
#include <time.h>
#include "Cell.h"
//generic function that checks for intersection between two objects
template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.top() <= mB.bottom() && mA.bottom() >= mB.top();
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(2000, 800), "Bacteria Simulation");
	sf::Mouse::setPosition({ 1300, 720 }, window);
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
	
	//Bacteria badBacteria(1280.f / 2, 720.f / 2, true);
	//testBacteria.sprite.setTexture(bacT);
	std::vector<Bacteria> bacG;
	bacG.push_back(goodBacteria);
	std::vector<Bacteria> bacB;
	//bacB.push_back(badBacteria);

	std::vector<Cell> cells;

	std::unordered_set<int> deleteIDS;

	std::unordered_map<int, Cell> bacToCell;
	std::unordered_map<int, std::unordered_set<int>> cellsToBac; 
	std::unordered_map<int, Bacteria> idToBac;


	int locationX = 0;
	int thresholdX = 2000;
	int thresholdY = 800;
	for (int i = 0; i < thresholdY; i += 400) {
		for (int j = 0; j < thresholdX; j += 400) {
			
			sf::RectangleShape rectangle(sf::Vector2f(0, 0));
			
			rectangle.move(j, i);

			// change the size to 100x100
			rectangle.setSize(sf::Vector2f(400, 400));
			rectangle.setOutlineThickness(2.0);
			rectangle.setOutlineColor(sf::Color::Black);
			//update map
			Cell c(rand() % 4000, rectangle);
			cells.push_back(c);

		}
	}
	



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
				Bacteria badBacteria(sf::Mouse::getPosition().x + 24.f, sf::Mouse::getPosition().y - 200.f, true);
				//Virus spawn(sf::Mouse::getPosition().x + 24.f , sf::Mouse::getPosition().y - 200.f);
				//spawn.sprite.setTexture(virusT);
				//virusV.push_back(spawn);
				bacB.push_back(badBacteria);
			
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				Bacteria goodBacteria(sf::Mouse::getPosition().x + 24.f, sf::Mouse::getPosition().y - 200.f, false);
				//Virus spawn(sf::Mouse::getPosition().x + 24.f , sf::Mouse::getPosition().y - 200.f);
				//spawn.sprite.setTexture(virusT);
				//virusV.push_back(spawn);
				bacG.push_back(goodBacteria);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				bacB.clear();
				bacG.clear();
			}
		
			/*
			
			Virus v;
			v.initialize();
			if(mouseClick)
			initialize virus at mouse click

			*/
			
				

		}
	
		window.clear();

	
		

		//CELLS FOR OBJECT COLLISIONS
		for(int i = 0; i < cells.size(); ++i)
			window.draw(cells[i].shape);
		

		//window.draw(testBacteria.shape);
		int sizeG = bacG.size();
		for (int x = 0; x < sizeG; ++x)
		{
			
			bacG[x].update(deleteIDS, bacG, cells, bacToCell, cellsToBac, idToBac);
			

		}
		int sizeB = bacB.size();
		for (int x = 0; x < sizeB; ++x)
		{
		
			bacB[x].update(deleteIDS, bacB, cells, bacToCell, cellsToBac, idToBac);
		
		
		}

		//DELETE HEALTH 0 GOOD BACTERIA
		for (int x = 0; x < bacG.size(); ++x)
		{
			if (deleteIDS.find(bacG[x].id) != deleteIDS.end()) {
				bacG.erase(bacG.begin() + x);
			}

		}

		for (Bacteria b : bacB) 
			window.draw(b.shape);
		
		for (Bacteria b : bacG) 
			window.draw(b.shape);
		
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