/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the class specification file for the Spaces class and its subclasses.
********************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Objects.hpp"

class Space
{
protected:
	Space * top;
	Space * bottom;
	Space * left;
	Space * right;

	void combat(Player* player, Character * enemy);

public:
	//Top getter function
	Space * getTop() { return top; }

	//Bottom getter function
	Space * getBottom() { return bottom; }

	//Left getter function
	Space * getLeft() { return left; }

	//Right getter function
	Space * getRight() { return right; }

	//Top setter function
	void setTop(Space * space) { top = space; }

	//Bottom setter function
	void setBottom(Space * space) { bottom = space; }

	//Left setter function
	void setLeft(Space * space) { left = space; }

	//Right setter function
	void setRight(Space * space) { right = space; }

	//Position Setter
	void setPosition(Space * _top, Space * _bottom, Space * _left, Space * _right);

	//Copy positions from an existing space
	void copyPosition(Space * input);

	//Space's action
	virtual void action(Player* player) = 0;

	//Virtual destructor
	virtual ~Space() {}
};

//Border of the board
class Border : public Space
{
public:
	//Default constructor
	Border() { top = bottom = left = right = nullptr; }
	//Constructor
	Border(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	Border(Space * input) { copyPosition(input); }

	virtual void action(Player* player) {}

	virtual ~Border() { }
};

//Blank Space
class Blank : public Space
{
public:
	//Default constructor
	Blank() { top = bottom = left = right = nullptr; }

	//Constructor
	Blank(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	Blank(Space * input) { copyPosition(input); }

	virtual void action(Player* player) {}

	virtual ~Blank() { }
};

//Space containing an item
class itemSpace : public Space
{
public:
	//Default constructor
	itemSpace() { top = bottom = left = right = nullptr; }

	//Constructor
	itemSpace(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	itemSpace(Space * input) { copyPosition(input); }

	virtual void action(Player* player);

	virtual ~itemSpace() { }
};

//Space containing the key
class keySpace : public Space
{
public:
	//Default constructor
	keySpace() { top = bottom = left = right = nullptr; }

	//Constructor
	keySpace(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	keySpace(Space * input) { copyPosition(input); }

	virtual void action(Player* player);

	virtual ~keySpace() { }
};

//Space containing an enemy, triggers fight
class enemySpace : public Space
{
public:
	//Default constructor
	enemySpace() { top = bottom = left = right = nullptr; }

	//Constructor
	enemySpace(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	enemySpace(Space * input) { copyPosition(input); }

	virtual void action(Player* player);

	virtual ~enemySpace() { }
};

//Boss containing boss, triggers boss fight
class bossSpace : public Space
{
private:
	Character * boss;
public:
	//Default constructor
	bossSpace() { top = bottom = left = right = nullptr; }

	//Constructor
	bossSpace(Space * top, Space * bottom, Space * left, Space * right) { setPosition(top, bottom, left, right); }

	//Copy constructor
	bossSpace(Space * input) { copyPosition(input); }

	//Set the boss character
	void setBoss(Character * _boss) { boss = _boss; }

	//Get boss character
	Character * getBoss() { return boss; }

	virtual void action(Player* player);

	virtual ~bossSpace() {}
};

#endif
