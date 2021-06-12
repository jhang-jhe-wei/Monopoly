#include"Print.h"
BOOL SetConsoleSize(int W, int H)
{
	BOOL ret;
	SMALL_RECT SR;
	SR.Top = 0;
	SR.Left = 0;
	SR.Bottom = H - 1;
	SR.Right = W - 1;
	ret = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &SR);
	if (!ret) return ret;

	COORD Sz;
	Sz.X = W;
	Sz.Y = H;

	return SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), Sz);
}
void SetCursorVisible(bool a)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 100;
	cci.bVisible = a; // �O�_�i��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void ConsoleFullScreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	/* �쪩�O�g�U���o��,���ھ� scan code �e�X���T��, �����n
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
	*/

}
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void getxy(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}
void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
//---------------------------------
void blank(int x1, int x2, int y1, int y2)
{
	for (int i = y1; i <= y2; i++)
	{
		gotoxy(x1, i);
		for (int j = x1; j < x2; j++)
		{
			cout << " ";
		}
	}
}
void PrintRec(int x, int y, int lenth, int width)
{
	gotoxy(x, y);
	cout << "�z ";
	for (int i = 0; i < width; i++) cout << "�w ";
	cout << "�{";
	for (int j = 0; j < lenth - 2; j++)
	{
		gotoxy(x, y + j + 1);
		cout << "�x";
		for (int i = 0; i < width * 2 + 1; i++) cout << " ";
		cout << "�x";
	}
	gotoxy(x, y + lenth - 1);
	cout << "�| ";
	for (int i = 0; i < width; i++) cout << "�w ";
	cout << "�}";
}
void PrintDice(int i)
{
	int x = 0, y = 0;
	getxy(x, y);
	switch (i)
	{
	case 1:
	{
		//1
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x       �x ";
		gotoxy(x, y + 2);
		cout << "�x   ��  �x ";
		gotoxy(x, y + 3);
		cout << "�x       �x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	case 2:
	{
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x     ���x ";
		gotoxy(x, y + 2);
		cout << "�x       �x ";
		gotoxy(x, y + 3);
		cout << "�x ��    �x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	case 3:
	{
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x     ���x ";
		gotoxy(x, y + 2);
		cout << "�x   ��  �x ";
		gotoxy(x, y + 3);
		cout << "�x ��    �x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	case 4:
	{
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 2);
		cout << "�x       �x ";
		gotoxy(x, y + 3);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	case 5:
	{
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 2);
		cout << "�x   ��  �x ";
		gotoxy(x, y + 3);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	case 6:
	{
		gotoxy(x, y);
		cout << "�z �w �w �w �{ ";
		gotoxy(x, y + 1);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 2);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 3);
		cout << "�x ��  ���x ";
		gotoxy(x, y + 4);
		cout << "�| �w �w �w �} ";
		break;
	}
	}
	gotoxy(x, y);
}
int RollDice()
{
	int num;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 6;
		PrintDice(num + 1);
		Sleep(35);
	}
	return num + 1;
}
int RollTwoDice()
{
	int num1, num2;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		gotoxy(58, 15);
		num1 = rand() % 6;
		PrintDice(num1 + 1);
		num2 = rand() % 6;
		gotoxy(68, 15);
		PrintDice(num2 + 1);
		Sleep(35);
	}
	return num1 + num2 + 2;
}
void PrintLeft(int playNum)
{
	gotoxy(2, 0);
	cout << "�z �w �w �w �w �w �{";
	gotoxy(2, 1);
	cout << "�x  Round    �x";
	gotoxy(2, 2);
	cout << "�| �w �w �w �w �w �}";
	int y = 0;
	for (int i = 0; i < playNum; i++)
	{
		y = 9 * i + 5;
		gotoxy(0, y);
		cout << "�z �w �w �w �w �w �w �w �{";
		gotoxy(0, y + 1);
		cout << "�x ";
		SetColor(backGroundColor[i]);
		cout << "       Player" << i + 1;
		SetColor();
		cout << "�x";
		gotoxy(0, y + 2);
		cout << "�x    �{��:$30000�x";
		gotoxy(0, y + 3);
		cout << "�x  �`�겣:$30000�x";
		gotoxy(0, y + 4);
		cout << "�u �w �s �w �s �w �s �w �t";
		gotoxy(0, y + 5);
		cout << "�x ���x ���x ���x ���x";
		gotoxy(0, y + 6);
		cout << "�u �w �q �w �q �w �q �w �t";
		gotoxy(0, y + 7);
		cout << "�x   �x   �x   �x   �x";
		gotoxy(0, y + 8);
		cout << "�| �w �r �w �r �w �r �w �}";
	}
}
void PrintRightBack()
{
	int x, y;
	x = 20;
	y = 0;
	gotoxy(x, y);
	cout << "�z �w �w �w �w �w �s";
	gotoxy(x, y + 1);
	cout << "�x           �x";
	gotoxy(x, y + 2);
	cout << "�u �w �w �w �w �w �q";
	gotoxy(x, y + 3);
	cout << "�x           �x";
	gotoxy(x, y + 4);
	cout << "�x  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << "�u �w �w �w �w �w �q";
	y = 35;
	gotoxy(x, y);
	cout << "�u �w �w �w �w �w �q";
	gotoxy(x, y + 1);
	cout << "�x           �x";
	gotoxy(x, y + 2);
	cout << "�u �w �w �w �w �w �q";
	gotoxy(x, y + 3);
	cout << "�x           �x";
	gotoxy(x, y + 4);
	cout << "�x  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << "�| �w �w �w �w �w �r";
	for (int i = 1; i < 7; i++)
	{
		x = 21 + 12 * i;
		y = 0;
		gotoxy(x, y);
		cout << " �w �w �w �w �w �s";
		gotoxy(x, y + 1);
		cout << "           �x";
		gotoxy(x, y + 2);
		cout << " �w �w �w �w �w �q";
		gotoxy(x, y + 3);
		cout << "           �x";
		gotoxy(x, y + 4);
		cout << "  �x  �x  �x  �x";
		gotoxy(x, y + 5);
		cout << " �w �w �w �w �w �r";
		y = 35;
		gotoxy(x, y);
		cout << " �w �w �w �w �w �s";
		gotoxy(x, y + 1);
		cout << "           �x";
		gotoxy(x, y + 2);
		cout << " �w �w �w �w �w �q";
		gotoxy(x, y + 3);
		cout << "           �x";
		gotoxy(x, y + 4);
		cout << "  �x  �x  �x  �x";
		gotoxy(x, y + 5);
		cout << " �w �w �w �w �w �r";
	}
	x = 105;
	y = 0;
	gotoxy(x, y);
	cout << " �w �w �w �w �w �{";
	gotoxy(x, y + 1);
	cout << "           �x";
	gotoxy(x, y + 2);
	cout << " �w �w �w �w �w �t";
	gotoxy(x, y + 3);
	cout << "           �x";
	gotoxy(x, y + 4);
	cout << "  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << "\b�q �w �w �w �w �w �t";
	y = 35;
	gotoxy(x, y + 1);
	cout << "           �x";
	gotoxy(x, y + 2);
	cout << " �w �w �w �w �w �t";
	gotoxy(x, y + 3);
	cout << "           �x";
	gotoxy(x, y + 4);
	cout << "  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << " �w �w �w �w �w �}";
	for (int i = 0; i < 5; i++)
	{
		x = 20;
		y = 5 + 5 * i;
		gotoxy(x, y + 1);
		cout << "�x           �x";
		gotoxy(x, y + 2);
		cout << "�u �w �w �w �w �w �t";
		gotoxy(x, y + 3);
		cout << "�x           �x";
		gotoxy(x, y + 4);
		cout << "�x  �x  �x  �x  �x";
		gotoxy(x, y + 5);
		cout << "�u �w �w �w �w �w �t";
		x = 104;
		gotoxy(x, y + 1);
		cout << "�x           �x";
		gotoxy(x, y + 2);
		cout << "�u �w �w �w �w �w �t";
		gotoxy(x, y + 3);
		cout << "�x           �x";
		gotoxy(x, y + 4);
		cout << "�x  �x  �x  �x  �x";
		gotoxy(x, y + 5);
		cout << "�u �w �w �w �w �w �t";
	}
	x = 20;
	y = 30;
	gotoxy(x, y + 1);
	cout << "�x           �x";
	gotoxy(x, y + 2);
	cout << "�u �w �w �w �w �w �t";
	gotoxy(x, y + 3);
	cout << "�x           �x";
	gotoxy(x, y + 4);
	cout << "�x  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << "�u �w �w �w �w �w �q";
	x = 104;
	gotoxy(x, y + 1);
	cout << "�x           �x";
	gotoxy(x, y + 2);
	cout << "�u �w �w �w �w �w �t";
	gotoxy(x, y + 3);
	cout << "�x           �x";
	gotoxy(x, y + 4);
	cout << "�x  �x  �x  �x  �x";
	gotoxy(x, y + 5);
	cout << "�q �w �w �w �w �w �t";
}
void SetPlayerLocation(int who, int where, int old)
{
	//�R���e�@�Ӧ�m 
	if (old >= 0 && old < 8)
	{
		gotoxy(22 + old * 12 + 3 * who, 4);
		cout << " ";
	}
	else if (old >= 8 && old < 14)
	{
		gotoxy(106 + 3 * who, 4 + 5 * (old - 7));
		cout << " ";
	}
	else if (old >= 14 && old < 22)
	{
		gotoxy(106 - (old - 14) * 12 + 3 * who, 39);
		cout << " ";
	}
	else if (old >= 22 && old < 28)
	{
		gotoxy(22 + 3 * who, 39 - 5 * (old - 21));
		cout << " ";
	}
	//��ܥثe��m 
	if (where >= 0 && where < 8)
	{
		gotoxy(22 + where * 12 + 3 * who, 4);
		SetColor(wordColor[who]);
		cout << who + 1;
		SetColor();
	}
	else if (where >= 8 && where < 14)
	{
		gotoxy(106 + 3 * who, 4 + 5 * (where - 7));
		SetColor(wordColor[who]);
		cout << who + 1;
		SetColor();
	}
	else if (where >= 14 && where < 22)
	{
		gotoxy(106 - (where - 14) * 12 + 3 * who, 39);
		SetColor(wordColor[who]);
		cout << who + 1;
		SetColor();
	}
	else if (where >= 22 && where < 28)
	{
		gotoxy(22 + 3 * who, 39 - 5 * (where - 21));
		SetColor(wordColor[who]);
		cout << who + 1;
		SetColor();
	}
}
void SetLand(int where, int whose)
{
	if (where >= 0 && where < 8)
	{
		gotoxy(24 + where * 12, 1);
		SetColor(backGroundColor[whose]);
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[where];
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		SetColor();
	}
	else if (where >= 8 && where < 14)
	{
		gotoxy(108, 1 + 5 * (where - 7));
		SetColor(backGroundColor[whose]);
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[where];
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		SetColor();
	}
	else if (where >= 14 && where < 22)
	{
		gotoxy(108 - (where - 14) * 12, 36);
		SetColor(backGroundColor[whose]);
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[where];
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		SetColor();
	}
	else if (where >= 22 && where < 28)
	{
		gotoxy(24, 36 - 5 * (where - 21));
		SetColor(backGroundColor[whose]);
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[where];
		for (int j = 8; j > locationName[where].size(); j -= 2)
		{
			cout << " ";
		}
		SetColor();
	}
}
void ReadFile(string fileName)
{
	fstream f1;
	f1.open(fileName, ios::in);
	int i;
	string t;
	if (!f1) cout << "open fail";
	else
	{
		getline(f1, t);
		for (int j = 0; j < 28; j++)
		{
			f1 >> i;
			f1 >> t;
			locationName[i] = t;
			getline(f1, t);
		}
	}
	f1.close();
}
void PrintRight()
{
	int x = 20, y = 0;
	//��t12 
	//�����t5 
	for (int i = 0; i < 8; i++)
	{
		gotoxy(x + 2 + i * 12, y + 1);
		cout << "0" << i;
		for (int j = 8; j > locationName[i].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[i];
	}
	for (int i = 8; i < 14; i++)
	{
		gotoxy(x + 86, y + 1 + (i - 7) * 5);
		if (i < 10) cout << "0";
		cout << i;
		for (int j = 8; j > locationName[i].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[i];
	}
	for (int i = 14; i < 22; i++)
	{
		gotoxy(x + 86 - (i - 14) * 12, y + 36);
		cout << i;
		for (int j = 8; j > locationName[i].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[i];
	}
	for (int i = 22; i < 28; i++)
	{
		gotoxy(x + 2, y + 36 - (i - 21) * 5);
		cout << i;
		for (int j = 8; j > locationName[i].size(); j -= 2)
		{
			cout << " ";
		}
		cout << locationName[i];
	}
}
void PrintPlayerLand(int who, int a[])
{
	int y = 9 * who + 12;
	int x = 2;
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x, y);
		if (a[i] < 10) cout << "0";
		cout << a[i];
		x += 4;
	}
}
void PrintMenu()
{
	int x = 49;
	int y = 23;
	PrintRec(x, y, 5, 8);
	PrintRec(x + 20, y, 5, 8);
	PrintRec(x, y + 5, 5, 8);
	PrintRec(x + 20, y + 5, 5, 8);
	gotoxy(x + 5, y + 2);
	cout << "�� �Y �� �l";
	gotoxy(x + 25, y + 2);
	cout << "�� �� �D ��";
	gotoxy(x + 25, y + 7);
	cout << "�� �� �� ��";
	gotoxy(x + 5, y + 7);
	cout << "�i �J �� ��";
}
void PrintRound(int r)
{
	gotoxy(11, 1);
	if (r < 10) cout << "0";
	cout << r;
}
void PrintTurn(int i)
{
	gotoxy(62, 6);
	cout << "���� Player ";
	SetColor(wordColor[i]);
	cout << i + 1;
	SetColor();
}
void SetPlayerMoney(int who, int num)
{
	gotoxy(11, 7 + who * 9);
	cout << num;
	int t = num;
	if (num < 0)
	{
		t *= -1;
		while (t < 1000)
		{
			cout << " ";
			t *= 10;
		}
		return;
	}
	if (num == 0)
	{
		cout << "    ";
		return;
	}
	while (t < 10000)
	{
		cout << " ";
		t *= 10;
	}
}
void SetPlayerProperty(int who, int num)
{
	gotoxy(11, 8 + who * 9);
	cout << num;
	int t = num;
	if (num < 0)
	{
		t *= -1;
		while (t < 1000)
		{
			cout << " ";
			t *= 10;
		}
		return;
	}
	if (num == 0)
	{
		cout << "    ";
		return;
	}
	while (t < 10000)
	{
		cout << " ";
		t *= 10;
	}
}
void ColorMenu(int choose, int color, string option[])
{
	int x = 49, y = 23;
	SetColor(color);
	switch (choose)
	{
	case 0:
	{
		gotoxy(x + 2, y + 1);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 2, y + 3);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 2, y + 2);
		cout << "   " << option[choose] << "  ";
		break;
	}
	case 1:
	{
		gotoxy(x + 22, y + 1);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 22, y + 3);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 22, y + 2);
		cout << "   " << option[choose] << "  ";
		break;
	}
	case 2:
	{
		gotoxy(x + 2, y + 6);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 2, y + 8);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 2, y + 7);
		cout << "   " << option[choose] << "  ";
		break;
	}
	case 3:
	{
		gotoxy(x + 22, y + 6);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 22, y + 8);
		for (int i = 0; i < 16; i++) cout << " ";
		gotoxy(x + 22, y + 7);
		cout << "   " << option[choose] << "  ";
		break;
	}
	}
	SetColor();
}
int PrintOnLand(estate where, int whose, int who, int price)
{
	gotoxy(55, 12);
	if (who != whose && whose != -1)
	{
		cout << locationName[where.number] << "�� ";
		SetColor(wordColor[whose]);
		cout << whose + 1;
		SetColor();
		cout << " ���g�a (���Ŭ�" << where.level << ")";
		gotoxy(60, 14);
		cout << "�A������I$" << price;
		gotoxy(60, 15);
		system("pause");
	}
	else
	{
		if (whose == -1)
		{
			gotoxy(60, 12);
			cout << locationName[where.number] << "�ثe�L�H�֦�";
			gotoxy(58, 14);
			cout << "�аݬO�_�ʶR? ($" << price << ")";
		}
		else
		{
			if (who == whose)
			{
				cout << locationName[where.number] << "���A���g�a (���Ŭ�" << where.level << ")";
				gotoxy(58, 14);
				cout << "�аݬO�_�ɯ�? ($" << price << ")";
			}
		}
		int choose = 1;
		char ch;
		int x = 64;
		gotoxy(x, 16);
		SetColor(240);
		cout << "�O";
		SetColor();
		gotoxy(x + 6, 16);
		cout << "�_";
		while (1)
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				if (ch == 75) //left
				{
					if (choose == 0)
					{
						gotoxy(x + 6 - 6 * choose, 16);
						cout << "�_";
						choose = 1;
						gotoxy(x + 6 - 6 * choose, 16);
						SetColor(240);
						cout << "�O";
						SetColor();
					}
				}
				else if (ch == 77) //right
				{
					if (choose == 1)
					{
						gotoxy(x + 6 - 6 * choose, 16);
						cout << "�O";
						choose = 0;
						gotoxy(x + 6 - 6 * choose, 16);
						SetColor(240);
						cout << "�_";
						SetColor();
					}
				}
			}
			else if (ch == 13)
			{
				blank(55, 85, 12, 16);
				return choose;
			}
		}
	}
	blank(55, 85, 12, 16);
	return 0;
}
void PrintChance(string content)
{
	gotoxy(64, 9);
	cout << "�� �|";
	int y = 11;
	while (content.size() > 36)
	{
		gotoxy(50, y);
		for (int i = 0; i < 36; i++)
		{
			cout << content[0];
			content.erase(content.begin());
		}
		y++;
	}
	gotoxy(50, y);
	cout << content;
	gotoxy(50, y + 1);
	system("pause");
	blank(64, 70, 9, 9);
	blank(50, 86, 11, y + 1);
}
void PrintDestiny(string content)
{
	gotoxy(64, 9);
	cout << "�R �B";
	int y = 11;
	while (content.size() > 36)
	{
		gotoxy(50, y);
		for (int i = 0; i < 36; i++)
		{
			cout << content[0];
			content.erase(content.begin());
		}
		y++;
	}
	gotoxy(50, y);
	cout << content;
	gotoxy(50, y + 1);
	system("pause");
	blank(64, 70, 9, 9);
	blank(50, 86, 11, y + 1);
}
void PrintBank(Player& who)
{
	gotoxy(60, 9);
	cout << "�� �� �� ��";
	gotoxy(61, 11);
	cout << "�� �� �� :";
	gotoxy(75, 9);
	cout << "�{�s�l�B: $" << who.getDeposit();
	gotoxy(75, 10);
	cout << "�ثe�t��: $" << who.loan;
	int choose = 0;
	char ch;
	int x = 56;
	gotoxy(x, 13);
	SetColor(240);
	cout << "�s��";
	SetColor();
	gotoxy(x + 7, 13);
	cout << "����";
	gotoxy(x + 14, 13);
	cout << "�ɶU";
	string op[3] = { "�s��" , "����" , "�ɶU" };
	while (1)
	{
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 75) //left
			{
				if (choose != 0)
				{	
					gotoxy(x + 7 * choose, 13);
					cout << op[choose];
					choose--;
					gotoxy(x + 7 * choose, 13);
					SetColor(240);
					cout << op[choose];
					SetColor();
				}
			}
			else if (ch == 77) //right
			{
				if (choose != 2)
				{
					gotoxy(x + 7 * choose, 13);
					cout << op[choose];
					choose++;
					gotoxy(x + 7 * choose, 13);
					SetColor(240);
					cout << op[choose];
					SetColor();
				}
			}
		}
		else if (ch == 13)
		{
			blank(50, 95, 11, 14);
			break;
		}
		else if (ch == 27) //Esc
		{
			blank(50, 95, 9, 14);
			return ;
		}
	}
	int num;
	SetCursorVisible(true);
	if (choose == 0) // �s��
	{
		gotoxy(60, 11);
		cout << "�п�J���B:";
		while (1)
		{
			gotoxy(61, 12);
			cin >> num;
			if (num == 0) break;
			if (num <= who.money && num > 0)
			{
				//�s�ھާ@
				who.buffer += num;
				who.money -= num;
				break;
			}
			else
			{
				gotoxy(59, 11);
				cout << "�п�J�A����B:";
				gotoxy(61, 12);
				for (int i = 0; i < 10; i++)cout << " ";
			}
		}
	}
	else if (choose == 1) //����
	{
		gotoxy(60, 11);
		cout << "�п�J���B:";
		while (1)
		{
			gotoxy(61, 12);
			cin >> num;
			if (num == 0) break;
			if (num <= who.getDeposit() && num > 0)
			{
				//���ھާ@
				who.buffer -= num;
				who.money += num;
				break;
			}
			else
			{
				gotoxy(59, 11);
				cout << "�п�J�A����B:";
				gotoxy(61, 12);
				for (int i = 0; i < 10; i++)cout << " ";
			}
		}
	}
	else if (choose == 2)	// �ɴ�
	{
		gotoxy(60, 11);
		cout << "�п�J���B:";
		while (1)
		{
			gotoxy(61, 12);
			cin >> num;
			if (num == 0) break;
			if (who.loan+num <= who.total && num > 0)
			{
				if (who.counter == -1)
				{
					who.counter = 3;
				}
				who.loan += num;
				who.deposit += num;
				break;
			}
			else
			{
				gotoxy(59, 11);
				cout << "�п�J�A����B:";
				gotoxy(61, 12);
				for (int i = 0; i < 10; i++)cout << " ";
			}
		}
	}
	SetCursorVisible(false);
	blank(50, 95, 9, 14);
	return;
}
int PrintTool()
{
	int x = 49;
	int y = 23;
	string tmp[4] = { "   �� ��   " , "�� �� �� �l" , "�� �� �� �l" , " �� �@ �n  " };
	PrintRec(x, y, 5, 8);
	PrintRec(x + 20, y, 5, 8);
	PrintRec(x, y + 5, 5, 8);
	PrintRec(x + 20, y + 5, 5, 8);
	gotoxy(x + 5, y + 2);
	cout << "   �� ��   ";
	gotoxy(x + 25, y + 2);
	cout << "�� �� �� �l";
	gotoxy(x + 25, y + 3);
	cout << "   $2000    ";
	gotoxy(x + 5, y + 7);
	cout << "�� �� �� �l";
	gotoxy(x + 5, y + 8);
	cout << "   $500    ";
	gotoxy(x + 25, y + 7);
	cout << " �� �@ �n  ";
	gotoxy(x + 25, y + 8);
	cout << "   $3000    ";
	int choose = 0, t = 0;
	ColorMenu(choose, 240, tmp);
	SetColor(240);
	gotoxy(x + 5, y + 3);
	cout << "   $3000    ";
	SetColor();
	while (1)
	{
		char ch;
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			switch (ch)
			{
			case 72: // �W 
			{
				if (choose / 2 == 1) choose -= 2;
				break;
			}
			case 80: //�U 
			{
				if (choose / 2 == 0) choose += 2;
				break;
			}
			case 75: //�� 
			{
				if (choose % 2 == 1) choose--;
				break;
			}
			case 77: // �k 
			{
				if (choose % 2 == 0) choose++;
				break;
			}
			}
			if (t != choose)
			{
				ColorMenu(t, 7, tmp);
				SetColor();
				switch (t)
				{
				case 0:
				{
					gotoxy(x + 5, y + 3);
					cout << "   $3000    ";
					break;
				}
				case 1:
				{
					gotoxy(x + 25, y + 3);
					cout << "   $2000    ";
					break;
				}
				case 2:
				{
					gotoxy(x + 5, y + 8);
					cout << "   $500    ";
					break;
				}
				case 3:
				{
					gotoxy(x + 25, y + 8);
					cout << "   $3000    ";
					break;
				}
				}
				t = choose;
				ColorMenu(t, 240, tmp);
				SetColor(240);
				switch (t)
				{
				case 0:
				{
					gotoxy(x + 5, y + 3);
					cout << "   $3000    ";
					break;
				}
				case 1:
				{
					gotoxy(x + 25, y + 3);
					cout << "   $2000    ";
					break;
				}
				case 2:
				{
					gotoxy(x + 5, y + 8);
					cout << "   $500    ";
					break;
				}
				case 3:
				{
					gotoxy(x + 25, y + 8);
					cout << "   $3000    ";
					break;
				}
				}
				SetColor();
			}
		}
		else if (ch == 13) //Enter
		{
			return choose;
		}
		else if (ch == 27) //ESC
		{
			return -1;
		}
	}
}
int SaleLand(vector<int> where, vector<int> level, vector<int> price)
{
	int num = where.size();
	gotoxy(60, 9);
	cout << "�� �� �g �a";
	PrintRec(52, 12, 3, 6);
	PrintRec(65, 12, 3, 3);
	PrintRec(72, 12, 3, 3);
	int index = 0;
	gotoxy(54, 13);
	cout << where[index] << "." << locationName[where[index]];
	gotoxy(67, 13);
	cout << "lv";
	gotoxy(69, 13);
	cout << level[index];
	gotoxy(74, 13);
	cout << "$" << price[index];
	while (1)
	{
		char ch;
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 75) // left
			{
				if (index == 0) index = num - 1;
				else index--;
			}
			else if (ch == 77) // right
			{
				index = (index + 1) % num;
			}
			else continue;
			//�M��
			gotoxy(54, 13); cout << "          ";
			gotoxy(75, 13); cout << "     ";
			//���
			gotoxy(54, 13);
			cout << where[index] << "." << locationName[where[index]];
			gotoxy(69, 13);
			cout << level[index];
			gotoxy(74, 13);
			cout << "$" << price[index];
		}
		else if (ch == 13) // ENTER
		{
			int choose = 1; // 1���R  0����
			char ch;
			int x = 64;
			gotoxy(x, 16);
			SetColor(240);
			cout << "�O";
			SetColor();
			gotoxy(x + 6, 16);
			cout << "�_";
			while (1)
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					if (ch == 75) //left
					{
						if (choose == 0)
						{
							gotoxy(x + 6 - 6 * choose, 16);
							cout << "�_";
							choose = 1;
							gotoxy(x + 6 - 6 * choose, 16);
							SetColor(240);
							cout << "�O";
							SetColor();
						}
					}
					else if (ch == 77) //right
					{
						if (choose == 1)
						{
							gotoxy(x + 6 - 6 * choose, 16);
							cout << "�O";
							choose = 0;
							gotoxy(x + 6 - 6 * choose, 16);
							SetColor(240);
							cout << "�_";
							SetColor();
						}
					}
				}
				else if (ch == 13)
				{
					if (choose == 0)
					{
						blank(64, 80, 15, 16);
						break;
					}
					else
					{
						blank(50, 90, 9, 16);
						return where[index];
					}
				}
			}
		}
	}
	return 0;
}
void PrintStock(string name[], int price[], int updown[], Player& who)
{
	gotoxy(75, 9);
	int num = who.getDeposit();
	cout << "�{�s�l�B: $" << num << "    ";
	gotoxy(60, 9);
	cout << "�� �� �� ��";
	gotoxy(54, 11);
	cout << "�Ѳ��W��       ����      �i��";
	PrintRec(50, 12, 3, 7);
	PrintRec(65, 12, 3, 5);
	PrintRec(76, 12, 3, 3);
	int index = 0;
	gotoxy(52, 13);
	cout << name[index];
	gotoxy(67, 13);
	if (updown[index] == 2)//����
	{
		SetColor(79);
	}
	else if (updown[index] == 3) //�^��
	{
		SetColor(47);
	}
	else if (updown[index] == -1)
	{
		SetColor();
	}
	else if (updown[index] == 1) SetColor(12);
	else if (updown[index] == 0) SetColor(2);
	cout << "$" << price[index];
	SetColor();
	gotoxy(78, 13);
	cout << who.stock[index];
	gotoxy(86, 13);
	cout << "1 / 3";
	while (1)
	{
		gotoxy(75, 9);
		int num = who.getDeposit();
		cout << "�{�s�l�B: $" << num << "    ";
		char ch;
		ch = _getch();
		if (ch == 27) //ESC
		{
			blank(50, 95, 9, 14);
			break;
		}
		else if (ch == -32)
		{
			ch = _getch();
			if (ch == 75) // left
			{
				if (index == 0) index = 2;
				else index--;
			}
			else if (ch == 77) // right
			{
				index = (index + 1) % 3;
			}
			else continue;
			//�M��
			gotoxy(52, 13); cout << "             ";
			gotoxy(67, 13); cout << "        ";
			gotoxy(78, 13); cout << "   ";
			//���
			gotoxy(52, 13);
			cout << name[index];
			gotoxy(67, 13);
			if (updown[index] == 2)//����
			{
				SetColor(79);
			}
			else if (updown[index] == 3) //�^��
			{
				SetColor(47);
			}
			else if (updown[index] == -1)
			{
				SetColor();
			}
			else if (updown[index] == 1) SetColor(12);
			else if (updown[index] == 0) SetColor(2);
			cout << "$" << price[index];
			SetColor();
			gotoxy(78, 13);
			cout << who.stock[index];
			gotoxy(86, 13);
			cout << index + 1;
		}
		else if (ch == 13) // ENTER
		{
			int choose = 1; // 1���R  0����
			char ch;
			int x = 64;
			gotoxy(x, 16);
			SetColor(240);
			cout << "�R";
			SetColor();
			gotoxy(x + 6, 16);
			cout << "��";
			while (1)
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					if (ch == 75) //left
					{
						if (choose == 0)
						{
							gotoxy(x + 6 - 6 * choose, 16);
							cout << "��";
							choose = 1;
							gotoxy(x + 6 - 6 * choose, 16);
							SetColor(240);
							cout << "�R";
							SetColor();
						}
					}
					else if (ch == 77) //right
					{
						if (choose == 1)
						{
							gotoxy(x + 6 - 6 * choose, 16);
							cout << "�R";
							choose = 0;
							gotoxy(x + 6 - 6 * choose, 16);
							SetColor(240);
							cout << "��";
							SetColor();
						}
					}
				}
				else if (ch == 13)
				{
					blank(55, 85, 15, 16);
					gotoxy(62, 15);
					if (choose == 0 && who.stock[index] == 0)
					{
						cout << "�����ѼƬ��s�L�k�X��";
						gotoxy(60, 16);
						system("pause");
						blank(55, 90, 15, 16);
						break;
					}
					SetCursorVisible(true);
					cout << "�п�J�ƶq:";
					int num;
					while (1)
					{
						gotoxy(68, 16);
						cin >> num;
						if (num == 0) break;
						if (choose == 1)
						{
							if (num * price[index] <= who.getDeposit() && num > 0) break;
						}
						else
						{
							if (num <= who.stock[index]) break;
						}
						gotoxy(59, 15);
						cout << "�п�J�A��ƶq:";
						gotoxy(68, 16);
						for (int i = 0; i < 10; i++) cout << " ";
					}
					//num ���R��ƶq
					if (choose == 1)
					{
						//�R
						if (price[index] * num <= who.getDeposit())
						{
							who.buffer -= (price[index] * num);
							who.stock[index] += num;
						}
					}
					else if (choose == 0)
					{
						//��
						if (who.stock[index] >= num)
						{
							who.buffer += (price[index] * num);
							who.stock[index] -= num;
						}
					}
					blank(55, 90, 15, 16);
					SetCursorVisible(false);
					break;
				}
			}
			gotoxy(78, 13);
			cout << who.stock[index];
		}
	}
	return;
}
int PrintEsc()
{
	int y = 60, x = 9;
	SetColor(9);
	gotoxy(y, x);
	cout << "�� �� �� �� �� �� �� �� �� ";
	gotoxy(y, x + 1);
	cout << "��               �� ";
	gotoxy(y, x + 2);
	cout << "�� �� �� �� �� �� �� �� �� ";
	gotoxy(y, x + 3);
	cout << "��               �� ";
	gotoxy(y, x + 4);
	cout << "�� �� �� �� �� �� �� �� �� ";
	gotoxy(y, x + 5);
	cout << "��               �� ";
	gotoxy(y, x + 6);
	cout << "�� �� �� �� �� �� �� �� �� ";
	gotoxy(y, x + 7);
	cout << "��               �� ";
	gotoxy(y, x + 8);
	cout << "�� �� �� �� �� �� �� �� �� ";
	gotoxy(y, x + 9);
	cout << "��               �� ";
	gotoxy(y, x + 10);
	cout << "�� �� �� �� �� �� �� �� �� ";
	SetColor(112);
	string out[5];
	out[0] = "�~��C��";
	out[1] = "���s�}�l";
	out[2] = "���}�C��";
	out[3] = "�s���ɮ�";
	out[4] = "Ū���ɮ�";
	gotoxy(y + 5, x + 1);
	cout << out[0];
	SetColor();
	gotoxy(y + 5, x + 3);
	cout << out[1];
	gotoxy(y + 5, x + 5);
	cout << out[2];
	gotoxy(y + 5, x + 7);
	cout << out[3];
	gotoxy(y + 5, x + 9);
	cout << out[4];
	int choose = 1;
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 72)
			{
				if (choose != 1)
				{
					gotoxy(y + 5, x - 1 + choose * 2);
					cout << out[choose - 1];
					choose--;
					gotoxy(y + 5, x - 1 + choose * 2);
					SetColor(112);
					cout << out[choose - 1];
					SetColor();
				}
			}
			if (ch == 80)
			{
				if (choose != 5)
				{
					gotoxy(y + 5, x - 1 + choose * 2);
					cout << out[choose - 1];
					choose++;
					gotoxy(y + 5, x - 1 + choose * 2);
					SetColor(112);
					cout << out[choose - 1];
					SetColor();
				}
			}
		}
		else if (ch == 13)
		{
			blank(60, 80, 9, 20);
			if (choose == 1)//�~��C��
			{
				return 0;
			}
			else if (choose == 2)//���s�}�l
			{
				return -1;
				//reset
			}
			else if (choose == 3)//���}�C��
			{
				system("cls");
				exit(1);
			}
			else if (choose == 4)//�s��
			{
				return 1;
			}
			else if (choose == 5)//Ū��
			{
				return 2;
			}
		}
		else if (ch == 27) // ESC
		{
			blank(60, 80, 9, 20);
			return 0;
		}
	}
}
void PrintStop(int where)
{
	if (where >= 0 && where < 8)
	{
		gotoxy(22 + where * 12, 3);
		SetColor(224);
		cout << "   ����   ";
		SetColor();
	}
	else if (where >= 8 && where < 14)
	{
		gotoxy(106, 3 + 5 * (where - 7));
		SetColor(224);
		cout << "   ����   ";
		SetColor();
	}
	else if (where >= 14 && where < 22)
	{
		gotoxy(106 - (where - 14) * 12, 38);
		SetColor(224);
		cout << "   ����   ";
		SetColor();
	}
	else if (where >= 22 && where < 28)
	{
		gotoxy(22, 38 - 5 * (where - 21));
		SetColor(224);
		cout << "   ����   ";
		SetColor();
	}
}
void PrintSign(string content, int num)
{
	int len;
	int y = 10;
	if (num == 2) y = 12;
	len = content.size();
	gotoxy(68 - len / 2, y);
	cout << content;
}
void PrintDie(int who)
{
	gotoxy(3, 7 + who * 9);
	cout << "   �}���F QQ ";
	gotoxy(3, 8 + who * 9);
	cout << "   �}���F QQ ";
}
int PrintInput(int which)
{
	int num;
	SetCursorVisible(true);
	if (which == 1) // ����
	{
		gotoxy(59, 11);
		cout << "�п�J��m���ٮy��:";
		gotoxy(68, 12);
		cin >> num;
		while (num < 0) num += 28;
		if (num > 27) num %= 28;
	}
	else if (which == 2) // ������l
	{
		gotoxy(61, 11);
		cout << "�п�J��l�I��:";
		gotoxy(68, 12);
		cin >> num;
		while (num <= 0) num += 6;
		if (num > 6) num %= 6;
	}
	SetCursorVisible(false);
	blank(56, 80, 11, 12);
	return num;
}
void victory(int t)
{
	int x = 30, y = 15;
	int i = 1;
	system("cls");
	Sleep(500);
	gotoxy(x, y);
	if (t == 1)
	{
		SetColor(12);
		cout << "  �i�i�i�i�i�i��   �i�i��              �i�i�i�i�i��   �i�i��       �i�i�� �i�i�i�i�i�i�i�� �i�i�i�i�i�i��           �i�i�� "; gotoxy(x, y + i); i++; cout <<
			"  �i�i�������������i�i�� �i�i��            �i�i�������������i�i�� �����i�i��   �i�i������ �i�i���������������������� �i�i�������������i�i��       �i�i�i�� "; gotoxy(x, y + i); i++; cout <<
			"  �i�i�i�i�i�i������ �i�i��            �i�i�i�i�i�i�i��   �����i�i�i�i������   �i�i�i�i�i��     �i�i�i�i�i�i������       �����i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i������������������   �i�i��            �i�i�������������i�i��     �����i�i������     �i�i��������������     �i�i�������������i�i��         �i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i��           �i�i�i�i�i�i�i��  �i�i��     �i�i��       �i�i��       �i�i�i�i�i�i�i�� �i�i��     �i�i��         �i�i��"; gotoxy(x, y + i); i++; cout <<
			"  ����������           ������������������������������  ����������     ����������       ����������       ������������������������������ ����������     ����������         ����������";
	}
	else if (t == 2)
	{
		SetColor(9);
		cout << "  �i�i�i�i�i�i��   �i�i��              �i�i�i�i�i��   �i�i��       �i�i�� �i�i�i�i�i�i�i�� �i�i�i�i�i�i��      �i�i�i�i�i�i�� "; gotoxy(x, y + i); i++; cout <<
			"  �i�i�������������i�i�� �i�i��            �i�i�������������i�i�� �����i�i��   �i�i������ �i�i���������������������� �i�i�������������i�i��    ���������������������i�i�� "; gotoxy(x, y + i); i++; cout <<
			"  �i�i�i�i�i�i������ �i�i��            �i�i�i�i�i�i�i��   �����i�i�i�i������   �i�i�i�i�i��     �i�i�i�i�i�i������      �i�i�i�i�i������"; gotoxy(x, y + i); i++; cout <<
			"  �i�i������������������   �i�i��            �i�i�������������i�i��     �����i�i������     �i�i��������������     �i�i�������������i�i��    �i�i������������������ "; gotoxy(x, y + i); i++; cout <<
			"  �i�i��           �i�i�i�i�i�i�i��  �i�i��     �i�i��       �i�i��       �i�i�i�i�i�i�i�� �i�i��     �i�i��    �i�i�i�i�i�i�i��"; gotoxy(x, y + i); i++; cout <<
			"  ����������           ������������������������������  ����������     ����������       ����������       ������������������������������ ����������     ����������    ������������������������������";
	}
	else if (t == 3)
	{
		SetColor(10);
		cout << "  �i�i�i�i�i�i��   �i�i��              �i�i�i�i�i��   �i�i��       �i�i�� �i�i�i�i�i�i�i�� �i�i�i�i�i�i��      �i�i�i�i�i�i�� "; gotoxy(x, y + i); i++; cout <<
			"  �i�i�������������i�i�� �i�i��            �i�i�������������i�i�� �����i�i��   �i�i������ �i�i���������������������� �i�i�������������i�i��    ���������������������i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i�i�i�i�i������ �i�i��            �i�i�i�i�i�i�i��   �����i�i�i�i������   �i�i�i�i�i��     �i�i�i�i�i�i������      �i�i�i�i�i������"; gotoxy(x, y + i); i++; cout <<
			"  �i�i������������������   �i�i��            �i�i�������������i�i��     �����i�i������     �i�i��������������     �i�i�������������i�i��      �����������������i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i��           �i�i�i�i�i�i�i��  �i�i��     �i�i��       �i�i��       �i�i�i�i�i�i�i�� �i�i��     �i�i��    �i�i�i�i�i�i������"; gotoxy(x, y + i); i++; cout <<
			"  ����������           ������������������������������  ����������     ����������       ����������       ������������������������������ ����������     ����������    �������������������������� ";
	}
	else if (t == 4)
	{
		SetColor(14);
		cout << "  �i�i�i�i�i�i��   �i�i��              �i�i�i�i�i��   �i�i��       �i�i�� �i�i�i�i�i�i�i�� �i�i�i�i�i�i��      �i�i��     �i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i�������������i�i�� �i�i��            �i�i�������������i�i�� �����i�i��   �i�i������ �i�i���������������������� �i�i�������������i�i��    �i�i��     �i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i�i�i�i�i������ �i�i��            �i�i�i�i�i�i�i��   �����i�i�i�i������   �i�i�i�i�i��     �i�i�i�i�i�i������    �i�i�i�i�i�i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i������������������   �i�i��            �i�i�������������i�i��     �����i�i������     �i�i��������������     �i�i�������������i�i��    ���������������������i�i��"; gotoxy(x, y + i); i++; cout <<
			"  �i�i��           �i�i�i�i�i�i�i��  �i�i��     �i�i��       �i�i��       �i�i�i�i�i�i�i�� �i�i��     �i�i��              �i�i��"; gotoxy(x, y + i); i++; cout <<
			"  ����������           ������������������������������  ����������     ����������       ����������       ������������������������������ ����������     ����������              ����������";
	}
	i += 2;
	gotoxy(x, y + i);
	SetColor(15);
	cout <<
		"                                     �i�i��         �i�i��  �i�i��  �i�i�i��      �i�i��"; gotoxy(x, y + i); i++; cout <<
		"                                     �i�i��         �i�i��  �i�i��  �i�i�i�i��    �i�i��"; gotoxy(x, y + i); i++; cout <<
		"                                     �i�i��   �i��   �i�i��  �i�i��  �i�i�����i�i��  �i�i��"; gotoxy(x, y + i); i++; cout <<
		"                                     �i�i�� �i�i�i�� �i�i��  �i�i��  �i�i�� �����i�i�ߢi�i��"; gotoxy(x, y + i); i++; cout <<
		"                                     �����i�i�i�����i�i�i������  �i�i��  �i�i��  �����i�i�i�i��"; gotoxy(x, y + i); i++; cout <<
		"                                       �������������� ��������������    ����������  ����������    ������������������";
	gotoxy(x + 45, y + i + 1);
	system("pause");
}