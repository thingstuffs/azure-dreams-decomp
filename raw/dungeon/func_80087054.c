#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern M2C_UNK func_80048A44();
extern M2C_UNK func_8009F644();
extern s32 func_800A5C70(void);
extern u16 D_80013714;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_800DCFB0;
extern M2C_UNK D_800DD0B8;

void func_8008C7B4(void *arg0, s32 arg1, void *arg2, void *arg3) {
#ifndef NON_MATCHING
    register u8 *flags ASM_REG("$3");
    register s32 initial_state ASM_REG("$2");
#else
    M2C_UNK *flags = &D_80083160;
#endif

#ifndef NON_MATCHING
    initial_state = 0x1C;
    ASM_KEEP_NV(initial_state);
    FIELD(arg0, s8, 0x9A) = initial_state;
    flags = (u8 *)0x80080000;
#else
    FIELD(arg0, s8, 0x9A) = 0x1C;
#endif
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    ASM_SCHED_BARRIER();
#ifndef NON_MATCHING
    ASM_KEEP_NV(flags);
#endif
    if (D_80013714 & 2) {
        goto set_control;
    }
#ifndef NON_MATCHING
    flags += 0x3160;
    ASM_KEEP_NV(flags);
#endif
    if (!(FIELD(flags, s32, 8) & 0x20) || (func_800A5C70() == 0)) {
        goto after_control;
    }
set_control:
    {
        M2C_UNK *control = &D_80083460;

        FIELD(control, u16, 2) = (u16)(FIELD(control, u16, 2) | 0x80);
    }
after_control:
    func_8009F644(arg3, 0x10, 0, 0);
    {
#ifndef NON_MATCHING
        register u8 *lookup ASM_REG("$5");
#else
        u8 *lookup;
#endif

        if (FIELD(arg3, s32, 0x1C) & 0x100000) {
#ifndef NON_MATCHING
            register u8 *tail_page ASM_REG("$2");

            tail_page = (u8 *)0x800E0000;
            ASM_KEEP(tail_page);
            lookup = tail_page - 0x2F48;
#else
            lookup = (u8 *)&D_800DD0B8;
#endif
        } else {
#ifndef NON_MATCHING
            register u8 *tail_page ASM_REG("$2");

            ASM_SET(tail_page);
            tail_page = (u8 *)0x800E0000;
            ASM_KEEP(tail_page);
            lookup = tail_page - 0x3050;
#else
            lookup = &D_800DCFB0;
#endif
        }
        FIELD(arg2, u8 *, 0x2C) = lookup;
#ifndef NON_MATCHING
        {
            register u8 *element ASM_REG("$2");

            element = lookup + (((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7);
            ASM_KEEP_NV(element);
            func_80048A44(arg2, *element, 0, 1);
        }
#else
        func_80048A44(arg2, lookup[((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0, 1);
#endif
    }
}
