#include "save_io.h"
#include "main.h"
#include "screen.h"

int InitSave(Player **save)
{
	*save = (Player *)calloc(SAVESIZE, sizeof(Player));
	if (save == NULL)
	{
		return FAIL;
	}
	ExecuteFree(*save);
	return SUCCESS;
}

int GetClearedQuizCount(Player save[], int id)
{
	int i = 0, result = 0;

	for (i = 0; i < QUIZCOUNT; i++)
	{
		result += (save[id].cleared & (1 << i)) && 1;
	}
	return result;
}

int Save(Player *player, Player save[], int id)
{
	FILE *saveFile = fopen("save.sav", "wb");
	uint8_t hash = 0;

	if (saveFile == NULL)
	{
		return FAIL;
	}

	if (player != NULL && save != NULL)
	{
		save[id] = *player;
	}
	else
	{
		fclose(saveFile);
		return FAIL;
	}

	sha256(save, sizeof(Player) * SAVESIZE, &hash);
	
	if (fwrite(save, sizeof(Player), SAVESIZE, saveFile) < (sizeof(Player) * SAVESIZE))
	{
		fclose(saveFile);
		return FAIL;
	}

	if (fwrite(&hash, 8, 1, saveFile) < 8)
	{
		fclose(saveFile);
		return FAIL;
	}

	fclose(saveFile);
	return SUCCESS;
}

int LoadFromFile(Player save[])
{
	FILE *saveFile = fopen("save.sav", "rb");
	uint8_t fileHash = 0, newHash = 0;

	if (saveFile == NULL)
	{
		return FAIL;
	}

	if (fread(save, sizeof(Player), SAVESIZE, saveFile) < (sizeof(Player) * SAVESIZE))
	{
		fclose(saveFile);
		return FAIL;
	}

	if (fread(&fileHash, 8, 1, saveFile) < 8)
	{
		fclose(saveFile);
		return FAIL;
	}

	fclose(saveFile);

	sha256(save, sizeof(Player) * SAVESIZE, &newHash);

	if (fileHash != newHash)
	{
		return FAIL;
	}

	return SUCCESS;
}

void ExecuteFree(Player save[])
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