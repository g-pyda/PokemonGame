#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <fstream>
// for sleep()
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#include<windows.h>
#define sleep(x) Sleep(1000*x)
#else
#include<unistd.h>
#endif



using namespace std;

// enum representing states of the fight module
enum fight_outcome { kill, catching, runaway, win, failure };

// enum representing indexes of pokemons in the pokedex
enum pokeindex
{
    Null, Bulbasaur = 1, Ivysaur, Venusaur, Charmander, Charmeleon,
    Charizard, Squirtle, Wartortle, Blastoise, Caterpie,
    Metapod, Butterfree, Weedle, Kakuna, Beedrill,
    Pidgey, Pidgeotto, Pidgeot, Rattata, Raticate,
    Spearow, Fearow, Ekans, Arbok, Pikachu,
    Raichu, Sandshrew, Sandslash, NidoranF, Nidorina,
    Nidoqueen, NidoranM, Nidorino, Nidoking, Clefairy,
    Clefable, Vulpix, Ninetales, Jigglypuff, Wigglytuff,
    Zubat, Golbat, Oddish, Gloom, Vileplume,
    Paras, Parasect, Venonat, Venomoth, Diglett,
    Dugtrio, Meowth, Persian, Psyduck, Golduck,
    Mankey, Primeape, Growlithe, Arcanine, Poliwag,
    Poliwhirl, Poliwrath, Abra, Kadabra, Alakazam,
    Machop, Machoke, Machamp, Bellsprout, Weepinbell,
    Victreebel, Tentacool, Tentacruel, Geodude, Graveler,
    Golem, Ponyta, Rapidash, Slowpoke, Slowbro,
    Magnemite, Magneton, Farfetchd, Doduo, Dodrio,
    Seel, Dewgong, Grimer, Muk, Shellder,
    Cloyster, Gastly, Haunter, Gengar, Onix,
    Drowzee, Hypno, Krabby, Kingler, Voltorb,
    Electrode, Exeggcute, Exeggutor, Cubone, Marowak,
    Hitmonlee, Hitmonchan, Lickitung, Koffing, Weezing,
    Rhyhorn, Rhydon, Chansey, Tangela, Kangaskhan,
    Horsea, Seadra, Goldeen, Seaking, Staryu,
    Starmie, MrMime, Scyther, Jynx, Electabuzz,
    Magmar, Pinsir, Tauros, Magikarp, Gyarados,
    Lapras, Ditto, Eevee, Vaporeon, Jolteon,
    Flareon, Porygon, Omanyte, Omastar, Kabuto,
    Kabutops, Aerodactyl, Snorlax, Articuno, Zapdos,
    Moltres, Dratini, Dragonair, Dragonite, Mewtwo,
    Mew
};

// enum representing type of pokemon 
// (important in case of ressistance to the attacks)
enum types
{
    Normal, Fire, Water, Electric, Grass,
    Ice, Fighting, Poison, Ground, Flying,
    Psychic, Bug, Rock, Ghost, Dragon,
    Fairy, Steel, Dark
};

//vector of strings of types of pokemons
const static vector <string> types_s = {
    "Normal", "Fire", "Water", "Electric", "Grass",
    "Ice", "Fighting", "Poison", "Ground", "Flying",
    "Psychic", "Bug", "Rock", "Ghost", "Dragon",
    "Fairy", "Steel", "Dark"
};

// enum representing role of the pokemon (defensive/balanced/offensive)
// (important in case of boundaries of the CP and PP)
enum roles
{
    Defensive, Balanced, Offensive
};

// enum representing health level of the pokemon
// (important in case of boundaries of the HP)
enum healthLevel
{
    Low, Medium, High, VeryHigh
};

// structure that represents information about the pokemon in the pokedex
struct pokepage
{
    // place in the pokedex of the pokemon
    pokeindex index;
    // name of the pokemon
    string name;
    // classification by role in the battle
    roles role;
    // classification by health level
    healthLevel health;
    // vector of types of the pokemon
    vector <types> type;
    // number of evolution stages
    // 0>1>2 combination, 3>4 combination, 5 combination
    int stages;
    // place in the pokedex of the evolution 
    // (if non existent - index = Null)
    pokeindex evolution;
};

// vector that stores pages about the pokemons - POKEDEX
// {pokeindex, name, fight-role, health-level, types, stage of evolution, next evolution}
const static vector <pokepage> pokedex =
{
   {Bulbasaur, "Bulbasaur", Balanced, Medium, {Grass, Poison}, 0, Ivysaur},
   {Ivysaur, "Ivysaur", Balanced, Medium, {Grass, Poison}, 1, Venusaur},
   {Venusaur, "Venusaur", Defensive, High, {Grass, Poison}, 2, Null},
   {Charmander, "Charmander", Offensive, Low, {Fire}, 0, Charmeleon},
   {Charmeleon, "Charmeleon", Offensive, Medium, {Fire}, 1, Charizard},
   {Charizard, "Charizard", Offensive, High, {Fire, Flying}, 2, Null},
   {Squirtle, "Squirtle", Defensive, Low, {Water}, 0, Wartortle},
   {Wartortle, "Wartortle", Defensive, Medium, {Water}, 1, Blastoise},
   {Blastoise, "Blastoise", Defensive, High, {Water}, 2, Null},
   {Caterpie, "Caterpie", Defensive, Low, {Bug}, 0, Metapod},
   {Metapod, "Metapod", Defensive, Low, {Bug}, 1, Butterfree},
   {Butterfree, "Butterfree", Balanced, Medium, {Bug, Flying}, 2, Null},
   {Weedle, "Weedle", Offensive, Low, {Bug, Poison}, 0, Kakuna},
   {Kakuna, "Kakuna", Defensive, Low, {Bug, Poison}, 1 , Beedrill},
   {Beedrill, "Beedrill", Offensive, Medium, {Bug, Poison}, 2, Null},
   {Pidgey, "Pidgey", Balanced, Low, {Normal, Flying}, 0, Pidgeotto},
   {Pidgeotto, "Pidgeotto", Balanced, Medium, {Normal, Flying}, 1, Pidgeot},
   {Pidgeot, "Pidgeot", Balanced, High, {Normal, Flying}, 2, Null},
   {Rattata, "Rattata", Offensive, Low, {Normal}, 3, Raticate},
   {Raticate, "Raticate", Offensive, Medium, {Normal}, 4, Null},
   {Spearow, "Spearow", Offensive, Low, {Normal, Flying}, 3, Fearow},
   {Fearow, "Fearow", Offensive, Medium, {Normal, Flying}, 4, Null},
   {Ekans, "Ekans", Offensive, Low, {Poison}, 3, Arbok},
   {Arbok, "Arbok", Offensive, Medium, {Poison}, 4, Null},
   {Pikachu, "Pikachu", Offensive, Low, {Electric}, 3, Raichu},
   {Raichu, "Raichu", Offensive, Medium, {Electric}, 4, Null},
   {Sandshrew, "Sandshrew", Defensive, Medium, {Ground}, 3, Sandslash},
   {Sandslash, "Sandslash", Defensive, High, {Ground}, 4, Null},
   {NidoranF, "NidoranF", Balanced, Low, {Poison}, 0, Nidorina},
   {Nidorina, "Nidorina", Balanced, Medium, {Poison}, 1, Nidoqueen},
   {Nidoqueen, "Nidoqueen", Defensive, High, {Poison, Ground}, 2, Null},
   {NidoranM, "NidoranM", Offensive, Low, {Poison}, 0, Nidorino},
   {Nidorino, "Nidorino", Offensive, Medium, {Poison}, 1, Nidoking},
   {Nidoking, "Nidoking", Offensive, High, {Poison, Ground}, 2, Null},
   {Clefairy, "Clefairy", Defensive, Medium, {Fairy}, 3, Clefable},
   {Clefable, "Clefable", Defensive, High, {Fairy}, 4, Null},
   {Vulpix, "Vulpix", Offensive, Low, {Fire}, 3, Ninetales},
   {Ninetales, "Ninetales", Offensive, Medium, {Fire}, 4, Null},
   {Jigglypuff, "Jigglypuff", Defensive, High, {Normal, Fairy}, 3, Wigglytuff},
   {Wigglytuff, "Wigglytuff", Defensive, High, {Normal, Fairy}, 4, Null},
   {Zubat, "Zubat", Balanced, Low, {Poison, Flying}, 3, Golbat},
   {Golbat, "Golbat", Balanced, Medium, {Poison, Flying}, 4, Null},
   {Oddish, "Oddish", Balanced, Low, {Grass, Poison}, 0, Gloom},
   {Gloom, "Gloom", Balanced, Medium, {Grass, Poison}, 1, Vileplume},
   {Vileplume, "Vileplume", Defensive, High, {Grass, Poison}, 2, Null},
   {Paras, "Paras", Offensive, Low, {Bug, Grass}, 3, Parasect},
   {Parasect, "Parasect", Offensive, Medium, {Bug, Grass}, 4, Null},
   {Venonat, "Venonat", Balanced, Low, {Bug, Poison}, 3, Venomoth},
   {Venomoth, "Venomoth", Offensive, Medium, {Bug, Poison}, 4, Null},
   {Diglett, "Diglett", Offensive, Low, {Ground}, 3, Dugtrio},
   {Dugtrio, "Dugtrio", Offensive, Medium, {Ground}, 4, Null},
   {Meowth, "Meowth", Offensive, Low, {Normal}, 3, Persian},
   {Persian, "Persian", Offensive, Medium, {Normal}, 4, Null},
   {Psyduck, "Psyduck", Balanced, Medium, {Water}, 3, Golduck},
   {Golduck, "Golduck", Balanced, Medium, {Water}, 4, Null},
   {Mankey, "Mankey", Offensive, Low, {Fighting}, 3, Primeape},
   {Primeape, "Primeape", Offensive, Medium, {Fighting}, 4, Null},
   {Growlithe, "Growlithe", Offensive, Medium, {Fire}, 3, Arcanine},
   {Arcanine, "Arcanine", Offensive, High, {Fire}, 4, Null},
   {Poliwag, "Poliwag", Defensive, Low, {Water}, 0, Poliwhirl},
   {Poliwhirl, "Poliwhirl", Defensive, Medium, {Water}, 1, Poliwrath},
   {Poliwrath, "Poliwrath", Defensive, High, {Water, Fighting}, 2, Null},
   {Abra, "Abra", Offensive, Low, {Psychic}, 0, Kadabra},
   {Kadabra, "Kadabra", Offensive, Low, {Psychic}, 1, Alakazam},
   {Alakazam, "Alakazam", Offensive, Low, {Psychic}, 2, Null},
   {Machop, "Machop", Offensive, Medium, {Fighting}, 0, Machoke},
   {Machoke, "Machoke", Offensive, Medium, {Fighting}, 1, Machamp},
   {Machamp, "Machamp", Offensive, High, {Fighting}, 2, Null},
   {Bellsprout, "Bellsprout", Offensive, Low, {Grass, Poison}, 0, Weepinbell},
   {Weepinbell, "Weepinbell", Offensive, Medium, {Grass, Poison}, 1, Victreebel},
   {Victreebel, "Victreebel", Offensive, Medium, {Grass, Poison}, 2, Null},
   {Tentacool, "Tentacool", Defensive, Low, {Water, Poison}, 3, Tentacruel},
   {Tentacruel, "Tentacruel", Defensive, Medium, {Water, Poison}, 4, Null},
   {Geodude, "Geodude", Defensive, Medium, {Rock, Ground}, 0, Graveler},
   {Graveler, "Graveler", Defensive, Medium, {Rock, Ground}, 1, Golem},
   {Golem, "Golem", Defensive, High, {Rock, Ground}, 2, Null},
   {Ponyta, "Ponyta", Offensive, Low, {Fire}, 3, Rapidash},
   {Rapidash, "Rapidash", Offensive, Medium, {Fire}, 4, Null},
   {Slowpoke, "Slowpoke", Defensive, High, {Water, Psychic}, 3, Slowbro},
   {Slowbro, "Slowbro", Defensive, High, {Water, Psychic}, 4, Null},
   {Magnemite, "Magnemite", Offensive, Low, {Electric, Steel}, 3, Magneton},
   {Magneton, "Magneton", Offensive, Medium, {Electric, Steel}, 4, Null},
   {Farfetchd, "Farfetchd", Balanced, Medium, {Normal, Flying}, 5, Null},
   {Doduo, "Doduo", Offensive, Low, {Normal, Flying}, 3, Dodrio},
   {Dodrio, "Dodrio", Offensive, Medium, {Normal, Flying}, 4, Null},
   {Seel, "Seel", Defensive, Medium, {Water}, 3, Dewgong},
   {Dewgong, "Dewgong", Defensive, Medium, {Water, Ice}, 4, Null},
   {Grimer, "Grimer", Defensive, Medium, {Poison}, 3, Muk},
   {Muk, "Muk", Defensive, High, {Poison}, 4, Null},
   {Shellder, "Shellder", Defensive, Low, {Water}, 3, Cloyster},
   {Cloyster, "Cloyster", Defensive, Medium, {Water, Ice}, 4, Null},
   {Gastly, "Gastly", Offensive, Low, {Ghost, Poison}, 0, Haunter},
   {Haunter, "Haunter", Offensive, Low, {Ghost, Poison}, 1, Gengar},
   {Gengar, "Gengar", Offensive, Medium, {Ghost, Poison}, 2, Null},
   {Onix, "Onix", Defensive, Low, {Rock, Ground}, 5, Null},
   {Drowzee, "Drowzee", Defensive, Medium, {Psychic}, 3, Hypno},
   {Hypno, "Hypno", Defensive, Medium, {Psychic}, 4, Null},
   {Krabby, "Krabby", Offensive, Low, {Water}, 3, Kingler},
   {Kingler, "Kingler", Offensive, Medium, {Water}, 4, Null},
   {Voltorb, "Voltorb", Offensive, Low, {Electric}, 3, Electrode},
   {Electrode, "Electrode", Offensive, Low, {Electric}, 4, Null},
   {Exeggcute, "Exeggcute", Balanced, Low, {Grass, Psychic}, 3, Exeggutor},
   {Exeggutor, "Exeggutor", Offensive, High, {Grass, Psychic}, 4, Null},
   {Cubone, "Cubone", Defensive, Low, {Ground}, 3, Marowak},
   {Marowak, "Marowak", Defensive, Medium, {Ground}, 4, Null},
   {Hitmonlee, "Hitmonlee", Offensive, Medium, {Fighting}, 3, Hitmonchan},
   {Hitmonchan, "Hitmonchan", Offensive, Medium, {Fighting}, 4, Null},
   {Lickitung, "Lickitung", Defensive, Medium, {Normal}, 5, Null},
   {Koffing, "Koffing", Defensive, Medium, {Poison}, 3, Weezing},
   {Weezing, "Weezing", Defensive, Medium, {Poison}, 4, Null},
   {Rhyhorn, "Rhyhorn", Defensive, Medium, {Ground, Rock}, 3, Rhydon},
   {Rhydon, "Rhydon", Defensive, High, {Ground, Rock}, 4, Null},
   {Chansey, "Chansey", Defensive, VeryHigh, {Normal}, 5, Null},
   {Tangela, "Tangela", Defensive, Medium, {Grass}, 5, Null},
   {Kangaskhan, "Kangaskhan", Balanced, Medium, {Normal}, 5, Null},
   {Horsea, "Horsea", Offensive, Low, {Water}, 3, Seadra},
   {Seadra, "Seadra", Offensive, Medium, {Water}, 4, Null},
   {Goldeen, "Goldeen", Balanced, Low, {Water}, 3, Seaking},
   {Seaking, "Seaking", Balanced, Medium, {Water}, 4, Null},
   {Staryu, "Staryu", Balanced, Low, {Water}, 3, Starmie},
   {Starmie, "Starmie", Balanced, Medium, {Water, Psychic}, 4, Null},
   {MrMime, "Mr. Mime", Defensive, Medium, {Psychic, Fairy}, 5, Null},
   {Scyther, "Scyther", Offensive, Medium, {Bug, Flying}, 5, Null},
   {Jynx, "Jynx", Offensive, Medium, {Ice, Psychic}, 5, Null},
   {Electabuzz, "Electabuzz", Offensive, Medium, {Electric}, 5, Null},
   {Magmar, "Magmar", Offensive, Medium, {Fire}, 5, Null},
   {Pinsir, "Pinsir", Offensive, Medium, {Bug}, 5, Null},
   {Tauros, "Tauros", Offensive, Medium, {Normal}, 5, Null},
   {Magikarp, "Magikarp", Defensive, Low, {Water}, 3, Gyarados},
   {Gyarados, "Gyarados", Offensive, High, {Water, Flying}, 4, Null},
   {Lapras, "Lapras", Defensive, High, {Water, Ice}, 5, Null},
   {Ditto, "Ditto", Balanced, Low, {Normal}, 5, Null},
   {Eevee, "Eevee", Balanced, Medium, {Normal}, 3, Null},
   {Vaporeon, "Vaporeon", Defensive, High, {Water}, 4, Null},
   {Jolteon, "Jolteon", Offensive, Medium, {Electric}, 4, Null},
   {Flareon, "Flareon", Offensive, Medium, {Fire}, 4, Null},
   {Porygon, "Porygon", Balanced, Medium, {Normal}, 4, Null},
   {Omanyte, "Omanyte", Defensive, Low, {Rock, Water}, 3, Omastar},
   {Omastar, "Omastar", Defensive, Medium, {Rock, Water}, 4, Null},
   {Kabuto, "Kabuto", Balanced, Low, {Rock, Water}, 3, Kabutops},
   {Kabutops, "Kabutops", Offensive, Medium, {Rock, Water}, 4, Null},
   {Aerodactyl, "Aerodactyl", Offensive, Medium, {Rock, Flying}, 5, Null},
   {Snorlax, "Snorlax", Defensive, VeryHigh, {Normal}, 5, Null},
   {Articuno, "Articuno", Defensive, High, {Ice, Flying}, 5, Null},
   {Zapdos, "Zapdos", Offensive, High, {Electric, Flying}, 5, Null},
   {Moltres, "Moltres", Offensive, High, {Fire, Flying}, 5, Null},
   {Dratini, "Dratini", Offensive, Low, {Dragon}, 0, Dragonair},
   {Dragonair, "Dragonair", Offensive, Medium, {Dragon}, 1, Dragonite},
   {Dragonite, "Dragonite", Balanced, High, {Dragon, Flying}, 2, Null},
   {Mewtwo, "Mewtwo", Offensive, High, {Psychic}, 5, Null},
   {Mew, "Mew", Balanced, Medium, {Psychic}, 5, Null}
};

// map to specify the efficiency of the pokemon in the attack
// rows - the attacking pokemon, columns - the attacked pokemon
static unordered_map<types, unordered_map<types, double>> efficiencyMap = {
    {Normal, {{Rock, 0.8}, {Ghost, 0.0}, {Steel, 0.8}}},
    {Fire, {{Fire, 0.8}, {Water, 0.8}, {Grass, 1.2}, {Ice, 1.2}, {Bug, 1.2}, {Rock, 0.8}, {Dragon, 0.8}, {Steel, 1.2}}},
    {Water, {{Fire, 1.2}, {Water, 0.8}, {Grass, 0.8}, {Ground, 1.2}, {Rock, 1.2}, {Dragon, 0.8}}},
    {Electric, {{Water, 1.2}, {Electric, 0.8}, {Grass, 0.8}, {Ground, 0.0}, {Flying, 1.2}, {Dragon, 0.8}}},
    {Grass, {{Fire, 0.8}, {Water, 1.2}, {Grass, 0.8}, {Poison, 0.8}, {Ground, 1.2}, {Flying, 0.8}, {Bug, 0.8}, {Rock, 1.2}, {Dragon, 0.8}, {Steel, 0.8}}},
    {Ice, {{Fire, 0.8}, {Water, 0.8}, {Grass, 1.2}, {Ice, 0.8}, {Ground, 1.2}, {Flying, 1.2}, {Dragon, 1.2}, {Steel, 0.8}}},
    {Fighting, {{Normal, 1.2}, {Ice, 1.2}, {Poison, 0.8}, {Flying, 0.8}, {Psychic, 0.8}, {Bug, 0.8}, {Rock, 1.2}, {Ghost, 0.0}, {Dark, 1.2}, {Steel, 1.2}, {Fairy, 0.8}}},
    {Poison, {{Grass, 1.2}, {Poison, 0.8}, {Ground, 0.8}, {Rock, 0.8}, {Ghost, 0.8}, {Steel, 0.0}, {Fairy, 1.2}}},
    {Ground, {{Fire, 1.2}, {Electric, 1.2}, {Grass, 0.8}, {Poison, 1.2}, {Flying, 0.0}, {Bug, 0.8}, {Rock, 1.2}, {Steel, 1.2}}},
    {Flying, {{Electric, 0.8}, {Grass, 1.2}, {Fighting, 1.2}, {Bug, 1.2}, {Rock, 0.8}, {Steel, 0.8}}},
    {Psychic, {{Fighting, 1.2}, {Poison, 1.2}, {Psychic, 0.8}, {Dark, 0.0}, {Steel, 0.8}}},
    {Bug, {{Fire, 0.8}, {Grass, 1.2}, {Fighting, 0.8}, {Poison, 0.8}, {Flying, 0.8}, {Psychic, 1.2}, {Ghost, 0.8}, {Dark, 1.2}, {Steel, 0.8}, {Fairy, 0.8}}},
    {Rock, {{Fire, 1.2}, {Ice, 1.2}, {Fighting, 0.8}, {Ground, 0.8}, {Flying, 1.2}, {Bug, 1.2}, {Steel, 0.8}}},
    {Ghost, {{Normal, 0.0}, {Psychic, 1.2}, {Ghost, 1.2}, {Dark, 0.8}}},
    {Dragon, {{Dragon, 1.2}, {Steel, 0.8}, {Fairy, 0.0}}},
    {Fairy, {{Fighting, 1.2}, {Dragon, 1.2}, {Dark, 1.2}, {Fire, 0.8}, {Poison, 0.8}, {Steel, 0.8}}},
    {Steel, {{Fire, 0.8}, {Water, 0.8}, {Electric, 0.8}, {Ice, 1.2}, {Rock, 1.2}, {Fairy, 1.2}}}
};


// matrix depicting the min CP of the pokemon
// rows - types, columns - stages
const unsigned int minCP[3][6]
{
    {30, 300, 1500, 30, 600, 50},
    {30, 400, 1800, 30, 700, 50},
    {30, 500, 2000, 30, 800, 50}
};

// matrix depicting the max CP of the pokemon
// rows - types, columns - stages
const static unsigned int maxCP[3][6]
{
    {400, 2000, 3000, 800, 2700, 2300},
    {500, 2200, 3500, 1000, 2900, 2500},
    {600, 2500, 4000, 1200, 3100, 2700}
};

// matrix depicting the min PP of the pokemon
// rows - types, columns - stages
const static unsigned int minPP[3][6]
{
    {10, 60, 120, 10, 90, 20},
    {10, 50, 100, 10, 80, 20},
    {10, 40, 80, 10, 70, 20}
};

// matrix depicting the max PP of the pokemon
// rows - types, columns - stages
const static unsigned int maxPP[3][6]
{
    {60, 120, 200, 90, 180, 180},
    {50, 100, 170, 80, 150, 150},
    {40, 80, 140, 70, 120, 120}
};

// matrix depicting the min HP of the pokemon
// rows - HealthLevel, columns - stages
const static unsigned int minHP[3][6]
{
    {10, 60, 120, 10, 90, 20},
    {10, 50, 100, 10, 80, 20},
    {10, 40, 80, 10, 70, 20}
};

// matrix depicting the max HP of the pokemon
// rows - HealthLevel, columns - stages
const static unsigned int maxHP[3][6]
{
    {60, 120, 200, 90, 180, 180},
    {50, 100, 170, 80, 150, 150},
    {40, 80, 140, 70, 120, 120}
};

// enum represeting possible special abilities of pokemons:
// -- healing - +3HP added during every round of battle
// -- special attack - creates additional effect of the attacked pokemon (depends on type)
// -- dodge - omitting the attak of the pokemon
// -- reemision - reemitting the attack of the oponent
// -- shield breaker - overcomes additional protection of the oponent
// -- shield - creates a barrier for the next attack of the oponent 
enum abilities { healing, spattack, dodge, reemit, sbreaker, shield };

// enum representing the colors created in the terminal
enum ColorName {
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    BrightBlack, BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta, BrightCyan, BrightWhite
};

// 2D array containing ASCII escape sequences for foreground and background colors
// example: colorCodes[BrightCyan][1]
const static string colorCodes[16][2] = {
    {"\x1B[30m", "\x1B[40m"},  // Black
    {"\x1B[31m", "\x1B[41m"},  // Red
    {"\x1B[32m", "\x1B[42m"},  // Green
    {"\x1B[33m", "\x1B[43m"},  // Yellow
    {"\x1B[34m", "\x1B[44m"},  // Blue
    {"\x1B[35m", "\x1B[45m"},  // Magenta
    {"\x1B[36m", "\x1B[46m"},  // Cyan
    {"\x1B[37m", "\x1B[47m"},  // White
    {"\x1B[90m", "\x1B[100m"}, // Bright Black
    {"\x1B[91m", "\x1B[101m"}, // Bright Red
    {"\x1B[92m", "\x1B[102m"}, // Bright Green
    {"\x1B[93m", "\x1B[103m"}, // Bright Yellow
    {"\x1B[94m", "\x1B[104m"}, // Bright Blue
    {"\x1B[95m", "\x1B[105m"}, // Bright Magenta
    {"\x1B[96m", "\x1B[106m"}, // Bright Cyan
    {"\x1B[97m", "\x1B[107m"}  // Bright White
};

const static string colorEnd = "\x1B[0m";
const static string clearTerminal = "\033c";
const static string invalidInput = colorCodes[Red][0] + "[!!!] Invalid input, try again." + colorEnd;

// array mapping Pokemon types to their respective colors
const int typeColors[18] = {
    White,      // Normal
    Red,        // Fire
    Blue,       // Water
    Yellow,     // Electric
    Green,      // Grass
    Cyan,       // Ice
    BrightRed,  // Fighting
    Magenta,    // Poison
    BrightBlack,      // Ground
    BrightBlue, // Flying
    BrightMagenta, // Psychic
    BrightGreen,   // Bug
    BrightYellow,  // Rock
    BrightBlack,         // Ghost
    BrightCyan,    // Dragon
    BrightWhite,   // Fairy
    BrightBlack,         // Steel
    BrightBlack          // Dark
};