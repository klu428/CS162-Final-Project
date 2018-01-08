/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class specification file for the objects(Items and Characters) class and their subclasses.
********************/

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Validation.hpp"

class Player;


/********************
** Description: This is the specifications for the Item classes and subclasses.
********************/

class Item
{
public:
	//Get item description
	virtual void printDescription() = 0;

	//Use an item
	virtual bool use(Player* player);

	//Equip item
	virtual void equipItem(Player* player) {}

	//Delete item
	virtual void deleteItem(Player* player) {}

	//Virtual destructor
	virtual ~Item() {}
};

//Heal 50% hp
class Potion : public Item
{
public:
	//Get item description
	virtual void printDescription() { std::cout << "Potion: Restores 50% HP"; }

	//Use Item
	virtual bool use(Player* player);
};

//Add 3 to each attack roll
class Sword : public Item
{
public:
	virtual void printDescription() { std::cout << "Sword: Attack + 3"; }

	//Equip item
	virtual void equipItem(Player * player);

	//Delete item
	virtual void deleteItem(Player* player);
};

//Adds 3 to armor
class Armor : public Item
{
public:
	virtual void printDescription() { std::cout << "Armor: Armor + 3"; }

	//Equip item
	virtual void equipItem(Player * player);

	//Delete item
	virtual void deleteItem(Player* player);
};

//Key to unlock boss battle
class Key : public Item
{
public:
	virtual void printDescription() { std::cout << "Key: Unlocks the door to the boss's lair"; }
};


/********************
** Description: This is the specifications for the Character classes and subclasses.
********************/

class Character
{
protected:

	std::string name;
	int armor;
	int strength;
	std::string characteristic;

public:
	//Armor getter function
	int getArmor() { return armor; }

	//Strength getter function
	int getStrength() { return strength; }

	//Name getter function
	std::string getName() { return name; }

	//Strength setter function
	void setStrength(int str) { strength = str; }

	//Name setter function
	void setName(std::string userName) { name = userName; }

	//Armor setter function
	void setArmor(int userArmor) { armor = userArmor; }

	//Roll for attack
	virtual int attack() = 0;

	//Roll for defense
	virtual void defense(int atk) = 0;

	//Virtual destructor
	virtual ~Character() {}
};


class Player : public Character
{
private:
	Item * items[6];
	const int maxItems = 6;
	const int maxStrength = 40;
	int bonusATK;
	int numItems;
	bool secondWind;
public:
	//Constructor
	Player();

	//1-Parameter Constructor for setting name
	Player(std::string userName);

	//Get max strength
	int getMaxStrength() { return maxStrength; }

	//Get bonus attack
	int getBonusATK() { return bonusATK; }

	//Get number of items
	int getNumItems() { return numItems; }

	//Get items
	Item * getItem(int index) { return items[index]; }

	//Set bonus attack
	void setBonusATK(int atk) { bonusATK = atk; }

	//Set number of items
	void setNumItems(int num) { numItems = num; }

	//Item Menu- Return true if item is used, return false if not
	bool itemMenu();

	//Add or replace an item
	bool addItem(Item * item);

	//Indicates if player has key or not
	bool hasKey();

	//Roll for attack
	virtual int attack();

	//Roll for defense
	virtual void defense(int atk);

	//Virtual destructor
	virtual ~Player();

};


class Vampire : public Character
{
public:
	//Constructor
	Vampire();

	//1-Parameter Constructor for setting name
	Vampire(std::string userName);

	//Roll for attack
	virtual int attack();

	//Roll for defense
	virtual void defense(int atk);

	//Virtual destructor
	virtual ~Vampire() {}
};


class Barbarian : public Character
{
public:
	//Constructor
	Barbarian();

	//1-Parameter Constructor for setting name
	Barbarian(std::string userName);

	//Roll for attack
	virtual int attack();

	//Roll for defense
	virtual void defense(int atk);

	//Virtual destructor
	virtual ~Barbarian() {}
};


class Blue_Men : public Character
{
public:
	//Constructor
	Blue_Men();

	//1-Parameter Constructor for setting name
	Blue_Men(std::string userName);

	//Roll for attack
	virtual int attack();

	//Roll for defense
	virtual void defense(int atk);

	//Virtual destructor
	virtual ~Blue_Men() {}
};


class Medusa : public Character
{
public:
	//Constructor
	Medusa();

	//1-Parameter Constructor for setting name
	Medusa(std::string userName);

	//Roll for attack
	virtual int attack();

	//Roll for defense
	virtual void defense(int atk);

	//Virtual destructor
	virtual ~Medusa() {}
};
#endif