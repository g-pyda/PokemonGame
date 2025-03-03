#include "constants.h"
#include <string>
#include "Potion.h"
#include "functions.h"

// default constructor used while rendering belongings of the marchant/stuff in the treasure
Potion::Potion()
{
	int k = rand()%2, t = rand()%13;
	if (k==0) // creation of the healing potion
	{
		kind = false;
		if (t < 4) 
		{
			points = 10;
			price = 30;
		}
		else if (t < 8)
		{
			points = 20;
			price = 50;
		}
		else if (t < 11)
		{
			points = 50;
			price = 120;
		}
		else
		{
			points = 200;
			price = 300;
		}
	}
	else // creation of the buff potion
	{
		kind = true;
		if (t < 4) 
		{
			points = 20;
			price = 50;
		}
		else if (t < 8)
		{
			points = 50;
			price = 110;
		}
		else if (t < 11)
		{
			points = 100;
			price = 200;
		}
		else
		{
			points = 200;
			price = 390;
		}
	}	
}

// constructor used while generating potions from the records
Potion::Potion(std::string elements[3])
{
	// array of std::string representing the elements of potion class
	// 0 - type, 1 - points, 2 - price
	if (elements[0] == "0") kind = false;
	else kind = true;
	points = std::stoi(elements[1]);
	price = std::stoi(elements[2]);
}

// methods to show the kind of potion
std::string Potion::ShowKind() const
{
	if (kind) return color("Buff",Blue);
	else return color("Healing",BrightMagenta);	
}

// method to show the points gained from the potion 
int Potion::ShowPoints() const
{
	return points;	
}

// method to show the market price of the potion
int Potion::ShowPrice() const
{
	return price;
}
