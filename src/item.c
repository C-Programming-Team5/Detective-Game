#include "item.h"

int SelectItem(int item)
{
    gotoxy(2, 25); printf("� ���Ǻ��� ã�ƺ���?");
    int POS = 6;
    CursorView(0);
    system("COLOR 0F");
    while (!GetAsyncKeyState(VK_RETURN))
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (POS <= 0)
            {
                POS = 6;
            }
            else
            {
                POS -= 1;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (POS >= 6)
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
            gotoxy(1, 27); printf("1.��ǻ��");
            SetColor(15);
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 1:
            SetColor(3);
            gotoxy(1, 27); printf("1.��ǻ��");
            SetColor(15);
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 2:
            gotoxy(1, 27); printf("1.��ǻ��");
            SetColor(3);
            gotoxy(21, 27); printf("2.å�� ��");
            SetColor(15);
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 3:
            gotoxy(1, 27); printf("1.��ǻ��");
            gotoxy(21, 27); printf("2.å�� ��");
            SetColor(3);
            gotoxy(41, 27); printf("3.å�� ��");
            SetColor(15);
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 4:
            gotoxy(1, 27); printf("1.��ǻ��");
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            SetColor(3);
            gotoxy(61, 27); printf("4.ĥ��");
            SetColor(15);
            gotoxy(81, 27); printf("5.������");
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 5:
            gotoxy(1, 27); printf("1.��ǻ��");
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            SetColor(3);
            gotoxy(81, 27); printf("5.������");
            SetColor(15);
            gotoxy(101, 27); printf("6.���ư���");
            break;
        case 6:
            gotoxy(1, 27); printf("1.��ǻ��");
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
            SetColor(3);
            gotoxy(101, 27); printf("6.���ư���");
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