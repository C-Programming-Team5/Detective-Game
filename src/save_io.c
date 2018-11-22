#include "save_io.h"
#include "main.h"

Player * InitSave(void)
{
	Player *save = (Player *)calloc(SAVESIZE, sizeof(Player));
	FreeExecuter(save);
	atexit(FreeCaller); // 게임이 종료될 시 호출되어, 동적할당된 배열을 해제합니다.
	return save;
}

int GetClearedQuizCount(Player * player, int id)
{
	int i = 0, result = 0;

	for (i = 0; i < QUIZCOUNT; i++)
	{
		result += (player->cleared & (1 << i)) && 1;
	}
	return result;
}

void PrintSaveList(Player * player)
{
	int i = 0;

	CLS;
	for (i = 0; i < SAVESIZE; i++)
	{
		printf("%d번째 세이브\n", i);
		printf("맞힌 퀴즈 개수: %d\n", GetClearedQuizCount(player, i));
		printf("플레이 시간: "); 
	}
}

int InternelSave(Player *player, Player *save, int id)
{
	if (player != NULL && save != NULL)
	{
		save[id].cleared = player->cleared;
		save[id].playTime = player->playTime;
	}
	else
	{
		perror("세이브 실패입니다.\n");
		return 0;
	}
	return 1;
}

int SaveToFile(Player *player)
{
	FILE *saveFile = fopen("save.sav", "wb");
	uint8_t hash = 0;
	int i = 0;
	sha256(player, sizeof(Player) * SAVESIZE, &hash);
	
	for (i = 0; i < SAVESIZE; i++)
	{
		fprintf("%d %d\n", player[i].cleared, player[i].playTime);
	}
	fprintf("%d", hash);
	close(saveFile);
}

int LoadFromFile(Player *player)
{
	FILE *saveFile = fopen("save.sav", "rb");
	int i = 0;
	uint8_t fileHash = 0, newHash = 0;

	for (i = 0; i < SAVESIZE; i++)
	{
		fscanf(saveFile, "%d %d\n", &(player[i].cleared), &(player[i].playTime));
	}
	fscanf("%d", &fileHash);
	close(saveFile);
	sha256(player, sizeof(Player) * SAVESIZE, &newHash);
	if (fileHash != newHash)
	{
		perror("세이브 파일이 손상되었습니다!!!!\n");
		return 0;
	}
	return 1;
}

void FreeCaller(void)
{
	FreeExecuter(NULL);
	return;
}

void FreeExecuter(Player * save)
{
	static int count = 0;
	static Player *saved = NULL;

	if (count == 0)
	{
		saved = save;
		count = 1;
	}
	else
	{
		free(saved);
	}
	return;
}
