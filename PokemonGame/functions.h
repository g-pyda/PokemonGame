#pragma once

#include "constants.h"
#include "Pokemon.h"
#include "Potion.h"

// function that represents attack of the pokemon on the other one
void Attack(Pokemon* fighter, Pokemon* opponent, types effectA);

// function to read the records from the previous game
std::vector <std::string> readRecords();

// function to read name of the player from the text file
std::string getName(std::string line);

// function to read name of the player from the text file
int getExp(std::string line);

// function to read name of the player from the text file
int getGold(std::string line);

// function to read name of the player from the text file
std::vector <Pokemon> getPokemons(std::vector <std::string> lines);

// function to read name of the player from the text file
std::vector <Potion> getPotions(std::vector <std::string> lines);

// function to read status of caught pokemons
std::vector <bool> getPCaught(std::string line);

// function to wrap a std::string with terminal color
std::string color(std::string text, ColorName color, bool background = false);