# PokemonGame
Welcome to Pokemon Game README file.

## 1. Compilation
In order to properly compile the file, execute the following command in your terminal:

g++ -std=c++11 main.cpp Pokemon.cpp Potion.cpp Player.cpp functions.cpp -o pokemonGame

After compilation, your game should figure in the folder as "pokemonGame" program.

## 2. Execution
Execute the game by opening the "pokemonGame" program in the folder or through terminal.
If game works properly, it should ask for the choice of the player.

Note: If records file doesn't exist or is empty, the resume of the game won't be possible and the game will ask you to create your own character!

## 3. Gameplay
Game provides a few modules:

- fighting with a wild pokemon
- fighting with a coach
- finding treasures
- encountering the marchants and dealing with them
- healing/buffing the pokemons

The goal of the game is to catch all the pokemons!
Events and choice of the actions are always displayed in the terminal.

### Pokemons' characteristics
- Pokemons have their own experience (EXP), health (HP), combat power (CP) and protection (PP). Experience enhances the chances of evolution of the pokemon to the next stage, whreas the others predict the probabilities of specified special abilities
- After the fight, pokemons can be healed with the Healing potions, their combat power can also be improved by Buff potions

### Fighting with pokemons
- Fighting a coached pokemon can lead to gain of player's EXP, gold and pokemon's EXP and CP. During the loss, the pokemon stays alive with only 1 HP left.
- Wild pokemon, in contrary, can be weakened during the fight, and caught in only 3 trials (it can also escape from the scene in every of them). This fight can also lead to gain of player's EXP and pokemon's EXP and CP. During the loss, the pokemon dies and *can't be healed*. You can choose anothe pokemon to fight or run away.
  
- During the fights, it's crutial to know that some types of pokemons are more effective or weaker in respect to the others, for example, pokemons with fire type will be easily harmed by the water type ones.
- Special abilities advance the fight:
    - healing - 3 HP comes back to the pokemon every round of its attack
    - special attack - creates additional effect of the attacked pokemon, which enhances the given damage
    - dodge - omitts the attack of the opponent
    - reemision - reemits the attack of the opponent
    - shield breaker - destroys additional protection (shield) of the opponent
    - shield creator - creates a barrier (shield) for the next attack of the opponent
  also the specific pokemon attributes, ie. CP, HP and PP have the influence to probability of activation of those abilities during the fight

### The end
The game ends when the player catches all types of pokemons. The game keeps the record of all the types caught before, so the player don't have to carry all the pokemons in order to win!

Note: It's advisable to save the records after every event, but you don't have to do so.

Good luck in catching them all!
