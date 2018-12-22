#ifndef _SCREEN_H

#include "player.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define PAUSE system("pause > nul")
#define CLS system("cls")
#define CLSLINE(Y) gotoxy(1, (Y)); fputs("                                                                                                                        ", stdout)

// 특정한 키 입력을 받기 전까지 기다리는 매크로 함수입니다.
// ex) 엔터키 입력을 받을 경우, WAITFORKEY('\r')
#define WAITFORKEY(KEYCHAR) while (Getch() != (KEYCHAR));

// 특정한 키 입력을 받기 전까지 기다리는 매크로 함수입니다.
// ex) 엔터키 입력을 받을 경우, WAITFORVK(VK_RETURN)
#define WAITFORVK(VK) while (GetKey() != (VK));

// 단서 목록입니다.
const char *clues[] =
{
	"단서1: 그것은 세상 어디에도 묶여있지 않다.\n",
	"단서2 : 세상의 그 무엇보다 강하기도 하지만, 그 무엇보다 약하기도 하다.\n",
	"단서3 : 눈에 보이진 않지만, 정말 많은 이름을 갖고 있다.\n",
	"단서4 : 그것에게 멈춤이란 곧 죽음이다.\n",
	"단서5: 그 무엇보다 가볍고, 그 무엇보다 자유로운 것\n",
};

// 퀴즈 목록입니다.
const char const *quiz[][4] =
{
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다",
		"Q. 신분을 밝혀라!\n\n내가 A에게 다음과 같이 물었다고 해보자.\n나:여러분 가운데 기사는 몇 분이나 되십니까 ? \n이에 A가 대답했으나 발음이 불분명하여 B가 추가적으로 대답했다.\nB:A는 우리중 기사는 한 명이라고 말했다.그 순간 C가 끼어들었다.\nC:B는 지금 거짓말을 하고있습니다.",
		"B와 C의 신분을 밝혀라.(신분은 건달 혹은 기사이다)",
	},
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다",
		"Q.물고기 주인의 국적은?\n\n색깔이 다른 집이 일렬로 5채 있다.그리고 각 집에는 서로 다른 국적을 가진 사람들이 살고 있다.\n다섯 사람은 어떤 음료를 마시고, 어느 꽃을 기르고, 어느 동물을 키우고 있다.\n어느 두 사람도 마시는 음료, 기르는 꽃, 키우는 동물은 일치하지 않는다.",
		"영국인은 빨간 집에 살고, 스웨덴인은 개를 키우며, 덴마크인은 차를 마신다.\n초록집은 하얀 집의 왼쪽 집이며, 초록집에 사는 사람은 커피를 마신다.\n장미를 기르는 사람은 새를 키우고, 노란집 사람은 라일락을 기른다.\n한 가운데 사는 사람은 우유를 마시고, 노르웨이인은 첫번째 집에 산다.\n안개꽃을 기르는 사람은 고양이를 키우는 사람의 옆집에 산다.",
		"프리지아를 기르는 사람은 맥주를 마신다.\n독일인은 사루비아를 기르며, 노르웨이인은 파란집 옆에 산다.\n안개꽃을 기르는 사람은 사람은 생수를 마시는 사람과 이웃이다.\n\n그렇다면 물고기를 키우는 사람은 어느 나라의 사람일까?",
	},
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다",
		"Q.살아남자 미스터 화이트!\n\n세 명의 총잡이가 서로 동시에 결투를 벌인다.\n1.미스터 블랙은 명중률 100 % 의 사격 실력을 가지고 있다.\n2.미스터 그레이는 명중률 70 % 의 사격 실력을 갖고 있다.\n",
		"3.미스터 화이트는 명중률 30 % 의 사격 실력을 가지고 있다.\n그리고 총잡이들은 서로의 실력차를 감안해서, 화이트->그레이->블랙 순서대로 발포하기로 하며, 한 번에 한 발만 쏠 수 있다.\n이 때 화이트는 어떻게 쏴야 가장 생존률이 높은가 ?",
	},
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다",
		"Q.범인은 바로 너!\n\n한 마을에 보석 강도 살인 사건이 발생했다.\n용의자는 조상호, 이수억, 최수호, 박홍수로 총 4명이다.\n피해자는 다잉메시지로 '수어어' 라는 글자를 남겼다.",
		"범인은 누구인가?",
	},
	{
		"'n'을 누르면 다음 페이지로 넘어갑니다",
		"Q.슈뢰딩거의 다이어리\n\n슈뢰딩거의 다이어리에는 요일마다 알 수 없는 숫자가 적혀 있다.\n물음표에 들어갈 숫자는 무엇인가 ?",
		"MON = 3\nTUE = 5\nWED = 4\nTHU = ?",
	},
};

// 문제 선택지 목록입니다.
const char const *answer[][5] =
{
	{
		"*기사/기사",
		"*기사/건달",
		"*건달/기사",
		"*건달/건달",
	},
	{
		"*독일",
		"*스웨덴",
		"*영국",
		"*덴마크",
		"*노르웨이",
	},
	{
		"1. 블랙",
		"2. 그레이",
		"3. 허공",
	},
	{
		"*조상호",
		"*이수억",
		"*최수호",
		"*박홍수",
	},
	{
		"*1. 2",
		"*2. 4",
		"*3. 6",
		"*4. 8",
	},
};

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

// number가 -1이면 플레이어 데이터에 저장된 모든 단서를, 0~4라면 저장되어있는 해당 번호의 단서를 출력합니다.
void PrintClues(const Player * const player, int number);

// 화면을 비우고, 세이브 목록을 나타내는 함수입니다.
void PrintSaveList(const Player save[]);

// 프롤로그를 출력하는 함수입니다.
void Prologue(void);

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

#endif
