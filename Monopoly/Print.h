#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<fstream>
#include"database.h"
#include<vector>
using namespace std;
void ConsoleFullScreen();
BOOL SetConsoleSize(int W, int H);
void SetCursorVisible(bool a);
void hidecursor();
void gotoxy(int xpos, int ypos);
void getxy(int &x, int &y);
void SetColor(int color = 7);
void PrintRec(int x, int y, int lenth, int width); // x y 長 寬(幾個 "─ ")
void ReadFile(string fileName);
void PrintDice(int i);
void ColorMenu(int choose, int color, string option[]);
void blank(int x1, int x2, int y1, int y2);
//---------------------------------------
int RollDice(); // 骰骰子
int RollTwoDice();
void PrintLeft(int playNum); // 左邊框格 玩家人數
void SetPlayerLocation(int who, int where, int old = 0); //玩家位置  player 新位置 舊位置(一開始設0即可)
void SetLand(int where, int whose); //設定土地所有 幾號土地 player
void PrintRightBack(); //右邊框格
void PrintRight();//將地名填入
void PrintMenu();
void PrintRound(int r); //回合
void PrintTurn(int i); // 輪到誰 從0開始
void PrintPlayerLand(int who, int a[]); // player 等級array
void SetPlayerMoney(int who, int num); //player money
void SetPlayerProperty(int who, int num);// 財產
//------------------------------------------------------------
int PrintEsc(); // 1為存檔 2為讀檔
void PrintBank(Player& who); // 
void PrintStock(string name[], int price[], int updown[], Player& who); // 正為買 負為賣
int PrintTool();
int SaleLand(vector<int> where, vector<int> level, vector<int> price);
int PrintOnLand(estate where, int whose, int who, int price); // 無人土地 則 whose = -1 回傳 1為購買 0 為放棄
void PrintChance(string content);
void PrintDestiny(string content);
void PrintSign(string content, int num);
/*
後面搭
gotoxy(60, 14);
system("pause");
blank(55, 80, 10, 14);
*/
void PrintStop(int where);
int PrintInput(int which);//which = 1為路障  which = 2為遙控骰子
void victory(int t);
void PrintDie(int who);
