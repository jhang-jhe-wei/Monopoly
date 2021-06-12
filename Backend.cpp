#include "Backend.h"
Backend::Backend(string name)
{	
	ReadFile(name);
	file.open(name,ios::in);
	string temp;
	file >> mapName;
	file >> round;
	file >> amount_of_player;
	players = new Player[amount_of_player];	
	while (file >> temp)
	{		
		if (temp == "playerstate")break;
		int local = stoi(temp);
		string name;
		int type;		
		file >> name;
		file >> type;		
		if (type == 1) 
		{
			int price;
			int tolls[4];
			file >> price;
			for (int i = 0; i < 4; i++) 
			{
				file >> tolls[i];
			}
			Map map(local,name,type,price,tolls);
			maps.push_back(map);			
		}
		else 
		{
			Map map(local, name, type);
			maps.push_back(map);
		}		
	}	
	if (temp == "playerstate") 
	{
		getline(file, temp);
		playerState = stoi(temp);
		counter = playerState;
		for (int i = 0; i < amount_of_player; i++) 
		{				
			int number;
			int local;
			int money;
			file >> number;
			file >> local;
			file >> money;
			players[i].number = number;
			players[i].local = local;
			players[i].money = money;			
			getline(file, temp);			
			string buffer;
			bool flag = false;
			if(temp.size()!=0)
			{
				int a;
				int b;
				for (int j = 1; j < temp.size(); j++)
				{
					if (temp.at(j) != ' ')
					{
						buffer += temp.at(j);
					}
					else
					{
						if (!flag)
						{
							a = stoi(buffer);
							flag = true;
						}
						else
						{
							b = stoi(buffer);
							estate c(a, b);
							players[i].estates.push_back(c);
							flag = false;
						}
						buffer.clear();
					}
				}
				b = stoi(buffer);
				estate c(a, b);
				players[i].estates.push_back(c);
				buffer.clear();
			}			
		}		
	}
	for (int i = 0; i < amount_of_player; i++) //避免玩家位置超過地圖範圍
	{
		players[i].local %= maps.size();
	}
}

int Backend::getEsatate(Player a)
{	
		int sum = 0;
		for (int i = 0; i < a.estates.size(); i++)
		{
			sum += (a.estates.at(i).level + 1)*maps.at(a.estates.at(i).number).price;
		}
		return sum;	
}

void Backend::printCurrentPlayer()
{
	for (int i = 0; i < amount_of_player; i++) 
	{
		if (players[i].isDead)
		{
			//cout << "玩家" << i << "已破產" << endl;
			continue;
		}
		//cout << "No." << i << " \t位置:" << players[i].local << " \t金錢:" << players[i].money << endl;
		for (int j = 0; j < players[i].estates.size(); j++) 
		{			
			//cout << "地產位置:" << players[i].estates.at(j).number << "\t等級:" << players[i].estates.at(j).level << endl;
		}
		//cout << endl << endl;
	}
}

void Backend::rotation()
{
	playerState++;
	counter++;			
	playerState %= amount_of_player;
	while (players[playerState].isDead)
	{		
		playerState++;
		counter++;
		playerState %= amount_of_player;
	}
	if (counter >= amount_of_player)
	{
		
		currentStockPrice[0]+=rand() % 1000-500;
		currentStockPrice[1] += rand() % 1000 - 500;
		currentStockPrice[2] += rand() % 1000 - 500;

		//國票金融
		for (int i = 0; i < 3; i++) 
		{
			
			if (currentStockPrice[i] < 0) 
			{
				currentStockPrice[i] = 0;
				stockChang[i] = 3;
			}
			else if (currentStockPrice[i] - oldStockPrice[i] > 0)
			{
				if (currentStockPrice[i] - oldStockPrice[i] >= oldStockPrice[i]*0.1)
				{
					currentStockPrice[i] = oldStockPrice[i] + oldStockPrice[i] * 0.1;
					stockChang[i] = 2;
				}
				else 
				{
					stockChang[i] = 1;
				}
			}
			else if (currentStockPrice[i] - oldStockPrice[i] < 0)
			{
				if (currentStockPrice[i] - oldStockPrice[i] <= oldStockPrice[i] * 0.1)
				{
					currentStockPrice[i] = oldStockPrice[i] - oldStockPrice[i] * 0.1;
					stockChang[i] = 3;
				}
				else
				{
					stockChang[i] = 0;
				}
			}
			else if (currentStockPrice[i] - oldStockPrice[i] == 0) 
			{
				stockChang[i] = -1;
			}
			oldStockPrice[i] = currentStockPrice[i];
			if (currentStockPrice[i] < 0)
			{
				currentStockPrice[i] = 0;
				stockChang[i] = 3;
			}
		}
		for (int i = 0; i < amount_of_player; i++) 
		{
			if (players[i].loan > 0)
			{
				players[i].counter--;
			}
		}
		//股票更新
		counter = 0;
		round--;
	}	
}

void Backend::going()
{	
	int buffer = 0;
	if (players[playerState].controlDice != 0 && players[playerState].doubleDice)
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
		gotoxy(58, 15);
		PrintDice(players[playerState].controlDice);
		gotoxy(68, 15);
		PrintDice(players[playerState].controlDice);
		buffer = players[playerState].controlDice * 2;
		players[playerState].controlDice = 0;
		players[playerState].doubleDice = false;
	}
	else if (players[playerState].controlDice != 0) //遙控骰子
	{
		buffer = players[playerState].controlDice;
		RollDice();
		PrintDice(players[playerState].controlDice);
		players[playerState].controlDice = 0;
	}
	else if (players[playerState].doubleDice) //雙倍骰子
	{
		buffer = RollTwoDice();
		players[playerState].doubleDice = false;
	}
	else//正常擲骰子
	{
		buffer = RollDice();
	}
	for (int i = 0; i < buffer; i++) 
	{		
		oldLocal = players[playerState].local;
		players[playerState].local++;
		if (players[playerState].local >= maps.size()) //經過原點
		{
			players[playerState].local %= maps.size();
			SetPlayerLocation(playerState, players[playerState].local, oldLocal);
			players[playerState].deposit += 500;			
			players[playerState].deposit += players[playerState].deposit*0.25;//定存利息為25%
			players[playerState].deposit += players[playerState].buffer;//把暫存金額加入定存
			players[playerState].buffer = 0;//暫存歸零
		}
		else
		{
			SetPlayerLocation(playerState, players[playerState].local, oldLocal);
		}			
		if (maps.at(players[playerState].local).Roadblock&&players[playerState].local<maps.size())
		{				
			maps.at(players[playerState].local).Roadblock = false;
			int x = players[playerState].local;
			if (x >= 0 && x < 8)
			{
				gotoxy(22 + x * 12, 3);
				cout << "          ";
			}
			else if (x >= 8 && x < 14)
			{
				gotoxy(106, 3 + 5 * (x - 7));
				cout << "          ";
			}
			else if (x >= 14 && x < 22)
			{
				gotoxy(106 - (x - 14) * 12, 38);
				cout << "          ";
			}
			else if (x >= 22 && x < 28)
			{
				gotoxy(22, 38 - 5 * (x - 21));
				cout << "          ";
			}
			break;
		}			
		Sleep(300);
	}		
	blank(55, 80, 15, 20);
}

void Backend::play()
{
	PrintLeft(amount_of_player);
	PrintRightBack();
	PrintMenu();
	//ReadFile("basemap.txt");
	PrintRight();
	int choose = 0;
	int t = choose;
	int yesorno = 0;
	char ch;	
	ColorMenu(t, 240, option);
	//PrintDie(1);
	while (1)
	{				
		for (int i = 0; i < amount_of_player; i++)
		{			
			SetPlayerLocation(i, players[i].local, oldLocal);
			int lv[4] = {0,0,0,0};			
			if (!players[i].isDead) SetPlayerMoney(i, players[i].money);
			if (!players[i].isDead) SetPlayerProperty(i, players[i].getAll()+getEsatate(players[i]));
			players[i].total = players[i].getAll() + getEsatate(players[i]);
			for (int j = 0; j < players[i].estates.size(); j++)
			{
				SetLand(players[i].estates.at(j).number, i);
				lv[players[i].estates.at(j).level]++;
			}
			PrintPlayerLand(i, lv);
		}		
		if (round < 0) //判斷回合終了
		{
			int max = 0;
			for (int i = 1; i < amount_of_player; i++)
			{
				int a = players[i].getAll()- players[i].loan;				
				a += getEsatate(players[i]);
				
				int b = players[max].getAll()- players[max].loan;				
				b += getEsatate(players[max]);
				
				if (a > b)
				{
					max = i;
				}
			}
			victory(max + 1);			
			break;
		}
		int alive = 0;//判斷是否其他人都破產
		for (int i = 0; i < amount_of_player; i++)
		{
			if (!players[i].isDead)
			{
				alive++;
			}
			else
			{
				PrintDie(i);
			}
		}
		if (alive == 1)
		{
			//cout << "勝利者為";
			for (int i = 0; i < amount_of_player; i++)
			{
				if (!players[i].isDead)
				{
					victory(i + 1);
					//cout << "玩家" << i << endl;
					break;
				}
			}
			break;
		}
		PrintRound(round);
		PrintTurn(playerState);
		bool isEmpty = true;		
		if (players[playerState].counter == 0)
		{
			PrintSign("期限已到!由現金還款", 2);
			gotoxy(60, 14);
			system("pause");
			blank(55, 80, 10, 14);
			players[playerState].money -= players[playerState].loan;
			players[playerState].loan = 0;
			players[playerState].counter = -1;
			continue;
		}
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			switch (ch)
			{
			case 72: // 上 
			{
				if (choose / 2 == 1) choose -= 2;
				break;
			}
			case 80: //下 
			{
				if (choose / 2 == 0) choose += 2;
				break;
			}
			case 75: //左 
			{
				if (choose % 2 == 1) choose--;
				break;
			}
			case 77: // 右 
			{
				if (choose % 2 == 0) choose++;
				break;
			}
			}
			if (t != choose)
			{
				ColorMenu(t, 7, option);
				t = choose;
				ColorMenu(t, 240, option);
			}
		}
		else if (ch == 13) //Enter
		{
			switch (choose)
			{
			case 0:
			{

				if (players[playerState].money < 0) 
				{
					PrintSign("現金無法負債，您必須先提款", 1);
					gotoxy(60, 14);
					system("pause");
					blank(55, 80, 10, 14);
					continue;
				}
				gotoxy(64, 15);			
				oldLocal = players[playerState].local;
				going();
				SetPlayerLocation(playerState, players[playerState].local, oldLocal);
				if (maps.at(players[playerState].local).type == 1) //判斷位置
				{
					for (int i = 0; i < amount_of_player; i++) //判斷是否有地主
					{
						for (int j = 0; j < players[i].estates.size(); j++)
						{
							if (players[i].estates.at(j).number == players[playerState].local)
							{
								//cout << "找到土地所有人" << endl;
								if (i == playerState) //土地為自己的
								{
									yesorno = PrintOnLand(players[i].estates.at(j), i, playerState, maps.at(players[i].estates.at(j).number).price);
									//cout << "是否要升級?" << endl;									
									if (yesorno == 1) //升級
									{
										if (players[playerState].money >= maps.at(players[playerState].local).price&&players[playerState].estates.at(j).level < 3)
										{
											//cout << "已升級" << endl;
											players[playerState].money -= maps.at(players[playerState].local).price;
											players[playerState].estates.at(j).level++;
										}
										else
										{
											//cout << "金錢不足或已達到最高等級" << endl;
										}
									}									
									else {}
								}
								else //土地為別人的
								{
									if (players[playerState].safetyMask)//使用防護罩
									{
										PrintSign("防護罩免除過路費", 1);
										gotoxy(60, 14);
										system("pause");
										blank(55, 80, 10, 14);
										players[playerState].safetyMask = false;
									}
									else 
									{
										yesorno = PrintOnLand(players[i].estates.at(j), i, playerState, maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level]);
										players[playerState].money -= maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
										players[i].money += maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
										
									}
								}
								isEmpty = false;
							}
						}
					}
					if (isEmpty) //土地是空的
					{
						estate buffer(players[playerState].local, 0);
						yesorno = PrintOnLand(buffer, -1, playerState, maps.at(players[playerState].local).price);
						//cout << "土地" << players[playerState].local << "是空的是否要購買?" << endl;						
						if (yesorno == 1) //購買
						{
							if (players[playerState].money >= maps.at(players[playerState].local).price)
							{
								//cout << "已購買" << endl;
								players[playerState].money -= maps.at(players[playerState].local).price;
								estate buffer(players[playerState].local, 0);
								players[playerState].estates.push_back(buffer);
							}
							else
							{
								PrintSign("金額不足!", 1);
								gotoxy(60, 14);
								system("pause");
								blank(55, 80, 10, 14);
								//cout << "金錢不足" << endl;
							}
						}						
						else {}
					}

				}
				else if (maps.at(players[playerState].local).type == -1) //命運
				{
					int bigest = 0;
					int buffer_number = 0;
					switch (chance())
					{
					case 1:
						PrintDestiny("衰神來臨,傳送至過路費最貴的土地");						
						for (int i = 0; i < amount_of_player; i++) 
						{
							for (int j = 0; j < players[i].estates.size(); j++) 
							{
								if (maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level] > bigest) 
								{
									buffer_number = players[i].estates.at(j).number;
								}
							}
						}
						oldLocal = players[playerState].local;						
						if (buffer_number != 0)
						{
							players[playerState].local = buffer_number;
						}
						SetPlayerLocation(playerState, players[playerState].local, oldLocal);
						if (maps.at(players[playerState].local).type == 1) //判斷位置
						{
							for (int i = 0; i < amount_of_player; i++) //判斷是否有地主
							{
								for (int j = 0; j < players[i].estates.size(); j++)
								{
									if (players[i].estates.at(j).number == players[playerState].local)
									{
										//cout << "找到土地所有人" << endl;
										if (i == playerState) //土地為自己的
										{
											yesorno = PrintOnLand(players[i].estates.at(j), i, playerState, maps.at(players[playerState].local).price);
											//cout << "是否要升級?" << endl;									
											if (yesorno == 1) //升級
											{
												if (players[playerState].money >= maps.at(players[playerState].local).price&&players[playerState].estates.at(j).level < 3)
												{
													//cout << "已升級" << endl;
													players[playerState].money -= maps.at(players[playerState].local).price;
													players[playerState].estates.at(j).level++;
												}
												else
												{
													//cout << "金錢不足或已達到最高等級" << endl;
												}
											}
											else {}
										}
										else //土地為別人的
										{
											if (players[playerState].safetyMask)//使用防護罩
											{
												players[playerState].safetyMask = false;
											}
											else
											{
												yesorno = PrintOnLand(players[i].estates.at(j), i,playerState, maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level]);
												players[playerState].money -= maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
												players[i].money += maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
												
											}
										}										
									}
								}
							}							
						}
						break;
					case 2:
						PrintDestiny("因造勢大會，走走停停共5步(每一步皆可升級、購買...等等)");
						for (int n = 0; n < 5; n++) 
						{
							for (int i = 0; i < amount_of_player; i++)
							{
								SetPlayerLocation(i, players[i].local, oldLocal);
								int lv[4] = { 0,0,0,0 };
								if (!players[i].isDead) SetPlayerMoney(i, players[i].money);
								if (!players[i].isDead) SetPlayerProperty(i, players[i].getAll() + getEsatate(players[i]));
								players[i].total = players[i].getAll() + getEsatate(players[i]);
								for (int j = 0; j < players[i].estates.size(); j++)
								{
									SetLand(players[i].estates.at(j).number, i);
									lv[players[i].estates.at(j).level]++;
								}
								PrintPlayerLand(i, lv);
							}
							isEmpty = true;
							oldLocal = players[playerState].local;
							players[playerState].local++;
							SetPlayerLocation(playerState, players[playerState].local, oldLocal);
							if (maps.at(players[playerState].local).type == 1) //判斷位置
							{
								for (int i = 0; i < amount_of_player; i++) //判斷是否有地主
								{
									for (int j = 0; j < players[i].estates.size(); j++)
									{
										if (players[i].estates.at(j).number == players[playerState].local)
										{
											//cout << "找到土地所有人" << endl;
											if (i == playerState) //土地為自己的
											{
												yesorno = PrintOnLand(players[i].estates.at(j), i, playerState, maps.at(players[playerState].local).price);
												//cout << "是否要升級?" << endl;									
												if (yesorno == 1) //升級
												{
													if (players[playerState].money >= maps.at(players[playerState].local).price&&players[playerState].estates.at(j).level < 3)
													{
														//cout << "已升級" << endl;
														players[playerState].money -= maps.at(players[playerState].local).price;
														players[playerState].estates.at(j).level++;
													}
													else if(players[playerState].money < maps.at(players[playerState].local).price)
													{
														PrintSign("金額不足!", 1);
														gotoxy(60, 14);
														system("pause");
														blank(55, 80, 10, 14);
													}
													else if (players[playerState].estates.at(j).level >= 3)
													{
														PrintSign("等級已達最高!", 1);
														gotoxy(60, 14);
														system("pause");
														blank(55, 80, 10, 14);
													}
												}
												else {}
											}
											else //土地為別人的
											{
												if (players[playerState].safetyMask)//使用防護罩
												{
													players[playerState].safetyMask = false;
												}
												else
												{
													yesorno = PrintOnLand(players[i].estates.at(j), i, playerState, maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level]);
													players[playerState].money -= maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
													players[i].money += maps.at(players[i].estates.at(j).number).tolls[players[i].estates.at(j).level];
													
												}
											}
											isEmpty = false;
										}
									}
								}
								if (isEmpty) //土地是空的
								{
									estate buffer(players[playerState].local, 0);
									yesorno = PrintOnLand(buffer, -1, playerState, maps.at(players[playerState].local).price);
									//cout << "土地" << players[playerState].local << "是空的是否要購買?" << endl;						
									if (yesorno == 1) //購買
									{
										if (players[playerState].money >= maps.at(players[playerState].local).price)
										{
											//cout << "已購買" << endl;
											players[playerState].money -= maps.at(players[playerState].local).price;
											estate buffer(players[playerState].local, 0);
											players[playerState].estates.push_back(buffer);
											SetLand(players[playerState].local, playerState);
										}
										else if(players[playerState].money < maps.at(players[playerState].local).price)
										{
											PrintSign("金額不足!", 1);
											gotoxy(60, 14);
											system("pause");
											blank(55, 80, 10, 14);
										}
									}
									else {}
								}
								players[playerState].safetyMask = false;
							}
						}
						break;
					case 3:
						PrintDestiny("中氣不足，再骰一次!");
						continue;
						break;			
					case 4:
						PrintDestiny("沒有任何事發生，待在原地不想動");
						break;
					default:
						break;
					}
				}
				else if (maps.at(players[playerState].local).type == -2) //機會
				{
					int temp = players[playerState].money;
					string c;
					switch (chance())
					{
					case 1:
						PrintChance("好財神股票上漲2000元，並且獲得2張股票");
						currentStockPrice[2] += 2000;
						players[playerState].stock[2] += 2;
						break;
					case 2:
						PrintChance("貪小便宜找了偷工減料的建商，地震發生時，自身地產全部等級-1(Level0不動)");
						for (int i = 0; i < players[playerState].estates.size(); i++) 
						{
							if (players[playerState].estates.at(i).level > 0) 
							{
								players[playerState].estates.at(i).level -= 1;
							}
						}
						break;
					case 3:
						PrintChance("扶美女過馬路，積積陰陰德，加2000元");
						players[playerState].money += 2000;
						break;		
					case 4:
						//PrintChance("與其他玩家相撞，拿錯皮包(現金交換)");
						int t;
						t = chance() - 1;
						while (t == playerState || players[t].isDead) t = chance() - 1;
						//string c;
						c = "與玩家";
						c += ('1' + t);
						c += "相撞，拿錯皮包(現金交換)";
						PrintChance(c);
						players[playerState].money = players[t].money;
						players[t].money = temp;
						break;
					default:
						break;
					}
				}
				else {}//起點
				if (players[playerState].getAll() < 0) //破產
				{					
					
					while (players[playerState].getAll() < 0) //變賣土地 初始價格*等級/2
					{
						for (int i = 0; i < amount_of_player; i++)
						{
							SetPlayerLocation(i, players[i].local, oldLocal);
							int lv[4] = { 0,0,0,0 };
							if(!players[i].isDead) SetPlayerMoney(i, players[i].money);
							if (!players[i].isDead) SetPlayerProperty(i, players[i].getAll() + getEsatate(players[i]));
							players[i].total = players[i].getAll() + getEsatate(players[i]);
							for (int j = 0; j < players[i].estates.size(); j++)
							{
								SetLand(players[i].estates.at(j).number, i);
								lv[players[i].estates.at(j).level]++;
							}
							PrintPlayerLand(i, lv);
						}
						if (players[playerState].estates.size() == 0)
						{
							players[playerState].isDead = true;
							players[playerState].estates.clear();
							SetPlayerLocation(playerState, -1, players[playerState].local);
							players[playerState].local = -1;
							break;
						}
						vector<int> where;
						vector<int> level;
						vector<int> price;
						for (int i = 0; i < players[playerState].estates.size(); i++) 
						{
							where.push_back(players[playerState].estates.at(i).number);
							level.push_back(players[playerState].estates.at(i).level);
							price.push_back(maps.at(players[playerState].estates.at(i).number).price*(players[playerState].estates.at(i).level+1)/2);
						}
						int buffer = SaleLand(where, level, price);
						for (int k = 0; k < players[playerState].estates.size(); k++)
						{
							if (players[playerState].estates.at(k).number == buffer)
							{
								SetLand(buffer, 4);
								players[playerState].money += maps.at(buffer).price*(players[playerState].estates.at(k).level+1) / 2;								
								players[playerState].estates.erase(players[playerState].estates.begin() + k);
								break;
							}
						}
						if (players[playerState].getAll() > 0) 
						{
							break;
						}
					}
				}				
				players[playerState].safetyMask = false;
				rotation();//換人

				break;
			}
			case 1: //使用道具
			{
				if (players[playerState].money < 0) 
				{
					PrintSign("現金無法負債，您必須先提款", 1);
					gotoxy(60, 14);
					system("pause");
					blank(55, 80, 10, 14);
					continue;
				}
				int temp = 4;
				temp = PrintTool();
				PrintMenu();
				ColorMenu(t, 240, option);				
				if (temp == 1) //遙控骰子 2000元
				{
					int t;
					if (players[playerState].money-2000 >= 0 && players[playerState].controlDice == 0)
					{
						t = PrintInput(2);
						players[playerState].money -= 2000;
						players[playerState].controlDice = t;						
						continue;
					}
					else if (players[playerState].money - 2000 < 0)
					{
						PrintSign("金額不足!", 1);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
					else if (players[playerState].controlDice != 0)
					{
						PrintSign("已購買過!", 2);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
				}
				else if (temp == 2) //雙倍骰子 500元
				{
					if (players[playerState].money - 500 >= 0 && !players[playerState].doubleDice)
					{
						players[playerState].money -= 500;
						players[playerState].doubleDice = true;
						continue;
					}
					else if (players[playerState].money - 500 < 0)
					{
						PrintSign("金額不足!", 1);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
					else if (players[playerState].doubleDice) 
					{
						PrintSign("已購買過!", 2);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
				}
				else if (temp == 0) //路障 3000元
				{					
					int t;
					if (players[playerState].money - 3000 >= 0)
					{		
						t = PrintInput(1);
						if (!maps.at(t).Roadblock)
						{
							players[playerState].money -= 3000;
							maps.at(t).Roadblock = true;
						}
						PrintStop(t);
						continue;
					}
					else if (players[playerState].money - 3000 < 0)
					{
						PrintSign("金額不足!", 1);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
					else if (maps.at(t).Roadblock)
					{
						PrintSign("已購買過!", 2);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
				}
				else if (temp == 3) //防護罩 3000
				{
					if (players[playerState].money - 3000 >= 0&& !players[playerState].safetyMask)
					{
						players[playerState].money -= 3000;
						players[playerState].safetyMask = true;
						continue;
					}
					else if (players[playerState].money - 3000 < 0)
					{
						PrintSign("金額不足!", 1);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
					else if (players[playerState].safetyMask)
					{
						PrintSign("已購買過!", 2);
						gotoxy(60, 14);
						system("pause");
						blank(55, 80, 10, 14);
					}
				}
				PrintMenu();
				ColorMenu(choose, 240, option);
				break;
			}
			case 2: //進入銀行
			{					
				PrintBank(players[playerState]);	
				break;
			}
			case 3: // 購買股票
			{					
				PrintStock(stockName, currentStockPrice, stockChang, players[playerState]);
				break;
			}
			}
		}
		else if (ch == 27) //ESC
		{
			int q;
			q = PrintEsc();
			if (q == 1)
			{
				int y = 56, x = 9;
				SetColor(14);
				gotoxy(y, x);
				cout << "╔ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╗ ";
				gotoxy(y, x + 1);
				cout << "║                   ║ ";
				gotoxy(y, x + 2);
				cout << "║                   ║ ";
				gotoxy(y, x + 3);
				cout << "║                   ║ ";
				gotoxy(y, x + 4);
				cout << "║                   ║ ";
				gotoxy(y, x + 5);
				cout << "╚ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╝ ";
				SetColor();
				gotoxy(y + 4, x + 1);
				cout << "請輸入存檔名:";
				gotoxy(y + 5, x + 3);
				string fileName;
				SetCursorVisible(true);
				cin >> fileName;
				SetCursorVisible(false);
				fstream f1;
				f1.open(fileName, ios::out);
				//存檔 用 f1 來存東西
				f1 << mapName <<' '<< round << ' ' << amount_of_player << '\n';
				for (int i = 0; i < maps.size(); i++) 
				{
					f1 << maps.at(i).local << ' ' << maps.at(i).name << ' ' << maps.at(i).type;
					if (maps.at(i).type == 1) 
					{
						f1 << ' ' << maps.at(i).price << ' ' << maps.at(i).tolls[0] << ' ' << maps.at(i).tolls[1] << ' ' << maps.at(i).tolls[2] << ' ' << maps.at(i).tolls[3] << '\n';
					}
					else 
					{
						f1 << '\n';
					}
				}
				f1 << "playerstate " << playerState << '\n';
				for (int i = 0; i < amount_of_player; i++) 
				{
					f1 << i << ' ' << players[i].local << ' ' << players[i].getAll();
					for (int j = 0; j < players[i].estates.size(); j++) 
					{
						f1 << ' ' << players[i].estates.at(j).number << ' ' << players[i].estates.at(j).level;
					}
					f1 << '\n';
				}
				f1.close();
			}
			else if (q == 2)
			{
				int y = 56, x = 9;
				SetColor(14);
				gotoxy(y, x);
				cout << "╔ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╗ ";
				gotoxy(y, x + 1);
				cout << "║                   ║ ";
				gotoxy(y, x + 2);
				cout << "║                   ║ ";
				gotoxy(y, x + 3);
				cout << "║                   ║ ";
				gotoxy(y, x + 4);
				cout << "║                   ║ ";
				gotoxy(y, x + 5);
				cout << "╚ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╝ ";
				SetColor();
				gotoxy(y + 4, x + 1);
				cout << "請輸入讀檔名:";
				gotoxy(y + 5, x + 3);
				string fileName;
				fstream file;
				SetCursorVisible(true);
				while (1)
				{
					cin >> fileName;
					file.open(fileName, ios::in);
					if (!file)
					{
						gotoxy(y + 4, x + 1);
						cout << "查無此檔請重試";
						gotoxy(y + 5, x + 3);
						for (int i = 0; i < 14; i++) cout << " ";
						gotoxy(y + 5, x + 3);
					}
					else break;
				}
				ReadFile(fileName);
				SetCursorVisible(false);
				//讀檔 用 f1 來讀東西
				PrintRightBack();
				PrintRight();
				blank(0, 20, 4, 50);
				maps.clear();//清除
				string temp;
				file >> mapName;
				file >> round;
				file >> amount_of_player;
				PrintLeft(amount_of_player);
				delete [] players;
				players = new Player[amount_of_player];
				while (file >> temp)
				{
					if (temp == "playerstate")break;
					int local = stoi(temp);
					string name;
					int type;
					file >> name;
					file >> type;
					if (type == 1)
					{
						int price;
						int tolls[4];
						file >> price;
						for (int i = 0; i < 4; i++)
						{
							file >> tolls[i];
						}
						Map map(local, name, type, price, tolls);
						maps.push_back(map);
					}
					else
					{
						Map map(local, name, type);
						maps.push_back(map);
					}
				}
				if (temp == "playerstate")
				{
					getline(file, temp);
					playerState = stoi(temp);
					counter = playerState;
					for (int i = 0; i < amount_of_player; i++)
					{
						int number;
						int local;
						int money;
						file >> number;
						file >> local;
						file >> money;
						players[i].number = number;
						players[i].local = local;
						players[i].money = money;					
						getline(file, temp);
						string buffer;
						bool flag = false;
						if (temp.size() != 0)
						{
							int a;
							int b;
							for (int j = 1; j < temp.size(); j++)
							{
								if (temp.at(j) != ' ')
								{
									buffer += temp.at(j);
								}
								else
								{
									if (!flag)
									{
										a = stoi(buffer);
										flag = true;
									}
									else
									{
										b = stoi(buffer);
										estate c(a, b);
										players[i].estates.push_back(c);
										flag = false;
									}
									buffer.clear();
								}
							}
							b = stoi(buffer);
							estate c(a, b);
							players[i].estates.push_back(c);
							buffer.clear();
						}
					}
				}
				for (int i = 0; i < amount_of_player; i++) //避免玩家位置超過地圖範圍
				{
					players[i].local %= maps.size();
					if (players[i].getAll() + getEsatate(players[i]) < 0)
					{
						players[i].isDead = true;
					}
					SetPlayerLocation(i, players[i].local, 0);
				}
				file.close();
				
			}
			else if (q == -1)
			{
			PrintRightBack();
			PrintRight();			
			fstream file;
			file.open("start.txt", ios::in);
			maps.clear();//清除
			string temp;
			file >> mapName;
			file >> round;
			file >> amount_of_player;
			blank(0, 20, 4, 50);
			PrintLeft(amount_of_player);
			delete[] players;
			players = new Player[amount_of_player];
			while (file >> temp)
			{
				if (temp == "playerstate")break;
				int local = stoi(temp);
				string name;
				int type;
				file >> name;
				file >> type;
				if (type == 1)
				{
					int price;
					int tolls[4];
					file >> price;
					for (int i = 0; i < 4; i++)
					{
						file >> tolls[i];
					}
					Map map(local, name, type, price, tolls);
					maps.push_back(map);
				}
				else
				{
					Map map(local, name, type);
					maps.push_back(map);
				}
			}
			if (temp == "playerstate")
			{
				getline(file, temp);
				playerState = stoi(temp);
				counter = playerState;
				for (int i = 0; i < amount_of_player; i++)
				{
					int number;
					int local;
					int money;
					file >> number;
					file >> local;
					file >> money;
					players[i].number = number;
					players[i].local = local;
					players[i].money = money;
					getline(file, temp);
					string buffer;
					bool flag = false;
					if (temp.size() != 0)
					{
						int a;
						int b;
						for (int j = 1; j < temp.size(); j++)
						{
							if (temp.at(j) != ' ')
							{
								buffer += temp.at(j);
							}
							else
							{
								if (!flag)
								{
									a = stoi(buffer);
									flag = true;
								}
								else
								{
									b = stoi(buffer);
									estate c(a, b);
									players[i].estates.push_back(c);
									flag = false;
								}
								buffer.clear();
							}
						}
						b = stoi(buffer);
						estate c(a, b);
						players[i].estates.push_back(c);
						buffer.clear();
					}
				}
			}
			for (int i = 0; i < amount_of_player; i++) //避免玩家位置超過地圖範圍
			{
				players[i].local %= maps.size();
				SetPlayerLocation(i, players[i].local, players[i].local + 1);
			}
			file.close();
			for (int i = 0; i < 28; i++) SetLand(i, 4);
			}
			blank(56, 80, 9, 15);
			
		}
	}
}

int chance()
{
	int num;
	srand(time(NULL));
	num = rand() % 4;
	return num + 1;
}
void start()
{
	ConsoleFullScreen();
	Sleep(1000);
	hidecursor();
	if (1)
	{
		cout << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNXXWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNKOkxxxdoodxkKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNX0kdoooloodxkOOOOxoodkNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWX0kdooolllodkOOOOOOOOOOOOOOxllxXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOxdoolloxkOOOOOOOOOOOOOOOOOOOOOOOxl : dXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWX0kddolodkOOOOOOkOOOOOOOOOOOOOOOOOOOOOOOOxc; dXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOxdoooxkOOkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOd;; xNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOxdoodkOOOkxdddkOOOOOOOOOOOOOOOOOOOOkkOOOOOkkkOOOOOkl, ; kNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOxdoodkOOOkxdddxxkOOOOOOOOOOOOOOOOkOOOOOddkOOOOkddxOOOOOOx : ':ONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKkdoodkOOOkxdddxxkOOOOOOOOOOOOOOOOOOOxdkOOOOkddkOOOOOxddkOOOOOkd, 'cKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNOxoooxOOOOkxdddxkOOOOOOOOOOOOOOOOOOOOOOxoxOOOOOOkoxOOOOOOkxoxkOOOOOkl''dXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMXOdoldkOOOOkdddxkOOOOOOOOOOOOOOOOOOOOOOOOOxokOOOOOOOOxoxOOOOOOOkddkOOOOOOxc.; OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMNOdoldkOOOOkdddxkOOOOOOOOOOOOOOOOOOOOOOOOOOOdokOOOOOOOOOOddkOOOOOOOOxodkOOOkOOd, 'lXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMNOdlldkOOOOkxddxkOOOOOOOOOOOOOOOOOOOOOOOOOOOOkdokOkOOOOOOOOOkoxOOOOOOOOOkddkOOOOOOkl';OWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMWKxllokOOOOOkdddkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkdokOOOOOOOOOOOOOxokOOOOOOOOOOxoxkOOOOOOd; 'oXMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMXkolokOOOOOOkddxkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkdlokOOOOOOOOOOOOOOkodOOOOOOOOOOOkddkOOOOOOkl':0WMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMW0dlldOOOOOOOOOkxkOOOOOkOOOOOOOOOOOOOOOOOOOOOOOOOOxdxkOOOOOOOOOOOOOOOOdokOOOOOOOOOOOOdokOOOOOOOd; ,kNMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMNkolokOOOOOOOOOOOOOOOkkxxxdddoooddddddddddddddddxxkkkkOOOOOOOOOOOOOOOOOOkoxOOOOOOOOOOOOOxoxOOOOOOOkc' oXMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMXxolxOOOOOOOOkkxdolc:;; cdddddxxxxdllodkOOOOkkkkkxxxxxxddddddoddxkOOOOOOOOOkoxOOOOOOOOOOOOOOxoxOOOOOOOOo, cKMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMWKxookOOOOkxdlc; , '........oXXXXXXXKxxO00xx0XXXXXXXXXXXXXXKkxddocldddoooodkOOOOkkOOOOOOOOOOOOOOOxoxOOOOOOOOx;:0WMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMXxldkOOkdl:, ...............xXXXXXXXOoxOkOXxxXXXXXXXXXXXXKkxO0KXXKkx0XKOkddollloxkOOOOkOOOOOOOOOOOxxOOOOOOOOOkc; OWMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMWOlokOxl : '..................'kXXXXXXXX0OK0dddOXXXXXXXXXXXXkdKKOOOkOOokXXXXXXXKOdolc : coxkOOOkOOOOOOOOOOOOOOOOOOOOxWMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMNdcxOd : '.....................:KXXXXXXXXXXXXK0KXXXXXXXXXXXXXOxkkkOK0kxOKXXXXXXXXXXXX0xoc;;;cdxOOOOOOOOOOOOOOOOOOOOOo:xNMMMMMMMMMMMMMMMMM" << endl <<
			"    MNd : xx; ........................oXXXXXXXXXXKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0xl; ''; coxOOOOOOOOOOOOOOOOd:dNMMMMMMMMMMMMMMM" << endl <<
			"    MO; lo'........................,OXXXXXX0dooddod0XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXOd:'..; coxOOOOOOOOOOOOOOOOxcdNMMMMMMMMMMMMMM" << endl <<
			"    Md, :'.........................lKXXXXKdcoOKXXOclKXXXXXXXXXXXXXXXXXKOdddddokKXXXXXXXXXXXXXXXXXXXXX0xc'..';ldkOOOOOOOOOOOOOxcdNMMMMMMMMMMMMMM" << endl <<
			"    Mk'..........................,OXXXXXo:OXXXXXXd:OXXXXXXXXXXXXXXX0o:lxOKK0xcoKXXXXXXXXXXXXXXXXXXXXXXX0d;....,cokOOOOOOOOOOOOkldXMMMMMMMMMMMMM" << endl <<
			"    MNl..........................oXXXXXKxkXXXXXXXxcx0KXXXXXXXXXXXXOco0KXXXXXX0coXXXXXXXXXXXXXXXXXXXXXXXXXKl......':okOOOOOOOOOOkloXMMMMMMMMMMMM" << endl <<
			"    MMXl........................ : 0XXXXXXXXXXXXXXXOlckXXXXXXXXXXXXXooKXXXXXXXXXlc0XXXXXXXXXXXXXXXXXXXK0OOO00l........':okOkkOOkllKMMMMMMMMMMMM" << endl <<
			"    MMMNk; ....................., kXXXXXXXXXXXXXXXKlc0XXXXXXXXXXXX0xkKXXXXXXXXXXdl0XXXXXXXXXXXXXXX0kxxxxxddol; ..........., cxOOOOkllKMMMMMMMMM" << endl <<
			"    MMMMMNkc...................dXXXXXXXXXXXXXX0xo; :kKXXXXXXXXXXXO;; xk0KXXXXXXXKKXXXXXXXXXXXXXXXKOOKXXXXXXXX0d; ............:dkOOkllKMMMMMMMMM" << endl <<
			"    MMMMMMMWKd : '..............:KXXXXXXXXXXKkooddO0koooodddxxxdollldxdddod0XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKl.............;okOOkclXMMMMMMMM" << endl <<
			"    MMMMMMMMMMWKxl; ...........oXXXXXXXXXKdldOXWMMWWMWX0OkxxxxxkOXWMMMMWKxlokXXXXXXXXXXXXXXXXXXXXXXKK000KXXXXXX0:..............; dkOx:dWMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMWN0xl; .......lXXXXXXXXOcoXMMMMMWXNMMMMMMMMMMMMMMMMMMMMMMNklo0XXXXXXXXXXXXXXXXXXXKkkkxkk0KXXXXKc................:xOo:0MMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMWKko : '..;0XXXXXXXllNMMMMMWkc0MMMMMMMMMMMMWXXMMMMMMMMMNdckXXXXXXXXXXXXXXXXXXOkkk00Ok0XXXX0;.................'okcdMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMWXOc'oXXXXXXXocKMMMW0o'lNMMMMMMMMMMMMXc, kNMMMMMMMMWx : kXXXXXXXXXXXXXXXXXKOO0XXXKKXXXKl....................ollMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMNl, kXXXXXX0dodddool; xMMMNOclONWMMM0, ..; x0XMMMMMMXcoXXXXXXXXXXXXXXXXXXXXXXXXXXXX0c.....................':cMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMK:, kXXXXXXXX0OOKXKlckOx : ....; lxOx:......, lk0XX0dckXXXXXXXXXXXXXXKXXXXXXXXXXKOl'.......................;xMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMWK : , dKXXXXXXXXXXXXKko, ....................'odddd0XXXXXXXXXXXXXKo;:odxkkkxoc;.......................'cxXWMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMXd, cOXXXXXXXXXXXXXKc., : cccccc::; , '......dXXXXXXXXXXXXXXXXXKx;................................,:okXWMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMW0l; ckKXXXXXXXXXXO::dooooooodoodol:...dKXXXXXXXXXXXXXXKxl, ...''....................',;:coxOKNWMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKdccokKXXXXXXXx; ldooooooooooddocclkXXXXXXXXXXXX0koc::ldk0KKKKK00OOkxxdddddxkkO0KKNWWMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKxooooxOKXXKo : cclllooollccloxKXXXXXXXK0Oxocc:cokKWWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN0kdddddddlc::cccllllodxOkkkxdoolllllloxOXWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOxdlcc:::::::: : ;;;;;;; :coxkKXWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl <<
			"    MM                                                                                                                                       MM" << endl <<
			"    MM ███╗       ███╗  ██████╗  ███╗       ██╗  ██████╗  ██████╗    ██████╗  ██╗     ██╗       ██╗ MM" << endl <<
			"    MM ████╗   ████║██╔═══════██╗████╗     ██║██╔═══════██╗██╔═════██╗██╔═══════██╗██║     ╚═██╗   ██╔═╝ MM" << endl <<
			"    MM ██╔═████╔═██║██║       ██║██╔═██╗   ██║██║       ██║██████╔═╝██║       ██║██║       ╚═████╔═╝   MM" << endl <<
			"    MM ██║ ╚═██╔═╝ ██║██║       ██║██║ ╚═██╗ ██║██║       ██║██╔═══════╝  ██║       ██║██║         ╚═██╔═╝     MM" << endl <<
			"    MM ██║   ╚═══╝   ██║╚═██████╔═╝██║   ╚═████║╚═██████╔═╝██║          ╚═██████╔═╝███████╗ ██║       MM" << endl <<
			"    MM ╚═══╝           ╚═══╝  ╚═══════════╝  ╚═══╝      ╚══════╝  ╚═══════════╝  ╚═══╝            ╚═══════════╝  ╚═════════════╝ ╚═══╝       MM" << endl <<
			"    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM";
	}
	int x = 155, y = 22;
	PrintRec(x, y, 5, 10);
	PrintRec(x, y + 4, 5, 10);
	gotoxy(x, y + 4);
	cout << "├ ";
	gotoxy(x + 22, y + 4);
	cout << "┤";
	string op[2] = { "     開 新 遊 戲    " , "     讀 取 檔 案    " };
	SetColor(240);
	gotoxy(x + 2, y + 1); for (int i = 0; i < 20; i++) cout << " ";
	gotoxy(x + 2, y + 3); for (int i = 0; i < 20; i++) cout << " ";
	gotoxy(x + 2, y + 2);
	cout << op[0];
	SetColor();
	gotoxy(x + 2, y + 6);
	cout << op[1];
	int choose = 0;
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 72)
			{
				if (choose == 1)
				{
					gotoxy(x + 2, y + 1 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 3 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 2 + choose * 4);
					cout << op[choose];
					choose = 0;
					SetColor(240);
					gotoxy(x + 2, y + 1 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 3 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 2 + choose * 4);
					cout << op[choose];
					SetColor();
				}
			}
			if (ch == 80)
			{
				if (choose == 0)
				{
					gotoxy(x + 2, y + 1 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 3 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 2 + choose * 4);
					cout << op[choose];
					choose = 1;
					SetColor(240);
					gotoxy(x + 2, y + 1 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 3 + choose * 4); for (int i = 0; i < 20; i++) cout << " ";
					gotoxy(x + 2, y + 2 + choose * 4);
					cout << op[choose];
					SetColor();
				}
			}
		}
		else if (ch == 13)
		{
			if (choose == 0)
			{
				//開新遊戲
				system("cls");
				Backend backend;
				backend.play();
				break;
			}
			else if (choose == 1)
			{
				blank(155, 180, 22, 30);
				//讀取檔案
				int y = 155, x = 22;
				SetColor(14);
				gotoxy(y, x);
				cout << "╔ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╗ ";
				gotoxy(y, x + 1);
				cout << "║                   ║ ";
				gotoxy(y, x + 2);
				cout << "║                   ║ ";
				gotoxy(y, x + 3);
				cout << "║                   ║ ";
				gotoxy(y, x + 4);
				cout << "║                   ║ ";
				gotoxy(y, x + 5);
				cout << "╚ ═ ═ ═ ═ ═ ═ ═ ═ ═ ╝ ";
				SetColor();
				gotoxy(y + 4, x + 1);
				cout << "請輸入讀檔名:";
				gotoxy(y + 5, x + 3);
				string fileName;
				fstream file;
				SetCursorVisible(true);
				while (1)
				{
					cin >> fileName;
					file.open(fileName, ios::in);
					if (!file)
					{
						gotoxy(y + 4, x + 1);
						cout << "查無此檔請重試";
						gotoxy(y + 5, x + 3);
						for (int i = 0; i < 14; i++) cout << " ";
						gotoxy(y + 5, x + 3);
					}
					else break;
				}
				SetCursorVisible(false);
				file.close();
				system("cls");
				Backend backend(fileName);
				backend.play();
				break;
			}
			
		}
	}
}