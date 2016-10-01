/* 

申明 本游戏的规格和实际的2048 规则有出入，
主要学习相关的思想。请不要用完美的眼光来对待这段代码！
*/


#include <iostream>
#include <deque>
#include<ctime>
#include<conio.h>

using namespace std;

const int MAXSIZE = 4;

int Array[MAXSIZE][MAXSIZE] = { 0 };

struct MyPoint
{
	int px;
	int py;
	MyPoint(int x, int y) :px(x), py(y) {}
	MyPoint& operator=(const MyPoint&point);
};

deque<MyPoint> Mydeque;

// 把所有的点入队列
void InToDeque();

MyPoint PopPoint();

void printArray();

// 向上的操作
void operatorUp();
void operatorDown();
void operatorLeft();
void operatorRight();

// 查看是否有可以合并的位置
bool checkingRow();
bool checkingCol();

void play();

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	play();
	system("pause");
	return 0;

}


void play()
{
	// 把零值入容器
	InToDeque();
	
	// 生成两个底
	for (int i = 0; i<2; ++i)
	{
		// 从容器中取出
		MyPoint tempPoint = PopPoint();
		if (tempPoint.px == -1 && tempPoint.py == -1)
		{
			return;
		}
		Array[tempPoint.px][tempPoint.py] = rand() % 10 ? 2 : 4;
	}

	// 打印当前的容器
	printArray();

	// 当前的游戏是否可以继续
	bool continuePlay = true;

	//  0x11 表示可以上下左右
	//  0x01 表示可以上下
	//  0x10 表示可以左右
	int direction = 0x11;

	while (continuePlay)
	{
		// 判断当前的按键是否被允许
		bool orderlyBotton = true;

		int ch = _getch();
		if (ch != 0xE0)
			continue;
		ch = _getch();

		switch (ch)
		{
		case 72:
			if (direction == 0x11 || direction == 0x01)
				operatorUp();
			else
			{
				orderlyBotton = false;
			}
			break;
		case 75:
			if (direction == 0x11 || direction == 0x10)
				operatorLeft();
			else
			{
				orderlyBotton = false;
			}
			break;
		case 80:
			if (direction == 0x11 || direction == 0x01)
				operatorDown();
			else
			{
				orderlyBotton = false;
			}
			break;
		case 77:
			if (direction == 0x11 || direction == 0x10)
				operatorRight();
			else
			{
				orderlyBotton = false;
			}
			break;
		}

		if (orderlyBotton)
		{
			// 把零值入容器
			InToDeque();

			MyPoint tempPoint = PopPoint();
			if (!(tempPoint.px == -1 && tempPoint.py == -1))
			{
				Array[tempPoint.px][tempPoint.py] = rand() % 10 ? 2 : 4;
			}
			printArray();


			if (!Mydeque.size())
			{
				int tempdirection = 0x00;

				if (checkingCol())
				{
					tempdirection += 0x01;
				}
				if (checkingRow())
				{
					tempdirection += 0x10;
				}

				direction = tempdirection;

				if (direction == 0x00)
				{
					continuePlay = false;
				}
			}
		}
		else
		{
			continuePlay = false;
		}
	}

}

MyPoint & MyPoint::operator=(const MyPoint & point)
{
	this->px = point.px;
	this->py = point.py;
	// TODO: 在此处插入 return 语句
	return *this;
}
void InToDeque()
{
	Mydeque.clear();

	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			if (Array[i][j] == 0)
			{
				Mydeque.push_back(MyPoint(i, j));
			}
		}
	}
}

MyPoint PopPoint()
{
	MyPoint newPoint(-1, -1);
	if (Mydeque.size())
	{
		int ret = rand() % Mydeque.size();
		newPoint = Mydeque[ret];
		Mydeque.erase(Mydeque.begin() + ret);
	}
	return newPoint;
}

void printArray()
{
	system("cls");
	system("title=2048");
	for (int i = 0; i < MAXSIZE; ++i)
	{
		for (int j = 0; j < MAXSIZE; ++j)
		{
			cout << Array[i][j] << " ";
		}
		cout << endl;
	}
}

// 上移
void operatorUp()
{
	int tempArr[MAXSIZE] = { 0 };
	
	for (int j = 0; j < MAXSIZE; ++j)
	{
		bool NotCompare = false;
		int index = 0;
		for (int i = 0; i < MAXSIZE; ++i)
		{
			if (Array[i][j] != 0)
			{
				if (!NotCompare)
				{
					tempArr[index++] = Array[i][j];
					NotCompare = true;
				}
				else
				{
					if (tempArr[index - 1] == Array[i][j])
					{
						tempArr[index - 1] *= 2;
						NotCompare = false;
					}
					else
					{
						tempArr[index++] = Array[i][j];
					}
				}
			}
		}
		for (int k = 0; k < MAXSIZE; ++k)
		{
			Array[k][j] = tempArr[k];
			tempArr[k] = 0;
		}
	}
}

// 下移
void operatorDown()
{
	int tempArr[MAXSIZE] = { 0 };
	
	for (int j = 0; j < MAXSIZE; ++j)
	{
		bool NotCompare = false;
		int index = MAXSIZE - 1;
		for (int i = MAXSIZE-1; i>=0; --i)
		{
			if (Array[i][j] != 0)
			{
				if (!NotCompare)
				{
					tempArr[index--] = Array[i][j];
					NotCompare = true;
				}
				else
				{
					if (tempArr[index+ 1] == Array[i][j])
					{
						tempArr[index +1] *= 2;
						NotCompare = false;
					}
					else
					{
						tempArr[index--] = Array[i][j];
					}
				}
			}
		}
		for (int k = 0; k < MAXSIZE; ++k)
		{
			Array[k][j] = tempArr[k];
			tempArr[k] = 0;
		}	
	}
}

// 左移
void operatorLeft()
{
	int tempArr[MAXSIZE] = { 0 };
	for (int i = 0; i < MAXSIZE; ++i)
	{
		int index = 0;
		bool NotCompare = false;

		for (int j = 0; j <MAXSIZE; ++j)
		{
			if (Array[i][j] != 0)
			{
				if (!NotCompare)
				{
					tempArr[index++] = Array[i][j];
					NotCompare = true;
				}
				else
				{
					if (tempArr[index-1] == Array[i][j])
					{
						tempArr[index - 1] *= 2;
						NotCompare = false;
					}
					else
					{
						tempArr[index++] = Array[i][j];
					}
				}
			}
		}
		for (int k = 0; k < MAXSIZE; ++k)
		{
			Array[i][k] = tempArr[k];
			tempArr[k] = 0;
		}
	}
}

// 右移
void operatorRight()
{
	int tempArr[MAXSIZE] = { 0 };
	for (int i = 0; i < MAXSIZE; ++i)
	{
		int index = MAXSIZE-1;
		bool NotCompare = false;

		for (int j = MAXSIZE - 1; j>=0; --j)
		{
			if (Array[i][j] != 0)
			{
				if (!NotCompare)
				{
					tempArr[index--] = Array[i][j];
					NotCompare = true;
				}
				else
				{
					if (tempArr[index + 1] == Array[i][j])
					{
						tempArr[index + 1] *= 2;
						NotCompare = false;
					}
					else
					{
						tempArr[index--] = Array[i][j];
					}
				}
			}
		}
		for (int k = 0; k < MAXSIZE; ++k)
		{
			Array[i][k] = tempArr[k];
			tempArr[k] = 0;
		}
	}
}

// 检查行
bool checkingRow()
{
	for (int i = 0; i < MAXSIZE - 1; ++i)
	{
		for (int j = 0; j < MAXSIZE - 1; ++j)
		{
			if (Array[i][j] == Array[i][j + 1])
			{
				return true;
			}
		}
	}
	return false;
}
// 检查列
bool checkingCol()
{
	for (int j = 0; j < MAXSIZE - 1; ++j)
	{
		for (int i = 0; i < MAXSIZE - 1; ++i)
		{
			if (Array[i][j] == Array[i + 1][j])
			{ 
				return true;
			}	
		}
	}
	return false;
}

