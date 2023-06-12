#include "stdafx.h"

void SetUp();
bool Update();
void Render();

enum Direction // 대소문자 입력 모두 받으려고 만듬
{
	A = 65,
	a = 97,
	S = 83,
	s = 115,
	K = 75,
	k = 107,
	L = 76,
	l = 108
};

struct Note
{
	int x;
	int y;
	bool isNote;
};

const int boardRowMax = 6;
const int boardColMax = 25;

const float delaySec = 0.5f;

int score = 0;

Note note[boardColMax]; // 별피하기에서 별 만들었던걸 연상시켜서 음표 만들어봄

int main()
{
	SetUp();

	while (Update())
	{
		Render();
	}

	return 0;
}

void SetUp() // 초기 화면 및 초기화
{
	system("Rhythm game");
	system("mode con:cols=70 lines=30");

	{
		HANDLE hConsole;
		CONSOLE_CURSOR_INFO ConsoleCursor;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		ConsoleCursor.bVisible = 0;
		ConsoleCursor.dwSize = 1;

		SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	}
	
	std::cout << "리듬 게임" << std::endl;

	system("pause");
	system("cls");

	for (int i = 0; i < boardColMax; i++)
	{
		note[i].isNote = false;
	}
}

bool Update() // 키 입력시 기능 및 음표 생성, 이동, 소멸 함수 들어가있음
{
	if (_kbhit())
	{
		int key;

		key = _getch();

		for (int i = 0; i < boardColMax; i++)
		{
			if (note[i].y == boardColMax)
			{
				if (note[i].x == 1 && (key == A || key == a))
				{
					score += 100;
					note[i].isNote = false;
				}
				else if (note[i].x == 2 && (key == S || key == s))
				{
					score += 100;
					note[i].isNote = false;
				}
				else if (note[i].x == 3 && (key == K || key == k))
				{
					score += 100;
					note[i].isNote = false;
				}
				else if (note[i].x == 4 && (key == L || key == l))
				{
					score += 100;
					note[i].isNote = false;
				}
				//else
				//	 score -= 100;
			}
		}
	}

	for (int i = 0; i < boardColMax; i++)
	{
		if (note[i].isNote == false)
		{
			note[i].x = Math::Random(1, 4);
			note[i].y = 0;
			note[i].isNote = true;
			break;
		}
	}

	for (int i = 0; i < boardColMax; i++)
	{
		if (note[i].isNote)
		{
			note[i].y++;
		}
	}

	for (int i = 0; i < boardColMax; i++)
	{
		if (note[i].isNote && note[i].y >boardColMax)
		{
			note[i].isNote = false;
			// score -= 100;
		}
	}

	return true;
}

void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Render() // 출력부
{
	system("cls");

	for (int i = 0; i < boardRowMax; i++)
	{
		gotoxy(i, 0);
		std::cout << "■";

		for (int j = 0; j < boardColMax; j++)
		{
			if (i == 0 || i == boardRowMax - 1)
			{
				gotoxy(i, j);
				std::cout << "■";
			}
		}
		gotoxy(i, boardColMax);
		std::cout << "〓";

		gotoxy(i, boardColMax + 1);
		switch (i)
		{
		case 1:
			std::cout << "A ";
		case 2:
			std::cout << "S ";
		case 3:
			std::cout << "K ";
		case 4:
			std::cout << "L ";
		}
	}
	
	gotoxy(boardRowMax + 1, boardColMax);
	std::cout << "점수 : " << score;

	for (int i = 0; i < boardColMax; i++)
	{
		if (note[i].isNote)
		{
			gotoxy(note[i].x, note[i].y);
			std::cout << "♪";
		}
	}

	Sleep(500); // 렌더링 간격
}

/*
	음표가 연속으로 나올때 키를 꾹 눌러서 연속으로 점수를 얻게하는 방식 미구현
	Sleep(500)으로 0.5초 안에 키입력을 받으면 점수가 올라가는데 키입력과 싱크가 좀 안맞는 느낌이 듬
	Timer 클래스 사용 못함
*/