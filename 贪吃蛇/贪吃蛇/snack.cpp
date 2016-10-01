#include <conio.h>
#include<Windows.h>
#include "snack.h"

Point::Point(int x, int y)
{
	px = x; 
	py = y;
}

Point & Point::operator=(const Point & point)
{
	this->px = point.px;
	this->py = point.py;
	// TODO: 在此处插入 return 语句
	return *this;
}

bool Point::operator==(const Point & point)
{
	return (this->px == point.px && this->py == point.py);
}

Point & Point::operator+=(const Point & point)
{
	this->px += point.px;
	this->py += point.py;
	return *this;
}

Map::Map()
{
	this->mCol = 20;
	this->mRow = 20;
	this->SnackGO = Pause;
}

Map::Map(int row, int col)
{
	this->mRow = row;
	this->mCol = col;
}

void createMap(Map & map)
{
	map.pMap = new char*[map.mRow];
	for (int i = 0; i < map.mRow; ++i)
	{
		map.pMap[i] = new char[map.mCol];
	}

	// 第一列 和 最后一列
	for (int i = 0; i < map.mRow; ++i)
	{
		map.pMap[i][map.mCol - 1] = '#';
		map.pMap[i][0] = '#';
	}
	// 第一行 和 最后一行
	for (int i = 0; i < map.mCol; ++i)
	{
		map.pMap[0][i] = '#';
		map.pMap[map.mRow - 1][i] = '#';
	}

	bool createFlag = false;
	while (!createFlag)
	{
		map.SnackHead.px = rand() % (map.mRow - 2) + 1;
		map.SnackHead.py = rand() % (map.mCol - 2) + 1;

		map.Food.px = rand() % (map.mRow - 2) + 1;
		map.Food.py = rand() % (map.mCol - 2) + 1;

		if (!(map.Food == map.SnackHead))
		{
			createFlag = true;
			map.flagFood = true;
			map.pMap[map.SnackHead.px][map.SnackHead.py] = '@';
			map.pMap[map.Food.px][map.Food.py] = '*';
		}
	}
}

void showMap(Map & map)
{
	for (deque<Point>::iterator cbi = map.SnackBody.begin(); cbi != map.SnackBody.end(); ++cbi)
	{
		map.pMap[cbi->px][cbi->py] = 'O';
	}

	system("cls");

	for (int i=0;i<map.mRow;++i)
	{
		for (int j = 0; j < map.mCol; ++j)
		{
			if (map.pMap[i][j] == '#' || map.pMap[i][j] == '*' || map.pMap[i][j] == '@'|| map.pMap[i][j] == 'O')
				cout << map.pMap[i][j] ;
			else
				cout << " ";
			cout << " ";
		}
		cout << endl;
	}
	
}


// 如果吃到食物，那么返回true
bool SnackEatFood(Map & map)
{
	if (map.SnackHead==map.Food)
	{
		return true;
	}
	return false;
}

void Play(Map & map)
{
	bool continuePlay = true;
	char ch = 0;
	ch = _getch();
	if (ch)
	{
		map.SnackGO = Down;
	}
	while (continuePlay)
	{
		// 速度在这调节
		Sleep(500);
		 ch = 0;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 'w':
			case 'W':
			{
				if (map.SnackGO != Down)
				{
					map.SnackGO = Up;
				}
				break;
			}
			case 's':
			case 'S':
			{
				if (map.SnackGO != Up)
				{
					map.SnackGO = Down;
				}
				break;
			}
			case 'a':
			case 'A':
			{
				if (map.SnackGO != Right)
				{
					map.SnackGO = Left;
				}
				break;
			}
			case 'd':
			case 'D':
			{
				if (map.SnackGO != Left)
				{
					map.SnackGO = Right;
				}
				break;
			}
			default:
				break;
			}
		}
		Point oldSnackHead = map.SnackHead;
		map.pMap[map.SnackHead.px][map.SnackHead.py] = ' ';
		switch (map.SnackGO)
		{
		case Down:
		{
			map.SnackHead.px += 1;
			break;
		}
		case Up:
		{
			map.SnackHead.px -= 1;
			break;
		}
		case Left:
		{
			map.SnackHead.py -= 1;
			break;
		}
		case Right:
		{
			map.SnackHead.py += 1;
			break;
		}
		}
		map.SnackBody.push_front(oldSnackHead);

		if (!SnackEatFood(map))
		{
			map.pMap[(*(map.SnackBody.end() - 1)).px][(*(map.SnackBody.end() - 1)).py] = ' ';
			map.SnackBody.pop_back();
		}
		else
		{
			map.flagFood = false;
			createFood(map);
		}
		if (!decideSnack(map))
		{
			continuePlay = false;
		}
		else
		{
			map.pMap[map.SnackHead.px][map.SnackHead.py] = '@';
			showMap(map);
		}
		
	}
}



void createFood(Map & map)
{
	while (!map.flagFood)
	{
		map.flagFood = true;
		map.Food.px = rand() % (map.mRow - 2) + 1;
		map.Food.py = rand() % (map.mCol - 2) + 1;
		for (deque<Point>::iterator bi=map.SnackBody.begin();bi!=map.SnackBody.end();++ bi)
		{
			if (*bi == map.Food)
			{
				map.flagFood = false;
			}
		}
		if(map.Food==map.SnackHead)
			map.flagFood = false;
	}
	map.pMap[map.Food.px][map.Food.py] = '*';
}

bool decideSnack(Map & map)
{
	for (deque<Point>::iterator bi = map.SnackBody.begin();bi!=map.SnackBody.end(); ++bi)
	{
		if (map.SnackHead == *bi)
			return false;
	}
	
	return !(map.pMap[map.SnackHead.px ][map.SnackHead.py] == '#');
}

