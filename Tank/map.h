#include <SFML\Graphics.hpp>
const int HEIGHT_SIZE = 25;//размер карты высота
const int WIDTH_SIZE = 40;//размер карты ширина 



sf::String TileMap[HEIGHT_SIZE] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   s                                  0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

//void randomMapGenerate()
//{
//	int randomElementX = 0;
//	int randomElementY = 0;
//	srand(time(0));
//	int countStone = 2;
//
//	while (countStone > 2)
//	{
//		randomElementX = 1 + rand() % (WIDTH_SIZE - 1);
//		randomElementY = 1 + rand() % (HEIGHT_SIZE - 1);
//		if (TileMap[randomElementY][randomElementY] == ' ')
//		{
//			TileMap[randomElementY][randomElementY] = 's';
//			countStone--;
//		}
//	}
//}