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

void PrintSaveList(Player * player) // 수정 필요
{
	int i = 0;

	CLS;
	for (i = 0; i < SAVESIZE; i++)
	{
		printf("%d번째 세이브\n", i);
		printf("맞힌 퀴즈 개수: %d\n", GetClearedQuizCount(player, i));
		printf("플레이 시간: %d\n\n", player[i].playTime);
	}
	return;
}

int InternelSave(Player *player, Player *save, int id)
{
	if (player != NULL && save != NULL)
	{
		save[id].cleared = player->cleared;
		save[id].playTime = player->playTime;
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

int SaveToFile(Player *player)
{
	FILE *saveFile = fopen("save.sav", "wb");
	uint8_t hash = 0;
	int i = 0;
	if (saveFile == EOF)
	{
		return FAIL;
	}
	sha256(player, sizeof(Player) * SAVESIZE, &hash);
	
	for (i = 0; i < SAVESIZE; i++)
	{
		fprintf("%d %d\n", player[i].cleared, player[i].playTime);
	}
	fprintf("%d", hash);
	close(saveFile);
	return SUCCESS;
}

int LoadFromFile(Player *player)
{
	FILE *saveFile = fopen("save.sav", "rb");
	int i = 0;
	uint8_t fileHash = 0, newHash = 0;

	for (i = 0; i < SAVESIZE; i++)
	{
		if (fscanf(saveFile, "%d %d\n", &(player[i].cleared), &(player[i].playTime)) <= 0)
		{
			fclose(saveFile);
			return FAIL;
		}
	}
	if (fscanf("%d", &fileHash) <= 0)
	{
		fclose(saveFile);
		return FAIL;
	}
	fclose(saveFile);
	sha256(player, sizeof(Player) * SAVESIZE, &newHash);
	if (fileHash != newHash)
	{
		return FAIL;
	}
	return SUCCESS;
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
