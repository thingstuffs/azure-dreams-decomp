#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[];
extern s16 D_80083228[8];
extern u16 D_80083462[8];
extern u8 D_800E23E0[];
extern u8 D_80171A80[];
extern Callback D_80176374[];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(u32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80171344(void) __attribute__((noreturn));
extern void func_801713EC(void) __attribute__((noreturn));
extern void func_80171458(void) __attribute__((noreturn));
extern void func_801716F0(void) __attribute__((noreturn));
extern void func_80171704(void) __attribute__((noreturn));
extern void func_801717A8(void) __attribute__((noreturn));

void func_801711B0(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$21") = arg1;
    register void *part ASM_REG("$20") = arg2;
    register void *base ASM_REG("$18") = obj;
    register s32 work ASM_REG("$16");
    s32 direction;
    register s32 state_load ASM_REG("$2");
    register void *call0 ASM_REG("$4");
    register void *call1 ASM_REG("$5");
    register void *call2 ASM_REG("$6");
    register void *call3 ASM_REG("$7");
    register u16 part_flags ASM_REG("$3");
    Callback callback_high;
    Callback callback;
    s32 compare_new;
    s16 floor;
    s32 flags;
    s32 normal_flags;
    s32 special_flags;
    u16 new_part_flags;
    register u16 counter ASM_REG("$3");
    s32 effect_arg;

    if (D_80083462[0] & 0x2000) {
        callback_high = FIELD(obj, Callback, 0x8C);
        if (callback_high == (Callback)D_80171A80) {
            register void *entry0 ASM_REG("$4") = arg0;

            ASM_UNDEF(entry0);
            callback_high(entry0, arg1, arg2, entry0);
            func_801717A8();
        }
        FIELD(obj, u8, 0x71) &= 0x7F;
        func_801717A8();
    }

    ASM_KEEP(obj);
    ASM_KEEP(motion);
    ASM_KEEP(part);
    ASM_KEEP(base);

    call0 = obj;
    call1 = motion;
    call2 = part;
    state_load = FIELD(obj, u8, 0x6D);
    ASM_KEEP(state_load);
    call3 = obj;
    work = (s8)state_load;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
        return;
    }

    callback = FIELD(obj, Callback, 0x8C);
    if (callback != 0) {
        callback(obj, motion, part, obj);
    }
    D_80176374[FIELD(obj, u8, 0x9A)](obj, motion, part, obj);

    state_load = (s32)work << 16;
    ASM_KEEP(state_load);
    compare_new = FIELD(obj, s8, 0x6D);
    state_load >>= 16;
    if (state_load != compare_new) {
        func_800AA36C(obj, motion, part, obj);
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (!(FIELD(obj, u32, 0x1C) & 0x40000) &&
        !(FIELD(obj, u16, 0x98) & 8)) {
        FIELD(motion, s32, 0x14) += FIELD(obj, s8, 0x9D) * 0x14000;
        FIELD(obj, u8, 0x9D)++;
        func_80171344();
    }

    FIELD(obj, u8, 0x9D) = 0;
    ASM_KEEP(obj);
    FIELD(obj, s32, 0x90) += FIELD(motion, s32, 0x14);
    part_flags = FIELD(part, u16, 0x14);

    if (!(part_flags & 0x8000)) {
        direction = ((D_80083228[0] + FIELD(base, s16, 0x2A) + 0x100) >> 9) & 7;
        ASM_MEM_BARRIER();
        state_load = FIELD(obj, s16, 0x94);
        work = direction;
        if (state_load != work) {
            func_80047738(part,
                FIELD(FIELD(part, u8 *, 0x2C), u8, work),
                FIELD(part, s8, 4));
            FIELD(obj, s16, 0x94) = direction;
        }

        if (D_8006CCF8[work] != 0) {
            state_load = FIELD(part, u16, 0x14);
            state_load |= 1;
            ASM_TAILSLOT_PIN(state_load);
            func_801713EC();
        }
        ASM_KEEP(work);
        FIELD(part, u16, 0x14) &= 0xFFFE;

        func_800A020C(FIELD(base, u32, 0x1C), (u8 *)part + 0xC);
        if (!(FIELD(base, u32, 0x1C) & 0x20)) {
            if (!(FIELD(part, u16, 0x14) & 0x40)) {
                func_800478B8(part);
                state_load = 0xF7FF0000;
                ASM_TAILSLOT_PIN(state_load);
                func_80171458();
            }
        } else {
            FIELD(part, u16, 0x14) |= 0x7000;
            FIELD(base, u32, 0x1C) &= 0xFFFBFFFF;
        }

        normal_flags = FIELD(base, u32, 0x1C) & 0xF7FFFFFF;
        FIELD(base, u32, 0x1C) = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(FIELD(part, u16, 0x14) & 0x40) &&
                FIELD(part, u8 *, 0x2C) == D_800E23E0) {
                counter = FIELD(obj, u16, 0x9E);
                state_load = (s32)counter << 16;
                ASM_KEEP(state_load);
                state_load >>= 16;
                effect_arg = state_load * 0x55;
                ASM_KEEP_DEP_NV(counter, effect_arg);
                counter++;
                FIELD(obj, u16, 0x9E) = counter;
                FIELD(obj, s32, 0xA0) +=
                    func_800644B8(effect_arg) << 4;
            }

            floor = -0x20;
            if (!(FIELD(obj, u16, 0x98) & 8)) {
                if (floor < FIELD(obj, s16, 0x92)) {
                    FIELD(obj, u16, 0x92) = FIELD(obj, u16, 0x92) - 8;
                    func_80171704();
                }
                ASM_SCHED_BARRIER();
                if (FIELD(obj, s16, 0x92) < -0x28) {
                    FIELD(obj, u16, 0x92) = FIELD(obj, u16, 0x92) + 8;
                    func_80171704();
                }
            }
        } else {
            state_load = FIELD(obj, s32, 0xA0);
            FIELD(obj, u16, 0x9E) = 0;
            FIELD(obj, s32, 0xA0) = 0;
            FIELD(obj, s32, 0x90) -= state_load;
            if (!(FIELD(obj, u16, 0x98) & 8)) {
                floor = func_800BCB04(FIELD(motion, u16, 2),
                                      FIELD(motion, u16, 6),
                                      (s16)(FIELD(base, u16, 0x88) - 0x20)) -
                        FIELD(base, u16, 0x88);
                if (floor < FIELD(obj, s16, 0x92)) {
                    FIELD(obj, s16, 0x92) = floor;
                    FIELD(obj, u8, 0x9D) = 0;
                    FIELD(motion, s32, 0x14) = 0;
                    FIELD(base, u32, 0x1C) |= 0x08000000;
                    func_80171704();
                }
            }
        }
    } else {
        new_part_flags = part_flags & 0x800;
        if (new_part_flags) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        FIELD(part, u16, 0x14) = new_part_flags;
        ASM_SCHED_BARRIER();

        special_flags = FIELD(base, u32, 0x1C) & 0xF7FFFFFF;
        FIELD(base, u32, 0x1C) = special_flags;
        if (!(special_flags & 0x40000)) {
            state_load = FIELD(obj, s32, 0xA0);
            FIELD(obj, u16, 0x9E) = 0;
            FIELD(obj, s32, 0xA0) = 0;
            FIELD(obj, s32, 0x90) -= state_load;
            if (!(FIELD(obj, u16, 0x98) & 8)) {
                floor = func_800BCB04(FIELD(motion, u16, 2),
                                      FIELD(motion, u16, 6),
                                      (s16)(FIELD(base, u16, 0x88) - 0x20)) -
                        FIELD(base, u16, 0x88);
                if (floor < FIELD(obj, s16, 0x92)) {
                    FIELD(obj, s16, 0x92) = floor;
                    FIELD(obj, u8, 0x9D) = 0;
                    FIELD(motion, s32, 0x14) = 0;
                    FIELD(base, u32, 0x1C) |= 0x08000000;
                    func_801716F0();
                }
            }
        } else {
            if (!(FIELD(part, u16, 0x14) & 0x40) &&
                FIELD(part, u8 *, 0x2C) == D_800E23E0) {
                counter = FIELD(obj, u16, 0x9E);
                state_load = (s32)counter << 16;
                ASM_KEEP(state_load);
                state_load >>= 16;
                effect_arg = state_load * 0x55;
                ASM_KEEP_DEP_NV(counter, effect_arg);
                counter++;
                FIELD(obj, u16, 0x9E) = counter;
                FIELD(obj, s32, 0xA0) +=
                    func_800644B8(effect_arg) << 4;
            }

            floor = -0x20;
            if (!(FIELD(obj, u16, 0x98) & 8)) {
                if (floor < FIELD(obj, s16, 0x92)) {
                    FIELD(obj, u16, 0x92) = FIELD(obj, u16, 0x92) - 8;
                } else if (FIELD(obj, s16, 0x92) < -0x28) {
                    FIELD(obj, u16, 0x92) = FIELD(obj, u16, 0x92) + 8;
                }
            }
        }

        if (FIELD(obj, u8, 0xB5) != 0) {
            FIELD(obj, u16, 0x92) = 0;
        }
    }

    flags = FIELD(base, u32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(base, u32, 0x1C) = flags & 0xBFFFFFFF;
        floor = func_800BCB04(
            (FIELD(part, u8, 0x24) << 6) | 0x20,
            (FIELD(part, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(base, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            FIELD(obj, u16, 0x92) += FIELD(base, u16, 0x88) - floor;
            FIELD(base, u16, 0x88) = floor;
        }
    }

    FIELD(motion, u16, 0xA) = FIELD(base, u16, 0x88) +
        FIELD(obj, u16, 0x92) - FIELD(obj, u16, 0xA2);
    FIELD(part, u16, 0x14) |= 0x40;
}
