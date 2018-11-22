#pragma once

// 글자색을 설정하는 함수입니다.
void SetColor(int color);
// 0을 인자로 주면 커서를 숨기고, 1을 인자로 주면 커서를 보이게 하는 함수입니다.
void CursorView(char show);
// 커서를 콘솔의 특정 위치로 이동시키는 함수입니다.
void gotoxy(int x, int y);
// 처음 화면을 띄우는 함수입니다.
void mainPtr(void);