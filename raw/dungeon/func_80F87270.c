#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(u16, u16, s16);
extern void func_80170C0C(void) __attribute__((noreturn));
extern void func_80170D30(void) __attribute__((noreturn));
extern void func_80171064(void) __attribute__((noreturn));
extern void func_80171068(void) __attribute__((noreturn));
extern void func_8017110C(void) __attribute__((noreturn));

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171138[];
extern Callback D_80174B1C[];

void func_80170A70(void *arg0, void *raw_arg1, void *raw_arg2)
{
    static void *const phase_entries[] = {
        &&phase_update_a,
        &&phase_update_b,
    };
    void *object = arg0;
    register void *arg1 ASM_REG("$21");
    register void *arg2 ASM_REG("$20");
    Callback callback;
    Callback callback2;
    s16 old_state;
    s16 direction;
    s16 ground;
    register s32 ground32 ASM_REG("$2");
    s16 angle;
    s32 bob;
    u16 flags;
    u16 new_flags;

    arg1 = raw_arg1;
    arg2 = raw_arg2;
    bob = 0;
    if (D_80083462 & 0x2000) {
        callback = FIELD(arg0, Callback, 0x8C);
        if (callback == (Callback)D_80171138) {
            callback(arg0, raw_arg1, raw_arg2, arg0);
            func_8017110C();
        }
        FIELD(arg0, u8, 0x71) &= 0x7F;
        func_8017110C();
    }

    ASM_KEEP_NV(arg1);
    ASM_KEEP_NV(arg2);
    old_state = (s8)FIELD(arg0, u8, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    callback2 = FIELD(arg0, Callback, 0x8C);
    if (callback2 != 0) {
        callback2(arg0, arg1, arg2, arg0);
    }
    D_80174B1C[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);
    if ((s16)old_state != FIELD(arg0, s8, 0x6D)) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

    if (!(FIELD(arg0, s32, 0x1C) & 0x40000) &&
        !(FIELD(arg0, u16, 0x98) & 8)) {
        FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
        FIELD(arg0, u8, 0x9D)++;
        func_80170C0C();
    }

    do { FIELD(arg0, u8, 0x9D) = 0; } while (0);
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);
    flags = FIELD(arg2, u16, 0x14);

    if (!(flags & 0x8000)) {
        angle = ((D_80083228 + FIELD(object, s16, 0x2A) + 0x100) >> 9) & 7;
        old_state = angle;
        if (FIELD(arg0, s16, 0x94) != old_state) {
            func_80047738(arg2,
                ((u8 *)FIELD(arg2, void *, 0x2C))[old_state],
                FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = angle;
        }

        {
            register u16 bit_flags ASM_REG("$2");

            if (D_8006CCF8[old_state] != 0) {
                bit_flags = FIELD(arg2, u16, 0x14) | 1;
            } else {
                bit_flags = FIELD(arg2, u16, 0x14) & 0xFFFE;
            }
            FIELD(arg2, u16, 0x14) = bit_flags;
        }

        if (FIELD(arg0, u8, 0x9A) != 8) {
            func_800A020C(FIELD(object, s32, 0x1C), (u8 *)arg2 + 0xC);
        }

        if (!(FIELD(object, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                {
                    register u32 tail_v0 ASM_REG("$2") = 0xF7FF0000;
                    ASM_TAILSLOT_PIN(tail_v0);
                    func_80170D30();
                }
            }
            goto clear_motion_flag;
        }

        FIELD(arg2, u16, 0x14) |= 0x7000;
        FIELD(object, s32, 0x1C) &= 0xFFFBFFFF;

clear_motion_flag:
        FIELD(object, s32, 0x1C) &= 0xF7FFFFFF;
        if (FIELD(object, s32, 0x1C) & 0x40000) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                {
                    s32 value = func_800644B8(
                        (FIELD(arg0, s16, 0xA0) << 12) / 40);
                    bob = value >> 9;
                    if (FIELD(arg0, u8, 0x9A) == 0x12) {
                        bob = value >> 10;
                    }
                }
phase_update_a:
                FIELD(arg0, s16, 0xA0) = (FIELD(arg0, s16, 0xA0) + 1) % 40;
            }

            if (!(FIELD(arg0, u16, 0x98) & 8)) {
                ground = (s16)(func_800BCB04(
                    FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                    (s16)(FIELD(object, u16, 0x88) - 0x20)) -
                    FIELD(object, u16, 0x88));
                if (FIELD(arg0, s16, 0x92) > ground - 0x30) {
                    FIELD(arg0, s16, 0x92) =
                        (u16)FIELD(arg0, s16, 0x92) - 8;
                    func_80171068();
                }
                ASM_SCHED_BARRIER();
                if (ground - 0x3A > FIELD(arg0, s16, 0x92)) {
                    FIELD(arg0, s16, 0x92) =
                        (u16)FIELD(arg0, s16, 0x92) + 8;
                    func_80171068();
                }
            }
            goto reset_bob;
        }

        FIELD(arg0, s16, 0xA0) = 0;
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            register s32 object_height ASM_REG("$4");

            ground32 = (s16)func_800BCB04(
                FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                (s16)(FIELD(object, u16, 0x88) - 0x20));
            object_height = FIELD(object, s16, 0x88);
            ground32 -= object_height;
            if (FIELD(arg0, s16, 0x92) > ground32) {
                FIELD(arg0, s16, 0x92) = ground32;
                FIELD(arg0, u8, 0x9D) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(object, s32, 0x1C) |= 0x08000000;
                func_80171068();
            }
        }
        goto reset_bob;
    }

    {
        if (flags & 0x800) {
            new_flags = flags & 0x8FFF;
        } else {
            new_flags = flags | 0x7000;
        }
        FIELD(arg2, u16, 0x14) = new_flags;
        ASM_SCHED_BARRIER();
    }
    FIELD(object, s32, 0x1C) &= 0xF7FFFFFF;

    if (!(FIELD(object, s32, 0x1C) & 0x40000)) {
        FIELD(arg0, s16, 0xA0) = 0;
        FIELD(arg0, s16, 0x92) = (u16)FIELD(arg0, s16, 0x92) - bob;
        bob = 0;
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            register s32 object_height ASM_REG("$4");

            ground32 = (s16)func_800BCB04(
                FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                (s16)(FIELD(object, u16, 0x88) - 0x20));
            object_height = FIELD(object, s16, 0x88);
            ground32 -= object_height;
            if (FIELD(arg0, s16, 0x92) > ground32) {
                FIELD(arg0, s16, 0x92) = ground32;
                FIELD(arg0, u8, 0x9D) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(object, s32, 0x1C) |= 0x08000000;
                func_80171064();
            }
        }
        goto finish_height;
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
        {
            s32 value = func_800644B8(
                (FIELD(arg0, s16, 0xA0) << 12) / 40);
            bob = value >> 9;
            if (FIELD(arg0, u8, 0x9A) == 0x12) {
                bob = value >> 10;
            }
        }
phase_update_b:
        FIELD(arg0, s16, 0xA0) = (FIELD(arg0, s16, 0xA0) + 1) % 40;
    }

    if (!(FIELD(arg0, u16, 0x98) & 8)) {
        ground = (s16)(func_800BCB04(
            FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
            (s16)(FIELD(object, u16, 0x88) - 0x20)) -
            FIELD(object, u16, 0x88));
        if (FIELD(arg0, s16, 0x92) > ground - 0x30) {
            FIELD(arg0, s16, 0x92) =
                (u16)FIELD(arg0, s16, 0x92) - 8;
        } else if (ground - 0x3A > FIELD(arg0, s16, 0x92)) {
            FIELD(arg0, s16, 0x92) =
                (u16)FIELD(arg0, s16, 0x92) + 8;
        } else {
            goto finish_height;
        }
    }

finish_height:
    FIELD(arg0, s16, 0xA0) = 0;

reset_bob:
    if (FIELD(object, s32, 0x1C) & 0x40000000) {
        FIELD(object, s32, 0x1C) &= 0xBFFFFFFF;
        ground = func_800BCB04(
            (FIELD(arg2, u8, 0x24) << 6) | 0x20,
            (FIELD(arg2, u8, 0x25) << 6) | 0x20,
            (s16)(FIELD(object, u16, 0x88) - 0x20));
        if (ground < 0x200) {
            FIELD(arg0, s16, 0x92) =
                (u16)FIELD(arg0, s16, 0x92) +
                (FIELD(object, u16, 0x88) - ground);
            FIELD(object, u16, 0x88) = ground;
        }
    }

    FIELD(arg1, s16, 0xA) =
        FIELD(object, u16, 0x88) + (u16)FIELD(arg0, s16, 0x92) + bob;
    FIELD(arg2, u16, 0x14) |= 0x40;
}
