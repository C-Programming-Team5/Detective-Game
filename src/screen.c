#include "main.h"
#include "screen.h"
#include "player.h"
#include "save_io.h"

// 단서 목록입니다.
char *clues[] =
{
	"단서1: 그것은 세상 어디에도 묶여있지 않다.\n",
	"단서2 : 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다.\n",
	"단서3 : 눈에 보이진 않지만, 정말 많은 이름을 갖고 있다.\n",
	"단서4 : 그것에게 멈춤이란 곧 죽음이다.\n",
	"단서5: 그 무엇보다 가볍고, 그 무엇보다 자유로운 것\n",
};

// 퀴즈 목록입니다.
char *quiz[][4] =
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

// 퀴즈 인덱스입니다.
int quizIndex[] = { 3, 4, 3, 3, 3 };

// 문제 선택지 목록입니다.
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

// 선택지 인덱스입니다.
int answerIndex[] = { 4, 5, 3, 4, 4 };

// 정답 목록입니다.
int rightAnswer[] = { 2, 0, 2, 0, 2 };


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

int StartScreen(void)
{
	int POS = 2;
	int key = 0;

	CLS;

	CursorView(0);
	SetColor(15);

	system("title ESCAPE");
	Title();

	do
	{
		SetColor(POS == 0 ? 3 : 15);
		GotoXY(53, 15); fputs("새로 하기", stdout);
		SetColor(POS == 1 ? 3 : 15);
		GotoXY(53, 17); fputs("이어 하기", stdout);
		SetColor(POS == 2 ? 3 : 15);
		GotoXY(53, 19); fputs("게임 종료", stdout);
		SetColor(15);

		key = GetKey();
		if (key == VK_UP)
		{
			POS = (POS + 2) % 3;
		}
		else if (key == VK_DOWN)
		{
			POS = (POS + 1) % 3;
		}

		
	} while (key != VK_RETURN);

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



void Prologue(int number)
{

  
    int i = 0;
    char Prologe[7][95] =
    {
        "'n'을 누르면 다음 페이지로 넘어갑니다.",
        "지끈거리는 머리를 붙잡으며 정신을 차렸다.",
        "어제 나는 분명 집에 간 것 같았는데, 강의실 안이다.",
        "집에 가기 위해 강의실문을 열었다.",
        "자물쇠가 내부에 설치 되어있어 열리지 않는다.",
        "휴대폰도 켜지지 않는다. 강의실을 나가기 위해선 5개의 비밀 번호가 필요한 것 같다.",
        "혹시라도 조교가 두고 간 비밀번호 종이가 있을 수도 있기 때문에 강의실 내부를 찾아보기로 했다.",

    };
    SetColor(15);
    CLS;
    for (i = 0; i < 7; i++)
    {
        LobbyScreen();
        GotoXY(1, 25);
        puts(Prologe[i]);
        WAITFORKEY('n');
        CLS;
    }
    return;
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
	int key = 0;
	int POS = 4;

	CLS;
	LobbyScreen();
	GotoXY(2, 25);  printf("이제 무엇을 할까? <키보드로 조작하고 엔터키를 눌러 결정한다.>");
	CursorView(0);
	SetColor(15);

	do
	{
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

		key = GetKey();
		if (key == VK_LEFT)
		{
			POS = (POS + 4) % 5;
		}
		else if (key == VK_RIGHT)
		{
			POS = (POS + 1) % 5;
		}

		
	} while (key != VK_RETURN);

	CLS;
	return POS;
}

int SelectItem(void)
{
	GotoXY(2, 25); printf("어떤 물건부터 찾아볼까?");
	int POS = 5;
	int key = 0;

	CursorView(0);
	SetColor(15);

	do
	{
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

		key = GetKey();
		if (key == VK_LEFT)
		{
			POS = (POS + 5) % 6;
		}
		else if (key == VK_RIGHT)
		{
			POS = (POS + 1) % 6;
		}
	} while (key != VK_RETURN);
	
	return POS;
}


void Quiz(int number)
{
    int i = 0;
    char x[100];
    int POS = 0;

    vvfp quizScreen[5] = { Quiz1Screen, Quiz2Screen, Quiz3Screen, Quiz4Screen, Quiz5Screen };
    vvfp MemoList[5] = { Memo1, Memo2, Memo3, Memo4, Memo5 };
    SetColor(15);
    CLS;
    for (i = 0; i < quizIndex[number]; i++)
    {
        quizScreen[number]();
        GotoXY(1, 25);
        puts(quiz[number][i]);
        WAITFORKEY('n');
        PlaySound(TEXT("next.wav"), NULL, SND_ASYNC);
        CLS;
    }
    quizScreen[number]();
    POS = Solve(POS);
    if(POS==1)
    {
        CLS;
        for (i = 0; i < quizIndex[number]; i++)
        {
            quizScreen[number]();
            GotoXY(1, 25);
            puts(quiz[number][i]);
            WAITFORKEY('n');
            PlaySound(TEXT("next.wav"), NULL, SND_ASYNC);
            CLS;
        }
    }

    else if (POS == 2)
    {
        CLS;
        MemoList[number]();
        scanf("%c", &x);
    }
    return;
}

void Answer(Player *player, int number)
{
	int POS = 0, i = 0;
	int key = 0;
	vvfp quizScreen[5] = { Quiz1Screen, Quiz2Screen, Quiz3Screen, Quiz4Screen, Quiz5Screen };

	CLS;
	SetColor(15);
	quizScreen[number]();
	CursorView(0);
	SetColor(15);

	do
	{
		for (i = 0; i < answerIndex[number]; i++)
		{
			SetColor(POS == i ? 3 : 15);
			GotoXY(21 + i * 20, 27);
			fputs(answer[number][i], stdout);
		}

		key = GetKey();
		if (key == VK_LEFT)
		{
			POS = (POS + answerIndex[number] - 1) % answerIndex[number];
		}
		else if (key == VK_RIGHT)
		{
			POS = (POS + 1) % answerIndex[number];
		}
	} while (key != VK_RETURN);

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

	if (input == NULL) // 만약 핸들을 얻는데 실패했을 경우, keyCode값을 초기화함과 동시에 -1을 리턴합니다.
	{
		*keyCode = 0;
		return -1;
	}

	if (GetConsoleMode(input, &oldConsoleMode) == FALSE) // 콘솔의 기존 설정을 얻어오고, 만약 실패했을 경우 keyCode값을 초기화함과 동시에 -1을 반환합니다.
	{
		*keyCode = 0;
		return -1;
	}

	newConsoleMode = 0; // 새로운 콘솔 모드는 모든 플래그가 비활성된 상태입니다.

	SetConsoleMode(input, newConsoleMode); // 콘솔의 모든 모드를 비활성 시킵니다.

	if (ReadConsoleInput(input, &rec, 1, &readData) == 0) // 만약 키 값을 읽는 것에 실패할 경우, keyCode값을 초기화하고 -1을 반환합니다.
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


int Solve(int pos)
{
    int select = 0;
    int key = 0;
    int POS = 2;
    int x = 0;

    CursorView(0);
    SetColor(15);

    do
    {
        SetColor(POS == 0 ? 3 : 15);
        GotoXY(1, 27); printf("*문제를 푼다");
        SetColor(POS == 1 ? 3 : 15);
        GotoXY(21, 27); printf("*다시 문제를 본다");
        SetColor(POS == 2 ? 3 : 15);
        GotoXY(41, 27); printf("*메모장을 연다");
        SetColor(15);

        key = GetKey();
        if (key == VK_LEFT)
        {
            POS = (POS + 2) % 3;
        }
        else if (key == VK_RIGHT)
        {
            POS = (POS + 1) % 3;
        }
    } while (key != VK_RETURN);
    CLS;

    return POS;
}

void Memo1(void)
{
    printf("Q.신분을 밝혀라!\n");
    printf("내가 A에게 다음과 같이 물었다고 해보자.\n");
    printf("나: 여러분 가운데 기사는 몇 분이나 되십니까?\n");
    printf("이에 A가 대답했으나 발음이 불분명하여 B가 추가적으로 대답했다.\n");
    printf("B: A는 우리 중 기사는 한 명이라고 말했다.\n");
    printf("그 순간 C가 끼어들었다.\n");
    printf("C: B는 지금 거짓말을 하고 있습니다.\n");
    printf("B와 C의 신분을 밝혀라.(신분은 건달 혹은 기사이다.\n\n");
    printf("*기사/기사  *기사/건달  *건달/기사  *건달/건달\n\n");
    printf("(엔터키를 누르면 답 선택지로 넘어갑니다.)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
}

void Memo2(void)
{
    printf("Q.물고기 주인의 국적은?\n");
    printf("색깔이 다른 집이 일렬로 5채 있다. 그리고 각 집에는 서로다른 국적을 가진 사람들이 살고 있다.\n");
    printf("다섯 사람은 어떤 음료를 마시고, 어느 꽃을 기르고, 어느 동물을 키우고있다.\n");
    printf("어느 두 사람도 마시는 음료, 기르는 꽃, 키우는 동물은 일치하지 않는다.\n");
    printf("영국인은 빨간 집에 살고, 스웨덴인은 개를 키우며, 덴마크 인은 차를 마신다.\n");
    printf("초록집은 하얀 집의 왼쪽 집이며, 초록집에 사는 사람은 커피를 마신다.\n");
    printf("장미를 기르는 사람은 새를 키우고, 노란집 사람은 라일락을 기른다.\n");
    printf("한 가운데 사는 사람은 우유를 마시고, 노르웨이인은 첫번째 집에 산다.\n");
    printf("안개꽃을 기르는 사람은 고양이를 키우는 사람의 옆집에 산다.\n");
    printf("프리지아를 기르는 사람은 맥주를 마신다.\n");
    printf("독일인은 사루비아를 기르며, 노르웨이인은 파란집 옆에 산다.\n");
    printf("안개꽃을 기르는 사람은 사람은 생수를 마시는 사람과 이웃이다.\n");
    printf("그렇다면 물고기를 키우는 사람은 어느 나라의 사람일까?\n\n");
    printf("*독일     *스웨덴    *영국    *덴마크    *노르웨이\n\n");
    printf("(엔터키를 누르면 답 선택지로 넘어갑니다.)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
}

void Memo3(void)
{
    printf("Q.살아남자 미스터 화이트!\n");
    printf("세 명의 총잡이가 서로 동시에 결투를 벌인다.\n");
    printf("1.미스터 블랙은 명중률 100 % 의 사격 실력을 가지고 있다.\n");
    printf("2.미스터 그레이는 명중률 70 % 의 사격 실력을 갖고 있다.\n");
    printf("3.미스터 화이트는 명중률 30 % 의 사격 실력을 가지고 있다.\n");
    printf("그리고 총잡이들은 서로의 실력차를 감안해서, 화이트->그레이->블랙 순서대로 발포하기로 하며, 한 번에 한 발만 쏠 수 있다.\n");
    printf("이 때 화이트는 어떻게 쏴야 가장 생존률이 높은가?\n\n");
    printf("*블랙    *그레이    *허공\n\n");
    printf("(엔터키를 누르면 답 선택지로 넘어갑니다.)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
}

void Memo4(void)
{
    printf("Q.범인은 바로 너!\n");
    printf("한 마을에 보석 강도 살인 사건이 발생했다.\n");
    printf("용의자는 조상호, 이수억, 최수호, 박홍수로 총 4명이다.\n");
    printf("피해자는 다잉메시지로 '수어어' 라는 글자를 남겼다.\n");
    printf("범인은 누구인가?\n\n");
    printf("*조상호    *이수억    *최수호    *박홍수\n\n");
    printf("(엔터키를 누르면 답 선택지로 넘어갑니다.)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
}

void Memo5(void)
{
    printf("Q.슈뢰딩거의 다이어리\n");
    printf("슈뢰딩거의 다이어리에는 요일마다 알 수 없는 숫자가 적혀 있다.\n");
    printf("물음표에 들어갈 숫자는 무엇인가?\n");
    printf("MON = 3    TUE = 5     WED = 4     THU = ?\n\n");
    printf("*2     *4      *6      *8\n\n");
    printf("(엔터키를 누르면 답 선택지로 넘어갑니다.)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
}