#pragma once

#include <stdio.h>
#include <stdlib.h>
/*
	Github의 ilvn / SHA256 repo에서 가져온 코드입니다.
	SHA-256 알고리즘에 대한 자세한 설명은 https://csrc.nist.gov/csrc/media/publications/fips/180/4/final/documents/fips180-4-draft-aug2014.pdf
	데이터를 암호화하는 SHA-256 해시 함수를 제공합니다. 세이브의 무결성 검증을 위해 사용합니다.
*/
#include "sha256.h"

#define SAVESIZE 5 // 최대 세이브 개수를 지정하는 상수입니다.

typedef struct player // 세이브를 위한 플레이어 구조체로, 후에 player.h로 이동할 수도 있습니다.
{
    unsigned cleared; // 무엇을 클리어했는지 2진수 마스킹 형태로 저장하는 멤버입니다.
    unsigned playTime; // 플레이 시간을 저장하는 멤버입니다.
} Player;

// 클리어한 퀴즈의 개수를 반환하는 함수입니다.
int GetClearedQuizCount(Player *player, int id);
// 화면을 비우고, 세이브 목록을 나타내는 함수입니다.
void PrintSaveList(Player *player);
int InternelSave(Player *player, int id);