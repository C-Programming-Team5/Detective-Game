#ifndef _PLAYER_H
#define _PLAYER_H

#include <time.h>

// 타이머 함수의 인자값을 위한 열거형입니다.
enum
{
	START,
	END
};

// 세이브를 위한 플레이어 구조체입니다.
typedef struct player
{
	// 무엇을 클리어했는지 2진수 마스킹 형태로 저장하는 멤버입니다.
	unsigned cleared;
	// 플레이 시간을 저장하는 멤버입니다.
	unsigned playTime;
} Player;

// START를 받으면 시간을 초기화하고, END를 받으면 초기화 때부터 현재까지 지난 초를 반환합니다.
clock_t StopWatch(int flag);

#endif
