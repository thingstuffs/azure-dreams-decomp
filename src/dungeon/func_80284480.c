#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
    u16 field_4;
} DungeonCell;

extern s16 D_8008333C[12];
extern DungeonCell D_800EA000[];

void func_80017480(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4)
{
    s32 y;
    register s32 height ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 y_test ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 y_end;
    s32 x;
    s32 x_end;
    register s32 width ASM_REG("$12");   /* MATCH pin: retail register colouring depends on it */
    s16 *config;
    DungeonCell *cells;

    y = (s16)arg1;
    config = D_8008333C;
    cells = D_800EA000;
    height = (s16)arg3;
    y_test = y + height;
    if (y < y_test) {
        arg0 = (s32)((u32)arg0 << 16);
        arg2 = (s32)((u32)arg2 << 16);
        width = arg2 >> 16;
        y_end = y_test;
        do {
            x = arg0 >> 16;
            ASM_KEEP_NV(arg2);   /* MATCH pin: retail delay-slot fill depends on it */
            if (x < x + width) {
                x_end = x + (arg2 >> 16);
                do {
                    cells[x + (y << config[10])].field_4 &= arg4;
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}

/* MECHANISM: Shifted arg2 feeds t4 width, then crosses a pre-guard value boundary.
   Pinned a3/v1/t2 y roles and a join barrier preserve the bound copy and word-12 nop. */
