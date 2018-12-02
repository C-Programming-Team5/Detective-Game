#include "main.h"
#include "screen.h"
#include "save_io.h"

int main(int argc, char *argv[])
{
	int selected = 0;
	int action = 1;
	Player save[SAVESIZE]; // 세이브용 배열
	Player player = {0, 0}; // 플레이용 임시 데이터

	memset(save, 0, sizeof(save)); // 세이브 배열을 초기화합니다.

	selected = StartScreen();
	switch (selected)
	{
		case 0: // 게임 시작
			StopWatch(START);
			Prologue();
			GameLoop(&player, save);
			break;
		case 1: // 이어 하기
			if (LoadFromFile(save) == FAIL)
			{
				perror("파일을 불러올 수 없습니다.\n");
				return 1;
			}
			selected = 0;
			while (selected < '1' || '5' < selected)
			{
				PrintSaveList(save);
				puts("로드할 번호를 입력하세요: ");
				selected = Getch();
			}
			memcpy(&player, save + selected - '1', sizeof(Player));
			GameLoop(&player, save);
			break;
		default: // 게임 종료
			break;
	}
	return 0;
}

void GameLoop(Player *player, Player save[])
{
	int select = 0, item = 0, saveNum = 0;
	
	while (select != 4)
	{
		select = LobbyPlay();

		switch (select)
		{
			case 0: // 퀴즈 풀기
				while (item != 5)
				{
					PlaySound(TEXT("walking.wav"), NULL, SND_ASYNC);
					LobbyScreen();
					item = SelectItem();
					if (item != 5)
					{
						if (item == 1)
							PlaySound(TEXT("click.wav"), NULL, SND_ASYNC);
						Quiz(item);
						Answer(player, item);
					}
				}
				break;
			case 1: // 단서 보기
				PrintClues(player, -1);
				break;
			case 2: // 자물쇠 풀기
				OpenLock();
				break;
			case 3: // 세이브
				while (saveNum < '1' || '5' < saveNum)
				{
					PrintSaveList(save);
					gotoxy(1, 27);
					puts("몇번 세이브에 저장하시겠습니까?");
					saveNum = Getch();
				}
				Save(player, save, saveNum - '1');
				puts("세이브가 완료되었습니다.");
				break;
			case 4: // 게임 종료
				break;
			default:
				break;
		}
	}
}