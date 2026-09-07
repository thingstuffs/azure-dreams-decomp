#include "common.h"

extern s16 D_80025FF4;
extern s32 D_800814A0;

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_81971398(void *arg0)
{
    register void *base ASM_REG("$6");
    register s32 i ASM_REG("$7");
    register u8 *p ASM_REG("$5");
    register u8 *page ASM_REG("$2");
    u16 count;

    base = arg0;
    do { i = 0; } while (0);
    p = base;
    ASM_SCHED_BARRIER();
#ifdef NON_MATCHING
    page = (u8 *)&D_80025FF4 - 0x5FF4;
#else
    page = (u8 *)0x80020000;
#endif
    ASM_KEEP(page);
    count = FIELD(base, u16, 0x38);
    FIELD(page, s16, 0x5FF4) = 1;
    count--;
    FIELD(base, u16, 0x38) = count;
    do {
        FIELD(p, u8, 0x0C) =
            FIELD(p, u8, 0x1C) * FIELD(base, s16, 0x38) /
            FIELD(base, s16, 0x3A);
        FIELD(p, u8, 0x0D) =
            FIELD(p, u8, 0x1D) * FIELD(base, s16, 0x38) /
            FIELD(base, s16, 0x3A);
        i++;
        FIELD(p, u8, 0x0E) =
            FIELD(p, u8, 0x1E) * FIELD(base, s16, 0x38) /
            FIELD(base, s16, 0x3A);
        p += 4;
    } while (i < 4);
    if (FIELD(base, s16, 0x38) <= 0) {
        FIELD(base, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
