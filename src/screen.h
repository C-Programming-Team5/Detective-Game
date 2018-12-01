#pragma once
#include "player.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define PAUSE system("pause > nul")
#define CLS system("cls")
#define CLSLINE(Y) gotoxy(1, (Y)); fputs("                                                                                                                        ", stdout)

// 특정한 키 입력을 받기 전까지 기다리는 매크로 함수입니다.
// ex) 엔터키 입력을 받을 경우, WAITFORKEY('\r');
#define WAITFORKEY(KEYCHAR) while (Getch() != (KEYCHAR));

// getch를 표준 + Win32API 로 구현한 코드입니다. 안정성이 높습니다.
TCHAR Getch(void);

// 글자색을 설정하는 함수입니다.
void SetColor(int color);

// 0을 인자로 주면 커서를 숨기고, 1을 인자로 주면 커서를 보이게 하는 함수입니다.
void CursorView(char show);

// 커서를 콘솔의 특정 위치로 이동시키는 함수입니다.
void gotoxy(int x, int y);

// 처음 화면을 띄우는 함수입니다.
void InitialPrint(void);

// 시작 선택화면을 띄우는 함수입니다. 새로시작 선택시 0을, 이어하기 선택시 1을, 종료하기 선택시 2를 반환합니다.
int StartScreen(void);

// 플레이어 데이터를 받아 단서를 출력합니다.
void PrintClues(const Player * const player);

// 화면을 비우고, 세이브 목록을 나타내는 함수입니다.
void PrintSaveList(const Player save[]);

// 프롤로그를 출력하는 함수입니다.
void Prologue(void);

// 로비 배경화면을 출력하는 함수입니다.
void LobbyScreen(void);

// 로비 선택지 화면을 출력하고 결과값을 받아오는 함수입니다.
int LobbyPlay(int choice);

// 아이템 선택화면을 출력하고 결과값을 받아오는 함수입니다.
int SelectItem(int item);

// 5번문제를 출력하는 함수입니다.
int Quiz5(int quiz5);

// 5번문제의 답을 출력하고 결과값을 받아오는 함수입니다.
int Answer5(int ans5);