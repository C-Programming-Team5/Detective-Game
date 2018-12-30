#ifndef _SCREEN_H
#define _SCREEN_H

#include "player.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define PAUSE system("pause > nul")
#define CLS system("cls")
#define CLSLINE(Y) GotoXY(1, (Y)); fputs("                                                                                                                        ", stdout)


// 특정한 키 입력을 받기 전까지 기다리는 매크로 함수입니다.
// ex) 엔터키 입력을 받을 경우, WAITFORKEY('\r')
#define WAITFORKEY(KEYCHAR) while (Getch() != (KEYCHAR));

// 특정한 키 입력을 받기 전까지 기다리는 매크로 함수입니다.
// ex) 엔터키 입력을 받을 경우, WAITFORVK(VK_RETURN)
#define WAITFORVK(VK) while (GetKey() != (VK));

// getch를 표준 + Win32API 로 구현한 코드입니다. 안정성이 높습니다.
TCHAR Getch(void);

// 글자색을 설정하는 함수입니다.
void SetColor(int color);

// 0을 인자로 주면 커서를 숨기고, 1을 인자로 주면 커서를 보이게 하는 함수입니다.
void CursorView(char show);

// 커서를 콘솔의 특정 위치로 이동시키는 함수입니다.
void GotoXY(int x, int y);

// 처음 화면을 띄우는 함수입니다.
void InitialPrint(void);

// 시작 선택화면을 띄우는 함수입니다. 새로시작 선택시 0을, 이어하기 선택시 1을, 종료하기 선택시 2를 반환합니다.
int StartScreen(void);

// number가 -1이면 플레이어 데이터에 저장된 모든 단서를, 0~4라면 저장되어있는 해당 번호의 단서를 출력합니다.
void PrintClues(const Player * const player, int number);

// 화면을 비우고, 세이브 목록을 나타내는 함수입니다.
void PrintSaveList(const Player save[]);

// 프롤로그를 출력하는 함수입니다.
void Prologue(int nuber);

// 로비 배경화면을 출력하는 함수입니다.
void LobbyScreen(void);

// 로비 선택지 화면을 출력하고 결과값을 받아오는 함수입니다.
int LobbyPlay(void);

// 아이템 선택화면을 출력하고 결과값을 받아오는 함수입니다.
int SelectItem(void);

// 문제를 출력하는 함수입니다.
void Quiz(int number);

// 문제의 답을 출력하고 결과값을 받아오는 함수입니다.
void Answer(Player *player, int number);

// 문 그림을 나타내는 함수입니다.
void PrintDoor(void);

// 문이 열리는 첫번째 모습을 나타내는 함수입니다.
void PrintDoor1(void);

// 문이 열리는 두번째 모습을 나타내는 함수입니다.
void PrintDoor2(void);

// 비밀번호를 입력받는 함수입니다.
int OpenLock(void);

// 컴퓨터 그림을 나타내는 함수입니다.
void Quiz1Screen(void);

// 책상아래 그림을 나타내는 함수입니다.
void Quiz2Screen(void);

// 책상 위 그림을 나타내는 함수입니다.
void Quiz3Screen(void);

// 칠판 그림을 나타내는 함수입니다.
void Quiz4Screen(void);

// 포스터 그림을 나타내는 함수입니다.
void Quiz5Screen(void);

// 시작할때 제목을 나타내는 함수입니다.
void Title(void);

// 엔딩을 출력하는 함수입니다.
void PrintEnding(void);

// 실패 엔딩을 출력하는 함수입니다.
void PrintFail(void);

// ERROR가 발생시 -1을 리턴하고, 정상 입력시 1을 리턴하며 keyCode를 VK값으로 설정하고, 키를 뗄 때 0을 반환하면서, keyCode를 0으로 설정합니다.
// https://docs.microsoft.com/ko-kr/windows/desktop/inputdev/virtual-key-codes VK값 리스트입니다.
int GetKeyboard(int *keyCode);

// GetKeyboard의 사용을 Getch와 비슷하게 만들어주는 인터페이스입니다. 오류시 혹은 키를 뗄 시 0을, 키 입력시 VK값을 반환합니다.
int GetKey(void);

int Memo(int pos);

void Memo1(void);

void Memo2(void);

void Memo3(void);

void Memo4(void);

void Memo5(void);

#endif
