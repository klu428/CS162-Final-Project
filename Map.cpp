/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class implementation file for the Map class
********************/

#include "Map.hpp"

Map::Map()
{
	//Create two dimensional array of Space pointers
	data = new Space**[numRow];
	for (int j = 0; j < numRow; j++)
	{
		data[j] = new Space*[numCol];
	}

	//Allocate horizontal borders
	for (int b = 0; b < numCol; b++)
	{
		data[0][b] = new Border();
		data[numRow - 1][b] = new Border();
	}

	//Allocate vertical borders
	for (int b = 1; b < numRow - 1; b++)
	{
		data[b][0] = new Border();
		data[b][numCol - 1] = new Border();
	}

	//Fill with blank spaces
	for (int i = 1; i < numRow - 1; i++)
	{
		for (int j = 1; j < numCol - 1; j++)
		{
			data[i][j] = new Blank();
		}
	}

	//Set links for borders
	for (int j = 0; j < numCol; j++)
	{
		if (j == 0)
		{
			data[0][j]->setPosition(data[1][j], nullptr, nullptr, data[0][j + 1]);
			data[numRow - 1][j]->setPosition(nullptr, data[numRow - 2][j], nullptr, data[numRow - 1][j + 1]);
		}
		else if (j == numCol - 1)
		{
			data[0][j]->setPosition(data[1][j], nullptr, data[0][j - 1], nullptr);
			data[numRow - 1][j]->setPosition(nullptr, data[numRow - 2][j], data[numRow - 1][j - 1], nullptr);
		}
		else
		{
			data[0][j]->setPosition(data[1][j], nullptr, data[0][j - 1], data[0][j + 1]);
			data[numRow - 1][j]->setPosition(nullptr, data[numRow - 2][j], data[numRow - 1][j - 1], data[numRow - 1][j + 1]);
		}
	}

	//Allocate vertical borders
	for (int i = 1; i < numRow - 1; i++)
	{
		data[i][0]->setPosition(data[i + 1][0], data[i - 1][0], nullptr, data[i][1]);
		data[i][numCol - 1]->setPosition(data[i + 1][numCol - 1], data[i - 1][numCol - 1], data[i][numCol - 2], nullptr);
	}

	//Fill with blank spaces
	for (int i = 1; i < numRow - 1; i++)
	{
		for (int j = 1; j < numCol - 1; j++)
		{
			data[i][j]->setPosition(data[i + 1][j], data[i - 1][j], data[i][j - 1], data[i][j + 1]);
		}
	}

	//Set player space
	pRow = 1;
	pCol = 1;

	//Create boss space
	bSpace = new bossSpace();
	generateSpace(bSpace);

	//Create key space
	Space * temp = new keySpace();
	generateSpace(temp);
	temp = nullptr;

	//Create 10 item spaces
	for (int i = 0; i < 10; i++)
	{
		temp = new itemSpace();
		generateSpace(temp);
		temp = nullptr;
	}

	//Create 15 enemies
	for (int i = 0; i < 15; i++)
	{
		temp = new enemySpace();
		generateSpace(temp);
		temp = nullptr;
	}
	
}

//Generate space
void Map::generateSpace(Space* space)
{
	//Randomly generate spaces
	int rowPos;
	int colPos;
	bool invalid;

	do
	{
		invalid = false;

		//Generate 2 random numbers within confines of map
		rowPos = rand() % (numRow - 2) + 1;
		colPos = rand() % (numCol - 2) + 1;

		//Check if blank space
		if (typeid(Blank) != typeid(*data[rowPos][colPos]) || data[rowPos][colPos] == getPlayerSpace())
		{
			invalid = true;
		}
	} while (invalid);

	//Generate space
	space->copyPosition(data[rowPos][colPos]);
	delete data[rowPos][colPos];
	data[rowPos][colPos] = space;
}

//Display the data
void Map::displayMap()
{
	for (int i = numRow - 1; i >= 0; i--)
	{
		for (int j = 0; j < numCol; j++)
		{
			if (data[i][j] == getPlayerSpace())
			{
				std::cout << "+";
			} else if (data[i][j] == bSpace)
			{
				std::cout << "!";
			} else if (typeid(keySpace) == typeid(*data[i][j]))
			{
				std::cout << "K";
			} else if (typeid(itemSpace) == typeid(*data[i][j]))
			{
				std::cout << "?";
			} else if (typeid(Border) == typeid(*data[i][j]))
			{
				std::cout << "#";
			} else
			{
				std::cout << " ";
			}
		}

		std::cout << std::endl;
	}
}


//Replace player's space with a blank space
void Map::blankOut()
{
	Space * temp = new Blank(getPlayerSpace());
	delete getPlayerSpace();
	setPlayerSpace(temp);
}



//Destructor
Map::~Map()
{
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			delete data[i][j];
		}
		delete[] data[i];
	}

	delete [] data;
}

