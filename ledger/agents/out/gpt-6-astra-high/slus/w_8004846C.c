#include "common.h"

typedef struct {
    s16 x, y, w, h;
} S_8004846C_RECT;

extern void StoreImage(S_8004846C_RECT *rect, void *p);
extern void DrawSync(s32 a0);
extern s32 func_80047200(s32 a0, s32 a1, s32 a2);
extern s32 func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3);

/* Reads a 16x1 VRAM tile and redraws it at tile index minus 0x80. */
void func_8004846C(s32 tile_index)
{
    S_8004846C_RECT rect;
    s32 pixels[8];

    rect.x = (tile_index & 0x3F) << 4;
    rect.y = tile_index >> 6;
    rect.w = 0x10;
    rect.h = 1;
    StoreImage(&rect, pixels);
    DrawSync(0);
    func_80047200((s32)pixels, 1, 0);
    func_8003F80C((s32)pixels, tile_index - 0x80, 1, 2);
    DrawSync(0);
}
