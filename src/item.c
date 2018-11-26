#include "item.h"

int SelectItem(int item)
{
<<<<<<< HEAD
    gotoxy(2, 25); printf("어떤 물건부터 찾아볼까?");
=======
    gotoxy(2, 25); printf("� ���Ǻ��� ã�ƺ���?");
>>>>>>> parent of 8df393d... SelectItem update
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
            gotoxy(1, 27); printf("1.컴퓨터");
            SetColor(15);
<<<<<<< HEAD
            gotoxy(21, 27); printf("2.책상 밑");
            gotoxy(41, 27); printf("3.책상 위");
            gotoxy(61, 27); printf("4.칠판");
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
            break;
        case 1:
            SetColor(3);
            gotoxy(1, 27); printf("1.컴퓨터");
            SetColor(15);
<<<<<<< HEAD
            gotoxy(21, 27); printf("2.책상 밑");
            gotoxy(41, 27); printf("3.책상 위");
            gotoxy(61, 27); printf("4.칠판");
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(21, 27); printf("2.å�� ��");
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
            break;
        case 2:
            gotoxy(1, 27); printf("1.컴퓨터");
            SetColor(3);
            gotoxy(21, 27); printf("2.책상 밑");
            SetColor(15);
<<<<<<< HEAD
            gotoxy(41, 27); printf("3.책상 위");
            gotoxy(61, 27); printf("4.칠판");
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(41, 27); printf("3.å�� ��");
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
            break;
        case 3:
            gotoxy(1, 27); printf("1.컴퓨터");
            gotoxy(21, 27); printf("2.책상 밑");
            SetColor(3);
            gotoxy(41, 27); printf("3.책상 위");
            SetColor(15);
<<<<<<< HEAD
            gotoxy(61, 27); printf("4.칠판");
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(61, 27); printf("4.ĥ��");
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
            break;
        case 4:
            gotoxy(1, 27); printf("1.컴퓨터");
            gotoxy(21, 27); printf("2.책상 밑");
            gotoxy(41, 27); printf("3.책상 위");
            SetColor(3);
            gotoxy(61, 27); printf("4.칠판");
            SetColor(15);
<<<<<<< HEAD
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
            break;
        case 5:
            gotoxy(1, 27); printf("1.컴퓨터");
            gotoxy(21, 27); printf("2.책상 밑");
            gotoxy(41, 27); printf("3.책상 위");
            gotoxy(61, 27); printf("4.칠판");
            SetColor(3);
<<<<<<< HEAD
            gotoxy(81, 27); printf("5.포스터");
=======
            gotoxy(81, 27); printf("5.������");
>>>>>>> parent of 8df393d... SelectItem update
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