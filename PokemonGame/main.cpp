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
	cout << displayBar() << endl
		<< "\t\t\tWelcome to the Pokemon Game!" << endl << endl;
	do
	{
		cout << "\tChoose option:" << endl
			<< "\t   0: New Game" << endl
			<< "\t   1: Resume Game" << endl
			<< "\t   2: Quit" << endl;

		cin >> choice;
		cout << clearTerminal;
		if (!cin.good()) {
			cout << colorCodes[Red][0] << invalidInput << colorEnd << endl << endl;
			cin.clear();
			cin.ignore(1000, '\n');
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
		vector <string> recordLines;
		try
		{
			recordLines = readRecords();
		}
		catch (const exception& e)
		{
			cout << colorCodes[Yellow][0] << "\t\tThe file with records doesn't exist." << colorEnd << endl << endl;
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
			string name = getName(recordLines[0]);
			int exp = getExp(recordLines[1]);
			int gold = getGold(recordLines[2]);
			vector <string> temp;
			int i = 3;
			for (;; i++)
			{
				if (recordLines[i].find("pokemons:") != std::string::npos)
					break;
				temp.push_back(recordLines[i]);
			}
			i--;
			vector <Potion> potions = getPotions(temp);
			temp.clear();
			for (i++; i < recordLines.size() - 2; i++)
			{
				temp.push_back(recordLines[i]);
			}
			vector <Pokemon> pokemons = getPokemons(temp);
			vector <bool> pokeCaught = getPCaught(recordLines[recordLines.size() - 1]);
			player = new Player(name, exp, gold, potions, pokemons, pokeCaught);
			break;
		}
		else cout << endl << "\t\tThe records weren't read so you have to start a new game." << endl;
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
	cout << clearTerminal;
	cout << "\t\tHello, " << colorCodes[BrightBlue][0] << player->ShowName() << colorEnd << endl << "\t\tLET'S CATCH THEM ALL" << endl;
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
			player->ShowStats();
			do
			{
				cout << endl << "\t\tWhat action would you like to make?" << endl << endl
					<< colorCodes[BrightGreen][0] << "1: continue the journey!" << endl
					<< colorCodes[BrightCyan][0] << "2: use your potions on pokemons." << endl
					<< colorCodes[Blue][0] << "3: save your statistics." << endl
					<< colorCodes[Magenta][0] << "4: see, which pokemon species you've already caught" << endl
					<< colorCodes[BrightBlack][0] << "0: exit the game. WARNING! This action doesn't save your progress!" << colorEnd << endl;
				cin >> choice;
				cout << clearTerminal;
				if (!cin.good()) {
					cout << invalidInput << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					choice = -1;
				}
			} while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4);
			switch (choice)
			{
			case 0: // exit from the game
				cout << colorCodes[BrightCyan][0] << "\t\tThank you for playing!" << colorEnd << endl;
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
					cout << colorCodes[Yellow][0] << "\t\tUnfortunately you lost all of your pokemons! Better luck next time!" << colorEnd << endl << endl
						<< "\tWhat action would you like to make?" << endl
						<< "\t   1 - delete your current save to start over." << endl
						<< "\t   2 - exit the game without saving." << endl;
					cin >> choice;
					cout << clearTerminal;
					if (!cin.good()) {
						cout << invalidInput << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						choice = -1;
					}
				} while (choice != 1 && choice != 2);
				switch (choice) {
				case 1:
					remove("records.txt");
				case 2:
					cout << colorCodes[BrightCyan][0] << "\t\tThank you for playing!" << colorEnd << endl;
					delete player;
					return 0;
				}
			}
		}
		else if (event < 8) player->CoachBattle(); // battle with the coach
		else if (event < 13) player->Treasure(); // treasure found
		else player->Marchant(); // marchant found		
	}
	delete player;
	cout << colorCodes[BrightCyan][0] << "\t\tCongratulations! You caught them all!" << colorEnd << endl;
	return 0;
}