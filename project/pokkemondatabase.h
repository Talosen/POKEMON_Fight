//pokemondatabase class
#ifndef POKEMONDATEBASE_H
#define POKEMONDATEBASE_H
#include"pokemon.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
string iconfile[32] = { "001.txt","002.txt", "003.txt", "004.txt", "005.txt", "006.txt", "007.txt", "008.txt",
"009.txt", "010.txt", "011.txt", "012.txt", "013.txt", "014.txt","015.txt","016.txt","017.txt","018.txt","019.txt", 
"020.txt", "021.txt", "022.txt", "023.txt", "024.txt", "025.txt", "026.txt", "027.txt","028.txt","029.txt", "030.txt", 
"031.txt", "032.txt" };
char icon[30][600] = {};
class Pokemondatabase {
public:
	Pokemondatabase() { loadPokemondatabase(); }
	void loadPokemondatabase();
protected:
	vector< Pokemon* > pokemons;

};
void Pokemondatabase::loadPokemondatabase() {
	pokemons.resize(32);
	fstream inFile("pokemons.csv", ios::in);
	if (!inFile) {
		cout << "pokemons.csv could not be opened!";
		exit(1);
	}
	string line;
	int No = 1;
	int count = 0;
	/// /////////////////
	while (getline(inFile, line, '\n')&&count<32) {  //讀檔讀到跳行字元
		istringstream templine(line); // string 轉換成 stream
		string data;
		int hp, atk, def, no, speed, ability;
		string pokemonname, type;
		typetransform(templine, data, no);
		typetransform(templine, data, pokemonname);
		typetransform(templine, data, type);
		typetransform(templine, data, hp);
		typetransform(templine, data, atk);
		typetransform(templine, data, def);
		typetransform(templine, data, speed);
		typetransform(templine, data, ability);
		//icon
		fstream infile(iconfile[count], ios::in);
		if (!infile) {
			cout << "iconfile.txt could not be opened!";
			exit(1);
		}
		for (int j = 0; j < 30; j++)
			infile.getline(icon[j], 600);
		//pokemons[check].setIcons(icon);

		if (ability == 0) 
			pokemons[count] = new Pokemon(hp, hp,atk,def,pokemonname,type,no,speed,ability,icon);
		else if (ability == 1) 
			pokemons[count] = new Healpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 2)
			pokemons[count] = new Burningpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 3)
			pokemons[count] = new Counterpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 4)
			pokemons[count] = new Immunologypokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 5)
			pokemons[count] = new Leechpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 6)
			pokemons[count] = new Avoidpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 7)
			pokemons[count] = new DoubleAtkpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 8)
			pokemons[count] = new Poisonpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 9)
			pokemons[count] = new Lowspeedpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 10)
			pokemons[count] = new Rockpokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 11)
			pokemons[count] = new Lowdefencepokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		else if (ability == 12)
			pokemons[count] = new Lowatkencepokemon(hp, hp, atk, def, pokemonname, type, no, speed, ability, icon);
		//pokemons[count]->drawIcons();
		count++;
		
	}
}

#endif // POKEMONDATEBASE_H
