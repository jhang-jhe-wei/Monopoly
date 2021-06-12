#include "database.h"
estate::estate(int a, int b)
{
	number = a;
	level = b;
}

Map::Map(int _local, string _name, int _type)
{
	local = _local;
	name = _name;
	type = _type;
	Roadblock = false;
}

Map::Map(int _local, string _name, int _type, int _price, int _tolls[4])
{
	local = _local;
	name = _name;
	type = _type;
	price = _price;
	Roadblock = false;
	for (int i = 0; i < 4; i++)
	{
		tolls[i] = _tolls[i];
	}
}

int Player::getAll()
{
	int sum = 0;
	sum = money + stock[0] * currentStockPrice[0] + stock[1] * currentStockPrice[1] + stock[2] * currentStockPrice[2] + getDeposit() - loan;
	return sum;
}



int Player::getDeposit()
{
	return deposit + buffer;
}


