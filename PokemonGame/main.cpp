// command to compile:
// g++ main.cpp Pokemon.cpp Player.cpp Potion.cpp functions.cpp
#include "constants.h"
#include "classes.h"
#include "functions.h"

int main(int argc, char ** argv)
{
	// dispaying the information about the game and options
	int choice;
	cout << "------> Welcome to the Pokemon Game!" << endl << "Choose option:" << endl;
	do
	{
		cout << "0: New Game" << endl;
		cout << "1: Resume Game" << endl;
		cout << "2: Quit" << endl;
		cin >> choice;
		if (!cin.good()) {
			cout << "[!!!]Invalid input, try again." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			choice = -1;
		}
	} while(choice != 0 && choice != 1 && choice != 2);
	
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
	catch (const exception &e)
	{
		cout << endl << "----> The file with records doesn't exist." << endl;
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
	int i = 4;
	for (;;i++)
	{
		if (recordLines[i].find("pokemons:") != std::string::npos) 
			break;
		temp.push_back(recordLines[i]);
	}
	vector <Potion> potions = getPotions(temp);
	temp.clear();
	for (i++;i < recordLines.size() - 2;i++)
	{
		temp.push_back(recordLines[i]);
	}
	vector <Pokemon> pokemons = getPokemons(temp);
	vector <bool> pokeCaught = getPCaught(recordLines[recordLines.size()-1]);
	player = new Player(name, exp, gold, potions, pokemons, pokeCaught);
	break;
	}
	else cout << endl << "----> The records weren't read so you have to start a new game." << endl;
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
	cout << "------> Hello, " << player->ShowName() << endl << "------> LET'S CATCH THEM ALL" << endl;
	// lottery of events
	int event = 16;
	while (!player->CaughtAll())
	{
		if (event == 16) event = rand()%16; // the first iteration of the while loop
		else if (choice == 1 || event != 16)// not the first iteration
		{
			player->ShowStats();
			do
			{
				cout << endl << "------> What action would you like to make?" << endl;
				cout << "1 - continue the journey!" << endl;
				cout << "2 - use your potions on pokemons." << endl;
				cout << "3 - save your statistics." << endl;
				cout << "4 - see, which pokemon species you've already caught" << endl;
				cout << "0 - exit the game. WARNING! This action doesn't save your progress!" << endl;
				cin >> choice;
				if (!cin.good()) {
					cout << "[!!!]Invalid input, try again." << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					choice = -1;
				}
			} while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4);
			switch (choice)
			{
				case 0: // exit from the game
					cout << "------> Thank you for playing!";
					delete player;
					return 0;
				case 1: // generation of the next event
					event = rand()%16;
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
		if (event < 6) player->WildBattle(); // battle with wild pokemon
		else if (event < 8) player->CoachBattle(); // battle with the coach
		else if (event < 13) player->Treasure(); // treasure found
		else player->Marchant(); // marchant found		
	}
	delete player;
	cout << "------> Congratulations! You caught them all!" << endl;
	return 0;
}