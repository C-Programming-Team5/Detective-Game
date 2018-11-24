#include "main.h"
#include "screen.h"
#include "player.h"
#include "save_io.h"

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
	int POS = 2;
	CursorView(0);
	system("COLOR 0F");
	InitialPrint();
	while (!GetAsyncKeyState(VK_RETURN))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			if (POS <= 0)
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
			if (POS >= 2)
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
	return POS;
}

void PrintClues(Player *player)
{
	CLS;
	puts((player->cleared & 1) ? "힌트 1: 그것은 어디에도 없다." : "");
	puts((player->cleared & 2) ? "힌트 2: 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다." : "");
	puts((player->cleared & 4) ? "힌트 3: 눈에 보이진 않지만, 많은 이름을 갖고 있다." : "");
	puts((player->cleared & 8) ? "힌트 4: 그것에게 멈춤이란 곧 죽음이다." : "");
	puts((player->cleared & 16) ? "힌트 5: 그것은 세상에서 가장 가볍고 자유로운 존재이다." : "");
	return;
}

void PrintEnding(int flag)
{
	CLS;
	switch (flag)
	{
		case GAME_OVER:
			puts("GAME OVER");
			puts("Game Over 단서를 모아 다시 도전하자.");
			break;
		case GAME_CLEAR:
			puts
			(
				"문이 열렷다.\n"
				"문을 열자 보이는 것은 전산실이었다.\n"
				"아무래도 전산실 입구를 나가는 문이라고 착각한 것 같다.\n"
				"다시 강의실로 돌아가 도어락이 없는 평범한 문을 열고 밖으로 나왔다."
			);
		default:
			break;
	}
	return;
}

void PrintSaveList(Player save[])
{
	int i = 0;

	CLS;
	for (i = 0; i < SAVESIZE; i++)
	{
		printf("%d번째 세이브\n", i);
		printf("맞힌 퀴즈 개수: %d\n", GetClearedQuizCount(save, i));
		printf("플레이 시간: %d\n\n", save[i].playTime);
	}
	return;
}