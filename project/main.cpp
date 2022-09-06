//�_�i�ڹ�Ե{��
#include "rlutil.h"
#include <stdlib.h> // for srand() / rand()
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
#include"pokkemondatabase.h"
#include"player.h"
/// Tiles//https://stackoverflow.com/questions/10983078/c-what-does-ab-mean
#define FLOOR 0
#define WALL 1//���
#define GRASS (1 << 1)//��a
#define TREE (1 << 2)//��� 1*2*1=2
#define WATER (1 << 4)//���� 1*2*2=4
#define ENTRANCE (1 << 8)//�ؿv�J�f 1*2*4=8

#define MAPSIZE 15
int x = 20, y = 30;
void loadmap(char** map);
void draw(char** map);
int main() {
	srand(time(NULL));
	int wincount = 0;
	char* map[31] = {};
	loadmap(map);//���a��
	loadTypes();
	Pokemondatabase pokemondatabase;
	Player player;
	rlutil::hidecursor();
	/*rlutil::saveDefaultColor();
	cout << "Welcome! Use WASD to move, ESC to quit.\n";*/
	//rlutil::anykey("Hit any key to start.\n");
	//�e�a��
	draw(map);
	//����
	while (1) {
		// Input
		if (kbhit()) {
			char k = rlutil::getkey();
			int oldx = x, oldy = y;//����
			if (k == 'a') { --x; }
			else if (k == 'd') { ++x; }
			else if (k == 'w') { --y; }
			else if (k == 's') { ++y; }
			else if (k == rlutil::KEY_ESCAPE) break;
			// �Y�J��ê��
			bool catchgrass = false, catchwater = false;
			if (map[y - 1][x - 1] == '*' || map[y - 1][x - 1] == '!' || map[y - 1][x - 1] == '1' || map[y - 1][x - 1] == '2' || map[y - 1][x - 1] == '3' || map[y - 1][x - 1] == '4'
				|| map[y - 1][x - 1] == '5' || map[y - 1][x - 1] == '6' || map[y - 1][x - 1] == '7' || map[y - 1][x - 1] == '8' || map[y - 1][x - 1] == '9' ||
				map[y - 1][x - 1] == 'A' || map[y - 1][x - 1] == 'B' || map[y - 1][x - 1] == 'C' || map[y - 1][x - 1] == 'D') {
				x = oldx; y = oldy;
			}
			//�ؿv�J�f�A�i�H��V
			else if (map[y - 1][x - 1] == '#') {
				int battle;
				rlutil::cls();//�M�ŵe��
				rlutil::setColor(rlutil::WHITE);
				cout << "�԰��Ы�1�A�k�]�Ы�2" << endl;
				cin >> battle;
				if (battle == 1) {
					rlutil::cls();//�M�ŵe��
					if (player.getCurrentPokemon() == nullptr) {
						try {//Exception handling
							player.maybeerror(player.getCurrentPokemon());
						}
						catch (int x) {
							std::cout << "�A�S���i�H�԰����d��" << endl;
							std::cout << "�ЦA�h�ԳҮ����a!" << endl;
							std::system("pause");
						}
					}
					else {
						Player npc(1);
						Player user(player);
						int posx = 1, posy = 2;
						user.getCurrentPokemon()->couticon(1, 2);
						user.getCurrentPokemon()->coutinfo(1, 29);
						user.showlistPokemon(1, 38);
						//posx = 25, posy = 2;
						npc.getCurrentPokemon()->couticon(60, 2);
						npc.getCurrentPokemon()->coutinfo(60, 29);
						npc.showlistPokemon(60, 38);
						int cnt = 1;
						if (user.getCurrentPokemon()->getSpeed() >= npc.getCurrentPokemon()->getSpeed()) {//�ڤ����
							while (true) {
								std::cout << "Round " << cnt << endl;
								cout << user.getName() << "�� " << user.getCurrentPokemon()->getName() << " ���� " << npc.getName() << "�� " << npc.getCurrentPokemon()->getName() << endl;
								user.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
								user.getCurrentPokemon()->showStats();
								npc.getCurrentPokemon()->showStats();
								if (npc.getCurrentPokemon()->getHP() <= 0) {
									if (npc.getCurrentPokemon() != nullptr) {
										npc.setdiedPokemon();
										if (user.getCurrentPokemon()->getHP() <= 0) {//�T�O�p�G�d���Q������
											user.setdiedPokemon();
										}
										cout << user.getName() << "�Ѿl�԰��d��:" << endl;
										user.showAlivePokemon();
										cout << npc.getName() << "�Ѿl�԰��d��:" << endl;
										npc.showAlivePokemon();
										cnt = 0;
										system("pause");
									}
									if (npc.getCurrentPokemon() == nullptr) {
										cout << ">>> Player  " << user.getName() << " win!, Player" << npc.getName() << " lose! <<<" << endl;
										wincount++;
										break;
									}

								}
								cout << npc.getName() << "�� " << npc.getCurrentPokemon()->getName() << " ���� " << user.getName() << "�� " << user.getCurrentPokemon()->getName() << endl;
								npc.getCurrentPokemon()->attack(*user.getCurrentPokemon());
								//�T�{���`���A
								user.getCurrentPokemon()->checkstate(user.getCurrentPokemon()->getpoisonCount(), user.getCurrentPokemon()->getspeedCount(), user.getCurrentPokemon()->getdefenseCount(), user.getCurrentPokemon()->getattackCount());
								npc.getCurrentPokemon()->checkstate(npc.getCurrentPokemon()->getpoisonCount(), npc.getCurrentPokemon()->getspeedCount(), npc.getCurrentPokemon()->getdefenseCount(), npc.getCurrentPokemon()->getattackCount());
								user.getCurrentPokemon()->showStats();
								npc.getCurrentPokemon()->showStats();
								if (user.getCurrentPokemon()->getHP() <= 0) {
									if (user.getCurrentPokemon() != nullptr) {
										user.setdiedPokemon();
										if (npc.getCurrentPokemon()->getHP() <= 0) {//�T�O�p�G���~�Q��糤�����
											npc.setdiedPokemon();
										}
										cout << user.getName() << "�Ѿl�԰��d��:" << endl;
										user.showAlivePokemon();
										cout << npc.getName() << "�Ѿl�԰��d��:" << endl;
										npc.showAlivePokemon();
										cnt = 0;
										system("pause");
									}
									if (user.getCurrentPokemon() == nullptr) {
										cout << ">>> Player  " << npc.getName() << " win!, Player" << user.getName() << " lose! <<<" << endl;
										//npc.getCurrentPokemon()->showStats();
										break;
									}

								}
								std::cout << "===============================" << std::endl;
								cnt++;
							}
							system("pause");
						}
						else {
							while (true) {
								std::cout << "Round " << cnt << std::endl;
								cout << npc.getName() << "�� " << npc.getCurrentPokemon()->getName() << " ���� " << user.getName() << "�� " << user.getCurrentPokemon()->getName() << endl;
								npc.getCurrentPokemon()->attack(*user.getCurrentPokemon());
								user.getCurrentPokemon()->showStats();
								npc.getCurrentPokemon()->showStats();
								if (user.getCurrentPokemon()->getHP() <= 0) {
									if (user.getCurrentPokemon() != nullptr) {
										user.setdiedPokemon();
										if (npc.getCurrentPokemon()->getHP() <= 0) {//�T�O�p�G�d���Q������
											npc.setdiedPokemon();
										}
										cout << user.getName() << "�Ѿl�԰��d��:" << endl;
										user.showAlivePokemon();
										cout << npc.getName() << "�Ѿl�԰��d��:" << endl;
										npc.showAlivePokemon();
										cnt = 0;
										system("pause");
									}
									if (user.getCurrentPokemon() == nullptr) {
										cout << ">>> Player  " << npc.getName() << " win!, Player" << user.getName() << " lose! <<<" << endl;
										//npc.getCurrentPokemon()->showStats();
										break;
									}

								}
								cout << user.getName() << "�� " << user.getCurrentPokemon()->getName() << " ���� " << npc.getName() << "�� " << npc.getCurrentPokemon()->getName() << endl;
								user.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
								//�T�{���`���A
								user.getCurrentPokemon()->checkstate(user.getCurrentPokemon()->getpoisonCount(), user.getCurrentPokemon()->getspeedCount(), user.getCurrentPokemon()->getdefenseCount(), user.getCurrentPokemon()->getattackCount());
								npc.getCurrentPokemon()->checkstate(npc.getCurrentPokemon()->getpoisonCount(), npc.getCurrentPokemon()->getspeedCount(), npc.getCurrentPokemon()->getdefenseCount(), npc.getCurrentPokemon()->getattackCount());
								user.getCurrentPokemon()->showStats();
								npc.getCurrentPokemon()->showStats();
								if (npc.getCurrentPokemon()->getHP() <= 0) {
									if (npc.getCurrentPokemon() != nullptr) {
										npc.setdiedPokemon();
										if (user.getCurrentPokemon()->getHP() <= 0) {//�T�O�p�G�d���Q������
											user.setdiedPokemon();
										}
										cout << user.getName() << "�Ѿl�԰��d��:" << endl;
										user.showAlivePokemon();
										cout << npc.getName() << "�Ѿl�԰��d��:" << endl;
										npc.showAlivePokemon();
										cnt = 0;
										system("pause");
									}
									if (npc.getCurrentPokemon() == nullptr) {
										cout << ">>> Player " << user.getName() << " win!, Player " << npc.getName() << " lose! <<<" << endl;
										//user.getCurrentPokemon()->showStats();
										break;
									}

								}
								std::cout << "===============================" << std::endl;
								cnt++;
							}
						}
					}
				}
				rlutil::cls();
			}
			//�����A�i�H��V 
			else if (map[y - 1][x - 1] == '~') { catchwater = true; }
			//��a�A�i�H��V
			else if (map[y - 1][x - 1] == ';') { catchgrass = true; }
			draw(map);
			//10%���_
			int possible = (rand() % 10) + 1;//1~10
			if ((possible == 1 ) && map[y - 1][x - 1] != '#') {//|| possible == 2 || possible == 3 || possible == 4 || possible == 5
				player.catchPokemon(catchgrass, catchwater);
				rlutil::cls();
				draw(map);
			}
			// Die
			if (wincount >= 7)
				break;
		}
	}
	rlutil::cls();
	rlutil::setColor(rlutil::WHITE);
	cout << "���ߧr!�AĹ�o�F�ӧQ!" << endl;
	system("pause");
	//�R��new���Ŷ�
	for (int i = 0; i < 31; i++) {
		if (map[i] == nullptr)
			delete[] map[i];
	}

	rlutil::resetColor();
	rlutil::showcursor();

	//return 0;
}
void loadmap(char** map) {
	for (int i = 0; i < 31; i++)//new char�a��
		map[i] = new char[105]();
	fstream inFile("yzumap.txt", ios::in);//Ū��
	if (!inFile) {
		cout << "yzumap.txt could not be opened!";
		exit(1);
	}
	//inFile.seekg(0, ios::end);
	//int numLine = inFile.tellg() / 93;//31��
	//inFile.seekg(0, ios::beg);
	//inFile.ignore(110, '\n');
	for (int i = 0; i < 31; i++) {
		inFile.getline(map[i], 105);
	}

	inFile.close();
	/*for (int i = 0; i < 31; i++) {
			cout << map[i]<<endl;
	}
	system("pause");*/
}
void draw(char** map) {
	rlutil::locate(1, 1);
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 93; j++) {
			if (map[i][j] == '\0') { cout << map[i][j]; }
			else if (map[i][j] == '*') { rlutil::setColor(rlutil::DARKGREY); cout << map[i][j]; }
			else if (map[i][j] == ';') { rlutil::setColor(rlutil::GREEN); cout << map[i][j]; }
			else if (map[i][j] == '!') { rlutil::setColor(rlutil::BROWN); cout << map[i][j]; }
			else if (map[i][j] == '#') { rlutil::setColor(rlutil::YELLOW); cout << map[i][j]; }
			else if (map[i][j] == '~') { rlutil::setColor(rlutil::BLUE); cout << map[i][j]; }
			else if (map[i][j] == '1' || map[i][j] == '2' || map[i][j] == '3' || map[i][j] == '4' || map[i][j] == '5' || map[i][j] == '6' || map[i][j] == '7' || map[i][j] == '8' || map[i][j] == '9') { rlutil::setColor(rlutil::GREY); cout << map[i][j]; }
			else if (map[i][j] == 'A' || map[i][j] == 'B' || map[i][j] == 'C' || map[i][j] == 'D') { rlutil::setColor(rlutil::LIGHTMAGENTA); cout << map[i][j]; }
			else cout << map[i][j];
		}
		cout << endl;
	}
	rlutil::locate(x, y);//���a�_�l�I
	rlutil::setColor(rlutil::RED);//���a�C��
	cout << "@";//���a�лx
	//rlutil::locate(1, 35);
	fflush(stdout);
	//system("pause");
}
