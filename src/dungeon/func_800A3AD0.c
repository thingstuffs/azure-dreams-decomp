#include "common.h"

extern s32 func_80033BC0(s32);
extern s32 func_800A697C(s32, s32);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);

extern s32 D_80012090[];
extern s16 D_8008146C;
extern s8 D_800DCF5A;
extern u8 D_800E3548[];
extern s16 D_800E3CCC;

s32 func_800A9230(void *arg0)
{
    s32 result;
    s32 state;
    s32 index;
    u8 *base;
    u8 *entry;
    u8 kind;

    result = 0;
    if (*(u8 *)((u8 *)arg0 + 0x13) == 0x20) {
        if (D_800E3CCC == 0) {
            D_800E3CCC = 1;
            state = *(s32 *)0x80012090;
            if (state == 0) {
                if (D_8008146C == 0x19) {
                    if (func_80033BC0(0x11F9) != 0) {
                        if (func_80033BC0(0x11FC) == 0) {
                            if ((s16)func_800A697C(0xD, 2) == 0) {
                                *(u8 *)&result = 2;
                                *((u8 *)&result + 1) = 0xD;
                                *(s16 *)((u8 *)*(void **)((u8 *)arg0 - 0x14) + 0x12) = 0xC;
                            }
                        }
                    }
                }
            }
        }
    }

    if (*(u8 *)&D_800DCF5A == 0) {
        goto done;
    }
    if (*(u8 *)((u8 *)arg0 + 0x49) != 0) {
        goto done;
    }
    if ((func_800A6D30() & 3) != 0) {
        goto done;
    }

    index = func_800A6DA4(1, 0x1F) & 0xFFFF;
    base = D_800E3548;
    entry = &base[index * 4];
    kind = entry[1];
    if (kind == 0) {
        goto done;
    }
    if (kind >= 0xB) {
        goto done;
    }
    if (kind != 1) {
        goto done;
    }
    if (entry[0] != 8) {
        goto done;
    }
    result = *(s32 *)entry;
    *(s32 *)entry = 0;

done:
    return result;
}

/* MECHANISM: A four-byte stack result and arg0-only s0 lifetime produce the 0x20 frame.
   The literal D_80012090 read coalesces its address/load in v1; an unsigned lvalue gives lbu.
   Splitting table index, base, and entry moves sll after the held lui/addiu and closes reorder. */
