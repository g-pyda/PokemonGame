
#include "constants.h"
#include "functions.h"
#include <string>
#include "Player.h"

// default constructor of the player
Player::Player()
{
	cout << "------> Insert your nickname: " << endl;
	cin >> name;
	// starting values for new player
	exp = 100;
	gold = 100;
	for (int i = 0; i < 151; i++) pokeCaught[i] = false;
	// creating a start pokemon
	Pokemon first(exp);
	int choice;

	while (true)
	{
		cout << "------> Choose your start pokemon: " << endl;
		cout << "1. Bulbasaur" << endl << "2. Squirtle" << endl << "3. Charmander" << endl;
		cin >> choice;
		printf("\033c");
		if (!cin.good()) {
			cout << "[!!!] Invalid input, try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
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
Player::Player(string n, int e, int g, vector <Potion> pt, vector <Pokemon> pk, vector <bool> pc)
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
	string choice;
	while (true)
	{
		try
		{
			// display all potions/pokemons in the inventory
	
			cout << "------> Choose the pokemon to sell od 'Q' to quit:" << endl;
			for (int i = 0; i < pokemons.size(); i++)
			{
				cout << i+1 << ". ";
				pokemons[i].BattleStats();
				cout << pokemons[i].ShowPrice()*0.8 << endl;
			}	
			cin >> choice;
			printf("\033c");

			// deleting the pokemon and adding coins

			if (choice == "q") break;
			else if (std::stoi(choice) > pokemons.size() && choice != "q")
			{
				cout << "[!!!] Invalid input, try again." << endl;
				choice.clear();	
				continue;
			}
			
			gold += pokemons[std::stoi(choice)].ShowPrice()*0.8;
			pokemons.erase(pokemons.begin()+std::stoi(choice)-1);
			break;
		}
		catch(const exception& e)
		{
			cout << "[!!!] Invalid input, try again." << endl;
			choice.clear();
		}
		
	}
	
				
	
}

void Player::SellPotion()
{
	
	string choice;
	while (true)
	{
		try
		{
			// display all potions/pokemons in the inventory
			cout << "------> Choose the potion to sell or 'Q' to quit:" << endl;
			for (int i = 0; i < potions.size(); i++)
			{
				cout << i+1 << "." << potions[i].ShowKind() << " " << potions[i].ShowPoints() 
				<< " " << potions[i].ShowPrice()*0.8 << endl;
			}
			cin >> choice;
			printf("\033c");
			if (choice == "q") break;
			else if (std::stoi(choice) > potions.size() && choice != "q")
			{
			cout << "[!!!]Invalid input, try again." << endl;
			choice.clear();
			continue;
			}
			// deleting the potion and adding coins
			gold += potions[std::stoi(choice)].ShowPrice()*0.8;
			potions.erase(potions.begin()+std::stoi(choice)-1);
			break;
		}
		catch(const exception& e)
		{
			cout << "[!!!]Invalid input, try again." << endl;
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
		cout << "------> You don't have enough money to buy this potion." << endl;
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
		cout << "------> You don't have enough money to buy this pokemon." << endl;
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

string Player::ShowName() const
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
	cout << endl << "| " << name << " | EXP: " << exp << " | GOLD: " << gold << " | EQ: " <<
		" pokemons - " << ShowPokemonNR() << " potions - " << ShowPotionNR() << " | " <<
		HMCaught() << " species caught |" << endl;
}

// method to display all the pokemons in the inventory
void Player::ShowPokemons()
{
	for (int i = 0; i < pokemons.size(); i++)
	{
		cout << i+1 << ". ";
		pokemons[i].BattleStats();
	}
}
        
// method to display all the potions in the inventory
void Player::ShowPotions()
{
	for (int i = 0; i < potions.size(); i++)
	{
		cout << potions[i].ShowKind() << " " << potions[i].ShowPoints() 
		<< "points " << potions[i].ShowPrice() << "coins" << endl;  
	}
}

// method activating game module: fighting with wild pokemon
void Player::WildBattle()
{
	// spawning the random pokemon
	Pokemon opponent(exp);
	// decision if to take up a battle
	cout << "------> You have encountered a wild pokemon!" << endl;
	opponent.BattleStats();
	cout << endl << "Your pokemons:" << endl;
	ShowPokemons();

	string choice;
	while (true)
	{
		cout << endl << "------> Do you want to fight?" << endl;
		cout << "Y - yes   N - no" << endl;
		cin >> choice;
		printf("\033c");
		if (choice == "y" || choice == "n") break;
		else cout << "[!!!] Invalid input, try again." << endl;
	}
			
	if(choice == "y")
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
		cout << "------> Choose the pokemon to fight." << endl;
		ShowPokemons();
		cin >> choice_p;
		printf("\033c");
		if (!cin.good()) {
			cout << "[!!!] Invalid input, try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if (choice_p <= pokemons.size()) break;
		else cout << "[!!!] Invalid input, try again." << endl;
	}
				
	Pokemon* fighter = &pokemons[choice_p - 1];
	cout << "------> You chose " << pokedex[fighter->index - 1].name << ". Let's fight!" << endl << endl;
	// loop of every round
	while (true)
	{	
		// choice of the attack of the player 
		cout << "   Your pokemon: ";
		fighter->BattleStats();
		cout << "   Wild pokemon: ";
		opponent.BattleStats();
		int choice_t;
		while (true)
		{
			cout << endl << "------> Choose type of the attack." << endl;
			for (int i = 0; i < pokedex[fighter->index - 1].type.size(); i++)
				cout << i + 1 << ". " << types_s[pokedex[fighter->index - 1].type[i]] << " attack." << endl;
			
			cin >> choice_t;
			printf("\033c");
			if (!cin.good()) {
				cout << "[!!!] Invalid input, try again." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			if (choice_t <= pokedex[fighter->index - 1].type.size()) break;
			else cout << "[!!!] Invalid input, try again." << endl;
		}
		effect = pokedex[fighter->index - 1].type[choice_t-1];
		// attack of the player
		cout << "   Your pokemon: ";
		fighter->BattleStats();
		cout << "   Wild pokemon: ";
		opponent.BattleStats();
		Attack(fighter, &opponent, effect);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		sleep(3);
		printf("\033c");
		// checking if the wild pokemon still can fight
		if (opponent.hp_left > opponent.hp || opponent.hp_left == 0)
		{
			// wild pokemon cannot fight back
			opponent.hp_left = 1;
			outcome = win;
			cout << "   Your pokemon: ";
			fighter->BattleStats();
			cout << "   Wild pokemon: ";
			opponent.BattleStats();
			cout << endl << "------> Wild pokemon cannot fight back!" << endl;
			
			while (true)
			{
				cout << "C - catch the pokemon" << endl << "K - kill the pokemon" << endl;
				cin >> choice;
				printf("\033c");
				if (choice == "c" || choice == "k") break;
				else cout << "[!!!] Invalid input, try again." << endl;
			}
			if (choice == "c") outcome = catching;
			else if (choice == "k") outcome = kill;
			break;
		} 
		cout << "   Your pokemon: ";
		fighter->BattleStats();
		cout << "   Wild pokemon: ";
		opponent.BattleStats();
		cout << endl << endl << "------> Watch out! The wild pokemon is attacking!" << endl;
		// wild pokemon strikes back
		effect = pokedex[opponent.index - 1].type[rand()%(pokedex[opponent.index - 1].type.size())];
		Attack(&opponent, fighter, effect);
		sleep(3);
		printf("\033c");
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		// checking if the player pokemon lost
		if (fighter->hp_left > fighter->hp || fighter->hp_left == 0)
		{
			// player lost
			outcome = failure;
			fighter->hp_left = 0;
			cout << "   Your pokemon: ";
			fighter->BattleStats();
			cout << "   Wild pokemon: ";
			opponent.BattleStats();
			cout << endl << endl << "------> Oh no. Your pokemon got killed!" << endl;
			
			pokemons.erase(pokemons.begin() + choice_p - 1);
			if (pokemons.size() <= 0) return;
			while (true)
			{
				cout << "C - choose another pokemon" << endl << "R - run away" << endl;
				cin >> choice;
				printf("\033c");
				if (choice == "c" || choice == "r") break;
				else cout << "[!!!] Invalid input, try again." << endl;
			}
			
			if (choice == "c")
			{
				while (true)
				{
					cout << "------> Choose the pokemon to fight." << endl;
					ShowPokemons();
					cin >> choice_p;
					printf("\033c");
					if (!cin.good()) {
						cout << "[!!!] Invalid input, try again." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						continue;
					}
					if (choice_p <= pokemons.size()) break;
					else cout << "[!!!] Invalid input, try again." << endl;
				}		
				Pokemon* fighter = &pokemons[choice_p - 1];
				cout << "------> You chose " << pokedex[fighter->index - 1].name << ". Let's fight!" << endl << endl;
			}
			else if (choice == "r")
			{
				outcome = runaway;
				break;
			}
		}
	}
	// action regarding to the outcome of the battle
	printf("\033c");
	switch (outcome)
	{
		case kill:
			cout << endl << "------> You killed the wild pokemon!" << endl;
			cout << "------> You receive 150 exp, your pokemon receives 50 exp and +50 CP." << endl;
			exp += 150;
			fighter->exp += 50;
			fighter->cp += 50;
			fighter->hp_left += 3;
			fighter->Evolve();
			break;
		case catching:
			for (int i = 0; i < 4; i++) // there are only 3 tries of catching
			{
				cout << endl << "------> You're trying to catch the " << pokedex[opponent.index - 1].name << endl;
				cout << "T - throw a pokeball" << endl;
				do
				{
					cin >> choice;
					printf("\033c");
				} while (choice != "t");
				// pokemon wasn't caught - it can escape now
				if (choice == "t" && rand()%100 - 10*i*i*i > exp*50/(0.5*opponent.cp + 100*opponent.pp + 10*opponent.hp_left))
				{
					cout << endl << "------> The pokemon escaped from the pokeball!" << endl << endl;
					// pokemon may escape
					if (rand()%100 < 80 * opponent.hp_left / opponent.hp)
					{
						cout << "------> Oh no, the pokemon run away from you! Better luck next time!" << endl;
						cout << "------> You receive 50 exp, your pokemon receives 100 exp and 50 CP." << endl;
						exp += 50;
						fighter->exp += 100; 
						fighter->cp += 50;
						fighter->hp_left += 3;
						fighter->Evolve();
						break;
					}
				}
				else if (choice == "t")// pokemon got caught
				{
					printf("\033c");
					cout << "------> Congratulations! You caught the " << pokedex[opponent.index - 1].name << endl;
					cout << "------> You receive 50 exp, your pokemon receives 100 exp and 50 CP." << endl;
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
					printf("\033c");
					cout << "------> Oh no, the pokemon run away! Better luck next time!" << endl;
					cout << "------> You receive 50 exp, your pokemon receives 100 exp and 50 CP." << endl;
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
			cout << "------> You receive 1 exp for trying. Better luck next time!" << endl;
			exp += 1;
			break;
	}
	}
}

// method activating game module: fighting with a coach
void Player::CoachBattle()
{
	// spawning the random pokemon
	Pokemon opponent(exp);
	// decision if to take up a battle
	printf("\033c");
	cout << "------> You have encountered a pokemon coach and they want to fight with you!" << endl << "------> Their pokemon: ";
	opponent.BattleStats();
	cout << endl << "Your pokemons:" << endl;
	ShowPokemons();

	string choice;
	while (true)
	{
		cout << endl << "------> Do you want to fight?" << endl;
		cout << "Y - yes   N - no" << endl;
		cin >> choice;
		printf("\033c");
		if (choice == "y" || choice == "n") break;
		else cout << "[!!!]Invalid input, try again." << endl;
	}
				
	if(choice == "y")
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
		cout << "------> Choose the pokemon to fight." << endl;
		ShowPokemons();
		cin >> choice_p;
		printf("\033c");
		if (!cin.good()) {
			cout << "[!!!]Invalid input, try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if (choice_p <= pokemons.size()) break;
		else cout << "[!!!]Invalid input, try again." << endl;
	}
				
	Pokemon* fighter = &pokemons[choice_p - 1];
	// loop for every round
	while (true)
	{
		// choice of the attack of the player 
		cout << endl << "   Your pokemon: ";
		fighter->BattleStats();
		cout << endl << "   Coached pokemon: ";
		opponent.BattleStats();
		int choice_t;
		while (true)
		{
			cout << endl << "------> Choose type of the attack." << endl;
			for (int i = 0; i < pokedex[fighter->index - 1].type.size(); i++)
				cout << i + 1 << ". " << types_s[pokedex[fighter->index - 1].type[i]] << " attack." << endl;
			cin >> choice_t;
			printf("\033c");
			if (!cin.good()) {
				cout << "[!!!] Invalid input, try again." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			if (choice_t <= pokedex[fighter->index - 1].type.size()) break;
			else cout << "[!!!] Invalid input, try again." << endl;
		}
		effect = pokedex[fighter->index - 1].type[choice_t-1];
		// attack of the player
		cout << endl << "   Your pokemon: ";
		fighter->BattleStats();
		cout << endl << "   Coached pokemon: ";
		opponent.BattleStats();
		Attack(fighter, &opponent, effect);
		sleep(3);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		printf("\033c");
		// coached pokemon got defeated
		if (opponent.hp_left > opponent.hp || opponent.hp_left == 0)
		{
			// wild pokemon cannot fight back
			opponent.hp_left = 1;
			outcome = win;
			cout << "   Your pokemon: ";
			fighter->BattleStats();
			cout << "   Coached pokemon: ";
			opponent.BattleStats();
			cout << endl << "------> Coached pokemon cannot fight back!" << endl;
			cout << "------> You receive 100 exp and 50 gold, your pokemon receives 50 exp and 20 cp." << endl;
			exp += 100;
			gold += 50;
			fighter->cp += 20;
			fighter->exp += 50;
			fighter->hp_left += 3;
			fighter->Evolve();
			break;
		} 
		cout << endl << "   Your pokemon: ";
		fighter->BattleStats();
		cout << endl << "   Coached pokemon: ";
		opponent.BattleStats();
		// the coached pokemon strikes back
		effect = pokedex[opponent.index - 1].type[rand()%(pokedex[opponent.index - 1].type.size())];
		Attack(&opponent, fighter, effect);
		sleep(3);
		special_attack = abilities(7);
		special_attack2 = abilities(7);
		
		printf("\033c");
		// pokemon got defeated
		if (fighter->hp_left > fighter->hp || fighter->hp_left == 0)
		{
			fighter->hp_left = 1;
			outcome = failure;
			cout << "   Your pokemon: ";
			fighter->BattleStats();
			cout << "   Coached pokemon: ";
			opponent.BattleStats();
			cout << endl << "------> Oh no! Your pokemon got defeated!" << endl;
			cout << "You receive 1 exp, your pokemon receives 5 exp and 1 CP." << endl;
			exp += 1;
			fighter->cp += 1;
			fighter->exp += 5;
			fighter->Evolve();
			break;
		}
	}
}
}

// method activating game module: finding a treasure
void Player::Treasure()
{
	printf("\033c");
	// there are different chances of encountering some treasures
	int lot = rand()%100;
	if (lot < 5)
	{
		cout << "------> You found a pokemon in the cage! Poor thing!" << endl;
		Pokemon found(exp);
		pokemons.push_back(found);
		pokeCaught[found.index-1] = true;
	}
	else if (lot < 30)
	{
		cout << "------> You found a chest with some stuff!" << endl;
		int amount = rand()%3 + 1;
		for (int i = 0; i < amount/2; i++)
		{
			Potion pot;
			cout << "Found " << pot.ShowKind() << " " << pot.ShowPoints() << endl;
			potions.push_back(pot);
		}
		if (lot < 50)
		{
			unsigned int c = rand()%21 * 10;
			cout << "Found " << c << "gold" << endl;
			gold += c;
		}
	}
	else
	{
		cout << "------> You encountered some experienced trainer who teached you some helpful techniques!" << endl;
		cout << "------> You receive 100 exp.";
		exp += 100;
	}
	
}

// method activating game module: encountering a marchant
void Player::Marchant()
{
	printf("\033c");
	cout << "------> You've encountered a marchant!" << endl;
	// generating the set of items and pokemons (inventory of the marchant)
	vector <Potion> marchant_pot;
	for (int i = 0; i < 6; i++)
		marchant_pot.push_back(Potion());
	int lot = rand()%3;
	vector <Pokemon> marchant_pok;
	for (int i = 0; i < lot; i++)
		marchant_pok.push_back(Pokemon(exp));
	// dispaying the inventory of the marchant
	//transaction module
	string choice;
	while (true)
	{
		cout << "----> What you can buy from the marchant:" << endl;
		for (int i = 0; i < marchant_pot.size(); i++)
			cout << i+1 << " " << marchant_pot[i].ShowKind() << " " << marchant_pot[i].ShowPoints() << " " << marchant_pot[i].ShowPrice() << " gold" << endl;
		for (int i = 0; i < marchant_pok.size(); i++)
			cout << i+marchant_pot.size()+1 << ". Mystery pokemon " << marchant_pok[i].ShowPrice() << " gold" << endl;
		do
		{
			cout << "----> What would you like to do?" << endl;
			cout << "SP - Sell pokemon   ST - Sell potion   B - Buy   Q - Quit" << endl;
			cin >> choice;
			printf("\033c");
		} while (choice != "sp" && choice != "st" && choice != "b" && choice != "q");
		if (choice == "sp") {
			if (pokemons.size() > 1)
				SellPokemon();
			else
				cout << endl << "[!!!] You have only one pokemon!" << endl;
		}
		else if (choice == "st") {
			if (potions.size() > 0)
				SellPotion();
			else 
				cout << endl << "[!!!] You don't have any potions yet!" << endl;
		}
		else if (choice == "b")
		{
			string bought;
			try
			{
				do 
				{
					cout << "------> Choose item from the marchant to buy or 'Q' to quit." << endl;;
					cin >> bought;
					printf("\033c");
					if (choice == "q" || std::stoi(bought)) break;
					else cout << "[!!!] Invalid input, try again." << endl;
				} while (std::stoi(bought) > marchant_pot.size() + marchant_pok.size()&& choice != "q");
			}
			catch (const exception &e)
			{
				if (choice != "q")
					cout << endl << "[!!!] Invalid input, try again." << endl;
			}
			if (bought == "q") continue;
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
		else if (choice == "q")
			break;
	}
	cout << "----> Thank you for your transactions!" << endl;
}

// method activating game module: healing
void Player::Healing()
{
	if (potions.size() <= 0) {
		cout << endl << "[!!!] You don't have any potions yet!" << endl;
		return;
	}
	cout << endl << "------> Your pokemons : " << endl;
	for (int i = 0; i < pokemons.size(); i++)
	{
		cout << i+1 << ". ";
		pokemons[i].BattleStats();
	}
	cout << endl << "------> Your potions : " << endl;
	for (int i = 0; i < potions.size(); i++)
	{
		cout << i+1 << ". " << potions[i].ShowKind() << " +" << potions[i].ShowPoints() << "  ";
		if (i%5 == 4) cout << endl;
	}
	while (true)
	{
		string choice;
		do
		{
			/// displaying the eq
			cout << "What would you like to do?" << endl;
			cout << "P - use potions   Q - quit" << endl;
			cin >> choice;
			printf("\033c");
		} while (choice != "p" && choice != "q");
		
		if (choice == "p") // healing/buffing
		{
			int choice_pok, choice_pot;
			try
			{
				do
				{
					cout << "------> Choose the pokemon: ";
					cin >> choice_pok;
					printf("\033c");
					if (!cin.good()) 
					{
						cout << "[!!!] Invalid input, try again." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						choice_pok = -1;
					}	
				} while (choice_pok > pokemons.size() || choice_pok <= 0);
			}
			catch (const exception &e)
			{
				cout << "[!!!] Invalid input, try again." << endl;
			}
			try
			{
				do
				{
					cout << "Choose the potion: ";
					cin >> choice_pot;
					printf("\033c");
					if (!cin.good()) 
					{
						cout << "[!!!] Invalid input, try again." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						choice_pot = -1;
					}	
				} while (choice_pot > potions.size() || choice_pot <= 0);
			}
			catch (const exception &e)
			{
				cout << "[!!!] Invalid input, try again." << endl;
			}
			pokemons[choice_pok - 1].TakePotion(potions[choice_pot - 1]);
			potions.erase(potions.begin() + choice_pot - 1);
			// displaying the eq again
			cout << endl << "------> Your pokemons : " << endl;
			for (int i = 0; i < pokemons.size(); i++)
			{
				cout << i+1 << ". ";
				pokemons[i].BattleStats();
			}
			cout << endl << "------> Your potions : " << endl;
			for (int i = 0; i < potions.size(); i++)
			{
				cout << i+1 << ". " << potions[i].ShowKind() << " +" << potions[i].ShowPoints() << "  ";
				if (i%5 == 4) cout << endl;
			}
		}
		else if (choice == "q") break;
	}
}

// method activating game module: showing already caught pokemons
void Player::ShowCaught()
{
	cout << "------> You already caught:" << endl;
	int count = 0;
	for (int i = 0; i < 151; i++)
	{
		if (pokeCaught[i]) 
		{
			cout << pokedex[i].name << ", ";
			if (++count%8 == 0)
				cout << endl;
		}
	}	
	cout << endl << "------> You still need to catch " << 151 - count << " species." << endl;
}

// method to write the records to the record file
void Player::writeRecords()
{
	ofstream file;
	file.open("records.txt", ofstream::out | ofstream::trunc);

	// writing the name
    file << "name: " << name << endl;
	// writing the exp
	file << "exp: " << exp << endl;
	// writing the gold
	file << "gold: " << gold << endl;
	// writing the potions
	file << "potions: ";
	for (int i = 0; i < potions.size(); i++)
	{
		if (i%8 == 0) cout << endl;
		file << "{";
		potions[i].ShowKind() == "Buff" ? file << "1," : file << "0,";
		file << potions[i].ShowPoints() << "," << potions[i].ShowPrice() << "}";
		
	}
	// writing the pokemons
	file << endl << "pokemons: " << endl;
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
		file << endl;
	}
	// writing the pocecaughts
	file << "pokecaught: " << endl;
	for (int i = 0; i < 151; i++)
	{
		pokeCaught[i] ? file << "1" : file << "0";
	}
	file << endl;
    // Close the file
    file.close();
    cout << "------> Your records are saved successfully." << endl;

}
