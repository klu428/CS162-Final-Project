/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class implementation file for the Game class
********************/

#include "Game.hpp"

Game::Game()
{
	//Set turn to first turn
	turn = 1;

	//Set player name
	std::string name;
	std::cout << "Enter your character's name: ";
	getline(std::cin, name);

	//Instantiate player
	player = new Player(name);

	//Instantiate boss
	boss = new Blue_Men();

	//Initialize gameboard
	board = new Map();

	//Set boss
	board->getBossSpace()->setBoss(boss);


}

//Menu for each round
void Game::roundMenu()
{
	int choice;
	std::string choices[2] = { "Move", "Inventory" };

	//Print round number
	std::cout << "Turn " << turn << "/" << turnLimit << std::endl << std::endl;

	//Move or use inventory
	bool noMove;
	do {
		noMove = false;

		choice = menu(choices, 2);

		switch (choice)
		{
		case 1:
			if (!move())
			{
				noMove = true;
			}
			break;
		case 2:
			player->itemMenu();
			noMove = true;
		}
	} while (noMove);

	turn++;
}

//Move the player, return true if player moved and false if no movement
bool Game::move()
{
	std::string choices[5] = { "Up", "Down", "Left", "Right", "Cancel" };
	int choice;
	bool invalid;
	Space * temp = nullptr;

	do {
		invalid = false;

		//Display move menu
		choice = menu(choices, 5);

		//Set a temp pointer to the desired move
		switch (choice)
		{
		case 1:
			temp = board->getPlayerSpace()->getTop();
			break;
		case 2:
			temp = board->getPlayerSpace()->getBottom();
			break;
		case 3:
			temp = board->getPlayerSpace()->getLeft();
			break;
		case 4:
			temp = board->getPlayerSpace()->getRight();
			break;
		case 5:
			return false;
		}

		//If temp is a border, display move invalid message and restart the loop
		if (typeid(Border) == typeid(*temp))
		{
			std::cout << "Invalid Move" << std::endl;
			invalid = true;
		}
		else if (typeid(bossSpace) == typeid(*temp))
		{
			//If player wants to move onto the boss space, check if they have the key
			if (!player->hasKey())
			{
				std::cout << "The door is locked!" << std::endl;
				invalid = true;
			}
		}
	} while (invalid);

	//If valid move, set space player was just on to blank
	board->blankOut();

	//Set player space to new space
	switch (choice)
	{
	case 1:
		board->moveUp();
		break;
	case 2:
		board->moveDown();
		break;
	case 3:
		board->moveLeft();
		break;
	case 4:
		board->moveRight();
		break;
	}

	return true;
	
}


//Check if game is over and print the corresponding message
bool Game::isGameOver()
{
	std::cout << std::endl;
 
	//If boss's strength is 0 or less, player wins
	if (boss->getStrength() <= 0)
	{
		std::cout << "CONGRATULATIONS! YOU WIN!" << std::endl;
		return true;
	}

	//If player's strength is 0 or less, or turn is over the limit, player loses
	if (player->getStrength() <= 0 || turn > turnLimit)
	{
		std::cout << "GAME OVER" << std::endl;
		return true;
	}

	return false;
}

//Destructor
Game::~Game()
{
	delete player;
	delete boss;
	delete board;
}


/********************/

#include "time.h"

int main()
{
	srand(time(NULL));

	std::cout << "Welcome to Kelvin's game! You control the '+', defeat the boss '!' in 50 turns." << std::endl;
	std::string firstMenu[2] = { "Play", "Quit" };

	if (menu(firstMenu, 2) == 2)
	{
		return 0;
	}

	Game newGame;
	CLEAR();

	while (!newGame.isGameOver())
	{
		newGame.getBoard()->displayMap();
		newGame.roundMenu();
		CLEAR();
		newGame.getBoard()->displayMap();
		newGame.getBoard()->getPlayerSpace()->action(newGame.getPlayer());
		CLEAR();
	}

}