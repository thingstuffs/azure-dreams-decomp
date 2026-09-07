#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_80042984();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern void func_800A56E0();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80170F68;
extern EntityCallback D_80174018[];

void func_80170AA4(void *input0, void *input1, void *input2)
{
    register void *arg0 ASM_REG("$17") = input0;
    register void *arg1 ASM_REG("$20") = input1;
    register void *arg2 ASM_REG("$19") = input2;
    register void *entity ASM_REG("$18") = arg0;
    register s16 work ASM_REG("$16");
    register s32 direction_copy ASM_REG("$21");
    register void *call0 ASM_REG("$4");
    register void *call1 ASM_REG("$5");
    register void *call2 ASM_REG("$6");
    register void *call3 ASM_REG("$7");
    register s32 state_load ASM_REG("$2");
    register s32 floor_height ASM_REG("$5");
    EntityCallback callback;
    register s32 arithmetic ASM_REG("$2");
    s16 height;
    s16 base_height;
    s32 previous_direction;
    s32 flags;
    s32 compare_new;
    s32 wobble;
    s32 wobble_base;
    u16 part_flags;
    u16 new_part_flags;
    u8 table_value;

    if (D_80083462 & 0x2000) {
        callback = FIELD(arg0, EntityCallback, 0x8C);
        if (callback == (EntityCallback)&D_80170F68) {
            register void *self ASM_REG("$4");
            self = input0;
            ASM_KEEP(self);
            callback(self, input1, input2, self);
            goto done;
        }
        FIELD(arg0, u8, 0x71) &= 0x7F;
        goto done;
    }

    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    call0 = arg0;
    call1 = arg1;
    call2 = arg2;
    state_load = FIELD(arg0, u8, 0x6D);
    ASM_KEEP(state_load);
    call3 = arg0;
    work = (s8)state_load;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
        return;
    }

    {
        register EntityCallback callback2 ASM_REG("$2");
        callback2 = FIELD(arg0, EntityCallback, 0x8C);
        if (callback2 != 0) {
            callback2(arg0, arg1, arg2, arg0);
        }
    }
    D_80174018[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);

    state_load = (s32)work << 16;
    ASM_KEEP(state_load);
    compare_new = FIELD(arg0, s8, 0x6D);
    state_load >>= 16;
    if (state_load != compare_new) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    if (FIELD(arg0, u16, 0x98) & 0x8000) {
        wobble = FIELD(arg0, u16, 0xAC) + 1;
        FIELD(arg0, s16, 0xAC) = wobble;
        if (((s16)wobble >> 2) >= 2) {
            FIELD(arg0, s16, 0xAC) = -8;
            func_800A56E0(0x60B);
        }
        wobble = FIELD(arg0, u16, 0xAC);
        wobble_base = FIELD(arg0, u16, 0xA6);
        wobble = (s16)wobble >> 2;
        if (wobble < 0) {
            wobble = -wobble;
        }
        wobble_base += wobble;
        FIELD(arg2, s16, 0x12) = wobble_base;
    } else if ((FIELD(arg0, s32, 0x14) & 7) != FIELD(arg0, s16, 0xAA)) {
        func_80042984(arg0);
        FIELD(arg0, s16, 0xAA) = FIELD(arg0, u16, 0x14) & 7;
    }

    part_flags = FIELD(arg2, u16, 0x14);
    if (!(part_flags & 0x8000)) {
        arithmetic = D_80083228 + FIELD(entity, s16, 0x2A) + 0x100;
        ASM_KEEP(arithmetic);
        work = (arithmetic >> 9) & 7;
        previous_direction = FIELD(arg0, s16, 0x94);
        ASM_KEEP(previous_direction);
        direction_copy = (u16)work;
        if (previous_direction != work) {
            if (FIELD(arg2, u8 *, 0x2C) != 0) {
                func_80047738(arg2,
                              FIELD(arg2, u8 *, 0x2C)[work],
                              FIELD(arg2, s8, 4));
            }
            FIELD(arg0, s16, 0x94) = work;
        }

        table_value = D_8006CCF8[direction_copy];
        ASM_KEEP(direction_copy);
        if (table_value != 0) {
            FIELD(arg2, u16, 0x14) |= 1;
        } else {
            FIELD(arg2, u16, 0x14) &= 0xFFFE;
        }
        if (!(FIELD(entity, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, volatile u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                goto after_part_flags;
            }
        } else {
            FIELD(arg2, volatile u16, 0x14) |= 0x7000;
        }
after_part_flags:
        func_800A020C(FIELD(entity, s32, 0x1C), (u8 *)arg2 + 0xC);
        goto motion;
    }

    if (part_flags & 0x800) {
        new_part_flags = part_flags & 0x8FFF;
    } else {
        new_part_flags = part_flags | 0x7000;
    }
    FIELD(arg2, u16, 0x14) = new_part_flags;

motion:
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

    if (FIELD(arg0, u16, 0x98) & 8) {
        FIELD(arg0, s8, 0x9D) = 0;
        goto accumulate;
    }

    FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
    FIELD(arg0, s8, 0x9D) = (u8)FIELD(arg0, s8, 0x9D) + 1;
    ASM_KEEP(arg0);
accumulate:
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);

    if (!(FIELD(arg0, u16, 0x98) & 4)) {
        height = func_800BCB04(FIELD(arg1, u16, 2),
                               FIELD(arg1, u16, 6),
                               (s16)(FIELD(entity, u16, 0x88) - 0x20));
        if (height < 0x200) {
            base_height = (s16)FIELD(entity, u16, 0x88);
            if (FIELD(arg0, s16, 0x92) + base_height < height) {
                FIELD(entity, s32, 0x1C) &= 0xF7FFFFFF;
                goto flags_test;
            }
            if (height >= base_height) {
                FIELD(arg0, s32, 0x90) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(entity, s32, 0x1C) |= 0x08000000;
                FIELD(arg0, s8, 0x9D) = 0;
                goto flags_test;
            }

            FIELD(arg1, s32, 0x14) = 0;
            FIELD(entity, s32, 0x1C) |= 0x08000000;
            FIELD(arg0, s8, 0x9D) = 0;
            FIELD(arg0, s16, 0x92) = height - FIELD(entity, u16, 0x88);

flags_test:
            flags = FIELD(entity, s32, 0x1C);
            if (flags & 0x40000000) {
                FIELD(entity, s32, 0x1C) = flags & 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (FIELD(arg2, u8, 0x24) << 6) | 0x20,
                    (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                    (s16)(FIELD(entity, u16, 0x88) - 0x20));
                ASM_KEEP(floor_height);
                FIELD(arg0, s16, 0x92) +=
                    FIELD(entity, u16, 0x88) - floor_height;
                FIELD(entity, u16, 0x88) = floor_height;
                goto finish;
            }
            goto finish;
        }
    }

    FIELD(entity, s32, 0x1C) &= 0xF7FFFFFF;

finish:
    FIELD(arg1, s16, 0xA) =
        FIELD(entity, u16, 0x88) + FIELD(arg0, u16, 0x92);
    FIELD(arg2, u16, 0x14) |= 0x40;

done:
    return;
}
