#include "snack.h"
#include <ctime>


/*
�����Ҫ�����ٶȣ����޸��ļ� snack.cpp play() �����е�ʱ�亯��
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