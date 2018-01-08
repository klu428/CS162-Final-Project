/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class specification file for the objects(Items and Characters) class and their subclasses.
********************/

#include "Objects.hpp"

/********************
** Description: This is the class implementation for the Item class.
********************/

//Display this message when player tries to use an item that cannot be used
bool Item::use(Player* player)
{
	std::cout << "This item cannot be used!" << std::endl;
	return false;
}


/********************
** Description: This is the class implementation for the Potion class.
********************/

//Raise the player's HP by 50% of their current HP or to max HP, whichever is lower
bool Potion::use(Player* player)
{
	int hp = player->getStrength() * 1.5;

	//If new HP will be lower than max, set it to new HP
	if (hp > player->getMaxStrength())
	{
		player->setStrength(player->getMaxStrength());
	}
	else //Set HP to max if new HP would go over max
	{
		player->setStrength(hp);
	}

	//Print message with new HP total
	std::cout << "You used a potion and recovered to " << player->getStrength() << "HP!" << std::endl;

	//Decrease the number of items the user has by 1
	player->setNumItems(player->getNumItems() - 1);

	return true;
}


/********************
** Description: This is the class implementation for the Sword class.
********************/

//Raise the player's bonus attack by 3
void Sword::equipItem(Player* player)
{
	player->setBonusATK(player->getBonusATK() + 3);
}

//If player replaces the item, lower the player's bonus attack by 3
void Sword::deleteItem(Player* player)
{
	player->setBonusATK(player->getBonusATK() - 3);
}


/********************
** Description: This is the class implementation for the Armor class.
********************/

//Raise the player's armor by 3
void Armor::equipItem(Player * player)
{
	player->setArmor(player->getArmor() + 3);
}

//If player replaces the item, lower the player's armor by 3
void Armor::deleteItem(Player* player)
{
	player->setArmor(player->getArmor() - 3);
}


/********************
** Character classes start here
********************/


/********************
** Description: This is the class implementation for the Player class.
********************/

//Constructor
Player::Player()
{
	name = "Player";
	armor = 0;
	strength = 40;
	bonusATK = 0;
	numItems = 0;
	secondWind = false;
	for (int i = 0; i < maxItems; i++)
	{
		items[i] = nullptr;
	}
}

//1-Parameter Constructor for setting name
Player::Player(std::string userName)
{
	name = userName;
	armor = 0;
	strength = 40;
	bonusATK = 0;
	numItems = 0;
	secondWind = false;
	for (int i = 0; i < maxItems; i++)
	{
		items[i] = nullptr;
	}
}

//Item Menu
bool Player::itemMenu()
{
	int itemChoice;

	//Items in inventory
	if (numItems == 0)
	{
		std::cout << "Your inventory is empty!" << std::endl;
		return false;
	}

	std::cout << "Items:" << std::endl;
	for (int i = 0; i < maxItems; i++)
	{
		std::cout << i + 1 << ". ";
		if (items[i] == nullptr)
		{
			std::cout << "Empty" << std::endl;
		}
		else
		{
			items[i]->printDescription();
			std::cout << std::endl;
		}
	}
		std::cout << maxItems + 1 << ". Cancel" << std::endl;

	//Use an item
	do {
		std::cout << "Use Item? ";
		itemChoice = validatePositiveRange(1, maxItems + 1);

		//Player cancels, return false
		if (itemChoice == maxItems + 1)
		{
			return false;
		}

		//Print message if user tries to use an empty slot
		if (items[itemChoice - 1] == nullptr)
		{
			std::cout << "This item slot is empty!" << std::endl;
		}
		
	} while (items[itemChoice - 1] == nullptr || !items[itemChoice - 1]->use(this));

	//If valid item, use it
	items[itemChoice - 1]->deleteItem(this);
	delete items[itemChoice - 1];
	items[itemChoice - 1] = nullptr;
	return true;
}


//Get an item
bool Player::addItem(Item* item)
{
	//Print item description
	std::cout << "You found a ";
	item->printDescription();
	std::cout << std::endl;
	SLEEP();

	//If the player is carrying less than max items, put the item into the player's first empty item slot
	if (numItems < maxItems)
	{
		for (int i = 0; i < maxItems; i++)
		{
			if (items[i] == nullptr)
			{
				items[i] = item;
				numItems++;
				return true;
			}
		}
	}

	int choice;
	bool invalid;
	int notKey = 1;

	//Menu for replacing an item
	for (int i = 0; i < numItems; i++)
	{
		std::cout << i + 1 << ". ";
		items[i]->printDescription();
		std::cout << std::endl;
	}

	//If item is key, another item must be replaced by it
	if (typeid(Key) == typeid(*item))
	{
		notKey = 0;
	}
	else {
		std::cout << "7. Cancel" << std::endl;
	}

	//Replace an item
	do {
		invalid = false;

		std::cout << "Select the item you would like to replace: ";
		choice = validatePositiveRange(1, maxItems + notKey) - 1;

		//Check that the choice is less than max items or the user canceled.
		if (choice < maxItems) {

			//Check if user is trying to replace the key
			if (typeid(Key) == typeid(*items[choice]))
			{
				std::cout << "You cannot replace the key!" << std::endl;
				invalid = true;
			}
			else
			{
				//Replace the desired item, return true
				items[choice]->deleteItem(this);
				delete items[choice];
				items[choice] = item;
				return true;
			}
		}
	} while (invalid);

	//Player did not add an item, so return false
	return false;
}


//Indicates if player has key
bool Player::hasKey()
{
	for (int i = 0; i < numItems; i++)
	{
		if (typeid(Key) == typeid(*items[i]))
		{
			return true;
		}
	}
	return false;
}


//Roll for attack
int Player::attack()
{
	int atk = rand() % 15 + 1 + bonusATK;
	std::cout << getName() << " rolled a " << atk << " for attack!" << std::endl;
	return atk;
}


//Roll for defense
void Player::defense(int atk)
{
	std::cout << getName() << " has " << getArmor() << " armor and " << getStrength() << " strength points" << std::endl;
	if (atk == -1)
	{
		setStrength(0);
		std::cout << getName() << "'s strength points instantly becomes " << strength << std::endl;
	}
	else
	{
		int def1 = rand() % 6 + 1;
		int def2 = rand() % 6 + 1;
		int totaldef = def1 + def2;
		int damage = atk - totaldef - armor;
		std::cout << getName() << " rolled a " << def1 << " and " << def2 << " for a total of " << totaldef << " defense!" << std::endl;
		std::cout << getName() << " takes " << atk << " attack - " << totaldef << " defense - " << armor << " armor for a total of " << damage << " damage!" << std::endl;
		if (damage <= 0)
		{
			std::cout << "The attack was ineffective and " << getName() << " did not take any damage" << std::endl;
		}
		else
		{
			strength -= damage;
			std::cout << getName() << "'s strength points has been reduced to " << strength << std::endl;
		}
	}

	if (strength <= 0 && !secondWind)
	{
		strength = 10;
		std::cout << getName() << " gained a second wind and comes back with " << strength << " strength points!" << std::endl;
		secondWind = true;
	}
}


//Destructor
Player::~Player() {
	for (int i = 0; i < maxItems; i++)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
		}
	}
}

/********************
** Description: This is the class implementation for the Vampire class.
********************/

//Constructor
Vampire::Vampire()
{
	name = "";
	armor = 1;
	strength = 18;
	characteristic = "Suave, debonair, but vicious and surprisingly risilient";
}

//1-Parameter Constructor for setting name
Vampire::Vampire(std::string userName)
{
	name = userName;
	armor = 1;
	strength = 18;
	characteristic = "Suave, debonair, but vicious and surprisingly risilient";
}


//Roll for attack
int Vampire::attack()
{
	int atk = rand() % 12 + 1;
	std::cout << "Vampire" << getName() << " rolled a " << atk << " for attack!" << std::endl;
	return atk;
}

//Roll for defense
void Vampire::defense(int atk)
{
	std::cout << "Vampire" << getName() << " has " << getArmor() << " armor and " << getStrength() << " strength points" << std::endl;
	if (rand() % 2)
	{
		std::cout << "Vampire" << getName() << " charmed the foe, causing the foe to stop their attack!" << std::endl;
	}
	else if (atk == -1)
	{
		setStrength(0);
		std::cout << "Vampire" << getName() << "'s strength points instantly becomes " << strength << std::endl;
	}
	else
	{
		int def = rand() % 6 + 1;
		int damage = atk - def - armor;
		std::cout << "Vampire" << getName() << " rolled a " << def << " for defense!" << std::endl;
		std::cout << "Vampire" << getName() << " takes " << atk << " attack - " << def << " defense - " << armor << " armor for a total of " << damage << " damage!" << std::endl;
		if (damage <= 0)
		{
			std::cout << "The attack was ineffective and Vampire" << getName() << " did not take any damage" << std::endl;
		}
		else
		{
			strength -= damage;
			std::cout << "Vampire" << getName() << "'s strength points has been reduced to " << strength << std::endl;
		}
	}
}


/********************
** Description: This is the class implementation for the Barbarian class.
********************/

//Constructor
Barbarian::Barbarian()
{
	name = "";
	armor = 0;
	strength = 12;
	characteristic = "Think Conan or Hercules from the movies. Big sword, big muscles, bare torso.";
}

//1-Parameter Constructor
Barbarian::Barbarian(std::string userName)
{
	name = userName;
	armor = 0;
	strength = 12;
	characteristic = "Think Conan or Hercules from the movies. Big sword, big muscles, bare torso.";
}

//Roll for attack
int Barbarian::attack()
{
	int atk1 = rand() % 6 + 1;
	int atk2 = rand() % 6 + 1;
	std::cout << "Barbarian" << getName() << " rolled a " << atk1 << " and " << atk2 << " for a total of " << atk1 + atk2 << " attack!" << std::endl;
	return atk1 + atk2;
}

//Roll for defense
void Barbarian::defense(int atk)
{
	std::cout << "Barbarian" << getName() << " has " << getArmor() << " armor and " << getStrength() << " strength points" << std::endl;
	if (atk == -1)
	{
		setStrength(0);
		std::cout << "Barbarian" << getName() << "'s strength points instantly becomes " << strength << std::endl;
	}
	else
	{
		int def1 = rand() % 6 + 1;
		int def2 = rand() % 6 + 1;
		int totaldef = def1 + def2;
		int damage = atk - totaldef - armor;
		std::cout << "Barbarian" << getName() << " rolled a " << def1 << " and " << def2 << " for a total of " << totaldef << " defense!" << std::endl;
		std::cout << "Barbarian" << getName() << " takes " << atk << " attack - " << totaldef << " defense - " << armor << " armor for a total of " << damage << " damage!" << std::endl;
		if (damage <= 0)
		{
			std::cout << "The attack was ineffective and Barbarian" << getName() << " did not take any damage" << std::endl;
		}
		else
		{
			strength -= damage;
			std::cout << "Barbarian" << getName() << "'s strength points has been reduced to " << strength << std::endl;
		}
	}
}


/********************
** Description: This is the class implementation for the Blue Men class.
********************/

//Constructor
Blue_Men::Blue_Men()
{
	name = "";
	armor = 3;
	strength = 12;
	characteristic = "They are small, 6 inch tall, but fast and tough. They are hard to hit so they can take some damage. They can also do a LOT of damage when they crawl inside enemies’ armor or clothing.";
}

//1-Parameter Constructor
Blue_Men::Blue_Men(std::string userName)
{
	name = userName;
	armor = 3;
	strength = 12;
	characteristic = "They are small, 6 inch tall, but fast and tough. They are hard to hit so they can take some damage. They can also do a LOT of damage when they crawl inside enemies’ armor or clothing.";
}

//Roll for attack
int Blue_Men::attack()
{
	int atk1 = rand() % 10 + 1;
	int atk2 = rand() % 10 + 1;
	std::cout << "Blue Men" << getName() << " rolled a " << atk1 << " and " << atk2 << " for a total of " << atk1 + atk2 << " attack!" << std::endl;
	return atk1 + atk2;
}

//Roll for defense
void Blue_Men::defense(int atk)
{
	std::cout << "Blue Men" << getName() << " have " << getArmor() << " armor and " << getStrength() << " strength points" << std::endl;
	if (atk == -1)
	{
		setStrength(0);
		std::cout << "Blue Men" << getName() << "'s strength points instantly becomes " << strength << std::endl;
	}
	else
	{
		int def1 = rand() % 6 + 1;
		int def2 = rand() % 6 + 1;
		int def3 = rand() % 6 + 1;
		int totaldef;
		int damage;

		if (getStrength() > 8)
		{
			totaldef = def1 + def2 + def3;
			damage = atk - totaldef - armor;
			std::cout << "Blue Men" << getName() << " rolled a " << def1 << ", " << def2 << ", and " << def3 << " for a total of " << totaldef << " defense!" << std::endl;
		}
		else if (getStrength() > 4)
		{
			totaldef = def1 + def2;
			damage = atk - totaldef - armor;
			std::cout << "Blue Men" << getName() << " rolled a " << def1 << " and " << def2 << " for a total of " << totaldef << " defense!" << std::endl;
		}
		else
		{
			totaldef = def1;
			damage = atk - totaldef - armor;
			std::cout << "Blue Men" << getName() << " rolled a " << def1 << " for a total of " << totaldef << " defense!" << std::endl;
		}

		std::cout << "Blue Men" << getName() << " takes " << atk << " attack - " << totaldef << " defense - " << armor << " armor for a total of " << damage << " damage!" << std::endl;
		if (damage <= 0)
		{
			std::cout << "The attack was ineffective and Blue Men" << getName() << " did not take any damage" << std::endl;
		}
		else
		{
			strength -= damage;
			std::cout << "Blue Men" << getName() << "'s strength points has been reduced to " << strength << std::endl;
		}
	}
}


/********************
** Description: This is the class implementation for the Medusa class.
********************/

//Constructor
Medusa::Medusa()
{
	name = "";
	armor = 3;
	strength = 8;
	characteristic = "Scrawny lady with snakes for hair which helps her during combat. Just don’t look at her!";
}

//1-Parameter Constructor
Medusa::Medusa(std::string userName)
{
	name = userName;
	armor = 3;
	strength = 8;
	characteristic = "Scrawny lady with snakes for hair which helps her during combat. Just don’t look at her!";
}

//Roll for attack
int Medusa::attack()
{
	int atk1 = rand() % 6 + 1;
	int atk2 = rand() % 6 + 1;
	int totalatk = atk1 + atk2;
	if (totalatk == 12)
	{
		std::cout << "Medusa" << getName() << " rolled a " << totalatk << " , so she uses her special ability, Glare, to turn the foe to stone!" << std::endl;
		return -1;
	}
	std::cout << "Medusa" << getName() << " rolled a " << atk1 << " and " << atk2 << " for a total of " << atk1 + atk2 << " attack!" << std::endl;
	return totalatk;
}

//Roll for defense
void Medusa::defense(int atk)
{
	std::cout << "Medusa" << getName() << " has " << getArmor() << " armor and " << getStrength() << " strength points" << std::endl;
	if (atk == -1)
	{
		setStrength(0);
		std::cout << "Medusa" << getName() << "'s strength points instantly becomes " << strength << std::endl;
	}
	else
	{
		int def = rand() % 6 + 1;
		int damage = atk - def - armor;
		std::cout << "Medusa" << getName() << " rolled a " << def << " for defense!" << std::endl;
		std::cout << "Medusa" << getName() << " takes " << atk << " attack - " << def << " defense - " << armor << " armor for a total of " << damage << " damage!" << std::endl;
		if (damage <= 0)
		{
			std::cout << "The attack was ineffective and Medusa" << getName() << " did not take any damage" << std::endl;
		}
		else
		{
			strength -= damage;
			std::cout << "Medusa" << getName() << "'s strength points has been reduced to " << strength << std::endl;
		}
	}
}