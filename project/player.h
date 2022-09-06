//玩家的class
#ifndef PLAYER_H
#define PLAYER_H
//#include"pokemon.h"
#include"pokkemondatabase.h"
class Player :public Pokemondatabase {
public:
	Player() {}
	Player(int npc);
	Player(Player& m);
	void catchPokemon(bool g, bool w);
	void showAlivePokemon();
	void showlistPokemon(int x,int y);
	Pokemon* getCurrentPokemon();
	void setdiedPokemon();
	void addPokemon(Pokemon it,int pos);
	string getName()const { return Name; }
	void resetPokemon();
	void maybeerror(Pokemon* a) {
		if (a == nullptr)
			throw 10;
	}
private:
	Pokemon* PokemonList[3] = {};
	string Name = "我";
};
Player::Player(int npc) {
	Name = "NPC";
	for (int i = 0; i < 3; i++) {
		int take = (rand() % 32) + 0;
		Pokemon it= *pokemons[take];
		addPokemon(it, i);
	}
}
Player::Player(Player &m) {
	Name = m.Name;
	for (int i = 0; i < 3; i++) {
		Pokemon it = *m.PokemonList[i];
		addPokemon(it, i);
	}
}
void Player::catchPokemon(bool grass, bool water) {
	rlutil::cls();
	rlutil::setColor(rlutil::WHITE);
	cout << "You find the pokemon!" << endl;
	//Pokemon* catchpokemon = new Pokemon;
	Pokemon it;
	//pokemondatabase.pokemons[possible];
	if (grass == true) //grass增加40%
	{
		int possible = (rand() % 166);//分母0~165
		if (possible < 21) {
			it = *(pokemons[possible / 7]);//0~2
		}
		else {
			possible -= 21;
			possible = (rand() % 29);
			it = *(pokemons[possible+3]);//3~31
		}
	}
	else if (water == true) //water增加40%
	{
		int possible = (rand() % 166);//分母0~165
		if (possible < 21) {
			it = *(pokemons[(possible / 7) + 6]);//6~8
		}
		else {
			possible -= 21;
			possible = (rand() % 29);
			if(possible<6)
				it = *(pokemons[possible]);//0~5
			else
				it = *(pokemons[possible + 3]);//9~31
		}
	}
	else {
		int possible = (rand() % 32);//分母0~165
		it = *(pokemons[possible]);//9~31
	}
	it.drawIcons();
	//rlutil::locate(50,5);
	it.coutinfo(50, 7);
	rlutil::resetColor();
	//cout <<"Type: " <<catchpokemon->getType();
	//rlutil::locate(1,25);
	rlutil::locate(1, 28);
	cout << "寵物清單；" << endl;
	showlistPokemon(1,29);
	/*int posx = 1, posy = 30;
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr) {
			rlutil::locate(posx, 29);
			cout << "代號：" << i + 1 << endl;
			PokemonList[i]->coutinfo(posx, posy);
			posx += 20;
		}
	}*/
	int catchornot=0;
	cout << "捕捉請按1，放棄請按2" << endl;
	cin >> catchornot;
	int success = (rand() % 2);
	if (catchornot == 1) {//捕捉請按1
		if (success == 0) {
			cout << "捕捉失敗啦!" << endl;
			system("pause");
		}
		else {
			bool full = true;
			for (int i = 0; i < 3; i++) {
				if (PokemonList[i] == nullptr) {
					PokemonList[i] = new Pokemon;
					addPokemon(it,i);///////
					full = false;
					cout << "捕捉成功" << endl;
					break;
				}
			}
			if (full == true) {
				int get;
				cout << "寵物包已滿，如果想替換包裡的寵物請按寵物代號來確認，若是不想換請按0" << endl;
				cin >> get;
				if (get >= 1 && get <= 3) {
					addPokemon(it, get-1);
					cout << "捕捉成功" << endl;
				}
			}
			system("pause");
		}
	}
	else {
		cout << "放棄捕捉!" << endl;
		system("pause");
	}
}
void Player::addPokemon(Pokemon it, int pos) {

	switch (it.getAbility()) {
	case 0:
		PokemonList[pos] = new Pokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Normal(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 1:
		PokemonList[pos] = new Healpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Heal(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 2:
		PokemonList[pos] = new Burningpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Burning(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 3:
		PokemonList[pos] = new Counterpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new CounterAttack(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 4:
		PokemonList[pos] = new Immunologypokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Immunology(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 5:
		PokemonList[pos] = new Leechpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new LeechLife(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 6:
		PokemonList[pos] = new Avoidpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Avoid(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 7:
		PokemonList[pos] = new DoubleAtkpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new DoubleAttack(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 8:
		PokemonList[pos] = new Poisonpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new Poison(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 9:
		PokemonList[pos] = new Lowspeedpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new LowerSpeed(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 10:
		PokemonList[pos] = new Rockpokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new RockSkin(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 11:
		PokemonList[pos] = new Lowdefencepokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new LowerDefence(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;

	case 12:
		PokemonList[pos] = new Lowatkencepokemon(it.getHP(), it.getMaxHP(), it.getAttack(), it.getDefense(), it.getName(), it.getType(), it.getNo(), it.getSpeed(), it.getAbility(), it.Icons);
		//pokemons[i] = new LowerAttack(num, name, type, hp, atk, def, speed, ability, abiName, theicon);
		break;
	}
}
void Player::showAlivePokemon() {
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr) {
			PokemonList[i]->showStats();
		}
	}
	cout << endl;
}
void Player::showlistPokemon(int x,int y) {
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr) {
			rlutil::locate(x, y);
			cout << "代號：" << i + 1 << endl;
			PokemonList[i]->coutinfo(x, y+1);
			x += 20;
		}
	}
}
Pokemon* Player::getCurrentPokemon() {
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr)
			return PokemonList[i];
	}
	return nullptr;
}
void Player::setdiedPokemon() {
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr) {
			//delete PokemonList[i];
			PokemonList[i] = nullptr;
			break;
		}
	}
}
void Player::resetPokemon() {
	for (int i = 0; i < 3; i++) {
		if (PokemonList[i] != nullptr) {
			int k = 0;
			for (; k < 32; k++) {
				if (PokemonList[i]->getName() == pokemons[k]->getName())
					break;
			}
			*PokemonList[i] = *pokemons[k];
		}
	}
}

#endif // PLAYER_H