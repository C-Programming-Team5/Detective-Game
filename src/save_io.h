#pragma once

#include <stdio.h>
#include <stdlib.h>
/*
	Github의 ilvn / SHA256 repo에서 가져온 코드입니다.
	SHA-256 알고리즘에 대한 자세한 설명은 https://csrc.nist.gov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf
	데이터를 암호화하는 SHA-256 해시 함수를 제공합니다. 세이브의 무결성 검증을 위해 사용합니다.
*/
#include "sha256.h"
#include "main.h"
#include "player.h"

#define SAVESIZE 5 // 최대 세이브 개수를 지정하는 상수입니다.
#define SALT 20181224 // 해시에 쓰이는 SALT 입니다.

enum
{
	FAIL,
	SUCCESS
};

// 세이브 리스트를 초기화합니다. 성공시 SUCCESS, 실패시 FAIL을 반환합니다.
int InitSave(Player **save);

// 클리어한 퀴즈의 개수를 반환하는 함수입니다.
int GetClearedQuizCount(const Player const save[], const int id);

// 플레이어 데이터를 저장합니다. 성공시 SUCCESS, 실패시 FAIL을 반환합니다.
int Save(const Player * const player, Player save[], const int id);

// 파일로부터 세이브를 불러옵니다. 성공시 SUCCESS, 실패시 FAIL을 반환합니다.
int LoadFromFile(Player save[]);

// 처음 호출시 플레이어 세이브 리스트의 포인터를 저장하고, 다음 호출시, 저장된 동적 리스트를 해제합니다.
void ExecuteFree(Player save[]);
