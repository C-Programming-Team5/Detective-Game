#include "lobbyplay.h"

    int lobbyplay(int choice)
    {
        gotoxy(2, 25);  printf("���� ������ �ұ�?");
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
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                SetColor(15);
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                gotoxy(61, 27); printf("4.�����Ѵ�");
                gotoxy(81, 27); printf("5.�����Ѵ�");
                break;
            case 1:
                SetColor(3);
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                SetColor(15);
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                gotoxy(61, 27); printf("4.�����Ѵ�");
                gotoxy(81, 27); printf("5.�����Ѵ�");
                break;
            case 2:
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                SetColor(3);
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                SetColor(15);
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                gotoxy(61, 27); printf("4.�����Ѵ�");
                gotoxy(81, 27); printf("5.�����Ѵ�");
                break;
            case 3:
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                SetColor(3);
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                SetColor(15);
                gotoxy(61, 27); printf("4.�����Ѵ�");
                gotoxy(81, 27); printf("5.�����Ѵ�");
                break;
            case 4:
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                SetColor(3);
                gotoxy(61, 27); printf("4.�����Ѵ�");
                SetColor(15);
                gotoxy(81, 27); printf("5.�����Ѵ�");
                break;
            case 5:
                gotoxy(1, 27); printf("1.������ ã�ƺ���");
                gotoxy(21, 27); printf("2.�ܼ��� ����");
                gotoxy(41, 27); printf("3.�ڹ��踦 ����");
                gotoxy(61, 27); printf("4.�����Ѵ�");
                SetColor(3);
                gotoxy(81, 27); printf("5.�����Ѵ�");
                SetColor(15);
                break;
            default:
                break;
            }
            Sleep(100);
        }
        cls;
        return POS;
    }
