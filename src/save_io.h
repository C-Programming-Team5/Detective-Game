#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct player //player.h로 이동할 수도 있습니다.
{
    int id; // 쯔꾸르에서 흔히 쓰이는 여러개의 세이브를 위한 식별 코드입니다. 0에서 4 사이의 숫자가 들어갑니다.
    unsigned cleared; // 2진수 마스킹 형식으로 저장됩니다.
    unsigned playTime;
} Player;
