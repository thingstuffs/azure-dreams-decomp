#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s16 func_800A0818();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A9A04();
extern void func_800AD594();
extern s32 func_800AD9B4();

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80170E54;

void func_80172374(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp18;
    s32 state;
    s32 duration;
    s16 next_duration;
    s32 flags;
    u8 *global;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto decrement;
    }
    if (state == 2) {
        goto state2;
    }
    goto decrement;

state0:
    if (FIELD(arg0, s16, 0x96) != 8) {
        goto decrement;
    }
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg1, s32, 0x14) = 0xFFEE0000;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s32, 0xA4) = 0;
    FIELD(arg0, u8, 0x9B)++;

state1:
    duration = FIELD(arg0, s16, 0x96);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA4);
    if (duration != 0) {
        register s32 coord ASM_REG("$2");
        register s32 origin ASM_REG("$3");

        coord = FIELD(arg2, u8, 0x24) << 6;
        origin = FIELD(arg1, s16, 2) - 0x20;
        ASM_KEEP(coord);
        ASM_KEEP(origin);
        coord = ((coord - origin) << 16) / duration;
        origin = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0xC) = coord;
        coord = FIELD(arg2, u8, 0x25) << 6;
        ASM_KEEP(coord);
        ASM_KEEP(origin);
        FIELD(arg1, s32, 0x10) = ((coord - origin) << 16) / FIELD(arg0, s16, 0x96);
        FIELD(arg0, s32, 0xA4) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x40000;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA4);
    if (FIELD(arg0, s16, 0x96) < 3) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, s32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

state2:
    if (FIELD(arg3, s32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg0, u8, 0x9B)++;
    }

decrement:
    next_duration = (u16)FIELD(arg0, s16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = next_duration;
    if ((next_duration << 16) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 5);
        func_800A4ACC(arg3);

        global = (u8 *)&D_80083460;
        if (FIELD(global, s16, 8) != 0) {
            FIELD(global, s16, 8) = (u16)FIELD(global, s16, 8) - 1;
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
            goto call_update;
        }
        if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                u8 *map = D_80082E80;

                FIELD(arg3, s16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    FIELD(map, u8, 0x24), FIELD(map, u8, 0x25), &sp18);
            }
        }

call_update:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, u8 *, 0x8C) = &D_80170E54;
            func_800A9A04(arg3);
        }
    }
}
