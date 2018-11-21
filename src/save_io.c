#include "save_io.h"
#include "main.h"

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
	}
}

int InternelSave(Player * player, int id)
{
	return 0;
}
