#include "main.h"
#include "screen.h"
#include "player.h"
#include "save_io.h"

TCHAR Getch(void)
{
	DWORD mode, cc;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE); // 입력 핸들러를 가져옵니다. 이를 통해 입력을 제어할 수 있습니다.
	TCHAR c = 0;
	if (h == NULL)
	{
		return 0; // console not found
	}
	GetConsoleMode(h, &mode); // 원래 콘솔의 입력모드를 가져옵니다.
	SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)); // 원래 콘솔의 입력 모드에서 엔터 줄바꿈과 에코 기능을 비활성화 합니다.
	ReadConsole(h, &c, 1, &cc, NULL); // 콘솔 입력을 읽습니다.
	SetConsoleMode(h, mode); // 콘솔의 모드를 원래 상태로 되돌립니다.
	return c;
}

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

void GotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitialPrint(void)
{
	CLS;
	system("title ESCAPE");

	GotoXY(53, 15); fputs("새로 하기", stdout);
	GotoXY(53, 17); fputs("이어 하기", stdout);
	GotoXY(53, 19); fputs("게임 종료", stdout);
}

int StartScreen(void)
{
	int POS = 2;
	CursorView(0);
	SetColor(15);
	InitialPrint();
	while (!GetAsyncKeyState(VK_RETURN))
	{
        Title();
		if (GetAsyncKeyState(VK_UP))
		{
			POS = (POS + 2) % 3;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			POS = (POS + 1) % 3;
		}

		SetColor(POS == 0 ? 3 : 15);
		GotoXY(53, 15); fputs("새로 하기", stdout);
		SetColor(POS == 1 ? 3 : 15);
		GotoXY(53, 17); fputs("이어 하기", stdout);
		SetColor(POS == 2 ? 3 : 15);
		GotoXY(53, 19); fputs("게임 종료", stdout);
		SetColor(15);
		
		Sleep(500);
	}
	CLS;
	return POS;
}

void PrintClues(const Player * const player, int number)
{
	CLS;

	if (number == -1)
	{
		fputs((player->cleared & 1) ? clues[0] : "", stdout);
		fputs((player->cleared & 2) ? clues[1] : "", stdout);
		fputs((player->cleared & 4) ? clues[2] : "", stdout);
		fputs((player->cleared & 8) ? clues[3] : "", stdout);
		fputs((player->cleared & 16) ? clues[4] : "", stdout);
	}
	else
	{
		if (0 <= number && number <= 4)
		{
			fputs((player->cleared & (1 << number)) ? clues[number] : "", stdout);
		}
	}
	
	return;
}

void PrintSaveList(const Player save[])
{
	int i = 0;

	CLS;
	for (i = 0; i < SAVESIZE; i++)
	{
		printf("%d번째 세이브\n", i + 1);
		printf("맞힌 퀴즈 개수: %d\n", GetClearedQuizCount(save, i));
		printf("플레이 시간: %d 초\n\n", save[i].playTime);
	}
	return;
}

void Prologue(void)
{
	int i = 0;

	LobbyScreen();
	GotoXY(1, 25); printf(".");
	Sleep(1000); 
	GotoXY(2, 25); printf(".");
	Sleep(1000);
	GotoXY(3, 25); printf(".");
	Sleep(1000);
	GotoXY(4, 25); printf(".");
	Sleep(1000);
	GotoXY(5, 25); printf(".");
	Sleep(1000);
	GotoXY(6, 25); printf(".");

	GotoXY(1, 25);
	for (i = 0; i < 6; i++)
	{
		printf(".");
		Sleep(1000);
	}

	Sleep(1500);
	PlaySound(TEXT("searching.wav"), NULL, SND_ASYNC);//소리를 재생하고 바로 다음코드를 실행합니다.
	GotoXY(1, 25); printf("지끈거리는 머리를 붙잡으며 정신을 차렸다.");
	Sleep(3000);
	GotoXY(1, 25); printf("                                                                                       ");
	Sleep(100);
	GotoXY(1, 25); printf("어제 나는 분명 집에 간 것 같았는데, 강의실 안이다.");
	Sleep(3000);
	GotoXY(1, 25); printf("                                                                                       ");
	Sleep(100);
	GotoXY(1, 25); printf("집에 가기 위해 강의실문을 열었다.");
	Sleep(3000);
	GotoXY(1, 25); printf("                                                                                       ");
	Sleep(100);
	PlaySound(TEXT("lock.wav"), NULL, SND_ASYNC);
	GotoXY(1, 25); printf("자물쇠가 내부에 설치 되어있어 열리지 않는다.");
	Sleep(3000);
	GotoXY(1, 25); printf("                                                                                       ");
	Sleep(100);
	GotoXY(1, 25); printf("휴대폰도 켜지지 않는다. 강의실을 나가기 위해선 5개의 비밀번호가 필요한 것 같다.");
	Sleep(3000);
	GotoXY(1, 25); printf("                                                                                       ");
	Sleep(100);
	GotoXY(1, 25); printf("혹시라도 조교가 두고 간 비밀번호 종이가 있을 수도 있기 때문에 강의실 내부를 찾아보기로 했다.");
	Sleep(3000);
	CLS; //프롤로그 대사창을 모두 지웁니다.
}

void LobbyScreen(void) //아스키 코드로 구현한 그림입니다.
{
	
	printf("\n");
	printf("                    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("                   ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
	printf("                   ┃ ┃                                                          ┃ ┃\n");
	printf("   ┌─────┐         ┃ ┃                                                          ┃ ┃\n");
	printf("   │공 지│         ┃ ┃                                                          ┃ ┃\n");
	printf("   │     │         ┃ ┃                                                          ┃ ┃\n");
	printf("   └─────┘         ┃ ┃                                                          ┃ ┃\n");
	printf("                   ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
	printf("                    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("                  ===================================================================\n");
	printf("       ┏━━━━━━━━━━━━━━━┓         ┏━━━━━━━━━━━━━━━┓                  ┏━━━━━━━━━━━━━━━┓         ┏━━━━━━━━━━━━━━━┓       \n");
	printf("       ┃ ■■■■■■■┃         ┃ ■■■■■■■┃                  ┃ ■■■■■■■┃         ┃ ■■■■■■■┃\n");
	printf("       ┃ ■■■■■■■┃         ┃ ■■■■■■■┃                  ┃ ■■■■■■■┃         ┃ ■■■■■■■┃\n");
	printf("       ┃ ■■■■■■■┃         ┃ ■■■■■■■┃                  ┃ ■■■■■■■┃         ┃ ■■■■■■■┃\n");
	printf("      ─┃ ■■■■■■■┃─────────┃ ■■■■■■■┃─               ──┃ ■■■■■■■┃─────────┃ ■■■■■■■┃─\n");
	printf("     / ┗━━━━━━━━━━━━━━━┛         ┗━━━━━━━━━━━━━━━┛  ＼           /  ┗━━━━━━━━━━━━━━━┛         ┗━━━━━━━━━━━━━━━┛  ＼\n");
	printf("    /   ━━━━━┛   ┗━━━━━           ━━━━━┛   ┗━━━━━     ＼        /    ━━━━━┛   ┗━━━━━           ━━━━━┛   ┗━━━━━     ＼\n");
	printf("   /   ┗━━━━━━━━━━━━━━━┛         ┗━━━━━━━━━━━━━━━┛      ＼     /    ┗━━━━━━━━━━━━━━━┛         ┗━━━━━━━━━━━━━━━┛      ＼\n");
	printf("  ┌──────────────────────────────────────────────────────┐    ┌───────────────────────────────────────────────────────┐\n");
	printf("  └──────────────────────────────────────────────────────┘    └───────────────────────────────────────────────────────┘\n");
	printf("  │   │                                              │   │    │   │                                               │   │\n");
	printf("  │   │                                              │   │    │   │                                               │   │\n");
	printf("________________________________________________________________________________________________________________________\n");
	//아래는 대사를 입력할 공간입니다.
}

int LobbyPlay(void)
{
	int select = 0;
	CLS;
	LobbyScreen();
	GotoXY(2, 25);  printf("이제 무엇을 할까? <키보드로 조작하고 엔터키를 눌러 결정한다.>");
	int POS = 4;
	CursorView(0);
	SetColor(15);
	while (!GetAsyncKeyState(VK_RETURN))
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			POS = (POS + 4) % 5;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			POS = (POS + 1) % 5;
		}

		SetColor(POS == 0 ? 3 : 15);
		GotoXY(1, 27); printf("*물건을 찾아본다");
		SetColor(POS == 1 ? 3 : 15);
		GotoXY(21, 27); printf("*단서를 본다");
		SetColor(POS == 2 ? 3 : 15);
		GotoXY(41, 27); printf("*자물쇠를 연다");
		SetColor(POS == 3 ? 3 : 15);
		GotoXY(61, 27); printf("*저장한다");
		SetColor(POS == 4 ? 3 : 15);
		GotoXY(81, 27); printf("*종료한다");
		SetColor(15);

		Sleep(500);
	}
	CLS;
	return POS;
}

int SelectItem(void)
{
	GotoXY(2, 25); printf("어떤 물건부터 찾아볼까?");
	int POS = 5;

	CursorView(0);
	SetColor(15);
	while (!GetAsyncKeyState(VK_RETURN))
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			POS = (POS + 5) % 6;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			POS = (POS + 1) % 6;
		}

		SetColor(POS == 0 ? 3 : 15);
		GotoXY(1, 27); printf("*컴퓨터");
		SetColor(POS == 1 ? 3 : 15);
		GotoXY(21, 27); printf("*책상 밑");
		SetColor(POS == 2 ? 3 : 15);
		GotoXY(41, 27); printf("*책상 위");
		SetColor(POS == 3 ? 3 : 15);
		GotoXY(61, 27); printf("*칠판");
		SetColor(POS == 4 ? 3 : 15);
		GotoXY(81, 27); printf("*포스터");
		SetColor(POS == 5 ? 3 : 15);
		GotoXY(101, 27); printf("*돌아가기");
		SetColor(15);

		Sleep(500);
	}
	
	return POS;
}


void Quiz(int number)
{
	int index[] = {3, 4, 3, 3, 3};
	int i = 0;
	vvfp quizScreen[5] = {Quiz1Screen, Quiz2Screen, Quiz3Screen, Quiz4Screen, Quiz5Screen};
	SetColor(15);
	CLS;
	for (i = 0; i < index[number]; i++)
	{
		quizScreen[number]();
		GotoXY(1, 25);
		puts(quiz[number][i]);
		WAITFORKEY('n');
		CLS;
	}
	return;
}

void Answer(Player *player, int number)
{
	int index[] = {4, 5, 3, 4, 4};
	int rightAnswer[] = {2, 0, 2, 0, 2};
	int POS = 0, i = 0;
	vvfp quizScreen[5] = { Quiz1Screen, Quiz2Screen, Quiz3Screen, Quiz4Screen, Quiz5Screen };

	CLS;
	SetColor(15);
	quizScreen[number]();
	CursorView(0);
	SetColor(15);
	while (!GetAsyncKeyState(VK_RETURN)) 
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			POS = (POS + index[number] - 1) % index[number];
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			POS = (POS + 1) % index[number];
		}

		for (i = 0; i < index[number]; i++)
		{
			SetColor(POS == i ? 3 : 15);
			GotoXY(21 + i * 20, 27);
			fputs(answer[number][i], stdout);
		}
		Sleep(500);
	}
	CLS;
	SetColor(15);
	quizScreen[number]();

	if (POS == rightAnswer[number])
	{
		GotoXY(1, 25);
		printf("단서가 나타났다!");
		player->cleared |= (1 << number);
		GotoXY(1, 26);
		PrintClues(player, number);
		GotoXY(1, 27);
		printf("'n'을 눌러 다른 물건도 찾아보자.");
	}
	else
	{
		GotoXY(1, 25);
		printf("아무 일도 일어나지 않았다.");
		GotoXY(1, 26);
		printf("'n'을 눌러 다른 물건도 찾아보자.");
	}
	WAITFORKEY('n');
	CLS;
	return;
}

void PrintDoor(void)
{
	CLS;
	fputs
	(
		"                                         MMMMMMMMMMMMMMMMMMMMMM\n"
		"                                         MMMMMMMMMMMMMMMMMMMMMM\n"
		"                                         MMM                MMM\n"
		"                                         MMM                MMM\n"
		"                                         MMM                MMM\n"
		"                                         MMM    MMMMMMMM    MMM\n"
		"                                         MMM    M M  M M    MMM\n"
		"                                         MMM    M M  M M    MMM\n"
		"                                         MMM    M M  M M    MMM\n"
		"                                         MMM    M M  M M  MMMMM\n"
		"                                         MMM    MMMMMMMM  MMMMM\n"
		"                                         MMM    M      M  MMMMM\n"
		"                                         MMM    M  MM  M    MMM\n"
		"                                         MMM    M  MM  M    MMM\n"
		"                                         MMM    M      M    MMM\n"
		"                                         MMM    MMMMMMMM    MMM\n"
		"                                         MMM                MMM\n"
		"                                         MMM                MMM\n"
		"                                         MMM                MMM\n"
		"                                         MMN                MMM",
		stdout
	);
}

void PrintDoor1(void)
{
    CLS;
    fputs(
            "                                         MMMMMMMMMMMMMMMMMMMMMMMMM\n"
            "                                         MM MM■■■■■■■■■MM\n"
            "                                         MM  MMM■■■■■■■■MM\n"
            "                                         MM   MM■■■■■■■■MM\n"
            "                                         MM    MMM■■■■■■■MM\n"
            "                                         MM     MM■■■■■■■MM\n"
            "                                         MM      MMM■■■■■■MM\n"
            "                                         MM       MM■■■■■■MM\n"
            "                                         MM        MMM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM      MM MM■■■■■MM\n"
            "                                         MM      MM MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                         MM         MM■■■■■MM\n"
            "                                           MM       MMMMMMMMMMMMMM\n"
            "                                             MM     MM\n"
            "                                               MM   MM\n"
            "                                                  MMMM",
            stdout
            );
}

void PrintDoor2(void)
{
    CLS;
    fputs
        (
            "               MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MM                       MM■■■■■■■■■■■MM\n"
            "               MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
            stdout
            );
}

int OpenLock(void)
{
	char CorrectPW[] = "wind";
	char answer[5] = "";

	while (getchar() != '\n');
	PrintDoor();
	GotoXY(1, 25);
	fputs("암호를 입력하세요: ____", stdout);
	GotoXY(20, 25);
	fgets(answer, sizeof(answer), stdin);

	
	if (strcmp(CorrectPW, answer) == 0)
	{
        PrintDoor();
        Sleep(2000);
        PrintDoor1();
        Sleep(2000);
        PrintDoor2();
        Sleep(2000);
        CLS;
		return GAME_CLEAR;
	}
	else
	{
		return GAME_OVER;
	}
}

void Quiz1Screen(void) //아스키 코드로 구현한 그림입니다.
{
    printf("\n");
    printf("                              ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("                             ┃  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┃                                                          ┃  ┃\n");
    printf("                             ┃  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛  ┃\n");
    printf("                              ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("      ──────────────────────────────────────────────────┃        ┃─────────────────────────────────────────────\n");
    printf("     /                              ━━━━━━━━━━━━━━━━━━━━┛        ┗━━━━━━━━━━━━━━━━━━━━                          ＼\n");
    printf("    /                              ┃                                                  ┃                           ＼\n");
    printf("   /                                ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━                              ＼\n");
    printf("  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("  └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("________________________________________________________________________________________________________________________\n");
    //아래는 대사를 입력할 공간입니다.
}

void Quiz2Screen(void) //아스키 코드로 구현한 그림입니다.
{
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("      ─────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    printf("     /                                                                                                          ＼\n");
    printf("    /                                                                                                             ＼\n");
    printf("   /                                                                                                                ＼\n");
    printf("  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("  │                                                                                                                  │\n");
    printf("  └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("  │   │                                  __________                                                              │   │\n");
    printf("  │   │                                 /         /                                                              │   │\n");
    printf("  │   │                                / Quiz 2  /                                                               │   │\n");
    printf("  │   │                               /         /                                                                │   │\n");
    printf("  │   │                              /_________/                                                                 │   │\n");
    printf("  │___│                                                                                                          │___│\n");
    printf("________________________________________________________________________________________________________________________\n");
    //아래는 대사를 입력할 공간입니다.
}

void Quiz3Screen(void) //아스키 코드로 구현한 그림입니다.
{
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("         ───────────────────────────────────────────────────────────────────────────────────────────────\n");
    printf("        /                                 ____________                                                    ＼\n");
    printf("       /                                 /           /                                                      ＼\n");
    printf("      /                                 /  Quiz 3   /                                                         ＼\n");
    printf("     /                                 /           /                                                            ＼\n");
    printf("    /                                 /___________/                                                               ＼\n");
    printf("   /                                                                                                                ＼\n");
    printf("  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("  └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("  │   │                                                                                                          │   │\n");
    printf("  │___│                                                                                                          │___│\n");
    printf("________________________________________________________________________________________________________________________\n");
    //아래는 대사를 입력할 공간입니다.
}

void Quiz4Screen(void)
{
    printf("\n");
    printf("                    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("                   ┃ ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                     ┌─────●────┐                                          ┃ ┃\n");
    printf("                   ┃ ┃                     │   Quiz 4  │                                          ┃ ┃\n");
    printf("                   ┃ ┃                     │           │                                          ┃ ┃\n");
    printf("                   ┃ ┃                     │           │                                          ┃ ┃\n");
    printf("                   ┃ ┃                     │           │                                          ┃ ┃\n");
    printf("                   ┃ ┃                     └───────────┘                                          ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┃                                                                            ┃ ┃\n");
    printf("                   ┃ ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ ┃\n");
    printf("                    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("                  =====================================================================================\n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("________________________________________________________________________________________________________________________\n");
}

void Quiz5Screen(void)
{
    printf("\n");
    printf("                    ●────────────────────────────────────●\n");
    printf("                    │                                    │\n");
    printf("                    │           실습실 이용 방법         │\n");
    printf("                    │                                    │\n");
    printf("                    │        1. 이용 시간을 지킨다       │\n");
    printf("                    │                                    │\n");
    printf("                    │        2. 다른 SW 설치 금지        │\n");
    printf("                    │                                    │\n");
    printf("                    │        3. 음식물 섭취 금지         │\n");
    printf("                    │                                    │━━●━━━━┓\n");
    printf("                    │        4. P2P, 유해사이트 금지     │ Quiz 5 ┃\n");
    printf("                    │                                    │        ┃\n");
    printf("                    │        5. 사용 후, PC종료          │━━━━━━━━┛\n");
    printf("                    │                                    │\n");
    printf("                    │   ※다른 SW 발견시 조교에게 문의   │\n");
    printf("                    │                                    │\n");
    printf("                    ●────────────────────────────────────●\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("________________________________________________________________________________________________________________________\n");
}

void Title(void)
{
    GotoXY(36, 1); printf("\n");
    GotoXY(36, 2); printf("\n");
    GotoXY(36, 3); printf("     ___________  __________    ____   ______\n");
    GotoXY(36, 4); printf("    / ____/ ___/ / ____/    |  / __ ＼/ ____/\n");
    GotoXY(36, 5); printf("   / __/ ＼__ ＼/ /   / /|  | / /_/  / __/  \n");
    GotoXY(36, 6); printf("  / /___ ___/ /  /___/ ___  |/ _____/ /___  \n");
    GotoXY(36, 7); printf(" /_____//____/ ＼____/_/  |_|_/    /_____/\n");
}

void PrintEnding(void)
{
	CLS;
	puts("문이 열렸다.");
	puts("문을 열자 보이는 것은 전산실이었다.");
	puts("아무래도 전산실 입구를 나가는 문이라고 착각한 것 같다.");
	puts("다시 강의실로 돌아가 도어락이 없는 평범한 문을 열고 밖으로 나왔다.\n\n\n");

	puts("게임 클리어 축하드립니다!\n'n'키를 눌러 밖으로 나오실 수 있습니다.\n\n\n");
	puts("만든이들: 신슬기, 오승민, 유기원");
	WAITFORKEY('n');
}

void PrintFail(void)
{
	CLS;
	puts("저런... 정말로 유감이군요.");
	puts("GAME OVER");
	puts("'n'키를 눌러 밖으로 나오실 수 있습니다.");
	WAITFORKEY('n');
}

int GetKeyboard(int *keyCode)
{
	HANDLE input = GetStdHandle(STD_INPUT_HANDLE); // console의 핸들을 얻습니다.
	INPUT_RECORD rec; // key값을 저장하는 구조체입니다.
	DWORD oldConsoleMode = 0, newConsoleMode = 0, readData = 0; // 콘솔의 설정을 컨트롤 하는 변수들과, 읽힌 횟수를 세는 변수입니다.

	if (!SUCCEEDED(input)) // 만약 핸들을 얻는데 실패했을 경우, keyCode값을 초기화함과 동시에 -1을 리턴합니다.
	{
		*keyCode = 0;
		return -1;
	}

	if (!SUCCEEDED(GetConsoleMode(input, &oldConsoleMode))) // 콘솔의 기존 설정을 얻어오고, 만약 실패했을 경우 keyCode값을 초기화함과 동시에 -1을 반환합니다.
	{
		*keyCode = 0;
		return -1;
	}

	newConsoleMode = 0; // 새로운 콘솔 모드는 모든 플래그가 비활성된 상태입니다.

	SetConsoleMode(input, newConsoleMode); // 콘솔의 모든 모드를 비활성 시킵니다.

	if (!ReadConsoleInput(input, &rec, 1, &readData)) // 만약 키 값을 읽는 것에 실패할 경우, keyCode값을 초기화하고 -1을 반환합니다.
	{
		*keyCode = 0;
		return -1;
	}

	if (rec.Event.KeyEvent.bKeyDown == FALSE) // 만약 키 입력이 Press가 아니라 Release일 경우, 이것은 필요가 없기 때문에, keyCode 값을 초기화하며, 0을 반환합니다.
	{
		*keyCode = 0;
		SetConsoleMode(input, oldConsoleMode);
		return 0;
	}

	if (rec.EventType == KEY_EVENT) // 실제로 입력이 키보드 입력인지 체크하고, keyCode를 VK값으로 설정합니다.
	{
		*keyCode = rec.Event.KeyEvent.wVirtualKeyCode;
	}

	SetConsoleMode(input, oldConsoleMode); // 바꾼 콘솔 설정을 예전 설정으로 되돌립니다.

	return 1; // 모든 것이 성공적이면, 1을 리턴합니다!
}

int GetKey(void)
{
	int key = 0;

	if (GetKeyboard(&key) > 0)
	{
		return key;
	}
	return 0;
}