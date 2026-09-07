#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(p, t, n) (*(t)((u8 *)(p) + (n)))

extern M2C_UNK func_80047784();
extern M2C_UNK func_8009A350();
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80175EA8[9];

void func_809A0B58(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10;
    u16 temp_v0;
    u8 *temp_a1;
    u8 *temp_v1_base;

    func_8009A350(FIELD(arg2, u8 *, 0x24) - 1, FIELD(arg2, u8 *, 0x25),
                  ((u16)FIELD(arg3, u16 *, 0x2A) >> 9) & 7, &sp10);
    if (!(sp10 & 0x8400)) {
        temp_v0 = FIELD(arg0, u16 *, 0xB2) + 1;
        FIELD(arg0, u16 *, 0xB2) = temp_v0;
        if ((u32)(temp_v0 & 0xFFFF) >= 0x3D) {
            temp_v1_base = (u8 *)&D_80083460;
            FIELD(arg0, u16 *, 0xB2) = 0x3C;
            FIELD(temp_v1_base, u16 *, 0xA) =
                (u16)(FIELD(temp_v1_base, u16 *, 0xA) + 1);
            FIELD(arg0, s8 *, 0x9A) = 0x19;
            FIELD(arg0, s32 *, 0x8C) = 0;
            FIELD(arg0, s8 *, 0x9B) = 0;
            temp_a1 = D_80175EA8;
            FIELD(arg2, u8 **, 0x2C) = temp_a1;
            func_80047784(arg2,
                           temp_a1[((s32)(D_80083228 + FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
                           0);
            FIELD(arg0, u16 *, 0xB0) = (u16)FIELD(arg3, u16 *, 0x2A);
            FIELD(arg3, s32 *, 0x1C) = (s32)(FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
            temp_v0 = FIELD(arg0, u16 *, 0x92) - FIELD(arg0, u16 *, 0xA2);
            FIELD(arg0, u16 *, 0xA2) = 0;
            FIELD(arg0, s16 *, 0x9E) = 0;
            FIELD(arg0, u16 *, 0x92) = temp_v0;
        }
    }
}

/* MECHANISM: A named D_80083460 byte base forces retail's lui/addiu and +0xA accesses,
   restoring the missing word and downstream branch displacements. One subtraction
   expression snapshots both u16 operands before the two intervening zero stores. */
