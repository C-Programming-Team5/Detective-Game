#include "main.h"
#include "screen.h"
#include "save_io.h"

void CallAtExit(int argc, char *argv[])
{
	ExecuteFree(NULL);
	return;
}

int main(void)
{
	int selected = 0;
	Player *save = NULL; // 세이브용 배열
	Player player = {0, 0}; // 플레이용 임시 데이터

	atexit(CallAtExit); // 프로그램이 종료될 시 실행되어, 프로그램을 정리합니다.

	if (InitSave(&save) == FAIL)
	{
		perror("초기화 오류가 발생하였습니다. \n프로그램을 종료합니다.\n");
		return 1;
	}
	selected = StartScreen();
	switch (selected)
	{
		case 0: // 게임 시작
			StopWatch(START);
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

