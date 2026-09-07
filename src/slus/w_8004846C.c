#include "common.h"

typedef struct {
    s16 x, y, w, h;
} S_8004846C_RECT;

extern void StoreImage(S_8004846C_RECT *rect, void *p);
extern void DrawSync(s32 a0);
extern s32 func_80047200(s32 a0, s32 a1, s32 a2);
extern s32 func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3);

/* Captures a 16x1 tile of VRAM at the location derived from a0 (tile index)
 * into a scratch buffer via StoreImage, then re-uploads it twice via
 * func_80047200 / func_8003F80C to shift/redraw it 0x80 to the left. */
void func_8004846C(s32 a0)
{
    S_8004846C_RECT rect;
    s32 buf[8];

    rect.x = (a0 & 0x3F) << 4;
    rect.y = a0 >> 6;
    rect.w = 0x10;
    rect.h = 1;
    StoreImage(&rect, buf);
    DrawSync(0);
    func_80047200((s32)buf, 1, 0);
    func_8003F80C((s32)buf, a0 - 0x80, 1, 2);
    DrawSync(0);
}
