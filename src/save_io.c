#include "save_io.h"
#include "main.h"

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

int GetClearedQuizCount(const Player save[], int id)
{
	int i = 0, result = 0;

	for (i = 0; i < QUIZCOUNT; i++)
	{
		result += (save[id].cleared & (1 << i)) && 1;
	}
	return result;
}

int Save(const Player * const player, Player save[], int id)
{
	FILE *saveFile = fopen("save.sav", "wb");
	uint8_t firstHash = 0, secondHash = 0;

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

	// 두 번의 해싱 과정을 통해 보안성을 약간 강화하였습니다.
	sha256(save, sizeof(Player) * SAVESIZE, &firstHash);
	sha256(&firstHash, SHA256_BYTES, &secondHash);
	
	if (fwrite(save, sizeof(Player), SAVESIZE, saveFile) < (sizeof(Player) * SAVESIZE))
	{
		fclose(saveFile);
		return FAIL;
	}

	if (fwrite(&secondHash, 1, SHA256_BYTES, saveFile) < SHA256_BYTES)
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
	uint8_t fileHash = 0, firstHash = 0, secondHash = 0;

	if (saveFile == NULL)
	{
		return FAIL;
	}

	if (fread(save, sizeof(Player), SAVESIZE, saveFile) < (sizeof(Player) * SAVESIZE))
	{
		fclose(saveFile);
		return FAIL;
	}

	if (fread(&fileHash, 1, SHA256_BYTES, saveFile) < SHA256_BYTES)
	{
		fclose(saveFile);
		return FAIL;
	}

	fclose(saveFile);

	// 저장시에 사용한 방식을 사용해서 해시를 만듭니다.
	sha256(save, sizeof(Player) * SAVESIZE, &firstHash);
	sha256(&firstHash, SHA256_BYTES, &secondHash);

	if (fileHash != secondHash)
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