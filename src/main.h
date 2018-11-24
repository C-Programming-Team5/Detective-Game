#pragma once

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>

#define PAUSE system("pause > nul")
#define CLS system("cls")
#define QUIZCOUNT 5 // 퀴즈가 총 몇개인지 나타내는 상수입니다.

// 프로그램이 종료될 때 atexit함수로부터 호출되어, 프로그램을 정리합니다.
void CallAtExit(void);