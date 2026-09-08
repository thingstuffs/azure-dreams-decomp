#include "common.h"

/* PSY-Q GPU primitive rect */
typedef struct S_80052C10_RECT {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_80052C10_RECT;

/* Struct passed as arg1: only offsets 0x8 and 0xC (two text pointers) are
 * touched by this function; the rest is unknown padding. */
typedef struct S_80052C10_Arg1 {
    u8 pad0[8];
    u8 *text8;
    u8 *textC;
} S_80052C10_Arg1;

extern s32 ClearImage(S_80052C10_RECT *rect, u8 r, u8 g, u8 b); /* extern PSY-Q libgpu */
extern void func_80052A90(u8 *str, s16 x, s16 y); /* extern */

/* Clears two 64x16 VRAM text regions and draws the two strings at the given row. */
void func_80052C10(s16 row, S_80052C10_Arg1 *texts) {
    S_80052C10_RECT left_rect;
    S_80052C10_RECT right_rect;

    left_rect.x = 0x380;
    left_rect.y = row * 0x10;
    left_rect.w = 0x40;
    left_rect.h = 0x10;
    ClearImage(&left_rect, 0, 0, 0);

    right_rect.x = 0x3C0;
    right_rect.y = row * 0x10;
    right_rect.w = 0x40;
    right_rect.h = 0x10;
    ClearImage(&right_rect, 0, 0, 0);

    func_80052A90(texts->text8, 0x380, row * 0x10);
    func_80052A90(texts->textC, 0x3C0, row * 0x10);
}
