#include "player.h"

clock_t StopWatch(int flag)
{
    static clock_t start = 0, end = 0;
    
    switch (flag)
    {
        case START:
            start = clock();
            return 0;
        case END:
            end = clock();
            return (end - start) / CLOCKS_PER_SEC;
        default:
            return 0;
    }
}