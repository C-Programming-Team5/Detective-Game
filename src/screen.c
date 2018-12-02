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
	system("COLOR 0F");
	InitialPrint();
	while (!GetAsyncKeyState(VK_RETURN))
	{
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
		
		Sleep(100);
	}
	CLS;
	return POS;
}

void PrintClues(const Player * const player, int number)
{
	char *clues[] = 
	{
		"단서1: 그것은 세상 어디에도 묶여있지 않다.",
		"단서2 : 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다.",
		"단서3 : 눈에 보이진 않지만, 정말 많은 이름을 갖고 있다.",
		"단서4 : 그것에게 멈춤이란 곧 죽음이다.",
		"단서5: 그 무엇보다 가볍고, 그 무엇보다 자유로운 것",
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
		printf("플레이 시간: %d\n\n", save[i].playTime);
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
	Sleep(2000);
	PlaySound(TEXT("searching.wav"), NULL, SND_ASYNC);//소리를 재생하고 바로 다음코드를 실행합니다.
	gotoxy(1, 25); printf("지끈거리는 머리를 붙잡으며 정신을 차렸다.");
	Sleep(5000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("어제 나는 분명 집에 간 것 같았는데, 강의실 안이다.");
	Sleep(5000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("집에 가기 위해 강의실문을 열었다.");
	Sleep(5000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	PlaySound(TEXT("lock.wav"), NULL, SND_ASYNC);
	gotoxy(1, 25); printf("자물쇠가 내부에 설치 되어있어 열리지 않는다.");
	Sleep(5000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("휴대폰도 켜지지 않는다. 강의실을 나가기 위해선 5개의 비밀번호가 필요한 것 같다.");
	Sleep(5000);
	gotoxy(1, 25); printf("                                                                                       ");
	Sleep(100);
	gotoxy(1, 25); printf("혹시라도 조교가 두고 간 비밀번호 종이가 있을 수도 있기 때문에 강의실 내부를 찾아보기로 했다.");
	Sleep(5000);
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

int LobbyPlay(int choice, Player *player, Player save[])
{
	int select = 0;
	CLS;
	LobbyScreen();
	gotoxy(2, 25);  printf("이제 무엇을 할까? <키보드로 조작하고 엔터키를 눌러 결정한다.>");
	int POS = 4;
	CursorView(0);
	system("COLOR 0F");
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

		Sleep(100);
	}
	CLS;
	
	switch (POS)
	{
		case 0:
			PlaySound(TEXT("walking.wav"), NULL, SND_ASYNC);
			LobbyScreen();
			SelectItem(POS, player, save);
			break;
		case 1:
			break;
		case 2:
			OpenLock();
		case 3:
			while (select < '1' || '5' < select)
			{
				PrintSaveList(save);
				gotoxy(1, 27);
				puts("몇번 세이브에 저장하시겠습니까?");
				select = Getch();
			}
			Save(player, save, select - '0');
			puts("세이브가 완료되었습니다.");
			return POS;
		default:
			break;
	}
}

int SelectItem(int item, Player *player, Player save[])
{
	gotoxy(2, 25); printf("어떤 물건부터 찾아볼까?");
	int POS = 5;
	int retrace = 0;
	CursorView(0);
	system("COLOR 0F");
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

		Sleep(100);
	}
	switch (POS)
	{
	case 0:
	{
	PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
	Quiz1();
	Answer1(player);
	LobbyPlay(retrace, player, save);
	}
		
	case 1:
	{
		Quiz2();
		Answer2(player);
		LobbyPlay(retrace, player, save);
	}
	case 2:
	{
		Quiz3();
		Answer3(player);
		LobbyPlay(retrace, player, save);
	}
	case 3:
	{
		Quiz4();
		Answer4(player);
		LobbyPlay(retrace, player, save);
	}
	case 4:
	{
		Quiz5();
		Answer5(player);
		LobbyPlay(retrace, player, save);
	}
	case 5:
	{    
	LobbyPlay(POS, player, save); }
	default:
		return 0;
	}
	return 0;
}


void Quiz1(void)

{

	CLS;
	char *quiz1[] =
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다", "Q. 신분을 밝혀라!\n\n내가 A에게 다음과 같이 물었다고 해보자.\n나:여러분 가운데 기사는 몇 분이나 되십니까 ? \n이에 A가 대답했으나 발음이 불분명하여 B가 추가적으로 대답했다.\nB:A는 우리중 기사는 한 명이라고 말했다.그 순간 C가 끼어들었다.\nC:B는 지금 거짓말을 하고있습니다.",
		"B와 C의 신분을 밝혀라.(신분은 건달 혹은 기사이다)",
	};
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		LobbyScreen();
		gotoxy(1, 25);
		puts(quiz1[i]);
		WAITFORKEY('n');
		system("cls");
	}
	return 0;
}

void Answer1(Player *player)
{
	CLS;
	LobbyScreen();
	int ANS1 = 4;
	CursorView(0);
	system("COLOR 0F");
	while (!GetAsyncKeyState(VK_RETURN)) 
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ANS1 = (ANS1 + 3) % 4;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			ANS1 = (ANS1 + 1) % 4;
		}
			
			SetColor(ANS1 == 0 ? 3 : 15);
			gotoxy(21, 27); printf("*기사/기사");
			SetColor(ANS1 == 1 ? 3 : 15);
			gotoxy(41, 27); printf("*기사/건달");
			SetColor(ANS1== 2 ? 3 : 15);
			gotoxy(61, 27); printf("*건달/기사");
			SetColor(ANS1 == 3 ? 3 : 15);
			gotoxy(81, 27); printf("*건달/건달");
		  
			Sleep(100);
	}
	system("cls");

	LobbyScreen();
	switch (ANS1)
	{
	case 0:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 1:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 2:
	{
		gotoxy(1, 25); printf("단서가 나타났다!");
		player->cleared |= 1;
		gotoxy(1, 26); PrintClues(player, 0);
		gotoxy(1, 27); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 3:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	default:
		return 0;
	}

}

void Quiz2(void)
{
	CLS;
	char *quiz2[] =
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다", "Q.물고기 주인의 국적은?\n\n색깔이 다른 집이 일렬로 5채 있다.그리고 각 집에는 서로 다른 국적을 가진 사람들이 살고 있다.\n다섯 사람은 어떤 음료를 마시고, 어느 꽃을 기르고, 어느 동물을 키우고 있다.\n어느 두 사람도 마시는 음료, 기르는 꽃, 키우는 동물은 일치하지 않는다.",
		"영국인은 빨간 집에 살고, 스웨덴인은 개를 키우며, 덴마크인은 차를 마신다.\n초록집은 하얀 집의 왼쪽 집이며, 초록집에 사는 사람은 커피를 마신다.\n장미를 기르는 사람은 새를 키우고, 노란집 사람은 라일락을 기른다.\n한 가운데 사는 사람은 우유를 마시고, 노르웨이인은 첫번째 집에 산다.\n안개꽃을 기르는 사람은 고양이를 키우는 사람의 옆집에 산다.",
		"프리지아를 기르는 사람은 맥주를 마신다.\n독일인은 사루비아를 기르며, 노르웨이인은 파란집 옆에 산다.\n안개꽃을 기르는 사람은 사람은 생수를 마시는 사람과 이웃이다.\n\n그렇다면 물고기를 키우는 사람은 어느 나라의 사람일까?",
	};
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		LobbyScreen();
		gotoxy(1, 25);
		puts(quiz2[i]);
		WAITFORKEY('n');
		system("cls");
	}
	return 0;
}

void Answer2(Player *player)
{
	CLS;
	LobbyScreen();
	int ANS2 = 4;
	CursorView(0);
	system("COLOR 0F");
	while (!GetAsyncKeyState(VK_RETURN)) 
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ANS2 = (ANS2 + 4) % 5;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			ANS2 = (ANS2 + 1) % 5;
		}
			
			SetColor(ANS2 == 0 ? 3 : 15);
			gotoxy(21, 27); printf("*독일");
			SetColor(ANS2 == 1 ? 3 : 15);
			gotoxy(41, 27); printf("*스웨덴");
			SetColor(ANS2 == 2 ? 3 : 15);
			gotoxy(61, 27); printf("*영국");
			SetColor(ANS2 == 3 ? 3 : 15);
			gotoxy(81, 27); printf("*덴마크");
			SetColor(ANS2 == 4 ? 3 : 15);
			gotoxy(101, 27); printf("*노르웨이");
		   
		Sleep(100);
	}
	system("cls");
	LobbyScreen();
	switch (ANS2)
	{
	case 0:
	{
		
		gotoxy(1, 25); printf("단서가 나타났다!");
		player->cleared |= 2;
		gotoxy(1, 26); PrintClues(player, 1);
		gotoxy(1, 27); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 1:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 2:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 3:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 4:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	default:
		return 0;
	}
}

void Quiz3(void)
{
	CLS;
	char *quiz3[] =
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다", "Q.살아남자 미스터 화이트!\n\n세 명의 총잡이가 서로 동시에 결투를 벌인다.\n1.미스터 블랙은 명중률 100 % 의 사격 실력을 가지고 있다.\n2.미스터 그레이는 명중률 70 % 의 사격 실력을 갖고 있다.\n",
		"3.미스터 화이트는 명중률 30 % 의 사격 실력을 가지고 있다.\n그리고 총잡이들은 서로의 실력차를 감안해서, 화이트->그레이->블랙 순서대로 발포하기로 하며, 한 번에 한 발만 쏠 수 있다.\n이 때 화이트는 어떻게 쏴야 가장 생존률이 높은가 ?",
	};
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		LobbyScreen();
		gotoxy(1, 25);
		puts(quiz3[i]);
		WAITFORKEY('n');
		system("cls");
	}
	return 0;
}

void Answer3(Player *player)
{
	CLS;
	LobbyScreen();
	int ANS3 = 3;
	CursorView(0);
	system("COLOR 0F");
	while (!GetAsyncKeyState(VK_RETURN)) 
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ANS3 = (ANS3 + 2) % 3;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			ANS3 = (ANS3 + 1) % 3;
		}
		
			SetColor(ANS3 == 0 ? 3 : 15);
			gotoxy(21, 27); printf("1. 블랙");
			SetColor(ANS3 == 1 ? 3 : 15);
			gotoxy(41, 27); printf("2. 그레이");
			SetColor(ANS3 == 2 ? 3 : 15);
			gotoxy(61, 27); printf("3. 허공");
		  
		Sleep(100);
	}
	system("cls");
	SetColor(15);
	LobbyScreen();
	
	switch (ANS3)
	{
	case 0:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 1:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 2:
	{
		gotoxy(1, 25); printf("단서가 나타났다!");
		player->cleared |= 4;
		gotoxy(1, 26); PrintClues(player, 2);
		gotoxy(1, 27); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	default:
		return 0;
	}


}

void Quiz4(void)
{
	CLS;
	char *quiz4[] =
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다", "Q.범인은 바로 너!\n\n한 마을에 보석 강도 살인 사건이 발생했다.\n용의자는 조상호, 이수억, 최수호, 박홍수로 총 4명이다.\n피해자는 다잉메시지로 '수어어' 라는 글자를 남겼다.",
		"범인은 누구인가?",
	};
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		LobbyScreen();
		gotoxy(1, 25);
		puts(quiz4[i]);
		WAITFORKEY('n');
		system("cls");
	}
	return 0;
}

void Answer4(Player *player)
{
	CLS;
	LobbyScreen();
	int ANS4 = 4;
	CursorView(0);
	system("COLOR 0F");
	while (!GetAsyncKeyState(VK_RETURN)) 
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ANS4 = (ANS4 + 3) % 4;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			ANS4 = (ANS4 + 1) % 4;
		}
		
			SetColor(ANS4 == 0 ? 3 : 15);
			gotoxy(21, 27); printf("*조상호");
			SetColor(ANS4 == 1 ? 3 : 15);
			gotoxy(41, 27); printf("*이수억");
			SetColor(ANS4 == 2 ? 3 : 15);
			gotoxy(61, 27); printf("*최수호");
			SetColor(ANS4 == 3 ? 3 : 15);
			gotoxy(81, 27); printf("*박홍수");
		   
		Sleep(100);
	}
	system("cls");
	LobbyScreen();

	switch (ANS4)
	{
	case 0:
	{
		gotoxy(1, 25); printf("단서가 나타났다!");
		player->cleared |= 8;
		gotoxy(1, 26); PrintClues(player, 3);
		gotoxy(1, 27); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 1:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 2:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	case 3:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	default:
		return 0;
	}

}

void Quiz5(void)

{
	CLS;
	char *quiz5[] =
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다", "Q.슈뢰딩거의 다이어리\n\n슈뢰딩거의 다이어리에는 요일마다 알 수 없는 숫자가 적혀 있다.\n물음표에 들어갈 숫자는 무엇인가 ?",
		"MON = 3\nTUE = 5\nWED = 4\nTHU = ?",
	};
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		LobbyScreen();
		gotoxy(1, 25);
		puts(quiz5[i]);
		WAITFORKEY('n');
		system("cls");
	}
	return 0;
}

void Answer5(Player *player)
{
	CLS;
	LobbyScreen();
	int ANS5 = 4;
	CursorView(0);
	system("COLOR 0F");
	while (!GetAsyncKeyState(VK_RETURN))
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			ANS5 = (ANS5 + 3) % 4;
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			ANS5 = (ANS5 + 1) % 4;
		}

		SetColor(ANS5 == 0 ? 3 : 15);
		gotoxy(21, 27); printf("*1. 2");
		SetColor(ANS5 == 1 ? 3 : 15);
		gotoxy(41, 27); printf("*2. 4");
		SetColor(ANS5 == 2 ? 3 : 15);
		gotoxy(61, 27); printf("*3. 6");
		SetColor(ANS5 == 3 ? 3 : 15);
		gotoxy(81, 27); printf("*4. 8");

		Sleep(100);
	}
	system("cls");
	LobbyScreen();


	switch (ANS5)
	{
	case 0:
	{
		gotoxy(1, 25); printf("단서가 나타났다!");
		player->cleared |= 16;
		gotoxy(1, 26); PrintClues(player, 4);
		gotoxy(1, 27); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}

	case 1:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}

	case 2:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}

	case 3:
	{
		gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
		gotoxy(1, 26); printf("'n'을 눌러 다른 물건도 찾아보자");
		WAITFORKEY('n');
		CLS;
		return 0;
	}
	default:
		return 0;
	}
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

int OpenLock(void)
{
	char CorrectPW[] = "wind";
	char answer[5] = "";

	PrintDoor();
	gotoxy(1, 25);
	fputs("암호를 입력하세요: ____\b\b\b\b", stdout);
	fgets(answer, 5, stdin);
	if (strcmp(CorrectPW, answer) == 0)
	{
		return GAME_CLEAR;
	}
	else
	{
		return GAME_OVER;
	}
}