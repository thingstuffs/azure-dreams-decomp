#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, s32, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_800C9CA0(void);
extern void func_800C9D08(void);
extern void func_800C9E68();
extern void func_800C9F0C();

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800C9F34;
extern Callback D_800E0354[];

void func_800C9AAC(void *arg0, void *arg1, void *arg2)
{
    register u32 entry_value ASM_REG("$2") = D_80083462;
    register void *state ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$21") = arg1;
    register void *part ASM_REG("$19") = arg2;
    register void *secondary ASM_REG("$18") = state;
    Callback callback;
    s16 direction;
    s16 direction_index;
    register s32 flags ASM_REG("$3");
    register s32 adjusted_flags ASM_REG("$2");
    s16 target;
    u16 old_height;

    if (entry_value & 0x2000) {
        Callback early_callback = FIELD(state, Callback, 0x8C);
        if (early_callback == (Callback)&D_800C9F34) {
            register void *incoming_a0 ASM_REG("$4");
            ASM_KEEP(incoming_a0);
            early_callback(incoming_a0, motion, part, incoming_a0);
            func_800C9F0C(incoming_a0);
            return;
        } else {
            FIELD(state, u8, 0x71) &= 0x7F;
        }
        func_800C9F0C();
        return;
    }

    {
        register void *call_a0 ASM_REG("$4") = state;
        register void *call_a1 ASM_REG("$5") = motion;
        register void *call_a2 ASM_REG("$6") = part;
        ASM_KEEP(call_a0);
        ASM_KEEP(call_a1);
        ASM_KEEP(call_a2);
        call_a0 = state;
        call_a1 = motion;
        call_a2 = part;
        if (func_800A9E70(call_a0, call_a1, call_a2, state) != 0) {
            return;
        }
    }

    callback = FIELD(state, Callback, 0x8C);
    if (callback != 0) {
        callback(state, motion, part, state);
    }
    D_800E0354[FIELD(state, u8, 0x9A)](state, motion, part, state);

    if (FIELD(state, s16, 0xB8) == 0) {
        FIELD(part, u8, 0xC) += 4;
        FIELD(part, u8, 0xD) += 4;
        FIELD(part, u8, 0xE) += 4;
        if (FIELD(part, u8, 0xC) >= 0x40) {
            FIELD(state, s16, 0xB8) = 1;
        }
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    FIELD(state, s32, 0x90) += FIELD(motion, s32, 0x14);

    flags = FIELD(part, u16, 0x14);
    adjusted_flags = flags & 0x8000;
    if (!adjusted_flags) {
        direction = ((D_80083228 + FIELD(secondary, s16, 0x2A) + 0x100) >> 9) & 7;
        direction_index = direction;
        if (FIELD(state, s16, 0x94) != direction_index) {
            func_8003DB94(part,
                ((s32 *)FIELD(state, void *, 0xA4))[direction_index],
                FIELD(part, s8, 4));
            FIELD(state, s16, 0x94) = direction;
        }

        if (D_8006CCF8[direction_index] != 0) {
            register u32 tail_value ASM_REG("$2");
            tail_value = FIELD(part, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_value);
            func_800C9CA0();
            return;
        }

        FIELD(part, u16, 0x14) &= 0xFFFE;
        func_800A020C(FIELD(secondary, s32, 0x1C), (u8 *)part + 0xC);

        if (!(FIELD(secondary, s32, 0x1C) & 0x20)) {
            if (!(FIELD(part, u16, 0x14) & 0x40)) {
                func_800478B8(part);
                func_800C9D08();
                return;
            }
        } else {
            FIELD(part, u16, 0x14) |= 0x7000;
            FIELD(secondary, s32, 0x1C) &= 0xFFFBFFFF;
        }

        if (FIELD(secondary, s32, 0x1C) & 0x40000) {
            if (!(FIELD(part, u16, 0x14) & 0x40)) {
                u16 phase = FIELD(state, u16, 0x9E);
                FIELD(state, u16, 0x9E) = phase + 1;
                FIELD(state, s32, 0xA0) += func_800644B8((s16)phase * 0xAA) << 5;
            }

            if (!(FIELD(state, u16, 0x98) & 8)) {
                s32 lower_bound = -0x20;
                s16 height;
                func_800BCB04(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                    (s16)(FIELD(secondary, u16, 0x88) - 0x20));
                height = FIELD(state, s16, 0x92);
                if (lower_bound < height) {
                    FIELD(state, u16, 0x92) -= 8;
                    func_800C9E68(height);
                    return;
                }
                if (height < -0x28) {
                    FIELD(state, u16, 0x92) += 8;
                    func_800C9E68();
                    return;
                }
            }
        } else {
            register s32 accumulated ASM_REG("$2") = FIELD(state, s32, 0xA0);
            register s32 position ASM_REG("$3") = FIELD(state, s32, 0x90);
            register u32 motion_flags ASM_REG("$4") = FIELD(state, u16, 0x98);
            FIELD(state, u16, 0x9E) = 0;
            FIELD(state, s32, 0xA0) = 0;
            position -= accumulated;
            FIELD(state, s32, 0x90) = position;

            if (!(motion_flags & 8)) {
                target = func_800BCB04(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                    (s16)(FIELD(secondary, u16, 0x88) - 0x20)) -
                    FIELD(secondary, u16, 0x88);
                old_height = FIELD(state, u16, 0x92);
                if (FIELD(state, s16, 0x92) < target) {
                    FIELD(state, u16, 0x92) = old_height + 8;
                    if (target < FIELD(state, s16, 0x92)) {
                        FIELD(state, s16, 0x92) = target;
                        func_800C9E68();
                        return;
                    }
                } else {
                    FIELD(state, s16, 0x92) = target;
                    func_800C9E68();
                    return;
                }
            }
        }
    } else {
        adjusted_flags = flags & 0x800;
        if (adjusted_flags) {
            adjusted_flags = flags & 0x8FFF;
        } else {
            adjusted_flags = flags | 0x7000;
        }
        FIELD(part, u16, 0x14) = adjusted_flags;
    }

    {
        register s32 object_flags ASM_REG("$3");
        object_flags = FIELD(secondary, s32, 0x1C);
        if (object_flags & 0x40000000) {
        adjusted_flags = object_flags & 0xBFFFFFFF;
        FIELD(secondary, s32, 0x1C) = adjusted_flags;
        target = func_800BCB04(
            (FIELD(part, u8, 0x24) << 6) | 0x20,
            (FIELD(part, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(secondary, u16, 0x88) - 0x20));
        if (target < 0x200) {
            FIELD(state, u16, 0x92) += FIELD(secondary, u16, 0x88) - target;
            FIELD(secondary, u16, 0x88) = target;
        }
    }
    }

    FIELD(motion, u16, 0xA) = FIELD(secondary, u16, 0x88) +
        FIELD(state, u16, 0x92) - FIELD(state, u16, 0xA2);
    FIELD(part, u16, 0x14) |= 0x40;
}

/* MECHANISM: A real D_80083462 halfword read emits the two-word pre-frame preamble;
   the 0x30 frame holds s1/s5/s3/s2/s4/s0 in retail order, with guarded base pins.
   Reusing the $v0 flags local preserves the retail mask/store destination pair. */
