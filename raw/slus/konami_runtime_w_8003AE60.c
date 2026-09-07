#include "common.h"

#include "common.h"

extern void ClearImage(void *rect, u8 r, u8 g, u8 b);

void func_8003AE60(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b)
{
    s16 rect[4];

    rect[0] = x;
    rect[1] = y;
    rect[2] = w;
    rect[3] = h;
    ClearImage(rect, r, g, b);
}
