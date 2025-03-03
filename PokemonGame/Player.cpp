
#include "constants.h"
#include "functions.h"
#include <string>
#include "Player.h"

// default constructor of the player
Player::Player()
{
	std::cout << color("Insert your nickname: ",BrightWhite) << std::endl;
	std::cin >> name;
	// starting values for new player
	exp = 100;
	gold = 100;
	for (int i = 0; i < 151; i++) pokeCaught[i] = false;
	// creating a start pokemon
	Pokemon first(exp);
	int choice;

	while (true)
	{
		std::cout << color("Choose your start pokemon: ",BrightWhite) << std::endl
			<< color("1: Bulbasaur", BrightGreen) << std::endl 
			<< color("2: Squirtle", BrightBlue) << std::endl 
			<< color("3: Charmander", BrightRed) << std::endl;
		std::cin >> choice;
		std::cout << clearTerminal;
		if (!std::cin.good()) {
			std::cout << invalidInput << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		break;
	}
	pokemons.push_back(first);
	switch (choice)
	{
		case 1:
			pokemons[0].index = Bulbasaur;
			break;
		case 2:
			pokemons[0].index = Squirtle;
			break;
		case 3:
			pokemons[0].index = Charmander;
			break;
		case 4:
			pokemons[0].index = Pikachu;
			break;
		default:
			pokemons[0].index = Eevee;
			break;
	}
	pokeCaught[pokemons[0].index - 1] = true;
	pokemons[0].cp = 400;
	pokemons[0].hp_left = pokemons[0].hp = 40;
	pokemons[0].pp = 40;
}

// constructor of the player out of saved data
Player::Player(std::string n, int e, int g, std::vector <Potion> pt, std::vector <Pokemon> pk, std::vector <bool> pc)
{
	name = n;
	exp = e;
	gold = g;
	for (int i = 0; i < pt.size(); i++) potions.push_back(pt[i]);
	for (int i = 0; i < pk.size(); i++) pokemons.push_back(pk[i]);
	for (int i = 0; i < pc.size(); i++) pokeCaught[i] = pc[i];
}

// method to say if player found all pokemons
bool Player::CaughtAll()
{
	// iteration over every pokemon in the pokedex
	for (int i = 0; i < 60; i++)
		if (!pokeCaught[i]) return false; // if one pokemon is missing, then not all pokemons are found -> false in result
	return true; // loop iterated over every pokemon in the pokedex, so every pokemon was caught
}

// method to obtain an item/pokemon out of treasure/hostile
void Player::GetItem(Potion pot)
{
	potions.push_back(pot);
}

void Player::GetItem(Pokemon pok)
{
	pokemons.push_back(pok);
	pokeCaught[pok.index-1] = true;
}

// method to sell an object/pokemon from the inventory
void Player::SellPokemon()
{
	std::string choice;
	while (true)
	{
		try
		{
			// display all potions/pokemons in the inventory

			ShowStats();
			std::cout << std::endl; 
			for (int i = 0; i < pokemons.size(); i++)
			{
				std::cout << color(std::to_string(i + 1) + ". ", BrightWhite);
				pokemons[i].BattleStats();
				std::cout << "\t" <<  color(std::to_string(round(pokemons[i].ShowPrice() * 0.8)) + " coins", BrightYellow) << std::endl;
			}	
			std::cout << color("Choose the pokemon to sell or 'Q' to quit:", BrightWhite) << std::endl;
			std::cin >> choice;
			std::cout << clearTerminal;

			// deleting the pokemon and adding coins

			if (choice == "q" || choice == "Q") break;
			else if (std::stoi(choice) > pokemons.size() && choice != "q" && choice != "Q")
			{
				std::cout << invalidInput << std::endl;
				choice.clear();	
				continue;
			}
			
			gold += pokemons[std::stoi(choice)].ShowPrice()*0.8;
			pokemons.erase(pokemons.begin()+std::stoi(choice)-1);
			break;
		}
		catch(const std::exception& e)
		{
			std::cout << invalidInput << std::endl;
			choice.clear();
		}
		
	}
	
				
	
}

void Player::SellPotion()
{
	
	std::string choice;
	while (true)
	{
		try
		{
			// display all potions/pokemons in the inventory

			ShowStats();

			std::cout << color("Choose the potion to sell or 'Q' to quit:", BrightWhite) << std::endl;
			for (int i = 0; i < potions.size(); i++)
			{
				std::cout << color(std::to_string(i + 1) + ".", BrightWhite);
				if (potions[i].ShowKind() == "Buff") std::cout << color(potions[i].ShowKind(),Blue);
				else std::cout << color(potions[i].ShowKind(),BrightGreen);
				std::cout << color(": " + std::to_string(potions[i].ShowPoints()) + " " + std::to_string(potions[i].ShowPrice() * 0.8), BrightWhite)
				<< std::endl;
			}
			std::cin >> choice;
			std::cout << clearTerminal;
			if (choice == "q" || choice == "Q") break;
			else if (std::stoi(choice) > potions.size() && choice != "q" && choice != "Q")
			{
			std::cout << invalidInput << std::endl;
			choice.clear();
			continue;
			}
			// deleting the potion and adding coins
			gold += potions[std::stoi(choice)].ShowPrice()*0.8;
			potions.erase(potions.begin()+std::stoi(choice)-1);
			break;
		}
		catch(const std::exception& e)
		{
			std::cout << invalidInput << std::endl;
			choice.clear();
		}
		
	}
}

// method to buy an object/pokemon from the marchant
void Player::Buy(Potion pot)
{
	// deleting the coins and adding potion to the inventory
	if (gold > pot.ShowPrice())
	{
		gold -= pot.ShowPrice();
		potions.push_back(pot);
	}
	else
	{
		std::cout << color("You don't have enough money to buy this potion.", Red) << std::endl;
	}
}

void Player::Buy(Pokemon pok)
{
	// deleting the coins and adding potion to the inventory
	if (gold > pok.ShowPrice())
	{
		gold -= pok.ShowPrice();
		pokemons.push_back(pok);
	}
	else
	{
		std::cout << color("You don't have enough money to buy this pokemon.", Red) << std::endl;
	}
	pokeCaught[pok.index-1] = true;
}

// method to show data of the user
unsigned int Player::ShowEXP() const
{
	return exp;
}

unsigned int Player::ShowGold() const
{
	return gold;
}

std::string Player::ShowName() const
{
	return name;
}

unsigned int Player::ShowPokemonNR() const
{
	return pokemons.size();
}

unsigned int Player::ShowPotionNR() const
{
	return potions.size();
}

unsigned int Player::HMCaught() const
{
	int counter = 0;
	for (int i = 0; i < 151; i++)
	{
		if (pokeCaught[i]) counter++;
	}
	return counter;
}

// method to show statistics
void Player::ShowStats()
{
	std::cout << color("| " + name + " | ", BrightWhite) 
		<< color("EXP: " + std::to_string(exp), Blue) << color(" | ", BrightWhite)
		<< color("GOLD : " + std::to_string(gold), BrightYellow)
		<< color(" | EQ :", BrightWhite) 
		<< color(" pokemons - " + std::to_string(ShowPokemonNR()), BrightGreen)
		<< color(",", BrightWhite) 
		<< color(" potions - " + std::to_string(ShowPotionNR()), BrightMagenta) << color(" | ", BrightWhite)
		<< color(std::to_string(HMCaught()) + " species caught ", Green) << color("|", BrightWhite) << std::endl;
}

// method to display all the pokemons in the inventory
void Player::ShowPokemons()
{
	for (int i = 0; i < pokemons.size(); i++)
	{
		std::cout << color(std::to_string(i+1) + ". ", BrightWhite);
		pokemons[i].BattleStats();
	}
}
        
// method to display all the potions in the inventory
void Player::ShowPotions()
{
	for (int i = 0; i < potions.size(); i++)
	{
		std::cout << i + 1 << ". ";
		if (potions[i].ShowKind() == "Buff")
			std::cout << color(potions[i].ShowKind(), Blue) << " " 
			<< color(std::to_string(potions[i].ShowPoints()) + " points ", BrightWhite) 
			<< color(std::to_string(potions[i].ShowPrice()) + " coins", BrightYellow)
			<< std::endl;
		else std::cout << color(potions[i].ShowKind(), BrightMagenta) << " "
			<< color(std::to_string(potions[i].ShowPoints()) + " points ", BrightWhite)
			<< color(std::to_string(potions[i].ShowPrice()) + " coins", BrightYellow)
			<< std::endl;
	}
}

// method activating game module: fighting with wild pokemon
void Player::WildBattle()
{
	// spawning the random pokemon
	Pokemon opponent(exp);
	// decision if to take up a battle
	std::string choice;
	while (true)
	{
		std::cout << color("You have encountered a wild pokemon!", BrightWhite) << std::endl;
		opponent.BattleStats();
		std::cout << std::endl << color("Your pokemons:", BrightWhite) << std::endl;
		ShowPokemons();
		std::cout << std::endl << color("Do you want to fight?", BrightWhite) << std::endl;
		std::cout << color("Y: yes   N: no", BrightWhite) << std::endl;
		std::cin >> choice;
		std::cout << clearTerminal;
		if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") break;
		else std::cout << invalidInput << std::endl;
	}
	if (choice == "n" || choice == "N") return;
	else if(choice == "y" || choice == "Y")
	{
	fight_outcome outcome;
	unsigned int hp_taken;
	types effect;
	abilities special_attack = abilities(7);
	abilities special_attack2 = abilities(7);
	types sp_at_type;
	// pointer to the pokemon that fights
	int choice_p;
	while (true)
	{
		std::cout << color("Wild pokemon:", BrightWhite) << std::endl;
		opponent.BattleStats();
		std::cout << std::endl << color("Choose the pokemon to fight.", BrightWhite) << std::endl;
		ShowPokemons();
		std::cin >> choice_p;
		std::cout << clearTerminal;
		if (!std::cin.good()) {
			std::cout << invalidInput << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		if (choice_p <= pokemons.size() && choice_p > 0) break;
		else std::cout << invalidInput << std::endl;
	}
				
	Pokemon* fighter = &pokemons[choice_p - 1];
	std::cout << color("You chose ", BrightWhite) << color(pokedex[fighter->index - 1].name, Blue) 
		<< color(". Let's fight!", BrightWhite) << std::endl;
	sleep(2);
	// loop of every round
	while (true)
	{	
		// choice of the attack of the player 
		int choice_t;
		while (true)
		{
			std::cout << color("Your pokemon: ", BrightWhite);
			fighter->BattleStats();
			std::cout << color("Wild pokemon: ", BrightWhite);
			opponent.BattleStats();
			std::cout << std::endl << color("Choose type of the attack.", BrightWhite) << std::endl;
			for (int i = 0; i < pokedex[fighter->index - 1].type.size(); i++)
				std::cout << color(std::to_string(i + 1) + ". ", BrightWhite) 
					<< color(types_s[pokedex[fighter->index - 1].type[i]], (ColorName)typeColors[pokedex[fighter->index - 1].type[i]])
					<< color(" attack.", BrightWhite) << std::endl;
			
			std::cin >> choice_t;
			std::cout << clearTerminal;
			if (!std::cin.good()) {
				std::cout << invalidInput << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				continue;
			}
			if (choice_t <= pokedex[fighter->index - 1].type.size()) break;
			else std::cout << invalidInput << std::endl;
		}
		effect = pokedex[fighter->index - 1].type[choice_t-1];
		// attack of the player
		std::cout << color("Your pokemon: ", BrightWhite);
		fighter->BattleStats();
		std::cout << color("Wild pokemon: ", BrightWhite);
		opponent.BattleStats();
		Attack(fighter, &opponent, effect);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		sleep(3);
		std::cout << clearTerminal;
		// checking if the wild pokemon still can fight
		if (opponent.hp_left > opponent.hp || opponent.hp_left == 0)
		{
			// wild pokemon cannot fight back
			opponent.hp_left = 1;
			outcome = win;
			
			while (true)
			{
				std::cout << color("Your pokemon: ", BrightWhite);
				fighter->BattleStats();
				std::cout << color("Wild pokemon: ", BrightWhite);
				opponent.BattleStats();
				std::cout << std::endl << color("Wild pokemon cannot fight back!", BrightGreen) << std::endl << std::endl
					<< color("C: catch the pokemon", BrightWhite) << std::endl 
					<< color("K: kill the pokemon", BrightWhite) << std::endl;
				std::cin >> choice;
				std::cout << clearTerminal;
				if (choice == "c" || choice == "C" || choice == "k" || choice =="K") break;
				else std::cout << invalidInput << std::endl;
			}
			if (choice == "c" || choice == "C") outcome = catching;
			else if (choice == "k" || choice == "K") outcome = kill;
			break;
		} 
		std::cout << color("Your pokemon: ", BrightWhite);
		fighter->BattleStats();
		std::cout << color("Wild pokemon: ", BrightWhite);
		opponent.BattleStats();
		std::cout << std::endl << color("Watch out!", BrightRed) 
			<< color(" The wild pokemon is attacking!", BrightWhite) << std::endl;
		// wild pokemon strikes back
		effect = pokedex[opponent.index - 1].type[rand()%(pokedex[opponent.index - 1].type.size())];
		Attack(&opponent, fighter, effect);
		sleep(3);
		std::cout << clearTerminal;
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		// checking if the player pokemon lost
		if (fighter->hp_left > fighter->hp || fighter->hp_left == 0)
		{
			// player lost
			outcome = failure;
			fighter->hp_left = 0;
			std::cout << color("Your pokemon: ", BrightWhite);
			fighter->BattleStats();
			pokemons.erase(pokemons.begin() + choice_p - 1);
			if (pokemons.size() <= 0) {
				std::cout << std::endl << color("Oh no. Your pokemon got killed!", Red) << std::endl;
				sleep(3);
				return;
			}
			while (true)
			{
				std::cout << color("Wild pokemon: ", BrightWhite);
				opponent.BattleStats();
				std::cout << std::endl << color("Oh no. Your pokemon got killed!", Red) << std::endl;
				std::cout << color("C: choose another pokemon", BrightWhite) << std::endl 
					<< color("R: run away", BrightWhite) << std::endl;
				std::cin >> choice;
				std::cout << clearTerminal;
				if (choice == "c" || choice == "C" || choice == "r" || choice == "R") break;
				else std::cout << invalidInput << std::endl;
			}
			
			if (choice == "c" || choice == "C")
			{
				while (true)
				{
					std::cout << color("Wild pokemon: ", BrightWhite);
					opponent.BattleStats();
					std::cout << color("Choose the pokemon to fight.", BrightWhite) << std::endl;
					ShowPokemons();
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cin >> choice_p;
					std::cout << clearTerminal;
					if (!std::cin.good()) {
						std::cout << invalidInput << std::endl;
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						continue;
					}
					if (choice_p <= pokemons.size()) break;
					else std::cout << invalidInput << std::endl;
				}		
				fighter = &pokemons[choice_p - 1];
				std::cout << color("You chose ", BrightWhite) 
					<< color(pokedex[fighter->index - 1].name, Blue) 
					<< color(". Let's fight!", BrightWhite) << std::endl;
			}
			else if (choice == "r" || choice == "R")
			{
				outcome = runaway;
				break;
			}
		}
	}
	// action regarding to the outcome of the battle
	std::cout << clearTerminal;
	switch (outcome)
	{
		case kill:
			std::cout << color("You killed the wild pokemon!", BrightGreen) << std::endl
				<< color("You receive ", BrightWhite) << color("150 exp", Blue) 
				<< color(", your pokemon receives ", BrightWhite) << color("50 exp", BrightBlack) 
				<< color(" and ", BrightWhite) << color("50 CP", Blue) << color(".", BrightWhite) << std::endl;
			exp += 150;
			fighter->exp += 50;
			fighter->cp += 50;
			fighter->hp_left += 3;
			fighter->Evolve();
			break;
		case catching:
			for (int i = 0; i < 4; i++) // there are only 3 tries of catching
			{
				std::cout << color("You're trying to catch the ", BrightWhite) << color(pokedex[opponent.index - 1].name, Blue) << std::endl << std::endl
					<< color("T: throw a pokeball", BrightWhite) << std::endl;
				do
				{
					std::cin >> choice;
					std::cout << clearTerminal;
				} while (choice != "t" && choice != "T");
				// pokemon wasn't caught - it can escape now
				if ((choice == "t" || choice == "T") && rand() % 100 - 10 * i * i * i > exp * 50 / (0.5 * opponent.cp + 100 * opponent.pp + 10 * opponent.hp_left))
				{
					std::cout << color("The pokemon escaped from the pokeball!", BrightYellow) << std::endl << std::endl;
					// pokemon may escape
					if (rand()%100 < 80 * opponent.hp_left / opponent.hp)
					{
						sleep(3);
						std::cout << color("Oh no, the pokemon run away from you!", Yellow) 
							<< color(" Better luck next time!", BrightWhite) << std::endl
							<< color("You receive ", BrightWhite) << color("50 exp", Blue)
							<< color(", your pokemon receives ", BrightWhite) << color("100 exp", BrightBlack)
							<< color(" and ", BrightWhite) << color("50 CP", Blue) << color(".", BrightWhite) << std::endl;
						exp += 50;
						fighter->exp += 100; 
						fighter->cp += 50;
						fighter->hp_left += 3;
						fighter->Evolve();
						break;
					}
				}
				else if (choice == "t" || choice == "T")// pokemon got caught
				{
					std::cout << clearTerminal;
					std::cout << color("Congratulations!", BrightGreen) << color(" You caught the ", BrightWhite) 
						<< color(pokedex[opponent.index - 1].name, Blue) << std::endl 
						<< color("You receive ", BrightWhite) << color("50 exp", Blue)
						<< color(", your pokemon receives ", BrightWhite) << color("100 exp", BrightBlack)
						<< color(" and ", BrightWhite) << color("50 CP", Blue) << color(".", BrightWhite) << std::endl;
					opponent.hp_left = opponent.hp * 0.75;
					pokemons.push_back(opponent);
					pokeCaught[opponent.index - 1] = true;
					exp += 200;
					fighter->exp += 100; 
					fighter->cp += 50;
					fighter->hp_left += 3;
					fighter->Evolve();
					break;
				}
				if (i == 3) // pokemon wasn't caught in 3 tries so it escapes
				{	
					std::cout << clearTerminal;
					std::cout << color("Oh no, the pokemon run away from you!", Yellow)
						<< color(" Better luck next time!", BrightWhite) << std::endl
						<< color("You receive ", BrightWhite) << color("50 exp", Blue)
						<< color(", your pokemon receives ", BrightWhite) << color("100 exp", BrightBlack)
						<< color(" and ", BrightWhite) << color("50 CP", Blue) << color(".", BrightWhite) << std::endl;
					exp += 50;
					fighter->exp += 100; 
					fighter->cp += 50;
					fighter->hp_left += 3;
					fighter->Evolve();
					break;
				}
			}
			break;
		case runaway:
			outcome = runaway;
			std::cout << color("You receive ", BrightWhite) << color(" 1 exp", Blue) 
				<< color(" for trying. Better luck next time!", BrightWhite) << std::endl;
			exp += 1;
			break;
	}
	}
	sleep(3);
}

// method activating game module: fighting with a coach
void Player::CoachBattle()
{
	// spawning the random pokemon
	Pokemon opponent(exp);
	// decision if to take up a battle
	std::cout << clearTerminal;
	std::cout << color("You have encountered a pokemon coach and they want to fight with you!", BrightWhite) << std::endl 
		<< std::endl << color("Their pokemon: ", BrightWhite) << std::endl;
	opponent.BattleStats();
	std::cout << std::endl << color("Your pokemons:", BrightWhite) << std::endl;
	ShowPokemons();

	std::string choice;
	while (true)
	{
		std::cout << std::endl << color("Do you want to fight?", BrightWhite) << std::endl
			<< color("Y: yes   N: no", BrightWhite) << std::endl;
		std::cin >> choice;
		std::cout << clearTerminal;
		if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") break;
		else std::cout << invalidInput << std::endl;
	}
	if (choice == "n" || choice == "N") return;
	else if(choice == "y" || choice == "Y")
	{
	fight_outcome outcome;
	unsigned int hp_taken;
	types effect;
	abilities special_attack = abilities(7);;
	abilities special_attack2 = abilities(7);;
	types sp_at_type;
	// pointer to the pokemon that fights
	int choice_p;
	while (true)
	{
		std::cout << color("Coached pokemon: ", BrightWhite) << std::endl;
		opponent.BattleStats();
		std::cout << std::endl << color("Choose the pokemon to fight.", BrightWhite) << std::endl;
		ShowPokemons();
		std::cin >> choice_p;
		std::cout << clearTerminal;
		if (!std::cin.good()) {
			std::cout << invalidInput << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		if (choice_p <= pokemons.size() && choice_p > 0) break;
		else std::cout << invalidInput << std::endl;
	}
				
	Pokemon* fighter = &pokemons[choice_p - 1];
	// loop for every round
	while (true)
	{
		// choice of the attack of the player 
		int choice_t;
		while (true)
		{
			std::cout << color("Your pokemon: ", BrightWhite);
			fighter->BattleStats();
			std::cout << color("Coached pokemon: ", BrightWhite);
			opponent.BattleStats();
			std::cout << std::endl << color("Choose type of the attack.", BrightWhite) << std::endl;
			for (int i = 0; i < pokedex[fighter->index - 1].type.size(); i++)
				std::cout << color(std::to_string(i + 1) + ". ", BrightWhite) 
				<< color(types_s[pokedex[fighter->index - 1].type[i]], (ColorName)typeColors[pokedex[fighter->index - 1].type[i]]) 
				<< color(" attack.", BrightWhite) << std::endl;
			std::cin >> choice_t;
			std::cout << clearTerminal;
			if (!std::cin.good()) {
				std::cout << invalidInput << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				continue;
			}
			if (choice_t <= pokedex[fighter->index - 1].type.size()) break;
			else std::cout << invalidInput << std::endl;
		}
		effect = pokedex[fighter->index - 1].type[choice_t-1];
		// attack of the player
		std::cout << color("Your pokemon: ", BrightWhite);
		fighter->BattleStats();
		std::cout << color("Coached pokemon: ", BrightWhite);
		opponent.BattleStats();
		Attack(fighter, &opponent, effect);
		sleep(3);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		std::cout << clearTerminal;
		// coached pokemon got defeated
		if (opponent.hp_left > opponent.hp || opponent.hp_left == 0)
		{
			// wild pokemon cannot fight back
			opponent.hp_left = 1;
			outcome = win;
			std::cout << color("Your pokemon: ", BrightWhite);
			fighter->BattleStats();
			std::cout << color("Coached pokemon: ", BrightWhite);
			opponent.BattleStats();
			std::cout << std::endl << color("Coached pokemon cannot fight back!", BrightGreen) << std::endl
				<< color("You receive ", BrightWhite) << color("50 exp", Blue)
				<< color(" and ", BrightWhite) << color("50 coins", BrightYellow)
				<< color(", your pokemon receives ", BrightWhite) << color("100 exp", BrightBlack)
				<< color(" and ", BrightWhite) << color("50 CP", Blue) << color(".", BrightWhite) << std::endl;
			exp += 100;
			gold += 50;
			fighter->cp += 20;
			fighter->exp += 50;
			fighter->hp_left += 3;
			fighter->Evolve();
			break;
		} 
		std::cout << color("Your pokemon: ", BrightWhite);
		fighter->BattleStats();
		std::cout << color("Coached pokemon: ", BrightWhite);
		opponent.BattleStats();
		// the coached pokemon strikes back
		effect = pokedex[opponent.index - 1].type[rand()%(pokedex[opponent.index - 1].type.size())];
		Attack(&opponent, fighter, effect);
		sleep(3);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		std::cout << clearTerminal;
		// pokemon got defeated
		if (fighter->hp_left > fighter->hp || fighter->hp_left == 0)
		{
			fighter->hp_left = 1;
			outcome = failure;
			std::cout << color("Your pokemon: ", BrightWhite);
			fighter->BattleStats();
			std::cout << color("Coached pokemon: ", BrightWhite);
			opponent.BattleStats();
			std::cout << std::endl << color("Oh no! Your pokemon got defeated!", BrightRed) << std::endl
				<< color("You receive ", BrightWhite) << color("1 exp", Blue)
				<< color(", your pokemon receives ", BrightWhite) << color("5 exp", BrightBlack)
				<< color(" and ", BrightWhite) << color("1 CP", Blue) << color(".", BrightWhite) << std::endl;
			exp += 1;
			fighter->cp += 1;
			fighter->exp += 5;
			fighter->Evolve();
			break;
		}
	}
}
sleep(3);
}

// method activating game module: finding a treasure
void Player::Treasure()
{
	std::cout << clearTerminal;
	// there are different chances of encountering some treasures
	int lot = rand()%100;
	if (lot < 5)
	{
		std::cout << color("You found a pokemon in the cage! Poor thing!", BrightGreen) << std::endl;
		Pokemon found(exp);
		pokemons.push_back(found);
		pokeCaught[found.index-1] = true;
	}
	else if (lot < 30)
	{
		std::cout << color("You found a chest with some stuff!", BrightGreen) << std::endl;
		int amount = rand()%3 + 1;
		for (int i = 0; i < amount/2; i++)
		{
			Potion pot;
			std::cout << color("Found ", BrightWhite) << pot.ShowKind() 
				<< color(" " + std::to_string(pot.ShowPoints()), BrightWhite) << std::endl;
			potions.push_back(pot);
		}
		if (lot < 50)
		{
			unsigned int c = rand()%21 * 10;
			std::cout << color("Found ", BrightWhite) 
				<< color(std::to_string(c) + " gold", BrightYellow) << std::endl;
			gold += c;
		}
	}
	else
	{
		std::cout << color("You encountered some experienced trainer who teached you some helpful techniques!", BrightGreen) << std::endl
			<< color("You receive 100 exp.", BrightGreen);
		exp += 100;
	}
	std::cout << std::endl;
	sleep(3);
}

// method activating game module: encountering a marchant
void Player::Marchant()
{
	std::cout << clearTerminal;
	// generating the set of items and pokemons (inventory of the marchant)
	std::vector <Potion> marchant_pot;
	for (int i = 0; i < 6; i++)
		marchant_pot.push_back(Potion());
	int lot = rand()%3;
	std::vector <Pokemon> marchant_pok;
	for (int i = 0; i < lot; i++)
		marchant_pok.push_back(Pokemon(exp));
	// dispaying the inventory of the marchant
	//transaction module
	std::string choice;
	while (true)
	{
		do
		{
			ShowStats();
			std::cout << std::endl << color("You've encountered a marchant!", BrightWhite) << std::endl
				<< color("What you can buy from the marchant:", BrightWhite) << std::endl;
			for (int i = 0; i < marchant_pot.size(); i++)
				std::cout << color(std::to_string(i + 1), BrightWhite) << " " 
					<< marchant_pot[i].ShowKind() << " " 
					<< color(std::to_string(marchant_pot[i].ShowPoints()), BrightWhite) << " " 
					<< color(std::to_string(marchant_pot[i].ShowPrice()) + " gold", BrightYellow) << std::endl;
			for (int i = 0; i < marchant_pok.size(); i++)
				std::cout << color(std::to_string(i + marchant_pot.size() + 1) + ". Mystery pokemon ", BrightWhite) 
				<< color(std::to_string(marchant_pok[i].ShowPrice()) + " gold", BrightYellow) << std::endl;
			std::cout << color("What would you like to do?", BrightWhite) << std::endl
				<< color("SP: Sell pokemon   ST: Sell potion   B: Buy   Q: Quit", BrightWhite) << std::endl;
			std::cin >> choice;
			std::cout << clearTerminal;
		} while (choice != "sp" && choice != "SP" && choice != "st" && choice != "ST" 
			&& choice != "b" && choice != "B" && choice != "q" && choice != "Q");
		if (choice == "sp" || choice == "SP") {
			if (pokemons.size() > 1)
				SellPokemon();
			else
				std::cout << color("[!!!] You have only one pokemon!", Red) << std::endl;
		}
		else if (choice == "st" || choice == "ST") {
			if (potions.size() > 0)
				SellPotion();
			else 
				std::cout << color("[!!!] You don't have any potions yet!", Red) << std::endl;
		}
		else if (choice == "b" || choice == "B")
		{
			std::string bought;
			try
			{
				do 
				{
					ShowStats();
					std::cout << color("What you can buy from the marchant:", BrightWhite) << std::endl;
					for (int i = 0; i < marchant_pot.size(); i++)
						std::cout << color(std::to_string(i + 1), BrightWhite) << " "
						<< marchant_pot[i].ShowKind() << " "
						<< color(std::to_string(marchant_pot[i].ShowPoints()), BrightWhite) << " "
						<< color(std::to_string(marchant_pot[i].ShowPrice()) + " gold", BrightYellow) << std::endl;
					for (int i = 0; i < marchant_pok.size(); i++)
						std::cout << color(std::to_string(i + marchant_pot.size() + 1) + ". Mystery pokemon ", BrightWhite)
						<< color(std::to_string(marchant_pok[i].ShowPrice()) + " gold", BrightYellow) << std::endl;
					std::cout << color("Choose item from the marchant to buy or 'Q' to quit.", BrightWhite) << std::endl;
					std::cin >> bought;
					std::cout << clearTerminal;
					if (choice == "q" || choice =="Q" || std::stoi(bought)) break;
					else std::cout << invalidInput << std::endl;
				} while (std::stoi(bought) > marchant_pot.size() + marchant_pok.size() && choice != "q" && choice != "Q");
			}
			catch (const std::exception &e)
			{
				if (choice != "q" && choice != "Q")
					std::cout << std::endl << invalidInput << std::endl;
			}
			if (bought == "q" || bought == "Q") continue;
			else if (std::stoi(bought) > marchant_pot.size())
			{
				Buy(marchant_pok[std::stoi(bought)-marchant_pot.size()-1]);
				marchant_pok.erase(marchant_pok.begin() + std::stoi(bought) - marchant_pot.size()-1);
			}	
			else 
			{
				Buy(marchant_pot[std::stoi(bought)-1]);
				marchant_pot.erase(marchant_pot.begin() + std::stoi(bought) - 1);
			}	
		}
		else if (choice == "q" || choice == "Q")
			break;
	}
	std::cout << color("Thank you for your transactions!", BrightWhite) << std::endl;
}

// method activating game module: healing
void Player::Healing()
{
	if (potions.size() <= 0) {
		std::cout << color("[!!!] You don't have any potions yet!", Red) << std::endl;
		return;
	}
	while (true)
	{
		std::string choice;
		do
		{
			/// displaying the eq
			std::cout << color("Your pokemons : ", BrightWhite) << std::endl;
			for (int i = 0; i < pokemons.size(); i++)
			{
				std::cout << color(std::to_string(i + 1) + ". ", BrightWhite);
				pokemons[i].BattleStats();
			}
			std::cout << std::endl << color("Your potions : ", BrightWhite) << std::endl;
			for (int i = 0; i < potions.size(); i++)
			{
				std::cout << color(std::to_string(i + 1) + ". ", BrightWhite) 
					<< potions[i].ShowKind() 
					<< color(" +" + std::to_string(potions[i].ShowPoints()) + "   ", BrightWhite);
				if (i % 5 == 4) std::cout << std::endl;
			}
			std::cout << std::endl << std::endl << color("What would you like to do?", BrightWhite) << std::endl;
			std::cout << color("P - use potions   Q - quit", BrightWhite) << std::endl;
			std::cin >> choice;
			std::cout << clearTerminal;
		} while (choice != "p" && choice != "P" && choice != "q" && choice != "Q");
		
		if (choice == "p" || choice == "P") // healing/buffing
		{
			int choice_pok, choice_pot;
			try
			{
				do
				{
					std::cout << color("Your pokemons : ", BrightWhite) << std::endl;
					for (int i = 0; i < pokemons.size(); i++)
					{
						std::cout << color(std::to_string(i + 1) + ". ", BrightWhite);
						pokemons[i].BattleStats();
					}
					std::cout << std::endl << color("Choose the pokemon: ", BrightWhite);
					std::cin >> choice_pok;
					std::cout << clearTerminal;
					if (!std::cin.good()) 
					{
						std::cout << invalidInput << std::endl;
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						choice_pok = -1;
					}	
				} while (choice_pok > pokemons.size() || choice_pok <= 0);
			}
			catch (const std::exception &e)
			{
				std::cout << invalidInput << std::endl;
			}
			try
			{
				do
				{
					std::cout << color("Your potions : ", BrightWhite) << std::endl;
					for (int i = 0; i < potions.size(); i++)
					{
						std::cout << color(std::to_string(i + 1) + ". ", BrightWhite)
							<< potions[i].ShowKind()
							<< color(" +" + std::to_string(potions[i].ShowPoints()) + "   ", BrightWhite);
						if (i % 5 == 4) std::cout << std::endl;
					}
					std::cout << std::endl << color("Choose the potion: ", BrightWhite);
					std::cin >> choice_pot;
					std::cout << clearTerminal;
					if (!std::cin.good()) 
					{
						std::cout << invalidInput << std::endl;
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						choice_pot = -1;
					}	
				} while (choice_pot > potions.size() || choice_pot <= 0);
			}
			catch (const std::exception &e)
			{
				std::cout << invalidInput << std::endl;
			}
			pokemons[choice_pok - 1].TakePotion(potions[choice_pot - 1]);
			potions.erase(potions.begin() + choice_pot - 1);
		}
		else if (choice == "q" || choice == "Q") break;
	}
}

// method activating game module: showing already caught pokemons
void Player::ShowCaught()
{
	std::cout << color("You already caught:", BrightWhite) << std::endl;
	int count = 0;
	for (int i = 0; i < 151; i++)
	{
		if (pokeCaught[i]) 
		{
			std::cout << color(pokedex[i].name + ", ", BrightWhite);
			if (++count%8 == 0)
				std::cout << std::endl;
		}
	}	
	std::cout << std::endl << color("You still need to catch ", BrightWhite) 
		<< color(std::to_string(151 - count), Green) << color(" species.", BrightWhite) << std::endl;
}

// method to write the records to the record file
void Player::writeRecords()
{
	std::ofstream file;
	file.open("records.txt", std::ofstream::out | std::ofstream::trunc);

	// writing the name
    file << "name: " << name << std::endl;
	// writing the exp
	file << "exp: " << exp << std::endl;
	// writing the gold
	file << "gold: " << gold << std::endl;
	// writing the potions
	file << "potions: ";
	for (int i = 0; i < potions.size(); i++)
	{
		if (i%8 == 0) std::cout << std::endl;
		file << "{";
		potions[i].ShowKind() == "Buff" ? file << "1," : file << "0,";
		file << potions[i].ShowPoints() << "," << potions[i].ShowPrice() << "}";
		
	}
	// writing the pokemons
	file << std::endl << "pokemons: " << std::endl;
	for (int i = 0; i < pokemons.size(); i++)
	{
		file << "{" << pokemons[i].index << "," << pokemons[i].cp << "," << pokemons[i].hp <<
    		"," << pokemons[i].hp_left << "," << pokemons[i].pp << "," << pokemons[i].exp << ",";
		for (int j = 0; j < pokemons[i].ability.size(); j++)
		{
			if (j != 0) file << ";";
			file << int(pokemons[i].ability[j]);
		}
		file << ",";
		pokemons[i].shield ? file << "1}" : file << "0}";
		file << std::endl;
	}
	// writing the pocecaughts
	file << "pokecaught: " << std::endl;
	for (int i = 0; i < 151; i++)
	{
		pokeCaught[i] ? file << "1" : file << "0";
	}
	file << std::endl;
    // Close the file
    file.close();
    std::cout << color("Your records were saved successfully.", BrightWhite) << std::endl;

}
