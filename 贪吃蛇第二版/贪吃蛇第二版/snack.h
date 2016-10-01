#include <iostream>
#include<cstring>
#include <windows.h>
#include <list>
#include<ctime>
#include <algorithm>

using namespace std;




// 定义四种实体元素
const char SNACKHEAD = '@';
const char FOOD ='#';
const char WALL = '*';
const char SNACKBODY = 'O';

enum sanckGoDirection {
	Pause,Up,Down,Left,Right
};

struct Point 
{
	int mx;
	int my;
	
	//判断两个点是否相等
	bool operator==(const Point& point);
	void operator=(const Point& point);
};

// 蛇
struct Sanck
{
	// 蛇头
	Point SnackHead;
	// 蛇身
	list<Point> SnackBody;
	sanckGoDirection direction;
};


class Map
{
	// 画墙
	friend void DrawWall( Map& map);
	friend void Position(short x, short y, Map &map);
	friend void CreateFood(Map &map);
	friend void DrawSnack(Map &map);
	friend void SnackGO(Map &map);
	friend bool SnackGOFlag(Map &map);
public:
	Map();

private:
	// 向下  y
	short mapCol;

	// 向右 x
	short mapRow;
	HANDLE Console;
	Sanck sanck;
	Point food;
};



