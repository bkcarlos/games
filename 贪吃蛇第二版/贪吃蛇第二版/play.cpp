#include "snack.h"

void play()
{
	Map map;
	DrawWall(map);
	
	DrawSnack(map);
	CreateFood(map);
	SnackGO(map);
}


int main()
{
	play();

	//cout << endl;
	
	//system("pause");
	return 0;
}