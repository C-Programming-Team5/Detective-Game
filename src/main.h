#ifndef _MAIN_H
#define _MAIN_H
#pragma comment(lib, "winmm.lib")

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <string.h>
#include <mmsystem.h>

#include "player.h"

// 퀴즈가 총 몇개인지 나타내는 상수입니다.
#define QUIZCOUNT 5

// 게임의 성공 여부를 표시하기 위한 열거형입니다.
enum
{
	GAME_OVER,
	GAME_CLEAR
};

typedef void (*vvfp)(void);

// 게임의 메인 루프를 돌리기 위한 함수입니다.
void GameLoop(Player *player, Player save[]);

#endif
