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

/* Reads two adjacent VRAM blocks and decodes their data into a buffer at 0x80016000. */
void func_8004B568(void)
{
    RECT_8004B568 rect;
    void *decode_dst;
    s16 rect_x;
    s16 rect_w;
    s16 rect_h;
    s16 rect_y;
    s32 block_index;

    decode_dst = (void *)0x80016000;
    DrawSync(0);

    block_index = 0;
    rect_x = 0x140;
    rect_w = 0x40;
    rect_h = 0x80;
    D_80081480.field_0 = D_8008148C.field_0;
    rect_y = 0x100;

    for (; block_index < 2; block_index++) {
        rect.y = rect_y;
        rect.x = rect_x;
        rect.w = rect_w;
        rect.h = rect_h;
        StoreImage(&rect, (void *)D_8008148C.field_0);
        rect_y += 0x80;
        DrawSync(0);
        decode_dst = func_8004068C((void *)D_80081480.field_0, decode_dst);
    }
}
