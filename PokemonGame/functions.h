#pragma once

#include "constants.h"
#include "Pokemon.h"
#include "Potion.h"

// function that represents attack of the pokemon on the other one
void Attack(Pokemon* fighter, Pokemon* opponent, types effectA);

// function to read the records from the previous game
vector <string> readRecords();

// function to read name of the player from the text file
string getName(string line);

// function to read name of the player from the text file
int getExp(string line);

// function to read name of the player from the text file
int getGold(string line);

// function to read name of the player from the text file
vector <Pokemon> getPokemons(vector <string> lines);

// function to read name of the player from the text file
vector <Potion> getPotions(vector <string> lines);

// function to read status of caught pokemons
vector <bool> getPCaught(string line);
