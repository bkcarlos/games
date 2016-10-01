#include "snack.h"
#include<conio.h>


// 移动光标到 x和y 的位置
void Position(short x, short y,Map &map)
{
	COORD cors = { x,y };
	SetConsoleCursorPosition(map.Console, cors);
}

bool Point::operator==(const Point& point)
{
	return this->mx == point.mx && this->my == point.my;
}

void Point::operator=(const Point & point)
{
	this->mx = point.mx;
	this->my = point.my;
}

Map::Map()
{
	srand(static_cast<unsigned int>(clock()));

	// 获取窗口的句柄
	CONSOLE_CURSOR_INFO CurrInfo = { sizeof(CONSOLE_CURSOR_INFO), 0 };
	Console = GetStdHandle(STD_OUTPUT_HANDLE);

	this->mapCol = 20;
	this->mapRow = 20;

	this->sanck.SnackHead.mx = rand() % (this->mapRow - 2) + 1;
	this->sanck.SnackHead.my = rand() % (this->mapCol - 2) + 1;

	this->sanck.direction = Pause;
}

// 产生食物
void CreateFood(Map & map)
{
	if (map.sanck.SnackBody.size() == (map.mapRow - 2)*(map.mapCol - 2) - 1)
	{
		int ret = MessageBox(NULL, TEXT("恭喜你通过了,要不要再挑战一次"), TEXT("恭喜"), MB_YESNO);
		if (ret == IDYES)
		{
			map.sanck.SnackBody.clear();
		}
	}

	bool CreateFoodFlag = false;

	while (!CreateFoodFlag)
	{
		CreateFoodFlag = true;

		map.food.mx = rand() % (map.mapRow - 2) + 1;
		map.food.my = rand() % (map.mapCol - 2) + 1;

		if (map.food == map.sanck.SnackHead)
		{
			CreateFoodFlag = false;
		}
		if (CreateFoodFlag)
		{
			for (list<Point>::iterator bi = map.sanck.SnackBody.begin(); CreateFoodFlag != false &&
				bi != map.sanck.SnackBody.end(); ++bi)
			{
				if (*bi == map.food)
				{
					CreateFoodFlag = false;
				}
			}
		}
	}
	Position(map.food.mx*2, map.food.my, map);
	cout << FOOD << " ";
}

void DrawSnack(Map & map)
{
	Position(map.sanck.SnackHead.mx*2, map.sanck.SnackHead.my, map);
	cout << SNACKHEAD << " ";
	for (list<Point>::iterator bi = map.sanck.SnackBody.begin(); bi != map.sanck.SnackBody.end(); ++bi)
	{
		Position((bi->mx)*2,bi->my,map);
		cout << SNACKBODY << " ";
	}
	Position(0, map.mapCol, map);
}


void DrawWall( Map & map)
{

	// 上面的墙
	Position(0, 0,map);
	for (int i = 0; i < map.mapRow; ++i)
	{
		cout << WALL << " ";
	}

	// 左面的墙
	for (int i = 1; i < map.mapCol; ++i)
	{
		Position(0, i, map);
		cout << WALL << " ";
	}

	// 下面的墙
	Position(0, map.mapCol-1, map);
	for (int i = 1; i < map.mapRow; ++i)
	{
		cout << WALL << " ";
	}

	// 右面的墙
	for (int i = 1; i < map.mapCol; ++i)
	{
		Position(2*(map.mapRow-1), i, map);
		cout << WALL << " ";
	}
}

bool SnackGOFlag(Map & map)
{
	// 检测是否撞墙
	if ( map.sanck.SnackHead.mx == 0 || map.sanck.SnackHead.mx == map.mapRow - 1 ||
		 map.sanck.SnackHead.my == 0 || map.sanck.SnackHead.my == map.mapCol - 1)
	{
		return false;
	}

	// 检测是否撞到自己
	for (list<Point>::iterator ib = map.sanck.SnackBody.begin(); ib != map.sanck.SnackBody.end(); ++ib)
	{
		if (*ib == map.sanck.SnackHead)
		{
			return false;
		}
	}

	return true;
}




// 控制蛇的上下左右移动
void SnackGO(Map & map)
{
	bool continueFlag = true;
	while (continueFlag)
	{
		Sleep(500-map.sanck.SnackBody.size()*20);
		if (_kbhit())
		{
			int ch = _getch();
			switch (ch)
			{
			case 'w':
			case 'W':
				if (map.sanck.direction != Down)
				{
					map.sanck.direction = Up;
				}
				break;
			case 'a':
			case 'A':
				if (map.sanck.direction != Right)
				{
					map.sanck.direction = Left;
				}
				break;
			case 's':
			case 'S':
				if (map.sanck.direction != Up)
				{
					map.sanck.direction = Down;
				}
				break;
			case 'd':
			case 'D':
				if (map.sanck.direction != Left)
				{
					map.sanck.direction = Right;
				}
				break;
			}
		}
		Point oldSnackHead = map.sanck.SnackHead;
		
		
		map.sanck.SnackBody.push_front(oldSnackHead);
		// 吃到食物， 尾结点不被排除
		
		switch (map.sanck.direction)
		{
		case Up:
			map.sanck.SnackHead.my -= 1;
			break;
		case Down:
			map.sanck.SnackHead.my += 1;
			break;
		case Left:
			map.sanck.SnackHead.mx -= 1;
			break;
		case Right:
			map.sanck.SnackHead.mx += 1;
			break;
		case Pause:
			Sleep(500);
			//map.sanck.direction = Up;
			break;
		default:
			break;
		}

		// 如果蛇吃到食物，则不将原来的地方填充为空格
		// 蛇没吃到食物
		if (!(map.sanck.SnackHead == map.food))
		{
			Position(map.sanck.SnackBody.back().mx * 2, map.sanck.SnackBody.back().my, map);
			cout << " ";
			map.sanck.SnackBody.pop_back();
		}
		else // 蛇吃到食物了
		{
			Position(map.food.mx * 2, map.food.my, map);
			cout << " ";
			CreateFood(map);
		}

		if (SnackGOFlag(map))
		{
			// 将蛇头原来的位置填充为空格
			Position(oldSnackHead.mx * 2, oldSnackHead.my, map);
			cout << " ";
			DrawSnack(map);
		}
		else
		{
			continueFlag = false;
		}
	}	
}



