#include "main.h"
#include "screen.h"
#include "save_io.h"

int main(int argc, char *argv[])
{
	int selected = 0;
	int action = 0;
	Player save[SAVESIZE]; // 세이브용 배열
	Player player = {0, 0}; // 플레이용 임시 데이터

	memset(save, 0, sizeof(save)); // 세이브 배열을 초기화합니다.

	selected = StartScreen();
	switch (selected)
	{
		case 0: // 게임 시작
			StopWatch(START);
			Prologue();
			LobbyPlay(action);
			break;
		case 1: // 이어 하기
			if (LoadFromFile(save) == FAIL)
			{
				perror("파일을 불러올 수 없습니다.\n");
				return 1;
			}
			PrintSaveList(save);
			break;
		default: // 게임 종료
			break;
	}
	return 0;
}

