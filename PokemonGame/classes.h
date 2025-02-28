#ifndef __ALL_HEADERS__
#define __ALL_HEADERS__

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
		// default constructor used while rendering belongings of the marchant/stuff in the treasure
		Potion();
        // constructor used while generating potions from the records
        Potion(string elements[3]);
		// methods to show the kind of potion
		string ShowKind() const;
		// method to show the points gained from the potion 
		int ShowPoints() const;
		// method to show the market price of the potion
		int ShowPrice() const;
};

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
		// vector of special abilities obtained during evolution
		vector <abilities> ability;
		// information about usage of shield during fight
		bool shield;
		// method to evolve the pokemon
		void Evolve();
        friend class Player;
        // friend function that represents attack of the pokemon on the other one
        friend void Attack(Pokemon* fighter, Pokemon* opponent, types effectA);
	public:
		// default constructor (used while spawning coached/wild/marchant/hostile pokemon)
		Pokemon(unsigned int pl_exp);
        // constructor used while reading the data from the records
        Pokemon(string elements[8]);
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

// class representing player
class Player
{
	private:
		// name/nickname of the player
		string name;
		// experience of the player
		unsigned int exp;
		// gold obtained by the player
		unsigned int gold;
		// vector of posessed potions
		vector <Potion> potions;
		// vector of posessed pokemons
		vector <Pokemon> pokemons;
		// array depicting whether the pokemon was caught or not (to check if you caught them all)
		bool pokeCaught[151];
	public:
		// default constructor of the player
		Player();
		// constructor of the player out of saved data
		Player(string n, int e, int g, vector <Potion> pt, vector <Pokemon> pk, vector <bool> pc);
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
        string ShowName() const;
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
#endif