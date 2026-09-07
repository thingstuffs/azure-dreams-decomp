#include "common.h"

/* Clears two 64x16 rectangles (VRAM font pages at x=0x380/0x3C0, y=arg0*16)
 * and draws two text strings (from arg1's offset 8 / 0xC) at the same spots. */
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

void func_80052C10(s16 arg0, S_80052C10_Arg1 *arg1) {
    S_80052C10_RECT rect1;
    S_80052C10_RECT rect2;

    rect1.x = 0x380;
    rect1.y = arg0 * 0x10;
    rect1.w = 0x40;
    rect1.h = 0x10;
    ClearImage(&rect1, 0, 0, 0);

    rect2.x = 0x3C0;
    rect2.y = arg0 * 0x10;
    rect2.w = 0x40;
    rect2.h = 0x10;
    ClearImage(&rect2, 0, 0, 0);

    func_80052A90(arg1->text8, 0x380, arg0 * 0x10);
    func_80052A90(arg1->textC, 0x3C0, arg0 * 0x10);
}
