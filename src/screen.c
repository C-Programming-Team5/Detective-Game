#include "main.h"
#include "screen.h"
#include "player.h"
#include "save_io.h"

TCHAR Getch(void)
{
	DWORD mode, cc;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE); // 입력 핸들러를 가져옵니다. 이를 통해 입력을 제어할 수 있습니다.
	if (h == NULL)
	{
		return 0; // console not found
	}
	GetConsoleMode(h, &mode); // 원래 콘솔의 입력모드를 가져옵니다.
	SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT)); // 원래 콘솔의 입력 모드에서 엔터 줄바꿈과 에코 기능을 비활성화 합니다.
	TCHAR c = 0;
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

void PrintClues(const Player * const player)
{
	CLS;
	puts((player->cleared & 1) ? "힌트 1: 그것은 어디에도 없다." : "");
	puts((player->cleared & 2) ? "힌트 2: 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다." : "");
	puts((player->cleared & 4) ? "힌트 3: 눈에 보이진 않지만, 많은 이름을 갖고 있다." : "");
	puts((player->cleared & 8) ? "힌트 4: 그것에게 멈춤이란 곧 죽음이다." : "");
	puts((player->cleared & 16) ? "힌트 5: 그것은 세상에서 가장 가볍고 자유로운 존재이다." : "");
	return;
}

void PrintSaveList(const Player save[])
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
    PlaySound(TEXT("searching.wav"), NULL, SND_ASYNC);
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

int LobbyPlay(int choice)
{
    LobbyScreen();
	gotoxy(2, 25);  printf("이제 무엇을 할까?");
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
		gotoxy(1, 27); printf("1.물건을 찾아본다");
		SetColor(POS == 1 ? 3 : 15);
		gotoxy(21, 27); printf("2.단서를 본다");
		SetColor(POS == 2 ? 3 : 15);
		gotoxy(41, 27); printf("3.자물쇠를 연다");
		SetColor(POS == 3 ? 3 : 15);
		gotoxy(61, 27); printf("4.저장한다");
		SetColor(POS == 4 ? 3 : 15);
		gotoxy(81, 27); printf("5.종료한다");
		SetColor(15);

		Sleep(100);
	}
	CLS;
    if (POS == 0)
    {
        PlaySound(TEXT("walking.wav"), NULL, SND_ASYNC);
        LobbyScreen();
        SelectItem(POS);
    }
    else
     return POS;
}

int SelectItem(int item)
{
    gotoxy(2, 25); printf("어떤 물건부터 찾아볼까?");
    int POS = 5;
    int ans5, quiz5;
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
        gotoxy(1, 27); printf("1.컴퓨터");
        SetColor(POS == 1 ? 3 : 15);
        gotoxy(21, 27); printf("2.책상 밑");
        SetColor(POS == 2 ? 3 : 15);
        gotoxy(41, 27); printf("3.책상 위");
        SetColor(POS == 3 ? 3 : 15);
        gotoxy(61, 27); printf("4.칠판");
        SetColor(POS == 4 ? 3 : 15);
        gotoxy(81, 27); printf("5.포스터");
        SetColor(POS == 5 ? 3 : 15);
        gotoxy(101, 27); printf("6.돌아가기");
        SetColor(15);

        Sleep(100);
    }
    switch (POS)
    {
    case 0:
        PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
        return 0;
    case 1:

        return 0;
    case 2:
        return 0;
    case 3:
        return 0;
    case 4:
    { CLS;
    Quiz5(quiz5);
    Answer5(ans5); 
    }
    case 5:
    {    CLS;
    LobbyPlay(POS); }
    default:
        return POS;
    }
	//return POS;
}

int Quiz5(int quiz5)

{
    char *text[] =
   {
       "Q. 슈뢰딩거의 다이어리\n\n슈뢰딩거의 다이어리에는 요일마다 알 수 없는 숫자가 적혀 있다.\n물음표에 들어갈 숫자는 무엇인가 ?",
       "MON = 3\nTUE = 5\nWED = 4\nTHU = ?",
    };
   int i = 0;

    for (i = 0; i < 2; i++)
   {
       gotoxy(1, 25);
       puts(text[i]);
       Getch();
       system("cls");
    }

}

int Answer5(int ans5)
{

    int POS = 4;
    CursorView(0);
    system("COLOR 0F");
    while (1) {
        if (GetAsyncKeyState(VK_LEFT))
            if (POS == 0) POS = 3;
            else POS -= 1;
        else if (GetAsyncKeyState(VK_RIGHT))
            if (POS == 3) POS = 0;
            else POS += 1;
        else if (GetAsyncKeyState(VK_RETURN))
            break;


        switch (POS) {
        case 0:
            SetColor(3);
            gotoxy(21, 27); printf("1. 2");
            SetColor(15);
            gotoxy(41, 27); printf("2. 4");
            gotoxy(61, 27); printf("3. 6");
            gotoxy(81, 27); printf("4. 8");
            break;

        case 1:
            SetColor(3);
            gotoxy(41, 27); printf("2. 4");
            SetColor(15);
            gotoxy(21, 27); printf("1. 2");
            gotoxy(61, 27); printf("3. 6");
            gotoxy(81, 27); printf("4. 8");
            break;

        case 2:
            SetColor(3);
            gotoxy(61, 27); printf("3. 6");
            SetColor(15);
            gotoxy(21, 27); printf("1. 2");
            gotoxy(41, 27); printf("2. 4");
            gotoxy(81, 27); printf("4. 8");
            break;

        case 3:
            SetColor(3);
            gotoxy(81, 27); printf("4. 8");
            SetColor(15);
            gotoxy(21, 27); printf("1. 2");
            gotoxy(41, 27); printf("2. 4");
            gotoxy(61, 27); printf("3. 6");
            break;

        default: break;
        }
        Sleep(100);
    }
    system("cls");

    if (POS == 0)
    {
        gotoxy(1, 25); printf("단서가 나타났다!");
        gotoxy(1, 26); printf(" 단서5: 그 무엇보다 가볍고, 그 무엇보다 자유로운 것");
        return 0;
    }

    else if (POS == 1)
    {
        gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
        return 0;
    }

    else if (POS == 2)
    {
        gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
        return 0;
    }
    else if (POS == 3)
    {
        gotoxy(1, 25); printf("아무일도 일어나지 않았다.");
        return 0;
    }
    else
        return 0;
    
}
