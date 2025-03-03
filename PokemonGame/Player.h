#pragma once

#include "constants.h"
#include "Potion.h"
#include "Pokemon.h"

// class representing player
class Player
{
private:
	// name/nickname of the player
	std::string name;
	// experience of the player
	unsigned int exp;
	// gold obtained by the player
	unsigned int gold;
	// std::vector of posessed potions
	std::vector <Potion> potions;
	// std::vector of posessed pokemons
	std::vector <Pokemon> pokemons;
	// array depicting whether the pokemon was caught or not (to check if you caught them all)
	bool pokeCaught[151];
public:
	// default constructor of the player
	Player();
	// constructor of the player out of saved data
	Player(std::string n, int e, int g, std::vector <Potion> pt, std::vector <Pokemon> pk, std::vector <bool> pc);
	// method to say if player found all pokemons
	bool CaughtAll();
	// method to obtain an item/pokemon out of treasure/hostile
	void GetItem(Potion pot);
	void GetItem(Pokemon pok);
	// method to sell an object/pokemon from the inventory
	void SellPokemon();
	void SellPotion();
	// method to buy an object/pokemon from the marchant
	void Buy(Potion pot);
	void Buy(Pokemon pok);
	// method to show data of the user
	unsigned int ShowEXP() const;
	unsigned int ShowGold() const;
	std::string ShowName() const;
	unsigned int ShowPokemonNR() const;
	unsigned int ShowPotionNR() const;
	unsigned int HMCaught() const;
	// method to show statistics
	void ShowStats();
	// method to display all the pokemons in the inventory
	void ShowPokemons();
	// method to display all the potions in the inventory
	void ShowPotions();
	// method activating game module: fighting with wild pokemon
	void WildBattle();
	// method activating game module: fighting with a coach
	void CoachBattle();
	// method activating game module: finding a treasure
	void Treasure();
	// method activating game module: encountering a marchant
	void Marchant();
	// method activating game module: healing
	void Healing();
	// method activating game module: showing already caught pokemons
	void ShowCaught();
	// method to write the records to the record file
	void writeRecords();
};