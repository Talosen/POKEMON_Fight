//pokemon class/template
#ifndef POKEMON_H
#define POKEMON_H
#include <string>
#include <cstdlib> 
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
//global function 
double types[18][18];
template<typename T>//template
void typetransform(istringstream& templine, string data, T& detail) {
	stringstream tmp;
	getline(templine, data, ',');
	/*tmp.str("");
	tmp.clear();*/
	tmp << data;
	tmp >> detail;
}
void loadTypes() {
	ifstream infile("type.csv", ios::in);
	if (!infile) {
		cout << "type.csv could not be opened." << endl;
		exit(1);
	}
	string str, tmp;

	for (int i = 0; i < 18; i++) {
		getline(infile, str);
		istringstream templine(str);
		for (int j = 0; j < 18; j++)
			typetransform(templine, tmp, types[i][j]);
	}
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			cout << setw(4) << types[i][j];
		}
		cout << endl;
	}
	cout << endl;
	system("pause");
}

class Pokemon {
public:
	char Icons[30][600] = {};
	Pokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :HP(hp), MaxHP(mxhp), Attack(atk), Defense(def), Name(pokemonname), Type(type), No(no), Speed(speed), Ability(ability) { 
		string typeName[18] = { "Normal", "Fire" , "Water" , "Electric" , "Grass" , "Ice" , "Fighting" , "Poison" , "Ground" ,
		"Flying" , "Psychic" , "Bug" , "Rock" , "Ghost" , "Dragon" , "Dark" , "Steel" , "Fairy" };
		for (int i = 0; i < 18; i++) {
			if (getType() == typeName[i]) {
				typeCode = i;
				break;
			}
		}
		setIcons(icons); 
	}
	Pokemon() {}
	void setName(string pokemonname) { Name = pokemonname; }
	void setType(string type) { Type = type; }
	void setNo(int no) { No = no; }
	void setHP(int hp) { HP = hp; }
	void setMaxHP(int mxhp) { MaxHP = mxhp; }
	void setAttack(int atk) { Attack = atk; }
	void setDefense(int def) { Defense = def; }
	void setSpeed(int speed) { Speed = speed; }
	void setAbility(int ability) { Ability = ability; }
	void setpoisonCount(int poisoncount) { poisonCount = poisoncount; }
	void setspeedCount(int speedcount) { speedCount = speedcount; }
	void setdefenseCount(int defensecount) { defenseCount = defensecount; }
	void setattackCount(int attackcount) { attackCount = attackcount; }
	void setHurt(int hurt) { Hurt = hurt; }
	int getHP() const { return HP; }
	int getMaxHP() const { return MaxHP; }
	int getAttack() const { return Attack; }
	int getDefense() const { return Defense; }
	int getNo() const { return No; }
	int getSpeed() const { return Speed; }
	int getAbility() const { return Ability; }
	int getHurt() const { return Hurt; }
	int getTypeCode()const { return typeCode; }
	int getpoisonCount(){ return poisonCount; }
	int getspeedCount() { return speedCount; }
	int getdefenseCount(){ return defenseCount; }
	int getattackCount(){ return attackCount; }
	string getName() const { return Name; }
	string getType() const { return Type; }
	void checkstate(int poisonCount,int speedCount,int defenseCount,int attackCount);
	Pokemon(Pokemon& m) {
		HP = m.HP;
		MaxHP = m.MaxHP;
		Attack = m.Attack;
		Defense = m.Defense;
		No = m.No;
		Speed = m.Speed;
		Ability = m.Ability;
		Name = m.Name;
		Type = m.Type;
		setIcons(m.Icons);
		typeCode = m.typeCode;
		poisonCount = m.poisonCount;//�t�����A�n�k�s
		speedCount = m.speedCount;
		defenseCount = m.defenseCount;
		attackCount = m.attackCount;
	}
	Pokemon& operator=(Pokemon& m) {
		HP = m.HP;
		MaxHP = m.MaxHP;
		Attack = m.Attack;
		Defense = m.Defense;
		No = m.No;
		Speed = m.Speed;
		Ability = m.Ability;
		Name = m.Name;
		Type = m.Type;
		setIcons(m.Icons);
		typeCode = m.typeCode;
		poisonCount = m.poisonCount;//�t�����A�n�k�s
		speedCount = m.speedCount;
		defenseCount = m.defenseCount;
		attackCount = m.attackCount;
		return *this;
	}
	void setIcons(char icons[][600]) {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 600; j++) {
				Icons[i][j] = icons[i][j];
			}
		}
	}
	void drawIcons() {
		for (int i = 0; i < 30; i++) {
			cout << Icons[i] << endl;
		}
	}
	virtual void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}

		}
		else if (m.getAbility() == 10) {//�۽�
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦���w�ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
		}
		
	}
	virtual void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
	void coutinfo(int x, int y) {
		rlutil::locate(x, y++);
		cout << "No." << No << endl;
		rlutil::locate(x, y++);
		cout << Name << endl;
		rlutil::locate(x, y++);
		cout << "Type:" << Type << endl;
		rlutil::locate(x, y++);
		cout << "HP:" << HP << endl;
		rlutil::locate(x, y++);
		cout << "Attack:" << Attack << endl;
		rlutil::locate(x, y++);
		cout << "Defense:" << Defense << endl;
		rlutil::locate(x, y++);
		cout << "Speed:" << Speed << endl;
		rlutil::locate(x, y++);
		cout << "Ability:" << Ability << endl;
	}
	void couticon(int x, int y) {
		for (int i = 0; i < 30; i++) {
			rlutil::locate(x, y + i);
			cout << Icons[i] << endl;
		}
	}

protected:
	string Name;//�W�r
	string Type;//�ݩ�
	int No;//�s�X
	int HP;//�ͩR��
	int MaxHP;//�̤j�ͩR��
	int Attack;//�����O
	int Defense;//���m�O
	int Speed;//�t��
	int Ability;//��O�s�X
	int typeCode;
	int poisonCount = 0;
	int speedCount = 0;
	int defenseCount = 0;
	int attackCount = 0;
	int Hurt;//���h��
};

class Healpokemon :public Pokemon {//1
public:
	Healpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) {}
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {//�۽�
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A"<<Name <<"����ϼu�ˮ`�A���"<< m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		cout << Name << "�֦��^�_�ޯ�A�^�_3HP" << endl;
		HP += 3;//�C�^�X�^�_HP3
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Burningpokemon :public Pokemon {//2
public:
	Burningpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		int a = (rand() % 3) + 1;
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - (damage + a));
				m.setHurt(damage + a);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << damage << "HP" << endl;
				cout << m.getName() << "������[�����A���" << a << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - (damage + a));//�ˮ`-2
			m.setHurt(damage + a);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << damage << "HP" << endl;
			cout << m.getName() << "������[�����A���" << a << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - (damage + a));//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O+1~3�I�H���ˮ` )
			m.setHurt(damage + a);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}

	
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Counterpokemon :public Pokemon {//3
public:
	Counterpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Immunologypokemon :public Pokemon {//4
public:
	Immunologypokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		

	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Leechpokemon :public Pokemon {//5
public:
	Leechpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		int a = (rand() % 2) + 2;//2~3
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - (damage + a));
				m.setHurt(damage+a);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << damage << "HP" << endl;
				cout << Name << "�֦��l��ޯ�A�l��"<<a<<"HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - (damage+a));//�ˮ`-2
			m.setHurt(damage+a);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << damage << "HP" << endl;
			cout << Name << "�֦��l��ޯ�A�l��" << a << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - (damage + a));//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage + a);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << damage << "HP" << endl;
			cout << Name << "�֦��l��ޯ�A�l��" << a << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		HP += a;//�l��2~3�Ihp
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}

};
class Avoidpokemon :public Pokemon {//6
public:
	Avoidpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class DoubleAtkpokemon :public Pokemon {//7
public:
	DoubleAtkpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		int a = (rand() % 5);
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
			if (a == 0) {
				int dou = (rand() % 5);
				if (dou != 0) {
					m.setHP(m.getHP() - damage);
					m.setHurt(damage);//�p��ˮ`�q
					cout << Name <<"�o�ʤG������"<<m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
				}
				else {
					m.setHurt(0);//�p��ˮ`�q
					cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
				}
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
			if (a == 0) {
				m.setHP(m.getHP() - damage);//�ˮ`-2
				m.setHurt(damage*2);//�p��ˮ`�q
				cout << Name << "�o�ʤG������" << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else {
			m.setHP(m.getHP() - damage);
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << damage / 5 << "HP" << endl;
				HP = HP - damage / 5;
			}
			if (a == 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage*2);//�p��ˮ`�q
				cout << Name << "�o�ʤG������"<<m.getName() << "��������A���" << damage << "HP" << endl;
				if (m.getAbility() == 3) {
					cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << damage / 5 << "HP" << endl;
					HP = HP - damage / 5;
				}
			}
		}//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Poisonpokemon :public Pokemon {//8
private:
	bool poison = false;
public:
	Poisonpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) { setIcons(icons); }
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		if (poison == false) {//�T�{�o�ʹL�r�����F��?�Y�L�h�o��
			m.setpoisonCount(3);
			cout << m.getName() << "���r2�^�X" << endl;
			poison = true;
		}
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}
};
class Lowspeedpokemon :public Pokemon {//9
private:
	bool speedatk = false;
public:
	Lowspeedpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) {}
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		if (m.getAbility() != 4) {//lowspeed/4�K��
			if (speedatk == false) {
				m.setspeedCount(3);
				cout << m.getName() << "�t�׭��C2�^�X" << endl;
				speedatk = true;
			}
		}
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}

};
class Rockpokemon :public Pokemon {//10
public:
	Rockpokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) {}
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP()-damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���֦��۽��ޯ�A�ˮ`-2�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - (m.getHurt() / 5 - 2);
			}
		}

	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}

};
class Lowdefencepokemon :public Pokemon {//11
private:
	bool defenseatk = false;
public:
	Lowdefencepokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) {}
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		if (m.getAbility() != 4) {//lowdefense/4�K��
			if (defenseatk == false) {
				m.setdefenseCount(3);
				cout << m.getName() << "���m���C2�^�X" << endl;
				defenseatk = true;
			}
		}
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}

};
class Lowatkencepokemon :public Pokemon {//11
private:
	bool atkatk = false;
public:
	Lowatkencepokemon(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability, char icons[][600]) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability, icons) {}
	void attack(Pokemon& m) {
		unsigned int damage = (getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()];
		if (m.getAbility() == 6) {//�K�̶ˮ`
			int r = (rand() % 5);
			if (r != 0) {
				m.setHP(m.getHP() - damage);
				m.setHurt(damage);//�p��ˮ`�q
				cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			}
			else {
				m.setHurt(0);//�p��ˮ`�q
				cout << m.getName() << "��������A" << m.getName() << "Ĳ�o�j�קޯ�A���" << m.getHurt() << "HP" << endl;
			}
		}
		else if (m.getAbility() == 10) {
			unsigned int damage = ((getAttack() - m.getDefense()) * types[getTypeCode()][m.getTypeCode()]) - 2;
			m.setHP(m.getHP() - damage);//�ˮ`-2
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A" << m.getName() << "�֦��۽��ޯ�A�ˮ`���2�A���" << m.getHurt() << "HP" << endl;
		}
		else {
			m.setHP(m.getHP() - damage);//�Ĺ�Ǫ��ثe�ͩR�� = �Ĺ�Ǫ��ثe�ͩR�� - ( �����O - �Ĺ�Ǫ������m�O )
			m.setHurt(damage);//�p��ˮ`�q
			cout << m.getName() << "��������A���" << m.getHurt() << "HP" << endl;
			if (m.getAbility() == 3) {
				cout << m.getName() << "�֦��ϼu�ޯ�A" << Name << "����ϼu�ˮ`�A���" << m.getHurt() / 5 << "HP" << endl;
				HP = HP - m.getHurt() / 5;
			}
		}
		if (m.getAbility() != 4) {//lowdefense/4�K��
			if (atkatk == false) {
				m.setattackCount(3);
				cout << m.getName() << "�������C2�^�X" << endl;
				atkatk = true;
			}
		}
		
	}
	void showStats() {
		std::cout << std::setw(10) << Name << "(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
	}

};
void Pokemon::checkstate(int poison, int speed, int defense, int attack) {
	if (poison !=0) {
		if (poison == 3) {
			cout << Name << "���^�X������r����" << endl;
			poisonCount--;
		}
		else if (poison == 2) {
			cout << Name<<"����r�����ˮ`HP-2" << endl;
			HP -= 2;
			poisonCount--;
		}
		else if (poison == 1) {
			cout << Name << "����r�����ˮ`HP-2" << endl;
			HP -= 2;
			poisonCount--;
		}
	}
	if (speed != 0) {
		if (speed == 3) {
			cout << Name << "���^�X���@�γt�׭��C" << endl;
			speedCount--;
		}
		else if (speed == 2) {
			cout << Name << "�t�׭��C2" << endl;
			Speed = Speed - 2;
			speedCount--;
		}
		else if (speed == 1) {
			cout << Name << "�t�׭��C2" << endl;
			speedCount=-1;//�U�@���A�^�_
		}
		else if (speed == -1) {//�^�_���A
			speedCount = 0;
			Speed += 2;
		}
	}
	if (defense != 0) {
		if (defense == 3) {
			cout << Name << "���^�X���@�Ψ��m���C" << endl;
			defenseCount--;
		}
		else if (defense == 2) {
			cout << Name << "���m���C2" << endl;
			Defense = Defense - 2;
			defenseCount--;
		}
		else if (defense == 1) {
			cout << Name << "���m���C2" << endl;
			defenseCount = -1;//�U�@���A�^�_
		}
		else if (defense == -1) {//�^�_���A
			defenseCount = 0;
			Defense += 2;
		}
	}
	if (attack != 0) {
		if (attack == 3) {
			cout << Name << "���^�X���@�Χ������C" << endl;
			attackCount--;
		}
		else if (attack == 2) {
			cout << Name << "�������C2" << endl;
			Attack = Attack - 2;
			attackCount--;
		}
		else if (attack == 1) {
			cout << Name << "�������C2" << endl;
			attackCount = -1;//�U�@���A�^�_
		}
		else if (attack == -1) {//�^�_���A
			attackCount = 0;
			Attack += 2;
		}
	}

}
//(int hp, int mxhp, int atk, int def, string pokemonname, string type, int no, int speed, int ability) :Pokemon(hp, mxhp, atk, def, pokemonname, type, no, speed, ability) {}
#endif // POKEMON_H



