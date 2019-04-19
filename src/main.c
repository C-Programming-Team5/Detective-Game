#include "main.h"
#include "screen.h"
#include "save_io.h"

int main(void)
{
	int selected = 0, saveNum = 0;
	int number= 0;
	Player save[SAVESIZE]; // 세이브용 배열
	Player player = {0, 0}; // 플레이용 임시 데이터

	memset(save, 0, sizeof(save)); // 세이브 배열을 초기화합니다.

	system("mode con cols=9001 lins=120");
	selected = StartScreen();
	switch (selected)
	{
		case 0: // 게임 시작
			Prologue(number);
			GameLoop(&player, save);
			break;
		case 1: // 이어 하기
			if (LoadFromFile(save) == FAIL)
			{
				perror("파일을 불러올 수 없습니다.\n");
				return 1;
			}
			while (saveNum < '1' || '5' < saveNum)
			{
				PrintSaveList(save);
				puts("로드할 번호를 입력하세요: ");
				saveNum = Getch();
			}
			memcpy(&player, save + saveNum - '1', sizeof(Player));
			GameLoop(&player, save);
			break;
		case 2:
			show_rnk();
		case 3: // 게임 종료
			break;
		default:
			break;
	}
	return 0;
}

void GameLoop(Player *player, Player save[])
{
	int select = 0, item = 0, saveNum = 0;

	memset(player, 0, sizeof(Player));

	StopWatch(START);
	
	while (select != 4)
	{
		item = 0;
		saveNum = 0;
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
				puts("'n'키를 눌러 빠져나가자.");
				WAITFORKEY('n');
				break;
			case 2: // 자물쇠 풀기
				if (OpenLock() == GAME_CLEAR)
				{
					PrintEnding();
					create_rnk();
					//show_rnk();
					return;
				}
				else
				{
					PrintFail();
				}
				break;
			case 3: // 세이브
				while (saveNum < '1' || '5' < saveNum)
				{
					PrintSaveList(save);
					GotoXY(1, 27);
					puts("몇번 세이브에 저장하시겠습니까?");
					saveNum = Getch();
				}
				player->playTime += StopWatch(END);
				Save(player, save, saveNum - '1');
				puts("세이브가 완료되었습니다.");
				puts("'n'키를 눌러서 빠져나가자");
				WAITFORKEY('n');
				break;
			case 4: // 게임 종료
				break;
			default:
				break;
		}
	}
}