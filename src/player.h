#pragma once
#include <time.h>
#include "main.h"
enum
{
	START,
	END
};

typedef struct player // 세이브를 위한 플레이어 구조체입니다.
{
	unsigned cleared; // 무엇을 클리어했는지 2진수 마스킹 형태로 저장하는 멤버입니다.
	unsigned playTime; // 플레이 시간을 저장하는 멤버입니다.
} Player;

// START를 받으면 시간을 초기화하고, END를 받으면 초기화 때부터 현재까지 지난 초를 반환합니다.
clock_t StopWatch(int flag);