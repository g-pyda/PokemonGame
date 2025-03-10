#pragma once

#include "constants.h"

//class representing buff/healing potions
class Potion
{
private:
	// bool representing type of potion (true - buffs, false - healing)
	bool kind;
	// amount of CPp/HP added by the potion
	unsigned short int points;
	// market price of the potion
	unsigned short int price;
public:
	// default constructor used while rendering belongings of the merchant/stuff in the treasure
	Potion();
	// constructor used while generating potions from the records
	Potion(std::string elements[3]);
	// methods to show the kind of potion
	std::string ShowKind() const;
	// method to show the points gained from the potion 
	int ShowPoints() const;
	// method to show the market price of the potion
	int ShowPrice() const;
};
