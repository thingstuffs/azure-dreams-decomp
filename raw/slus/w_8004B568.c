#include "common.h"

/* PSX libgpu RECT: x,y,w,h as s16 fields. */
typedef struct {
    s16 x, y, w, h;
} RECT_8004B568;

/* S_80081480 / S_8008148C: only field_0 (a pointer-valued word) is touched
 * here; forced oversized (>8B) so gcc/as emit %hi/%lo addressing to match
 * the target asm, following the convention already established for these
 * same globals in src/w_80043CD0.c / src/w_80041AB0.c / src/w_8004425C.c. */
typedef struct {
    s32 field_0;
    s8 pad[8];
} S_80081480_8004B568;

typedef struct {
    s32 field_0;
    s8 pad[8];
} S_8008148C_8004B568;

extern S_80081480_8004B568 D_80081480;
extern S_8008148C_8004B568 D_8008148C;

extern void DrawSync(s32 a0);
extern s32 StoreImage(RECT_8004B568 *rect, void *p);
/* RLE-style byte decoder; returns the advanced dst pointer ($a1 at exit). */
extern void *func_8004068C(void *a0, void *a1);

/* Copies D_8008148C's leading word into D_80081480, then twice: builds a
 * 0x140x0x80x0x40x0x80 (RECT) rectangle stepping down VRAM by 0x80 lines,
 * stores it into the framebuffer at D_8008148C's pointer via StoreImage,
 * syncs the GPU, and decodes the object's data (func_8004068C) from
 * D_80081480's pointer into a growing destination buffer (starting at
 * 0x80016000). */
void func_8004B568(void)
{
    RECT_8004B568 rect;
    void *dst;
    s16 rectX;
    s16 rectW;
    s16 rectH;
    s16 y;
    s32 i;

    dst = (void *)0x80016000;
    DrawSync(0);

    i = 0;
    rectX = 0x140;
    rectW = 0x40;
    rectH = 0x80;
    D_80081480.field_0 = D_8008148C.field_0;
    y = 0x100;

    for (; i < 2; i++) {
        rect.y = y;
        rect.x = rectX;
        rect.w = rectW;
        rect.h = rectH;
        StoreImage(&rect, (void *)D_8008148C.field_0);
        y += 0x80;
        DrawSync(0);
        dst = func_8004068C((void *)D_80081480.field_0, dst);
    }
}
