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

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitialPrint(void)
{
	CLS;
	system("title ESCAPE");

	gotoxy(53, 15); fputs("새로 하기", stdout);
	gotoxy(53, 17); fputs("이어 하기", stdout);
	gotoxy(53, 19); fputs("게임 종료", stdout);
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
		gotoxy(53, 15); fputs("새로 하기", stdout);
		SetColor(POS == 1 ? 3 : 15);
		gotoxy(53, 17); fputs("이어 하기", stdout);
		SetColor(POS == 2 ? 3 : 15);
		gotoxy(53, 19); fputs("게임 종료", stdout);
		SetColor(15);
		
		Sleep(500);
	}
	CLS;
	return POS;
}

void PrintClues(const Player * const player, int number)
{
	char *clues[] = 
	{
		"단서1: 그것은 세상 어디에도 묶여있지 않다.\n",
		"단서2 : 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다.\n",
		"단서3 : 눈에 보이진 않지만, 정말 많은 이름을 갖고 있다.\n",
		"단서4 : 그것에게 멈춤이란 곧 죽음이다.\n",
		"단서5: 그 무엇보다 가볍고, 그 무엇보다 자유로운 것\n",
	};
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
	LobbyScreen();
	gotoxy(1, 25); printf(".");
	Sleep(1000); 
	gotoxy(2, 25); printf(".");
	Sleep(1000);
	gotoxy(3, 25); printf(".");
	Sleep(1000);
	gotoxy(4, 25); printf(".");
	Sleep(1000);
	gotoxy(5, 25); printf(".");
	Sleep(1000);
	gotoxy(6, 25); printf(".");
	Sleep(1500);
	PlaySound(TEXT("searching.wav"), NULL, SND_ASYNC);//소리를 재생하고 바로 다음코드를 실행합니다.
	gotoxy(1, 25); printf("지끈거리는 머리를 붙잡으며 정신을 차렸다.");
	Sleep(3000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("어제 나는 분명 집에 간 것 같았는데, 강의실 안이다.");
	Sleep(3000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("집에 가기 위해 강의실문을 열었다.");
	Sleep(3000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	PlaySound(TEXT("lock.wav"), NULL, SND_ASYNC);
	gotoxy(1, 25); printf("자물쇠가 내부에 설치 되어있어 열리지 않는다.");
	Sleep(3000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("휴대폰도 켜지지 않는다. 강의실을 나가기 위해선 5개의 비밀번호가 필요한 것 같다.");
	Sleep(3000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("혹시라도 조교가 두고 간 비밀번호 종이가 있을 수도 있기 때문에 강의실 내부를 찾아보기로 했다.");
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
	gotoxy(2, 25);  printf("이제 무엇을 할까? <키보드로 조작하고 엔터키를 눌러 결정한다.>");
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
		gotoxy(1, 27); printf("*물건을 찾아본다");
		SetColor(POS == 1 ? 3 : 15);
		gotoxy(21, 27); printf("*단서를 본다");
		SetColor(POS == 2 ? 3 : 15);
		gotoxy(41, 27); printf("*자물쇠를 연다");
		SetColor(POS == 3 ? 3 : 15);
		gotoxy(61, 27); printf("*저장한다");
		SetColor(POS == 4 ? 3 : 15);
		gotoxy(81, 27); printf("*종료한다");
		SetColor(15);

		Sleep(500);
	}
	CLS;
	return POS;
}

int SelectItem(void)
{
	gotoxy(2, 25); printf("어떤 물건부터 찾아볼까?");
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
		gotoxy(1, 27); printf("*컴퓨터");
		SetColor(POS == 1 ? 3 : 15);
		gotoxy(21, 27); printf("*책상 밑");
		SetColor(POS == 2 ? 3 : 15);
		gotoxy(41, 27); printf("*책상 위");
		SetColor(POS == 3 ? 3 : 15);
		gotoxy(61, 27); printf("*칠판");
		SetColor(POS == 4 ? 3 : 15);
		gotoxy(81, 27); printf("*포스터");
		SetColor(POS == 5 ? 3 : 15);
		gotoxy(101, 27); printf("*돌아가기");
		SetColor(15);

		Sleep(500);
	}
	
	return POS;
}


void Quiz(int number)
{
	char *quiz[][4] =//포인터 이차원배열
	{
		{
			"'n'을 누르면 다음 페이지로 넘어갑니다",
			"Q. 신분을 밝혀라!\n\n내가 A에게 다음과 같이 물었다고 해보자.\n나:여러분 가운데 기사는 몇 분이나 되십니까 ? \n이에 A가 대답했으나 발음이 불분명하여 B가 추가적으로 대답했다.\nB:A는 우리중 기사는 한 명이라고 말했다.그 순간 C가 끼어들었다.\nC:B는 지금 거짓말을 하고있습니다.",
			"B와 C의 신분을 밝혀라.(신분은 건달 혹은 기사이다)",
		},
		{
			"'n'을 누르면 다음 페이지로 넘어갑니다",
			"Q.물고기 주인의 국적은?\n\n색깔이 다른 집이 일렬로 5채 있다.그리고 각 집에는 서로 다른 국적을 가진 사람들이 살고 있다.\n다섯 사람은 어떤 음료를 마시고, 어느 꽃을 기르고, 어느 동물을 키우고 있다.\n어느 두 사람도 마시는 음료, 기르는 꽃, 키우는 동물은 일치하지 않는다.",
			"영국인은 빨간 집에 살고, 스웨덴인은 개를 키우며, 덴마크인은 차를 마신다.\n초록집은 하얀 집의 왼쪽 집이며, 초록집에 사는 사람은 커피를 마신다.\n장미를 기르는 사람은 새를 키우고, 노란집 사람은 라일락을 기른다.\n한 가운데 사는 사람은 우유를 마시고, 노르웨이인은 첫번째 집에 산다.\n안개꽃을 기르는 사람은 고양이를 키우는 사람의 옆집에 산다.",
			"프리지아를 기르는 사람은 맥주를 마신다.\n독일인은 사루비아를 기르며, 노르웨이인은 파란집 옆에 산다.\n안개꽃을 기르는 사람은 사람은 생수를 마시는 사람과 이웃이다.\n\n그렇다면 물고기를 키우는 사람은 어느 나라의 사람일까?",
		},
		{
			"'n'을 누르면 다음 페이지로 넘어갑니다",
			"Q.살아남자 미스터 화이트!\n\n세 명의 총잡이가 서로 동시에 결투를 벌인다.\n1.미스터 블랙은 명중률 100 % 의 사격 실력을 가지고 있다.\n2.미스터 그레이는 명중률 70 % 의 사격 실력을 갖고 있다.\n",
			"3.미스터 화이트는 명중률 30 % 의 사격 실력을 가지고 있다.\n그리고 총잡이들은 서로의 실력차를 감안해서, 화이트->그레이->블랙 순서대로 발포하기로 하며, 한 번에 한 발만 쏠 수 있다.\n이 때 화이트는 어떻게 쏴야 가장 생존률이 높은가 ?",
		},
		{
			"'n'을 누르면 다음 페이지로 넘어갑니다",
			"Q.범인은 바로 너!\n\n한 마을에 보석 강도 살인 사건이 발생했다.\n용의자는 조상호, 이수억, 최수호, 박홍수로 총 4명이다.\n피해자는 다잉메시지로 '수어어' 라는 글자를 남겼다.",
			"범인은 누구인가?",
		},
		{
			"'n'을 누르면 다음 페이지로 넘어갑니다",
			"Q.슈뢰딩거의 다이어리\n\n슈뢰딩거의 다이어리에는 요일마다 알 수 없는 숫자가 적혀 있다.\n물음표에 들어갈 숫자는 무엇인가 ?",
			"MON = 3\nTUE = 5\nWED = 4\nTHU = ?",
		},
	};
	int index[] = {3, 4, 3, 3, 3};//문장의 줄
	int i = 0;
	vvfp quizScreen[5] = {Quiz1Screen, Quiz2Screen, Quiz3Screen, Quiz4Screen, Quiz5Screen};//반환형이 없고 인자가 없는 함수 포인터 배열(그림)
	SetColor(15);//하얀색
	CLS;//삭제
	for (i = 0; i < index[number]; i++)
	{
		quizScreen[number]();//밖에서 물건선택시 받아옴(number)
		gotoxy(1, 25);//좌표
		puts(quiz[number][i]);//출력
		WAITFORKEY('n');//Getch를 특정 아스키코드와 같을때까지 입력값을 받으라는 while문을 묶은것
		CLS;
	}
	return;
}

void Answer(Player *player, int number)
{
	char *answer[][5] = 
	{
		{
			"*기사/기사",
			"*기사/건달",
			"*건달/기사",
			"*건달/건달",
		},
		{
			"*독일",
			"*스웨덴",
			"*영국",
			"*덴마크",
			"*노르웨이",
		},
		{
			"1. 블랙",
			"2. 그레이",
			"3. 허공",
		},
		{
			"*조상호",
			"*이수억",
			"*최수호",
			"*박홍수",
		},
		{
			"*1. 2",
			"*2. 4",
			"*3. 6",
			"*4. 8",
		},
	};
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
			gotoxy(21 + i * 20, 27);
			fputs(answer[number][i], stdout);
		}
		Sleep(500);
	}
	CLS;
	SetColor(15);
	quizScreen[number]();

	if (POS == rightAnswer[number])
	{
		gotoxy(1, 25);
		printf("단서가 나타났다!");
		player->cleared |= (1 << number);
		gotoxy(1, 26);
		PrintClues(player, number);
		gotoxy(1, 27);
		printf("'n'을 눌러 다른 물건도 찾아보자.");
	}
	else
	{
		gotoxy(1, 25);
		printf("아무 일도 일어나지 않았다.");
		gotoxy(1, 26);
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
	gotoxy(1, 25);
	fputs("암호를 입력하세요: ____", stdout);
	gotoxy(20, 25);
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
    gotoxy(36, 1); printf("\n");
    gotoxy(36, 2); printf("\n");
    gotoxy(36, 3); printf("     ___________  __________    ____   ______\n");
    gotoxy(36, 4); printf("    / ____/ ___/ / ____/    |  / __ ＼/ ____/\n");
    gotoxy(36, 5); printf("   / __/ ＼__ ＼/ /   / /|  | / /_/  / __/  \n");
    gotoxy(36, 6); printf("  / /___ ___/ /  /___/ ___  |/ _____/ /___  \n");
    gotoxy(36, 7); printf(" /_____//____/ ＼____/_/  |_|_/    /_____/\n");
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