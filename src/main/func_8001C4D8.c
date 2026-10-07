#include "common.h"

typedef struct MenuPolyPos {
    u8 pad_00[0x8];
    s16 y;
} MenuPolyPos;

typedef struct MenuPolyColor {
    u8 r;
    u8 g;
    u8 b;
    u8 pad_03[0x5];
    s16 y;
} MenuPolyColor;

typedef struct MenuMarkerPos {
    u8 pad_00[0xA];
    s16 y;
} MenuMarkerPos;

typedef struct MenuSprite {
    u8 pad_00[0x4];
    void *prim;
} MenuSprite;

typedef struct Menu {
    u8 pad_00[0x7C];
    u8 offsets[4];
    s32 frames;          /* 0x80 */
    s32 frame;           /* 0x84 */
    s32 target_row;      /* 0x88 */
    s32 start_row;       /* 0x8C */
    u8 pad_90[0x12C];
    MenuSprite *marker;  /* 0x1BC */
    MenuSprite *rows_a[4];  /* 0x1C0 */
    MenuSprite *rows_b[4];  /* 0x1D0 */
    MenuSprite *rows_c[4];  /* 0x1E0 */
    MenuSprite *rows_d[4];  /* 0x1F0 */
} Menu;

/* Animate the menu selection marker and each row's horizontal offset and color. */
void func_804034D8(Menu *menu)
{
    s32 i;
    s32 step;
    s32 start;
    s32 delta;
    s32 num;
    u8 *slot;
    u8 offset;
    u8 next;
    u8 row_offset;

    start = menu->start_row;
    delta = menu->target_row - start;
    num = delta * (menu->frame << 4);
    step = num / menu->frames;
    step += 10;
    ((MenuMarkerPos *)menu->marker->prim)->y = start * 16 + step;

    for (i = 0; i < 4; i++) {
        slot = (u8 *)menu + i + 0x7C;
        offset = *slot;
        if (i == menu->target_row) {
            step = (8 - offset) / (menu->frames - menu->frame + 1);
            next = offset + step;
        } else {
            next = offset;
            if (next != 0)
                next--;
        }
        *slot = next;
        row_offset = menu->offsets[i];
        ((MenuPolyColor *)menu->rows_c[i]->prim)->y = row_offset + 0x24;
        ((MenuPolyPos *)menu->rows_d[i]->prim)->y = row_offset + 0x8F;
        ((MenuPolyPos *)menu->rows_a[i]->prim)->y = row_offset + 9;
        ((MenuPolyPos *)menu->rows_b[i]->prim)->y = row_offset + 0x42;
        ((MenuPolyColor *)menu->rows_c[i]->prim)->r = menu->offsets[i] * 3 + 0x68;
        ((MenuPolyColor *)menu->rows_c[i]->prim)->g = menu->offsets[i] * 3 + 0x68;
        ((MenuPolyColor *)menu->rows_c[i]->prim)->b = menu->offsets[i] * 4 + 0x60;
    }

    if (menu->frame < menu->frames)
        menu->frame++;
}
