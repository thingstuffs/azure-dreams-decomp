#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801713A8[];
extern u8 D_80174494[];
extern u8 D_8017449C[];
extern EntityCallback D_80174504[];

extern void func_80047738();
extern void func_80047784();
extern void func_800478B8();
extern s32 func_800644B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();
extern void func_80170D54(void) __attribute__((noreturn));
extern void func_80170DFC(void) __attribute__((noreturn));
extern void func_80170E78(void) __attribute__((noreturn));
extern void func_80170EF0(void) __attribute__((noreturn));
extern void func_801711A0(void) __attribute__((noreturn));
extern void func_801712C8(void) __attribute__((noreturn));
extern void func_801712D8(void) __attribute__((noreturn));
extern void func_8017137C(void) __attribute__((noreturn));

void func_80170BB8(void *arg0, void *arg1, void *arg2)
{
    u16 initial_flags = D_80083462;
    register void *actor ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$21") = arg1;
    register void *object ASM_REG("$20") = arg2;
    register s32 bob ASM_REG("$22") = 0;
    register void *actor2 ASM_REG("$18") = actor;
    s16 index;
    register s16 direction ASM_REG("$19");
    s16 ground;
    s32 ground32;
    s32 result;
    s32 final_value;
    EntityCallback callback;
    u8 *palette;
    u16 object_flags;
    u16 common_flags;
    register u32 actor_flags ASM_REG("$3");

    if (initial_flags & 0x2000) {
        EntityCallback early_callback = FIELD(actor, EntityCallback, 0x8C);
        if ((void *)early_callback == (void *)D_801713A8) {
            register void *entry_arg0 ASM_REG("$4") = arg0;
            ASM_KEEP_NV(entry_arg0);
            early_callback(arg0, arg1, arg2, entry_arg0);
            func_8017137C();
        } else {
            FIELD(actor, u8, 0x71) &= 0x7F;
            func_8017137C();
        }
    }

    ASM_KEEP(actor);
    ASM_KEEP(motion);
    ASM_KEEP(object);
    ASM_KEEP(bob);
    ASM_KEEP(actor2);

    index = (s8)FIELD(actor, u8, 0x6D);
    if (func_800A9E70(actor, motion, object, actor) != 0) {
        return;
    }

    callback = FIELD(actor, EntityCallback, 0x8C);
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    D_80174504[FIELD(actor, u8, 0x9A)](actor, motion, object, actor);
    if ((s16)index != (s8)FIELD(actor, u8, 0x6D)) {
        func_800AA36C(actor, motion, object, actor);
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (!(FIELD(actor, u32, 0x1C) & 0x40000) &&
        !(FIELD(actor, u16, 0x98) & 8)) {
        FIELD(motion, s32, 0x14) += (s8)FIELD(actor, u8, 0x9D) * 0x14000;
        FIELD(actor, u8, 0x9D)++;
        func_80170D54();
        return;
    }

    do {
        FIELD(actor, volatile u8, 0x9D) = 0;
    } while (0);
    FIELD(actor, s32, 0x90) += FIELD(motion, s32, 0x14);
    object_flags = FIELD(object, u16, 0x14);

    if (!(object_flags & 0x8000)) {
        {
            register s32 dir_calc ASM_REG("$2");
            dir_calc = (D_80083228 + FIELD(actor2, s16, 0x2A) + 0x100) >> 9;
            ASM_KEEP(dir_calc);
            direction = dir_calc & 7;
        }
        if (FIELD(actor, s16, 0x94) != direction) {
            func_80047738(object, FIELD(object, u8 *, 0x2C)[direction],
                          FIELD(object, s8, 4));
            FIELD(actor, s16, 0x94) = direction;
        }
        if (D_8006CCF8[direction] != 0) {
            register u32 tail_v0 ASM_REG("$2") = FIELD(object, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_v0);
            func_80170DFC();
        }

        FIELD(object, u16, 0x14) &= 0xFFFE;
        if (FIELD(actor, u8, 0x9A) != 8) {
            func_800A020C(FIELD(actor2, s32, 0x1C), (u8 *)object + 0xC);
        }

        if (!(FIELD(actor2, u32, 0x1C) & 0x20)) {
            if (!(FIELD(object, u16, 0x14) & 0x40)) {
                func_800478B8(object);
                {
                    register u32 tail_v0 ASM_REG("$2") = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_v0);
                    func_80170E78();
                }
            }
        } else {
            FIELD(object, u16, 0x14) |= 0x7000;
            FIELD(actor2, u32, 0x1C) &= 0xFFFBFFFF;
        }

        actor_flags = FIELD(actor2, u32, 0x1C) & 0xF7FFFFFF;
        FIELD(actor2, u32, 0x1C) = actor_flags;
        if (actor_flags & 0x40000) {
            if (!(FIELD(object, u16, 0x14) & 0x40)) {
                object_flags = FIELD(actor, u16, 0x98);
                if (object_flags & 0x8000) {
                    FIELD(actor, u16, 0x98) = object_flags & 0x7FFF;
                    palette = FIELD(object, u8 *, 0x2C);
                    if (palette == D_8017449C) {
                        register void *tail_a1 ASM_REG("$5") = D_80174494;
                        ASM_TAILSLOT_PIN(tail_a1);
                        func_80170EF0();
                    }
                    else if (palette == D_80174494) {
                        ASM_SCHED_BARRIER();
                        FIELD(object, u8 *, 0x2C) = D_8017449C;
                        func_80047784(object,
                            D_8017449C[((D_80083228 + FIELD(actor2, s16, 0x2A) + 0x100) >> 9) & 7],
                            0);
                    }
                }
                if (FIELD(object, u16, 0x14) & 0x6000) {
                    FIELD(actor, u16, 0x98) |= 0x8000;
                    if (FIELD(object, u8 *, 0x2C) == D_80174494) {
                        FIELD(actor, s16, 0xA8) = 0;
                    }
                }
                result = func_800644B8((FIELD(actor, s16, 0xA8) << 12) / 21);
                bob = result >> 8;
                if (FIELD(actor, u8, 0x9A) == 0x12) {
                    bob = result >> 10;
                }
                FIELD(actor, s16, 0xA8)++;
            }

            if (!(FIELD(actor, u16, 0x98) & 8)) {
                ground = (s16)(func_800BCB04(FIELD(motion, u16, 2),
                    FIELD(motion, u16, 6),
                    (s16)(FIELD(actor2, u16, 0x88) - 0x20)) -
                    FIELD(actor2, u16, 0x88));
                if (FIELD(actor, s16, 0x92) > ground - 0x30) {
                    FIELD(actor, s16, 0x92) = FIELD(actor, s16, 0x92) - 8;
                    func_801712D8();
                    return;
                }
                ASM_SCHED_BARRIER();
                if (ground - 0x3A > FIELD(actor, s16, 0x92)) {
                    FIELD(actor, s16, 0x92) = FIELD(actor, s16, 0x92) + 8;
                    func_801712D8();
                    return;
                }
        }
        } else {
            common_flags = FIELD(actor, u16, 0x98);
            FIELD(actor, s16, 0xA8) = 0;
            FIELD(actor, u16, 0x98) = common_flags & 0x7FFF;
            if (!(common_flags & 8)) {
                ground32 = func_800BCB04(FIELD(motion, u16, 2),
                    FIELD(motion, u16, 6),
                    (s16)(FIELD(actor2, u16, 0x88) - 0x20)) -
                    FIELD(actor2, s16, 0x88);
                if (ground32 < FIELD(actor, s16, 0x92)) {
                    FIELD(actor, s16, 0x92) = ground32;
                    FIELD(actor, u8, 0x9D) = 0;
                    FIELD(motion, s32, 0x14) = 0;
                    FIELD(actor2, u32, 0x1C) |= 0x08000000;
                    func_801712D8();
                    return;
                }
            }
        }
        goto common_tail;
    }

    if (!(object_flags & 0x800)) {
        FIELD(object, u16, 0x14) = object_flags | 0x7000;
    } else {
        FIELD(object, u16, 0x14) = object_flags & 0x8FFF;
    }
    actor_flags = FIELD(actor2, u32, 0x1C) & 0xF7FFFFFF;
    FIELD(actor2, u32, 0x1C) = actor_flags;

    if (!(actor_flags & 0x40000)) {
        FIELD(actor, s16, 0xA8) = 0;
        FIELD(actor, s16, 0x92) -= bob;
        bob = 0;
        if (!(FIELD(actor, u16, 0x98) & 8)) {
            ground32 = func_800BCB04(FIELD(motion, u16, 2),
                FIELD(motion, u16, 6),
                (s16)(FIELD(actor2, u16, 0x88) - 0x20)) -
                FIELD(actor2, s16, 0x88);
            if (ground32 < FIELD(actor, s16, 0x92)) {
                FIELD(actor, s16, 0x92) = ground32;
                FIELD(actor, u8, 0x9D) = 0;
                FIELD(motion, s32, 0x14) = 0;
                FIELD(actor2, u32, 0x1C) |= 0x08000000;
                func_801712C8();
                return;
            }
        }
    } else {
        if (!(FIELD(object, u16, 0x14) & 0x40)) {
            object_flags = FIELD(actor, u16, 0x98);
            if (object_flags & 0x8000) {
                FIELD(actor, u16, 0x98) = object_flags & 0x7FFF;
                palette = FIELD(object, u8 *, 0x2C);
                if (palette == D_8017449C) {
                    register void *tail_a1 ASM_REG("$5") = D_80174494;
                    ASM_TAILSLOT_PIN(tail_a1);
                    func_801711A0();
                } else if (palette == D_80174494) {
                    ASM_KEEP(palette);
                    FIELD(object, u8 *, 0x2C) = D_8017449C;
                    func_80047784(object,
                        D_8017449C[((D_80083228 + FIELD(actor2, s16, 0x2A) + 0x100) >> 9) & 7],
                        0);
                }
            }
            if (FIELD(object, u16, 0x14) & 0x6000) {
                FIELD(actor, u16, 0x98) |= 0x8000;
                if (FIELD(object, u8 *, 0x2C) == D_80174494) {
                    FIELD(actor, s16, 0xA8) = 0;
                }
            }
            result = func_800644B8((FIELD(actor, s16, 0xA8) << 12) / 21);
            bob = result >> 8;
            if (FIELD(actor, u8, 0x9A) == 0x12) {
                bob = result >> 10;
            }
            FIELD(actor, s16, 0xA8)++;
        }

        if (!(FIELD(actor, u16, 0x98) & 8)) {
            ground = (s16)(func_800BCB04(FIELD(motion, u16, 2),
                FIELD(motion, u16, 6),
                (s16)(FIELD(actor2, u16, 0x88) - 0x20)) -
                FIELD(actor2, u16, 0x88));
            if (FIELD(actor, s16, 0x92) > ground - 0x30) {
                FIELD(actor, s16, 0x92) = FIELD(actor, s16, 0x92) - 8;
            } else if (ground - 0x3A > FIELD(actor, s16, 0x92)) {
                FIELD(actor, s16, 0x92) = FIELD(actor, s16, 0x92) + 8;
            }
        }
    }

cleanup_tail:
    FIELD(actor, s16, 0xA8) = 0;
    FIELD(actor, u16, 0x98) &= 0x7FFF;

common_tail:
    if (FIELD(actor2, u32, 0x1C) & 0x40000000) {
        FIELD(actor2, u32, 0x1C) = FIELD(actor2, u32, 0x1C) & 0xBFFFFFFF;
        ground = func_800BCB04((FIELD(object, u8, 0x24) << 6) | 0x20,
            (FIELD(object, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(actor2, u16, 0x88) - 0x20));
        if (ground < 0x200) {
            FIELD(actor, s16, 0x92) += FIELD(actor2, u16, 0x88) - ground;
            FIELD(actor2, u16, 0x88) = ground;
        }
    }
    final_value = FIELD(actor2, u16, 0x88) +
        (u16)FIELD(actor, s16, 0x92);
    final_value += bob;
    FIELD(motion, s16, 0xA) = final_value;
    FIELD(object, u16, 0x14) |= 0x40;
}
