/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class specification file for the Game class
********************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"

class Game
{
private:
	Player * player;
	Character * boss;
	Map * board;
	int turn;
	const int turnLimit = 50;
public:
	//Constructor
	Game();

	//Get board
	Map * getBoard() { return board; }
	
	//Get player
	Player * getPlayer() { return player; }

	//Menu at the start of each round
	void roundMenu();

	//Move player, returns true if valid and false if invalid
	bool move();

	//Check if game over
	bool isGameOver();

	//Destructor
	~Game();
};



#endif