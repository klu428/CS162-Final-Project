/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class specification file for the Map class
********************/

#ifndef MAP_HPP
#define MAP_HPP


#include "Spaces.hpp"

class Map
{
private:
	Space *** data;
	int pRow;
	int pCol;
	bossSpace * bSpace;
	const int numCol = 10;
	const int numRow = 10;
public:
	//Constructor
	Map();

	//Display the Map
	void displayMap();

	//Get boss space
	bossSpace * getBossSpace() { return bSpace; }

	//Get playerSpace
	Space * getPlayerSpace() { return data[pRow][pCol]; }

	//Player move up
	void moveUp() { pRow++; }

	//Player move down
	void moveDown() { pRow--; }

	//Player move left
	void moveLeft() { pCol--; }

	//Player move right
	void moveRight() { pCol++; }

	//Set playerSpace
	void setPlayerSpace(Space * space) { data[pRow][pCol] = space; }

	//Generate space, replacing a blank space
	void generateSpace(Space * space);

	//Replace player's space with a blank space
	void blankOut();

	//Destructor
	~Map();
};



#endif
