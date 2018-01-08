/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class implementation file for the Spaces class and its subclasses.
********************/

#include "Spaces.hpp"

/********************
** Description: This is the class implementation for the Space class.
********************/

void Space::setPosition(Space * _top, Space * _bottom, Space * _left, Space * _right)
{
	//Set pointers
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;

	//Set pointers back
	if (top != nullptr) {
		top->setBottom(this);
	}
	if (bottom != nullptr)
	{
		bottom->setTop(this);
	}
	if (left != nullptr) {
		left->setRight(this);
	}
	if (right != nullptr) {
		right->setLeft(this);
	}
}

//Copy pointers of a space, and have each space the input points to point to a new space
void Space::copyPosition(Space* input)
{
	setPosition(input->getTop(), input->getBottom(), input->getLeft(), input->getRight());
}

//Combat between a player and an enemy
void Space::combat(Player* player, Character * enemy)
{
	bool again;
	std::string optionMenu[3]{ "Attack", "Use Item", "Flee" };

	//Continue loop until either combatant dies
	while (player->getStrength() > 0 && enemy->getStrength() > 0)
	{
		do
		{
			again = false;

			std::cout << std::endl;

			//Option Menu
			int choice = menu(optionMenu, 3);

			std::cout << std::endl;

			switch (choice)
			{
			case 1: //Attack the enemy
				enemy->defense(player->attack());
				break;
			case 2: //Use an item
				if (!player->itemMenu())
				{
					again = true;
				}
				break;
			case 3: //Flee
				if (typeid(Blue_Men) == typeid(*enemy))
				{
					std::cout << "You cannot flee from the boss!";
					again = true;
				}
				else if (!(rand() % 5))
				{
					std::cout << "You escaped!" << std::endl;
					SLEEP();
					return;
				}
				else
				{
					std::cout << "You failed to flee!" << std::endl;
				}

			}
		} while (again == true);

		std::cout << std::endl;

		//Print message if attack kills enemy
		if (enemy->getStrength() <= 0)
		{
			std::cout << std::endl << "You defeated the enemy!" << std::endl;
			SLEEP();
			return;
		}

		//If enemy not dead, defend
		player->defense(enemy->attack());

		//Print message if enemy attack kills player
		if (player->getStrength() <= 0)
		{
			std::cout << std::endl << "You died..." << std::endl;
			SLEEP()
			return;
		}
	}
}


/********************
** Description: This is the class implementation for the itemSpace class.
********************/

void itemSpace::action(Player* player)
{
	Item * item;
	//Allocate a random item
	switch (rand() % 3)
	{
	case 0:
		item = new Sword();
		break;
	case 1:
		item = new Potion();
		break;
	case 2:
		item = new Armor();
	}

	//If player does not add item, delete it
	if (!player->addItem(item))
	{
		delete item;
	}
	else
	{
		item->equipItem(player);
	}
}


/********************
** Description: This is the class implementation for the keySpace class.
********************/

//Add the key to the player's inventory
void keySpace::action(Player* player)
{
	Item * key = new Key();

	player->addItem(key);
}


/********************
** Description: This is the class implementation for the enemySpace class.
********************/

void enemySpace::action(Player* player)
{
	Character * enemy;
	//Create random enemy
	switch (rand() % 3)
	{
	case 0:
		enemy = new Vampire();
		break;
	case 1:
		enemy = new Barbarian();
		break;
	case 2:
		enemy = new Medusa();
	}

	std::cout << "Enemy found!" << std::endl << std::endl;

	//Combat
	combat(player, enemy);

	//Delete enemy after combat
	delete enemy;

}


/********************
** Description: This is the class implementation for the bossSpace class.
********************/

void bossSpace::action(Player* player)
{
	std::cout << "You discovered the boss!" << std::endl << std::endl;

	//Combat
	combat(player, boss);

}