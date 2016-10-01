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


// 产生地图
	// 生成蛇头 @
	// 食物
// 打印地图
// 判断按键
// 判断食物是否被吃
// 连接蛇头
// -> 生成食物

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

	// 行 向下
	int mRow;

	// 列 向右
	int mCol;

	// 地图
	char **pMap;

	direction SnackGO;
};

void createMap(Map &map);
void showMap(Map &map);
bool SnackEatFood(Map &map);
void Play(Map &map);
void createFood(Map &map);
bool decideSnack(Map &map);
