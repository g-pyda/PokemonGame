

#include "constants.h"
#include <string>
#include "Pokemon.h"
#include "Potion.h"

// method to evolve the pokemon
void Pokemon::Evolve()
{
    if (exp >= 500)
    {
        cout << endl << "------> Amazing! Your " << pokedex[index + 1].name << "is evolving!";
        pokeindex evolution = Null;
	    if (index == Eevee)
        {
            int l = rand()%3;
            if (l == 0) evolution = Vaporeon;
            else if (l == 1) evolution == Flareon;
            else evolution == Jolteon;
        }
        else evolution == pokedex[index-1].evolution;
        if (evolution != Null)
        {
            exp = 0;
            // calculation of the new CP
            int max = maxCP[pokedex[index-1].role][pokedex[index-1].stages];
            int min = minCP[pokedex[index-1].role][pokedex[index-1].stages];
            double ratio = cp/((max - min) + 1);
            int newMax = maxCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            int newMin = minCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            cp = (newMax - newMin)*ratio + newMin;

            // calculation of the new HP
            max = maxHP[pokedex[index-1].role][pokedex[index-1].stages];
            min = minHP[pokedex[index-1].role][pokedex[index-1].stages];
            ratio = cp/((max - min) + 1);
            newMax = maxCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            newMin = minCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            hp = (newMax - newMin)*ratio + newMin;
            hp_left = hp;

            // calculation of the new PP
            max = maxPP[pokedex[index-1].role][pokedex[index-1].stages];
            min = minPP[pokedex[index-1].role][pokedex[index-1].stages];
            ratio = cp/((max - min) + 1);
            newMax = maxCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            newMin = minCP[pokedex[evolution-1].role][pokedex[evolution-1].stages];
            pp = (newMax - newMin)*ratio + newMin;

            // update of the index and adding the new ability
            index = evolution;
            cout << "It evolved into " << pokedex[index + 1].name;
            int lot = rand()%100;
            if (lot < 70)
            {
                int ab = rand()%6;
                // if the extra ability was already given in the first evolution, it can't be repeated
                while (!(ability.empty()) && ability[0] == abilities(ab))
                    ab = rand()%6;
                ability.push_back(abilities(ab));
                cout << " and gained an ability";
            }
            cout << "." << endl;
        }
    }
}

// default constructor (used while spawning coached/wild/marchant/hostile pokemon)
Pokemon::Pokemon(unsigned int pl_exp)
{
    srand(time(NULL));
	int lot = rand() % 151;
    while (true)
    {
        // 150 and 151 are legendary/mythical pokemons - very rare
        if ((lot == 149 || lot == 150) && rand()%100 < 10) 
            break;
        // pokemons of the base stage of evolution - 100% chance of appearance
        else if (pokedex[lot].stages == 0 || pokedex[lot].stages == 3 || pokedex[lot].stages == 5)
            break;
        // pokemons of futher evolutions - varying chances
        else if (pokedex[lot].stages == 1 && rand()%100 < 50)
            break;
        else if (pokedex[lot].stages == 2 && rand()%100 < 25)
            break;
        else if (pokedex[lot].stages == 4 && rand()%100 < 37)
            break;
        lot = rand()%151;
    }
    index = pokeindex(lot+1);
    exp = 0;
    // generated stats of the pokemon are dependent on the exp of the player
    double stat_mod = pl_exp/10000;
    if (stat_mod > 1) stat_mod = 1;
    // calculation of the CP
    int max = maxCP[pokedex[index-1].role][pokedex[index-1].stages];
    int min = minCP[pokedex[index-1].role][pokedex[index-1].stages];
    cp = min + rand()%int((max - min) * stat_mod + 10);

    // calculation of the HP
    max = maxHP[pokedex[index-1].role][pokedex[index-1].stages];
    min = minHP[pokedex[index-1].role][pokedex[index-1].stages];
    hp = min + rand()%int((max - min) * stat_mod + 2);
    hp_left = hp;

    // calculation of the PP
    max = maxPP[pokedex[index-1].role][pokedex[index-1].stages];
    min = minPP[pokedex[index-1].role][pokedex[index-1].stages];
    pp = min + rand()%int((max - min) * stat_mod + 2);

    // if the pokemon isn't at the basic stage of evolution, it can have an ability
    if (rand()%100 < 60) ability.push_back(abilities(rand()%6));

    shield = false;
}

// constructor used while reading the data from the records
Pokemon::Pokemon(string elements[8])
{
    // elements - array of string representing the elements of pokemon class
	// 0 - index, 1 - cp, 2 - hp, 3 - hp_left
	// 4 - pp, 5 - exp, 6 - ability, 7 - shield
    index = pokeindex(std::stoi(elements[0]));
    cp = std::stoi(elements[1]);
    hp = std::stoi(elements[2]);
    hp_left = std::stoi(elements[3]);
    pp = std::stoi(elements[4]);
    exp = std::stoi(elements[5]);
    for (int i = 0; i < elements[6].size(); i++)
    {
        if(elements[6][i] == ';') continue;
        ability.push_back(abilities(elements[6][i]-'0'));
    }
    if (elements[7] == "0") shield = false;
    else shield = true;
}

// method to use while using potions
void Pokemon::TakePotion(Potion pot)
{
    if (pot.ShowKind() == "Buff")
        cp += pot.ShowPoints();
    else hp_left += pot.ShowPoints();
    if (hp_left > hp) hp_left = hp;
}

// method to show atributes of the pokemon
unsigned int Pokemon::ShowPrice() const
{
    return 5*cp + 5*pp + 5*hp;
}

unsigned int Pokemon::ShowHP() const
{
    return hp;
}

unsigned int Pokemon::ShowPP() const
{
    return pp;
}

unsigned int Pokemon::ShowHP_LEFT() const
{
    return hp_left;
}

unsigned int Pokemon::ShowCP() const
{
    return cp;
}

bool Pokemon::ShowShield() const
{
    return shield;
}

unsigned int Pokemon::ShowEXP() const
{
    return exp;
}

pokeindex Pokemon::ShowINDEX() const
{
    return index;
}

// method to show info about the pokemon during the battle
void Pokemon::BattleStats()
{
    cout << pokedex[index - 1].name << " | " << hp_left << " / " << hp << " HP LEFT | " << cp << " CP | " << pp << " PP | type: ";
    int ty = pokedex[index - 1].type.size();
    for (int i = 0; i < ty; i++)
    {
        cout << types_s[pokedex[index - 1].type[i]];
        if (i != ty - 1) cout << ", ";
    }
    cout << " | ";
    int ab = ability.size();
    if (ab > 0)
    {   
        cout << "abilities: ";
        string st_abil[] = {"healing ", "special attack", "dodge", "reemit", "sbreaker", "shield"};
        for (int i = 0; i < ab; i++)
        {
            cout << st_abil[ability[i]];
            if (i != ab - 1) cout << ", ";
        }
        cout << " | ";
    }
    cout << "shield: ";
    if (shield) cout << "ACTIVE";
    else cout << "INACTIVE";
    cout << endl;
}
