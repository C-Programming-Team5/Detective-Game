#include "save_io.h"
#include "main.h"

int GetClearedQuizCount(const Player save[], const int id)
{
	int i = 0, result = 0;

	// 퀴즈 클리어 데이터를 순회하면서, 클리어 횟수를 카운트합니다.
	for (i = 0; i < QUIZCOUNT; i++)
	{
		result += (save[id].cleared & (1 << i)) && 1;
	}
	return result;
}

int Save(const Player * const player, Player save[], const int id)
{
	// 세이브 파일을 바이너리 쓰기 형태로 불러옵니다.
	FILE *saveFile = fopen("save.sav", "wb");
	// 해싱을 위한 버퍼입니다.
	uint8_t firstHash[SHA256_BYTES] = { 0 }, secondHash[SHA256_BYTES] = { 0 };

	// 만약 파일을 불러오지 못했다면, 세이브 실패입니다.
	if (saveFile == NULL)
	{
		return FAIL;
	}

	if (player!= NULL || save != NULL)
	{
		fclose(saveFile);
		return FAIL;
	}

	// 세이브 데이터를 배열에 저장합니다.
	memcpy(save + id, player, sizeof(Player));

	// 두 번의 해싱 과정을 통해 보안성을 약간 강화하였습니다.
	sha256(save, sizeof(Player) * SAVESIZE, &firstHash);
	sha256(&firstHash, SHA256_BYTES, &secondHash);
	
	// 정상적으로 데이터를 파일에 쓰지 못했다면, 실패입니다.
	if (fwrite(save, sizeof(Player), SAVESIZE, saveFile) < SAVESIZE)
	{
		fclose(saveFile);
		return FAIL;
	}

	// 파일에 정상적으로 무결성 검증 데이터를 쓰지 못했다면, 실패입니다.
	if (fwrite(&secondHash, 1, SHA256_BYTES, saveFile) < SHA256_BYTES)
	{
		fclose(saveFile);
		return FAIL;
	}

	// 모든 과정을 정상적으로 마친 후, 파일을 닫고, 성공을 반환합니다.
	fclose(saveFile);
	return SUCCESS;
}

int LoadFromFile(Player save[])
{
	// 세이브 파일을 바이너리 읽기 형태로 불러옵니다.
	FILE *saveFile = fopen("save.sav", "rb");
	// 파일에서 무결성 데이터를 읽어올 버퍼와, 해시값을 저장할 배열들입니다.
	uint8_t fileHash[SHA256_BYTES] = {0}, firstHash[SHA256_BYTES] = {0}, secondHash[SHA256_BYTES] = {0};

	// 파일을 열지 못했을 경우, 실패입니다.
	if (saveFile == NULL)
	{
		return FAIL;
	}

	// 파일로부터 읽어온 내용이 적을 경우, 실패입니다.
	if (fread(save, sizeof(Player), SAVESIZE, saveFile) < SAVESIZE)
	{
		fclose(saveFile);
		return FAIL;
	}

	// 파일로부터 무결성 검증 데이터를 제대로 읽지 못했을 경우, 실패입니다.
	if (fread(&fileHash, 1, SHA256_BYTES, saveFile) < SHA256_BYTES)
	{
		fclose(saveFile);
		return FAIL;
	}

	// 파일 읽기를 마치고, 파일을 닫습니다.
	fclose(saveFile);

	// 저장시에 사용한 방식을 사용해서 해시를 만듭니다.
	sha256(save, sizeof(Player) * SAVESIZE, &firstHash);
	sha256(&firstHash, SHA256_BYTES, &secondHash);

	// 파일로부터 읽은 해시와, 만들어진 해시를 비교하여 무결성을 체크합니다
	if (memcmp(fileHash, secondHash, SHA256_BYTES) != 0)
	{
		return FAIL;
	}

	return SUCCESS;
}
