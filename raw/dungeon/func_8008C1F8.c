#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_80082EB0;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];

void *func_800BA074(s32);

void func_80091958(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
    void *temp;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        temp = func_800BA074(D_80082EB0);
        FIELD(arg0, void *, 0xC8) = temp;
        if (temp == 0) {
            break;
        }
        FIELD(arg0, u8, 0x9B)++;
    case 1:
        if (FIELD(FIELD(arg0, void *, 0xC8), u16, 0x1E) & 0x8000) {
            FIELD(arg0, void *, 0xC8) = 0;
            FIELD(arg0, u8, 0x9B)++;
        }
        break;
    case 2:
        FIELD(&D_80082EB0, s32, 8) = 0;
        if (FIELD(arg3, s32, 0x1C) & 0x100000) {
            FIELD(arg0, void *, 0x8C) = D_8008EAC8;
        } else {
            FIELD(arg0, void *, 0x8C) = &D_8008ACDC;
        }
        break;
    }
}

/* MECHANISM: True-space function naming turns 0x80091A20/24 into local CFG joins.
   A natural 0/1/2 switch preserves the median dispatch and case fallthrough;
   the four-argument ABI keeps the live context in a3 and arg0 held in s0. */
