#pragma once

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <string.h>

#define QUIZCOUNT 5 // 퀴즈가 총 몇개인지 나타내는 상수입니다.

enum
{
	GAME_OVER,
	GAME_CLEAR
};

void GameLoop(Player *player, Player save[]);