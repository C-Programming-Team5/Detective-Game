#include "main.h"
#include "screen.h"
#include "save_io.h"

int main(void)
{
	int selected = 0;
	Player *save = InitSave(); // 세이브용 배열
	Player player = {0, 0}; // 플레이용 임시 데이터
	selected = StartScreen();
	switch (selected)
	{
		case 0: // 게임 시작
			break;
		case 1: // 이어 하기
			if (LoadFromFile(save) == 0)
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

