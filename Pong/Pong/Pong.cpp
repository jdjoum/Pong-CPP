#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <conio.h>

enum Direction { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class Ball
{
private:
	//Current Position of the Ball
	int x, y;
	//Original Position of the Ball
	int ogX, ogY;
	//Holds the Direction of the Ball
	Direction dir;
public:

	Ball(int posX, int posY)
	{
		ogX = posX;
		ogY = posY;
		x = posX;
		y = posY;
		dir = STOP;
	}

	void Reset()
	{
		x = ogX;
		y = ogY;
		dir = STOP;
	}

	void changeDirection(Direction d)
	{
		dir = d;
	}

	void randomDirection()
	{
		dir = (Direction)((rand() % 6) + 1);
	}


	inline int getX() { return x; }
	inline int getY() { return y; }
	inline Direction getDirection() { return dir; }

	void Move()
	{
		switch (dir)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UPLEFT:
			x--; y--;
			break;
		case DOWNLEFT:
			x--; y++;
			break;
		case UPRIGHT:
			x++; y--;
			break;
		case DOWNRIGHT:
			x++; y++;
			break;
		}
	}

	friend std::ostream& operator<<(std::ostream& o, Ball b)
	{
		//Prints the ball coordrinates and the direction of the ball
		o << "Ball [" << b.x << "," << b.y << "][" << b.dir << "]" << std::endl;
		return o;
	}
};

class Paddle
{
private:
	int x, y;
	int ogX, ogY;
public:
	Paddle()
	{
		x = y = 0;
	}

	Paddle(int posX, int posY) : Paddle()
	{
		ogX = posX;
		ogY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset() { x = ogX; y = ogY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	friend std::ostream& operator<<(std::ostream& o, Paddle b)
	{
		//Prints the ball coordrinates and the direction of the ball
		o << "Paddle [" << b.x << "," << b.y << "]" << std::endl;
		return o;
	}
};

class gameManager
{
private:
	//Game Size
	int width, height;
	//Player Scores
	int score1, score2;
	//Keys to control Players
	char up1, down1, up2, down2;
	//Quit Trigger Variable
	bool quit;
	//To Initialize Ball and Paddle Players
	Ball* ball;
	Paddle* p1;
	Paddle* p2;

public:
	gameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new Ball(w / 2, h / 2 - 3);
		p1 = new Paddle(1, h / 2 - 3);
		p2 = new Paddle(w - 2, h / 2 - 3);
	}

	~gameManager()
	{
		delete ball, p1, p2;
	}

	//Function to increase player scorez
	void scoreUp(Paddle* p)
	{
		if (p == p1)
		{
			score1++;
		}
		else if (p == p2)
		{
			score2++;
		}
		ball->Reset();
		p1->Reset();
		p2->Reset();
	}
	void Draw()
	{
		system("cls");
		std::cout << " -------------Welcome to Ping Pong!-------------" << std::endl;
		std::cout << "---------Created By: Julian-Justin Djoum---------" << std::endl;
		std::cout << " _______________________________________________" << std::endl << std::endl;
		//Top Game Board Boundary
		for (int i = 0; i < width + 2; i++)
		{
			std::cout << "\xB2";
		}

		std::cout << std::endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballX = ball->getX();
				int ballY = ball->getY();
				int p1X = p1->getX();
				int p2X = p2->getX();
				int p1Y = p1->getY();
				int p2Y = p2->getY();

				//Left Game Board Boundary
				if (j == 0)
					std::cout << "\xB2";

				if (ballX == j && ballY == i)
					std::cout << "O";
				//Player 1 Paddle
				else if (p1X == j && p1Y == i)
					std::cout << "\xDB";
				//Player 2 Paddle
				else if (p2X == j && p2Y == i)
					std::cout << "\xDB";

				//Player 1 Paddle
				else if (p1X == j && p1Y + 1 == i)
					std::cout << "\xDB";
				//Player 1 Paddle
				else if (p1X == j && p1Y + 2 == i)
					std::cout << "\xDB";
				//Player 1 Paddle
				else if (p1X == j && p1Y + 3 == i)
					std::cout << "\xDB";

				//Player 2 Paddle
				else if (p2X == j && p2Y + 1 == i)
					std::cout << "\xDB";
				//Player 2 Paddle
				else if (p2X == j && p2Y + 2 == i)
					std::cout << "\xDB";
				//Player 2 Paddle
				else if (p2X == j && p2Y + 3 == i)
					std::cout << "\xDB";

				//Blank Spaces Within Game Board
				else
					std::cout << " ";
				//Right Game Board Boundary
				if (j == width - 1)
					std::cout << "\xB2";
			}
			std::cout << std::endl;
		}
		//Bottom Game Board Boundary
		for (int i = 0; i < width + 2; i++)
			std::cout << "\xB2";
		std::cout << std::endl;

		std::cout << "Score 1: " << score1 << std::endl << "Score 2: " << score2 << std::endl;
	}
	void Input()
	{
		ball->Move();

		int ballX = ball->getX();
		int ballY = ball->getY();
		int p1X = p1->getX();
		int p2X = p2->getX();
		int p1Y = p1->getY();
		int p2Y = p2->getY();

		if (_kbhit())
		{
			char current = _getch();
			if (current == up1)
				if (p1Y > 0)
					p1->moveUp();
			if (current == up2)
				if (p2Y > 0)
					p2->moveUp();
			if (current == down1)
				if (p1Y + 4 < height)
					p1->moveDown();
			if (current == down2)
				if (p2Y + 4 < height)
					p2->moveDown();

			if (ball->getDirection() == STOP)
			{
				ball->randomDirection();
			}

			if (current == 'q')
				quit = true;
		}
	}

	void Logic()
	{
		int ballX = ball->getX();
		int ballY = ball->getY();
		int p1X = p1->getX();
		int p2X = p2->getX();
		int p1Y = p1->getY();
		int p2Y = p2->getY();

		//Left Paddle
		for (int i = 0; i < 4; i++)
		{
			if (ballX == p1X + 1)
			{
				if (ballY == p1Y + i)
					ball->changeDirection((Direction)((rand() % 3) + 4));
			}
		}

		//Right Paddle
		for (int i = 0; i < 4; i++)
		{
			if (ballX == p2X - 1)
			{
				if (ballY == p2Y + i)
					ball->changeDirection((Direction)((rand() % 3) + 1));
			}
		}

		//Bottom Wall Bouncing
		if (ballY == height - 1)
		{
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		}
		//Top Wall Bouncing
		if (ballY == 0)
		{
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		}
		//Right Wall Scoring
		if (ballX == width - 1)
		{
			scoreUp(p1);
		}
		//Left Wall Scoring
		if (ballX == 0)
		{
			scoreUp(p2);
		}
	}
	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};

int main()
{
	gameManager b(40, 20);
	b.Run();
	return 0;
}