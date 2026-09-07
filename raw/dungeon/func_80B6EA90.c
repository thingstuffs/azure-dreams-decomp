#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern s32 D_80170E5C;

void func_80172290(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 stack_value;
    s32 count;
    s32 flags;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto movement;
    }
    if (state >= 2) {
        goto high_state;
    }
    if (state == 0) {
        goto initialize;
    }
    goto countdown;

high_state:
    if (state == 2) {
        goto check_flag;
    }
    goto countdown;

initialize:
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg1, s32, 0x14) = 0xFFEE0000;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, u8, 0x9B)++;

movement:
    count = FIELD(arg0, s16, 0x96);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    if (count != 0) {
        {
            s32 coord = FIELD(arg2, u8, 0x24) << 6;
            s32 current = FIELD(arg1, s16, 2) - 0x20;

            FIELD(arg1, s32, 0x0C) = ((coord - current) << 16) / count;
        }
        {
            s32 coord = FIELD(arg2, u8, 0x25) << 6;
            s32 current = FIELD(arg1, s16, 6) - 0x20;

            FIELD(arg1, s32, 0x10) =
                ((coord - current) << 16) / FIELD(arg0, s16, 0x96);
        }
        FIELD(arg0, s32, 0xA0) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x40000;
    }

    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    if (FIELD(arg0, s16, 0x96) < 2) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, s32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

check_flag:
    if (FIELD(arg3, s32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg0, u8, 0x9B)++;
    }

countdown:
    if ((s16)--FIELD(arg0, u16, 0x96) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        {
            u8 *global_state = (u8 *)&D_80083460;

            if (FIELD(global_state, s16, 8) != 0) {
                FIELD(global_state, u16, 8)--;
            }
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (!(flags & 0x2000)) {
            goto low_flags;
        }
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
        goto call_entity;

low_flags:
        if (flags & 0x410) {
            goto call_entity;
        }
        if (flags & 0x20000) {
            u8 *map_state = D_80082E80;

            FIELD(arg3, s16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(map_state, u8, 0x24), FIELD(map_state, u8, 0x25), &stack_value);
        }

call_entity:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, s32 *, 0x8C) = &D_80170E5C;
            func_800A9A04(arg3);
        }
    }

done:
    return;
}
