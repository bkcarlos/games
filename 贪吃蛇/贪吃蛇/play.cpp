#include "snack.h"
#include <ctime>


/*
如果需要调节速度，请修改文件 snack.cpp play() 函数中的时间函数
*/

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Map map(20,20);
	createMap(map);
	showMap(map);
	Play(map);

	system("pause");
	return 0;
}