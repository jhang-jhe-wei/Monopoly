#pragma once
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include"Print.h"
#include"database.h"
using namespace std;
static class Backend
{
public:	
	string mapName;
	int round;
	int amount_of_player;
	int playerState;
	int counter = 0;
	int oldLocal = 0;	
	vector<Map> maps;
	fstream file;
	Player* players;
	Backend(string name= "start.txt");	
	int getEsatate(Player a);
	void printCurrentPlayer();//���L�{�b���a�����A
	void rotation();//���H
	void going();//�Y��l�é��e
	void play();
};
int chance();//���l�L�ʵe
void start();//�}��