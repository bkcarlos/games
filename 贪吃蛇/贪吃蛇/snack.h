#pragma once
#include<iostream>
#include<deque>
#include <windows.h>
#include <string>

using namespace std;

enum direction
{
	Pause, Up, Down, Left, Right
};


// ������ͼ
	// ������ͷ @
	// ʳ��
// ��ӡ��ͼ
// �жϰ���
// �ж�ʳ���Ƿ񱻳�
// ������ͷ
// -> ����ʳ��

struct Point
{
	Point() {}
	Point(int x, int y);
	Point &operator=(const Point& point);
	bool operator==(const Point& point);
	Point &operator+=(const Point&point);
	int px;
	int py;
};

class Map
{
	friend void createMap(Map &map);
	friend void showMap(Map &map);
	friend bool SnackEatFood(Map &map);
	friend void Play(Map &map);
	friend void createFood(Map &map);
	friend bool decideSnack(Map &map);

public:
	Map();
	Map(int row, int col);
private:
	deque<Point> SnackBody;

	Point SnackHead;
	Point Food;
	bool flagFood;

	// �� ����
	int mRow;

	// �� ����
	int mCol;

	// ��ͼ
	char **pMap;

	direction SnackGO;
};

void createMap(Map &map);
void showMap(Map &map);
bool SnackEatFood(Map &map);
void Play(Map &map);
void createFood(Map &map);
bool decideSnack(Map &map);
