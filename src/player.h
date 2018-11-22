#pragma once
#include "main.h"

typedef struct player // 세이브를 위한 플레이어 구조체입니다.
{
	unsigned cleared; // 무엇을 클리어했는지 2진수 마스킹 형태로 저장하는 멤버입니다.
	unsigned playTime; // 플레이 시간을 저장하는 멤버입니다.
} Player;