#include "Bacteria.h"



Bacteria::Bacteria()
{
}

Bacteria::Bacteria(float x, float y, bool isBadBacteria)
{
	shape.setPosition(x, y);
	
	
	health = 1;
	isBad = isBadBacteria;
	isBad ? shape.setFillColor(sf::Color::Red) : shape.setFillColor(sf::Color::Green);
	isBad ? shape.setRadius(m_radi + 5) : shape.setRadius(m_radi);
	shape.setOrigin(m_radi, m_radi);

	id = rand() % 40654483849;
}

//NEW COPY REPRODUCE
Bacteria::Bacteria(float x, float y, bool isBadBacteria, float radius, Bacteria parent)
{
	shape.setPosition(x, y);


	health = 1;
	isBad = isBadBacteria;
	isBad ? shape.setFillColor(sf::Color::Red) : shape.setFillColor(sf::Color::Green);
	
	shape.move(sf::Vector2f(parent.velocity.x - 10.f, parent.velocity.y + 20.f));
	shape.setRadius(radius);

	id = rand() % 40654483849;
}




void Bacteria::update(std::unordered_set<int> &idsToDelete, std::vector<Bacteria> &bacV, std::vector<Cell> &cells, std::unordered_map<int, Cell> &bacToCell,
	std::unordered_map<int, std::unordered_set<int>> &mapCellsToBac, std::unordered_map<int, Bacteria> &idToBacMap)
{
	
	Bacteria b = *this;
	

	//Check for current cell placement
	idToBacMap[b.id] = (*this);

	Cell currCell;
	int currCellID = 0;
	//if this bacteria no longer intersects with its previously mapped one
	if ((bacToCell.find((b).id) == bacToCell.end()) || (!bacToCell.at((b).id).shape.getGlobalBounds().intersects((b).shape.getGlobalBounds())))
	{
		//update find new cell for this bacteria to belong to
		for (int i = 0; i < cells.size(); ++i) {
			if (cells[i].shape.getGlobalBounds().intersects((b).shape.getGlobalBounds())) {
				auto it = bacToCell.find(b.id);
				//FIND NEW CELL
				if (it != bacToCell.end()) {
					it->second = cells[i];
				}
				else {
					bacToCell.insert(std::make_pair(b.id, cells[i]));
				}
				std::cout << "NEW BAC MAPPED TO A NEW CELL !!!" << std::endl;
				currCell = cells[i];
				currCellID = cells[i].id;
				break;
			}
		}
	}
	//IF STILL COLLIDING WITH PREVIOUS RECTANGLE (DIDNT MOVE OUT OF BOUNDS)
	if (currCellID == 0) { 
		currCell = bacToCell[b.id];
		currCellID = bacToCell[b.id].id;
	}
	//UPDATE SET WITH BACTERIA 
	auto it = mapCellsToBac.find(currCellID);
	
	if (it != mapCellsToBac.end()) {
		//update set
		it->second.insert(b.id);
		
	}
	else { //create new set
		
		std::unordered_set<int> newSet;
		newSet.insert(b.id);

		mapCellsToBac.insert(std::make_pair(currCellID, newSet));

		
	}

	//LOOK AT ALL BACTERIA IN THIS CELL CHECK FOR COLLISION IN HERE IF I AM BAD AND THEY ARE GOOD
	if (isBad) {
		for (int bacID : mapCellsToBac[currCellID]) {
			Bacteria otherBac = idToBacMap[bacID];
			if ((isBad && !otherBac.isBad) && otherBac.id != id && otherBac.shape.getGlobalBounds().intersects(shape.getGlobalBounds()) && otherBac.health != 0 && health != 0) {
				std::cout << "COLLISION" << std::endl;
				if (otherBac.shape.getRadius() < shape.getRadius()) {
					shape.setRadius(b.shape.getRadius() + (.5 * otherBac.shape.getRadius()));
					idToBacMap[bacID].health = 0;
					idsToDelete.insert(bacID);
				}
			}
		}
	}


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
	

	//Reproduce
		
	if (isBad) {
		if (frames > 1000 && rand() % 42 == 0 && bacV.size() <= 5000)
		{
			frames = 0;
			if (this->isBad)
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, true, shape.getRadius(), (*this)); //spawn bad bac
				bacV.push_back(newBacteria);
			}
			else
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, false, shape.getRadius(), (*this)); //spawn good bac
				bacV.push_back(newBacteria);
			}


		}
	}
	else { //GOOD BACTERIA REPRODUCE FASTER

		if (frames > 500 && bacV.size() <= 5000)
		{
			frames = 0;
			if (this->isBad)
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, true, shape.getRadius(), (*this)); //spawn bad bac
				bacV.push_back(newBacteria);
			}
			else
			{
				Bacteria newBacteria(this->shape.getPosition().x, this->shape.getPosition().y, false, shape.getRadius(), (*this)); //spawn good bac
				bacV.push_back(newBacteria);
			}


		}
	}
		

	
}

