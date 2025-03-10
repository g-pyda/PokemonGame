#pragma once

#include "constants.h"
#include "Potion.h"
#include <string>

// class representing a pokemon 
class Pokemon
{
private:
	// enum representing place of the pokemon in the pokedex
	// (overall information like name, min/max CP, HP, PP or type are stored here)
	pokeindex index;
	// Combat Power points of the pokemon
	unsigned int cp;
	//  Health Points of the pokemon
	unsigned int hp;
	// Health Points of the pokemon left after the battle
	unsigned int hp_left;
	// Protection Points of the pokemon
	unsigned int pp;
	// Experience Points that depict when the pokemon will evolve
	unsigned int exp;
	// std::vector of special abilities obtained during evolution
	std::vector <abilities> ability;
	// information about usage of shield during fight
	bool shield;
	// method to evolve the pokemon
	void Evolve();
	friend class Player;
	// friend function that represents attack of the pokemon on the other one
	friend std::string Attack(Pokemon* fighter, Pokemon* opponent, types effectA);
public:
	// default constructor (used while spawning coached/wild/merchant/hostile pokemon)
	Pokemon(unsigned int pl_exp);
	// constructor used while reading the data from the records
	Pokemon(std::string elements[8]);
	// method to use while using potions
	void TakePotion(Potion pot);
	// method to show info about the pokemon during the battle
	void BattleStats();
	// methods to show the atributes of the pokemon
	unsigned int ShowPrice() const;
	unsigned int ShowHP() const;
	unsigned int ShowPP() const;
	unsigned int ShowHP_LEFT() const;
	unsigned int ShowCP() const;
	bool ShowShield() const;
	unsigned int ShowEXP() const;
	pokeindex ShowINDEX() const;
};