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
void PrintRec(int x, int y, int lenth, int width); // x y �� �e(�X�� "�w ")
void ReadFile(string fileName);
void PrintDice(int i);
void ColorMenu(int choose, int color, string option[]);
void blank(int x1, int x2, int y1, int y2);
//---------------------------------------
int RollDice(); // ���l
int RollTwoDice();
void PrintLeft(int playNum); // ����خ� ���a�H��
void SetPlayerLocation(int who, int where, int old = 0); //���a��m  player �s��m �¦�m(�@�}�l�]0�Y�i)
void SetLand(int where, int whose); //�]�w�g�a�Ҧ� �X���g�a player
void PrintRightBack(); //�k��خ�
void PrintRight();//�N�a�W��J
void PrintMenu();
void PrintRound(int r); //�^�X
void PrintTurn(int i); // ����� �q0�}�l
void PrintPlayerLand(int who, int a[]); // player ����array
void SetPlayerMoney(int who, int num); //player money
void SetPlayerProperty(int who, int num);// �]��
//------------------------------------------------------------
int PrintEsc(); // 1���s�� 2��Ū��
void PrintBank(Player& who); // 
void PrintStock(string name[], int price[], int updown[], Player& who); // �����R �t����
int PrintTool();
int SaleLand(vector<int> where, vector<int> level, vector<int> price);
int PrintOnLand(estate where, int whose, int who, int price); // �L�H�g�a �h whose = -1 �^�� 1���ʶR 0 �����
void PrintChance(string content);
void PrintDestiny(string content);
void PrintSign(string content, int num);
/*
�᭱�f
gotoxy(60, 14);
system("pause");
blank(55, 80, 10, 14);
*/
void PrintStop(int where);
int PrintInput(int which);//which = 1������  which = 2��������l
void victory(int t);
void PrintDie(int who);
