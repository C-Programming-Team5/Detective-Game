#include "main.h"
#include "screen.h"

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitialPrint(void)
{
	CLS;
	system("title ESCAPE");

	gotoxy(53, 15); printf("새로 하기");
	gotoxy(53, 17); printf("이어 하기");
	gotoxy(53, 19); printf("게임 종료");
}

int StartScreen(void)
{
	int POS = 3;
	CursorView(0);
	system("COLOR 0F");
	InitialPrint();
	while (!GetAsyncKeyState(VK_RETURN))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			if (POS == 0)
			{
				POS = 2;
			}
			else
			{
				POS -= 1;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (POS == 2)
			{
				POS = 0;
			}
			else
			{
				POS ++;
			}
		}
		switch (POS)
		{
		case 0:
			SetColor(3);
			gotoxy(53, 15); printf("새로 하기");
			SetColor(15);
			gotoxy(53, 17); printf("이어 하기");
			gotoxy(53, 19); printf("게임 종료");
			break;
		case 1:
			gotoxy(53, 15); printf("새로 하기");
			SetColor(3);
			gotoxy(53, 17); printf("이어 하기");
			SetColor(15);
			gotoxy(53, 19); printf("게임 종료");
			break;
		case 2:
			gotoxy(53, 15); printf("새로 하기");
			gotoxy(53, 17); printf("이어 하기");
			SetColor(3);
			gotoxy(53, 19); printf("게임 종료");
			SetColor(15);
			break;
		default:
			break;
		}
		Sleep(100);
	}
	CLS;
}