// command to compile:
// g++ main.cpp Pokemon.cpp Player.cpp Potion.cpp functions.cpp
#include "constants.h"
#include "Player.h"
#include "Pokemon.h"
#include "Potion.h"
#include "functions.h"
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
	// dispaying the information about the game and options
	int choice;
	std::cout << color("Welcome to the Pokemon Game!", BrightWhite) << std::endl << std::endl;
	do
	{
		std::cout << color("Choose option:", BrightWhite) << std::endl
			<< color("0: New Game", BrightWhite) << std::endl
			<< color("1: Resume Game", BrightWhite) << std::endl
			<< color("2: Quit", BrightWhite) << std::endl;

		std::cin >> choice;
		std::cout << clearTerminal;
		if (!std::cin.good()) {
			std::cout << invalidInput << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			choice = -1;
		}
	} while (choice != 0 && choice != 1 && choice != 2);

	Player* player = nullptr;
	switch (choice)
	{
	case 1:
	{
		// player chosen from the records
		// reading the data of the player from the file
		bool success = true;
		std::vector <std::string> recordLines;
		try
		{
			recordLines = readRecords();
		}
		catch (const std::exception& e)
		{
			std::cout << color("The file with records doesn't exist.", Yellow) << std::endl << std::endl;
			success = false;
		}
		if (recordLines.empty()) success = false;
		else
		{
			success = false;
			for (int i = 0; i < recordLines.size(); i++)
				if (recordLines[i] != "") success = true;
		}
		if (success)
		{
			std::string name = getName(recordLines[0]);
			int exp = getExp(recordLines[1]);
			int gold = getGold(recordLines[2]);
			std::vector <std::string> temp;
			int i = 3;
			for (;; i++)
			{
				if (recordLines[i].find("pokemons:") != std::string::npos)
					break;
				temp.push_back(recordLines[i]);
			}
			i--;
			std::vector <Potion> potions = getPotions(temp);
			temp.clear();
			for (i++; i < recordLines.size() - 2; i++)
			{
				temp.push_back(recordLines[i]);
			}
			std::vector <Pokemon> pokemons = getPokemons(temp);
			std::vector <bool> pokeCaught = getPCaught(recordLines[recordLines.size() - 1]);
			player = new Player(name, exp, gold, potions, pokemons, pokeCaught);
			break;
		}
		else std::cout << std::endl << color("The records weren't read so you have to start a new game.",Yellow) << std::endl;
	}
	case 0:
		// new player created
		// initialization of the player
		player = new Player();
		break;
	case 2:
		return 0;
	}
	// main game module
	std::cout << clearTerminal;
	std::cout << color("Hello, ", BrightWhite) << color(player->ShowName(), BrightBlue) << std::endl << color("LET'S CATCH THEM ALL", BrightWhite) << std::endl;
	sleep(1);
	// lottery of events
	int event = 16;
	while (!player->CaughtAll())
	{
		if (event == 16) { // the first iteration of the while loop
			srand(time(NULL));
			event = rand() % 16;
			continue;
		}
		else if (choice == 1 || event != 16)// not the first iteration
		{
			do
			{
				std::cout << clearTerminal;
				player->ShowStats();
				std::cout << std::endl << color("What action would you like to make?", BrightWhite) << std::endl << std::endl
					<< color("1: continue the journey!", BrightGreen) << std::endl
					<< color("2: use your potions on pokemons.", BrightMagenta) << std::endl
					<< color("3: save your statistics.", Blue) << std::endl
					<< color("4: see, which pokemon species you've already caught", Green) << std::endl
					<< color("0: exit the game. WARNING! This action doesn't save your progress!", White) << std::endl;
				std::cin >> choice;
				std::cout << clearTerminal;
				if (!std::cin.good()) {
					std::cout << invalidInput << std::endl;
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					choice = -1;
				}
			} while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4);
			switch (choice)
			{
			case 0: // exit from the game
				std::cout << color("Thank you for playing!",Yellow) << std::endl;
				delete player;
				return 0;
			case 1: // generation of the next event
				event = rand() % 16;
				break;
			case 2: // healing/buffing
				player->Healing();
				break;
			case 3: // saving the records
				player->writeRecords();
				break;
			case 4: // showing already caught pokemons
				player->ShowCaught();
				break;
			}
			if (choice == 2 || choice == 3 || choice == 4) continue;
		}
		if (event < 6) {	// battle with wild pokemon
			player->WildBattle();
			if (player->ShowPokemonNR() <= 0) {
				do {
					std::cout << color("Unfortunately you lost all of your pokemons! Better luck next time!", Yellow) << std::endl << std::endl;
					sleep(3);
					std::cout << color("What action would you like to make?", BrightWhite) << std::endl
						<< color("1: delete your current save to start over.", BrightWhite) << std::endl
						<< color("2: exit the game without saving.", BrightWhite) << std::endl;
					std::cin >> choice;
					std::cout << clearTerminal;
					if (!std::cin.good()) {
						std::cout << invalidInput << std::endl;
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						choice = -1;
					}
				} while (choice != 1 && choice != 2);
				switch (choice) {
				case 1:
					remove("records.txt");
				case 2:
					std::cout << color("Thank you for playing!", Yellow) << std::endl;
					delete player;
					return 0;
				}
			}
		}
		else if (event < 8) player->CoachBattle(); // battle with the coach
		else if (event < 13) player->Treasure(); // treasure found
		else player->Marchant(); // merchant found		
	}
	delete player;
	std::cout << color("Congratulations! You caught them all!", BrightGreen) << std::endl;
	sleep(3);
	return 0;
}