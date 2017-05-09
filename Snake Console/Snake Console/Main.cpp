#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_S 115
#define KEY_A 97

enum MoveEnum { UP, DOWN, LEFT, RIGHT, null };
MoveEnum moveEnum = null;

int key = NULL;

const int sizeX = 20;
const int sizeY = 20;
const int refreshTime = 200;

int headX = 10;
int headY = 10;

int foodX;
int foodY;

bool found = false;

int score = 0;

int bodyCounter = 1;
int posX[sizeX * sizeY];
int posY[sizeX * sizeY];
int lastPosX[sizeX * sizeY];
int lastPosY[sizeX * sizeY];

int spaceCounter = 0;

void drawGame();
void changePos();
void movement();

int main()
{
	srand(time(0));
	foodX = (1 + rand() % (sizeX - 2));
	foodY = (1 + rand() % (sizeY - 2));
	while (1)
	{
		Sleep(refreshTime);
		system("cls");
		changePos();
		movement();
		drawGame();
	}
	return 0;
}

void drawGame()
{
	for (int y = 0; y < sizeY; y++)
	{
		if (y == 0 || y == sizeY - 1)
		{
			for (int i = 0; i < sizeX; i++)
			{
				std::cout << "* ";
			}
			std::cout << std::endl;
		}
		else
		{
			for (int x = 0; x < sizeX; x++)
			{
				if (x == 0 || x == sizeX - 1)
				{
					std::cout << "*";
				}
				else
				{
					found = false;

					// If player meets food then score
					if (headX == foodX && headY == foodY)
					{
						score++;
						bodyCounter++;
						if (moveEnum == UP)
						{
							posX[bodyCounter - 1] = posX[bodyCounter - 2];
							posY[bodyCounter - 1] = posY[bodyCounter - 2] + 1;
						}
						if (moveEnum == DOWN)
						{
							posX[bodyCounter - 1] = posX[bodyCounter - 2];
							posY[bodyCounter - 1] = posY[bodyCounter - 2] - 1;
						}
						if (moveEnum == LEFT)
						{
							posX[bodyCounter - 1] = posX[bodyCounter - 2] + 1;
							posY[bodyCounter - 1] = posY[bodyCounter - 2];
						}
						if (moveEnum == RIGHT)
						{
							posX[bodyCounter - 1] = posX[bodyCounter - 2] - 1;
							posY[bodyCounter - 1] = posY[bodyCounter - 2];
						}
						foodX = (1 + rand() % (sizeX - 2));
						foodY = (1 + rand() % (sizeY - 2));
					}

					// If lost
					if (headX == 1 || headX == 18 || headY == 1 || headY == 18)
					{
						Sleep(1000);
						headX = 10;
						headY = 10;
						foodX = (1 + rand() % (sizeX - 2));
						foodY = (1 + rand() % (sizeY - 2));
						moveEnum = null;
						score = 0;
						bodyCounter = 1;
						spaceCounter = 0;
						key = NULL;
					}

					// Draw parts

					for (int i = 0; i < bodyCounter; i++)
					{
						if (x == posX[i] && y == posY[i])
						{
							std::cout << "o ";
							found = true;
						}
					}

					// If food meets drawing coordinates then draw food
					spaceCounter = 0;
					if (x == foodX && y == foodY)
					{
						std::cout << "$";
						spaceCounter++;
					}

					if (found == true)
					{
						continue;
					}

					if (spaceCounter == 0)
						std::cout << "  ";
					if (spaceCounter == 1)
						std::cout << " ";

					if (x == sizeX - 2)
					{
						std::cout << " ";
					}

				}
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << "Score: " << score << std::endl;
}

void changePos()
{
	if (_kbhit() != 0)
	{
		key = _getch();

		if (key == KEY_A)
			bodyCounter++;
		if (key == KEY_UP)
			moveEnum = UP;
		else if (key == KEY_DOWN)
			moveEnum = DOWN;
		else if (key == KEY_LEFT)
			moveEnum = LEFT;
		else if (key == KEY_RIGHT)
			moveEnum = RIGHT;
		else if (key == KEY_S)
			moveEnum = null;
	}
}

void movement()
{
	for (int i = 0; i < bodyCounter; i++)
	{
		if (i == 0)
		{
			lastPosX[0] = headX;
			lastPosY[0] = headY;
			continue;
		}
		lastPosX[i] = posX[i];
		lastPosY[i] = posY[i];
	}

	if (key != NULL)
	{
		if (moveEnum == UP)
			headY--;
		if (moveEnum == DOWN)
			headY++;
		if (moveEnum == LEFT)
			headX--;
		if (moveEnum == RIGHT)
			headX++;
	}

	for (int i = 0; i < bodyCounter; i++)
	{
		if (i == 0)
		{
			posX[0] = headX;
			posY[0] = headY;
			continue;
		}
		posX[i] = lastPosX[i - 1];
		posY[i] = lastPosY[i - 1];
	}
}
