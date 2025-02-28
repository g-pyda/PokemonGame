#include "functions.h"
#include <string>

// function that represents attack of the pokemon on the other one
void Attack(Pokemon* fighter, Pokemon* opponent, types effectA)
{
	unsigned int hp_taken;
	types effect = effectA;
	abilities special_attack;
	// attack of the player
	hp_taken = 5 + fighter->cp / 200;
	// usage of special abilities
	cout << endl << pokedex[fighter->index - 1].name << " attacks " << pokedex[opponent->index - 1].name << " with " << types_s[effectA] << " attack." << endl;
	for (auto ab : fighter->ability)
	{
		switch (ab)
		{
		case healing:
			fighter->hp_left += 3;
			if (fighter->hp_left > fighter->hp)
			{
				cout << pokedex[fighter->index - 1].name << " used healing!" << endl;
				fighter->hp_left = fighter->hp;
				special_attack = healing;
			}
			break;
		case spattack:
			if (rand() % 100 < 50 * (fighter->hp_left / fighter->hp))
			{
				cout << pokedex[fighter->index - 1].name << " used special attack!" << endl;
				hp_taken *= 1.5;
				special_attack = spattack;
			}
			break;
		case sbreaker:
			if (rand() % 100 < 50 * (fighter->cp * 0.01 / fighter->hp))
			{
				cout << pokedex[fighter->index - 1].name << " used shield breaker!" << endl;
				opponent->shield = false;
				special_attack = sbreaker;
			}
			break;
		case shield:
			if (rand() % 100 < 50 * (fighter->pp / fighter->hp_left))
			{
				cout << pokedex[fighter->index - 1].name << " used shield!" << endl;
				special_attack = shield;
				fighter->shield = true;
			}
			break;
		}
	}
	// calculating the average efficiency of the attack
	double eff = 1;
	for (int j = 0; j < pokedex[opponent->index - 1].type.size(); j++)
		if (efficiencyMap[effect].count(pokedex[opponent->index - 1].type[j]))
			eff *= efficiencyMap[effect][pokedex[opponent->index - 1].type[j]];
		else
			eff *= 1.0;

	// update of the state of the wild pokemon
	// checking of the defensive abilities of the attacked pokemon
	for (auto ab : opponent->ability)
	{
		switch (ab)
		{
		case dodge:
			if (rand() % 100 < 50 * (opponent->pp / opponent->hp))
			{
				special_attack = dodge;
				cout << "Attack dodged by " << pokedex[opponent->index - 1].name << "!" << endl;
				hp_taken = 0;
			}
			break;
		case reemit:
			if (rand() % 100 < 50 * (0.01 * opponent->cp / opponent->pp))
			{
				special_attack = reemit;
				cout << "Attack reemited by " << pokedex[opponent->index - 1].name << "!" << endl;
				fighter->hp_left -= 5 * eff;
				hp_taken = 0;
			}
			break;
		}
	}
	if (opponent->shield)
	{
		cout << "Shield used by " << pokedex[opponent->index - 1].name << "!" << endl;
		hp_taken *= 0.25;
		opponent->shield = false;
	}
	cout << hp_taken * eff << " HP were taken from " << pokedex[opponent->index - 1].name << endl << endl;
	// applying the change of HP
	opponent->hp_left -= hp_taken * eff;
}

// function to read the records from the previous game
vector <string> readRecords()
{
	ifstream records;
	records.open("records.txt");
	vector <string> record_lines;
	string temp;
	int i = 0;
	do {
		getline(records, temp); //filling our string vector with the content of ith line of .txt file
		if (records.eof()) break;
		record_lines.push_back(temp);
	} while (!temp.empty() && ++i);
	return record_lines;
}

// function to read name of the player from the text file
string getName(string line)
{
	bool space = false;
	string name = "";
	for (int j = 0; j < line.size(); j++)
	{
		if (line[j] == ' ')
		{
			space = true;
			continue;
		}
		if (space) name += line[j];
	}
	return name;
}

// function to read exp of the player from the text file
int getExp(string line)
{
	bool space = false;
	string exp = "";
	for (int j = 0; j < line.size(); j++)
	{
		if (line[j] == ' ')
		{
			space = true;
			continue;
		}
		if (space) exp += line[j];
	}
	return stoi(exp);
}

// function to read gold of the player from the text file
int getGold(string line)
{
	bool space = false;
	string gold = "";
	for (int j = 0; j < line.size(); j++)
	{
		if (line[j] == ' ')
		{
			space = true;
			continue;
		}
		if (space) gold += line[j];
	}
	return stoi(gold);
}

// function to read pokemons of the player from the text file
vector <Pokemon> getPokemons(vector <string> lines)
{
	vector <Pokemon> result;
	bool parenthesis = false;
	string pokedata;
	// array of string representing the elements of pokemon class
	// 0 - index, 1 - cp, 2 - hp, 3 - hp_left
	// 4 - pp, 5 - exp, 6 - ability, 7 - shield
	string elements[8] = { "","","","","","","","" };
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '{') // start of data of the new pokemon
			{
				parenthesis = true;
				continue;
			}
			else if (lines[i][j] == '}') // end of the data - pokemon is created
			{
				parenthesis = false;
				// reading the data and assigning them to the specific atributes of the pokemon
				for (int k = 0, elem = 0; k < pokedata.size(); k++)
				{
					if (pokedata[k] == ',')
					{
						elem++;
						continue;
					}
					elements[elem] += pokedata[k];
				}
				// creating the pokemon containing this data and adding it to the result vector
				result.push_back(Pokemon(elements));

				for (int k = 0; k < 8; k++)
					elements[k] = "";
				pokedata = "";
				continue;
			}
			if (parenthesis) pokedata += lines[i][j];
		}
	}
	return result;
}

// function to read potions of the player from the text file
vector <Potion> getPotions(vector <string> lines)
{
	vector <Potion> result;
	bool parenthesis = false;
	string potionData;
	// array of string representing the elements of potion class
	// 0 - type, 1 - points, 2 - price
	string elements[3] = { "","","" };
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '{') // start of data of the new potion
			{
				parenthesis = true;
				continue;
			}
			else if (lines[i][j] == '}') // end of the data - potion is created
			{
				parenthesis = false;
				// reading the data and assigning them to the specific atributes of the potion
				for (int k = 0, elem = 0; k < potionData.size(); k++)
				{
					if (potionData[k] == ',')
					{
						elem++;
						continue;
					}
					elements[elem] += potionData[k];
				}
				// creating the potion containing this data and adding it to the result vector
				result.push_back(Potion(elements));
				for (int k = 0; k < 3; k++)
					elements[k] = "";
				potionData = "";
				continue;
			}
			if (parenthesis) potionData += lines[i][j];
		}
	}
	return result;
}

// function to read status of caught pokemons
vector <bool> getPCaught(string line)
{
	vector <bool> result;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '0') result.push_back(false);
		else result.push_back(true);
	}
	return result;
}