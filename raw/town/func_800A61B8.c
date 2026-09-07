#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *D_8008274C;
extern s32 D_800C5100;

void func_800A3918(void *arg0, s32 arg1) {
    s16 state;
    s32 value;
    register u8 *base ASM_REG("$4");
    s16 tmp;
    u16 utmp;

    state = FIELD(arg0, s16, 2);
    if (state == 0) {
        goto state_zero;
    }
    base = (u8 *)0x80100000;
    if (state == 1) {
        goto state_one;
    }
    goto finish;

state_zero:
    if (FIELD(arg0, s16, 0xC) == 0) {
        value = (s16)(FIELD(arg0, u16, 8) + 0x1BC0);
        FIELD(arg0, u16, 6) += 2;
        value %= 0x1C00;
    } else {
        value = (s16)(FIELD(arg0, u16, 8) + 0x1B71);
        FIELD(arg0, u16, 6) += 1;
        value %= 0x1C00;
    }
    FIELD(arg0, s16, 8) = value;
    ASM_SCHED_BARRIER();
    FIELD(arg0, u16, 0)++;
    if (FIELD(D_8008274C, void *, 0x74) == &D_800C5100) {
        FIELD(arg0, s16, 2) = 1;
    }
    goto finish;

state_one:
    ASM_KEEP_NV(base);
    tmp = FIELD(base, s16, 0xD8A);
    utmp = FIELD(base, u16, 0xD8A);
    if (tmp < -0x1FFF) {
        FIELD(base, s16, 0xD8A) = -0x2000;
    } else {
        FIELD(arg0, u16, 0x12) -= 0x20;
        tmp = utmp + FIELD(arg0, u16, 0x12);
        FIELD(base, s16, 0xD8A) = tmp;
        if (tmp < -0x1FFF) {
            FIELD(base, s16, 0xD8A) = -0x2000;
        }
    }
    if (FIELD(arg0, s16, 0x14) < 0x200) {
        FIELD(arg0, s16, 0x14) = FIELD(arg0, u16, 0x14) + 0x20;
    }
    if (FIELD(arg0, s16, 0xC) == 0) {
        value = (s16)(FIELD(arg0, u16, 8) + 0x1C00 - FIELD(arg0, u16, 0x14));
        FIELD(arg0, u16, 6) += 2;
        value %= 0x1C00;
    } else {
        value = (s16)(FIELD(arg0, u16, 8) + 0x1C00 - FIELD(arg0, s16, 0x14) * 2);
        FIELD(arg0, u16, 6) += 1;
        value %= 0x1C00;
    }
    FIELD(arg0, s16, 8) = value;
    ASM_SCHED_BARRIER();
    FIELD(arg0, u16, 0)++;

finish:
    FIELD(arg0, s16, 0x16) = FIELD(arg0, s16, 8) / 0x200 + 0x10;
}
