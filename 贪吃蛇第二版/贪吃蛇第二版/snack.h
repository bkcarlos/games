#include <iostream>
#include<cstring>
#include <windows.h>
#include <list>
#include<ctime>
#include <algorithm>

using namespace std;




// ��������ʵ��Ԫ��
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
	
	//�ж��������Ƿ����
	bool operator==(const Point& point);
	void operator=(const Point& point);
};

// ��
struct Sanck
{
	// ��ͷ
	Point SnackHead;
	// ����
	list<Point> SnackBody;
	sanckGoDirection direction;
};


class Map
{
	// ��ǽ
	friend void DrawWall( Map& map);
	friend void Position(short x, short y, Map &map);
	friend void CreateFood(Map &map);
	friend void DrawSnack(Map &map);
	friend void SnackGO(Map &map);
	friend bool SnackGOFlag(Map &map);
public:
	Map();

private:
	// ����  y
	short mapCol;

	// ���� x
	short mapRow;
	HANDLE Console;
	Sanck sanck;
	Point food;
};



