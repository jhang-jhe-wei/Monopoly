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
	void printCurrentPlayer();//打印現在玩家的狀態
	void rotation();//換人
	void going();//擲骰子並往前
	void play();
};
int chance();//骰骰子無動畫
void start();//開場