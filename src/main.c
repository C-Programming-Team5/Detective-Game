#include "main.h"

void mainPtr(void);

int main(void)
{
	CursorView(0);
	system("COLOR 0F");
	mainPtr();
	int POS = 3;
	CursorView(0);
	system("COLOR 0F");
	mainPtr();
	while (1) {
		if (GetAsyncKeyState(VK_UP))
			if (POS == 0) POS = 2;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_DOWN))
			if (POS == 2) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			break;
		switch (POS) {
		case 0:
			SetColor(3);
			gotoxy(53, 15); printf("���� �ϱ�");
			SetColor(15);
			gotoxy(53, 17); printf("�̾� �ϱ�");
			gotoxy(53, 19); printf("���� ����");
			break;
		case 1:
			gotoxy(53, 15); printf("���� �ϱ�");
			SetColor(3);
			gotoxy(53, 17); printf("�̾� �ϱ�");
			SetColor(15);
			gotoxy(53, 19); printf("���� ����");
			break;
		case 2:
			gotoxy(53, 15); printf("���� �ϱ�");
			gotoxy(53, 17); printf("�̾� �ϱ�");
			SetColor(3);
			gotoxy(53, 19); printf("���� ����");
			SetColor(15);
			break;
		default: break;
		}
		Sleep(100);
	}
	CLS;
	if (POS == 0) puts("����");
	else if (POS == 1) puts("�̾�");
	
	PAUSE;
	return 0;
}

void mainPtr(void)
{
	system("title ESCAPE");
	/*
	puts
	(
		"___________ _________    ____  ______\n"
		"/ ____ / ___// ____/   |  / __  / ____/\n"
		"/ __ / ___ / / / / | | / / _ / / __ /\n"
		"/ / ___ ___ / / / ___ / ___ | / ____ / / ___\n"
		"/ _____//____/_____/_/  |_/_/   /_____/   "
	);
	*/

	gotoxy(53, 15); printf("���� �ϱ�");
	gotoxy(53, 17); printf("�̾� �ϱ�");
	gotoxy(53, 19); printf("���� ����");
}