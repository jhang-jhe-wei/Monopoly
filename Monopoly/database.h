#pragma once
#include <string>
#include <vector>
using namespace std;
__declspec(selectany) int backGroundColor[5] = { 64 , 144 , 160 , 224 , 7};
__declspec(selectany) int wordColor[4] = { 12 , 9 , 10 , 14 };
__declspec(selectany) int stockChang[3] = { -1 , -1 , -1 };
__declspec(selectany) int oldStockPrice[3] = { 5000,3000,3000 };
__declspec(selectany) int currentStockPrice[3] = { 5000,3000,3000 };
__declspec(selectany) string locationName[28];
__declspec(selectany) string option[4] = { "�� �Y �� �l" , "�� �� �D ��" , "�i �J �� ��", "�� �� �� ��" }; 
__declspec(selectany) string stockName[3] = { "�겼����" , "�a���j��" , "�n�]��" };
class Map
{
public:
	Map(int _local, string _name, int _type);
	Map(int _local, string _name, int _type, int _price, int _tolls[4]);
	bool Roadblock;
	int local;
	string name;
	int type;
	int price;
	int tolls[4];
};

class estate
{
public:
	estate(int a, int b);
	int number;//local
	int level;
};

class Player
{
public:
	bool isDead = false;
	bool doubleDice = false;
	bool safetyMask = false;
	int total = 0;
	int loan = 0;
	int controlDice = 0;
	int number;
	int local;
	int money = 0;
	int deposit = 0;
	int stock[3] = { 0,0,0 };
	int buffer = 0;
	int counter = -1;
	int getAll();//�`�겣	
	int getDeposit();//�b�Ȧ檺����
	vector<estate> estates;//���a�֦����a��
};

