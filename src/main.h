#pragma once

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>

#define PAUSE system("pause > nul")
#define CLS system("cls")
#define QUIZCOUNT 5 // 퀴즈가 총 몇개인지 나타내는 상수입니다.

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);