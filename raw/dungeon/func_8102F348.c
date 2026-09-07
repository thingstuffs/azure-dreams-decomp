#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800A45D8(u16, u16, s16);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_800478B8(void *);
void func_8102F348(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x50);
    FIELD(arg0, s32, 0x50) += FIELD(arg0, s32, 0x5C);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x50);
        FIELD(arg0, s32, 0x50) = 0;
        FIELD(arg0, s32, 0x5C) = 0;
    }

    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x54);
    FIELD(arg0, s32, 0x54) += FIELD(arg0, s32, 0x60);
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0xA)) << 16) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x54);
        FIELD(arg0, s32, 0x54) = 0;
        FIELD(arg0, s32, 0x60) = 0;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x58);
    FIELD(arg0, s32, 0x58) += FIELD(arg0, s32, 0x64);
    temp_s0 = FIELD(arg1, s16, 0xA);
    if ((func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       (s16)((u16)FIELD(arg1, volatile s16, 0xA) - 4)) - 0x10) < temp_s0) {
        FIELD(arg0, s32, 0x58) = 0;
        FIELD(arg1, s16, 0xA) = func_800BCB04(
            FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
            (s16)((u16)FIELD(arg1, s16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        if (FIELD(arg0, s16, 0x14) == 0) {
            FIELD(arg0, s16, 0x14) = 1;
            FIELD(arg0, s16, 0x1E) = 0;
        }
    }

    FIELD(arg0, u16, 0x20)++;
    if ((FIELD(arg0, u16, 0x20) & 3) == 0) {
        func_800478B8(arg2);
    }

    FIELD(arg2, u16, 0x1C) += 100;
    if (FIELD(arg2, u16, 0x1C) > 0x1000) {
        FIELD(arg2, u16, 0x1C) = 0x1000;
    }

    FIELD(arg2, u16, 0x1E) += 100;
    if (FIELD(arg2, u16, 0x1E) > 0x1000) {
        FIELD(arg2, u16, 0x1E) = 0x1000;
    }

    FIELD(arg0, u16, 0x1E) = FIELD(arg0, u16, 0x1E) - 1;
    if ((s16)FIELD(arg0, u16, 0x1E) <= 0) {
        register s32 *status_page ASM_REG("$3") = (s32 *)0x80080000;
        ASM_KEEP(status_page);
        FIELD(arg0, u16, -2) |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        register s32 *status_page ASM_REG("$3") = (s32 *)0x80080000;
        ASM_KEEP(status_page);
        FIELD(arg0, u16, -2) |= 0x8000;
        status_page[0x14A0 / 4] |= 0x8000;
    }
}
