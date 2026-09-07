#include "common.h"

extern void func_80047784();

extern u8 D_80083160[];
extern s32 D_80083460;
extern u8 D_80170E94[];
extern u8 D_80175F10[];
extern u8 D_80175F28[];

#define FIELD(type, base, offset) (*(type *)((u8 *)(base) + (offset)))

void func_801748DC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 *data = D_80083160;
    u16 *counter;
    u8 state = FIELD(u8, arg0, 0x9B);

    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (FIELD(u16, arg2, 0x14) & 0xE000) {
        FIELD(void *, arg2, 0x2C) = D_80175F28;
        func_80047784(arg2,
            D_80175F28[((FIELD(s16, data, 0xC8) +
                FIELD(s16, arg3, 0x2A) + 0x100) >> 9) & 7], 0);
        FIELD(u8, arg0, 0x9B)++;
    }
    goto done;

state_one:
    {
        s32 flags = FIELD(s32, data, 8);

        if (!(flags & 0x100) && (flags & 0xFFFF)) {
            FIELD(void *, arg2, 0x2C) = D_80175F10;
            func_80047784(arg2,
                D_80175F10[((FIELD(s16, data, 0xC8) +
                    FIELD(s16, arg3, 0x2A) + 0x100) >> 9) & 7], 0);
            FIELD(void *, arg0, 0x8C) = D_80170E94;
            FIELD(s16, arg0, 0xA6) = 0;
            counter = (u16 *)&D_80083460;
            counter[5]--;
        }
    }

done:
    return;
}

/* MECHANISM: The true-space labeled CFG makes both apparent func_801749EC jumps local epilogue edges.
   The 0x18 frame holds only s0/ra; symbolic counter[5] indexing keeps D_80083460 as a base,
   restoring its separate lui/addiu pair and the retail +0xA halfword accesses. */
