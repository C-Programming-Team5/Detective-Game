#include "lobbyplay.h"

    int LobbyPlay(int choice)
    {
        gotoxy(2, 25);  printf("이제 무엇을 할까?");
        int POS = 5;
        CursorView(0);
        system("COLOR 0F");
        while (!GetAsyncKeyState(VK_RETURN))
        {
            if (GetAsyncKeyState(VK_LEFT))
            {
                if (POS <= 0)
                {
                    POS = 5;
                }
                else
                {
                    POS -= 1;
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                if (POS >= 5)
                {
                    POS = 0;
                }
                else
                {
                    POS++;
                }
            }
            switch (POS)
            {
            case 0:
                SetColor(3);
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                SetColor(15);
                gotoxy(21, 27); printf("2.단서를 본다");
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                gotoxy(61, 27); printf("4.저장한다");
                gotoxy(81, 27); printf("5.종료한다");
                break;
            case 1:
                SetColor(3);
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                SetColor(15);
                gotoxy(21, 27); printf("2.단서를 본다");
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                gotoxy(61, 27); printf("4.저장한다");
                gotoxy(81, 27); printf("5.종료한다");
                break;
            case 2:
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                SetColor(3);
                gotoxy(21, 27); printf("2.단서를 본다");
                SetColor(15);
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                gotoxy(61, 27); printf("4.저장한다");
                gotoxy(81, 27); printf("5.종료한다");
                break;
            case 3:
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                gotoxy(21, 27); printf("2.단서를 본다");
                SetColor(3);
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                SetColor(15);
                gotoxy(61, 27); printf("4.저장한다");
                gotoxy(81, 27); printf("5.종료한다");
                break;
            case 4:
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                gotoxy(21, 27); printf("2.단서를 본다");
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                SetColor(3);
                gotoxy(61, 27); printf("4.저장한다");
                SetColor(15);
                gotoxy(81, 27); printf("5.종료한다");
                break;
            case 5:
                gotoxy(1, 27); printf("1.물건을 찾아본다");
                gotoxy(21, 27); printf("2.단서를 본다");
                gotoxy(41, 27); printf("3.자물쇠를 연다");
                gotoxy(61, 27); printf("4.저장한다");
                SetColor(3);
                gotoxy(81, 27); printf("5.종료한다");
                SetColor(15);
                break;
            default:
                break;
            }
            Sleep(100);

        }
        cls;
        switch (POS)
        {
        case 0:
            LobbyScreen();
            SelectItem(); //물건 선택창으로 넘어갑니다.

        }
        return POS;
    }
