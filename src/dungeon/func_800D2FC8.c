#include "common.h"

typedef void (*Callback)();

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

extern void func_8003DB94();
extern void func_800478B8();
extern s32 func_80069EF8(void);
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern void func_800D88E4(void) __attribute__((noreturn));
extern void func_800D8930(void) __attribute__((noreturn));
extern void func_800D8954(void) __attribute__((noreturn));
extern void func_800D8A30(void) __attribute__((noreturn));
extern void func_800D8A78(void) __attribute__((noreturn));
extern void func_800D8AC4(void) __attribute__((noreturn));
extern void func_800D8B98(void) __attribute__((noreturn));
extern void func_800D8C18(void) __attribute__((noreturn));
extern void func_800D8C3C(void) __attribute__((noreturn));

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800D8C64;
extern u8 D_800E260C[];
extern Callback D_800E264C[];

void func_800D8728(void *arg0, void *arg1, void *arg2)
{
    register void *self ASM_REG("$4") = arg0;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *entity ASM_REG("$17") = self;   /* MATCH pin: load-bearing for the whole function shape */
    register void *motion ASM_REG("$20") = arg1;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *monster = arg2;
    register void *actor ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 previous_direction;
    register s32 direction_temp ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 state_direction ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 lookup_direction ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 compare_direction ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s16 floor;
    u16 flags;

    ASM_KEEP_NV(self);   /* MATCH pin: retail keeps a computation the compiler would drop */
    actor = entity;
    FIELD(monster, u16, 0x12) = 0;

    if (D_80083462 & 0x2000) {
        Callback special_callback = FIELD(entity, Callback, 0x8C);
        if (special_callback == (Callback)&D_800D8C64) {
            special_callback(entity, motion, monster, self);
            func_800D8C3C();
        }
        FIELD(entity, u8, 0x71) &= 0x7F;
        func_800D8C3C();
    }

    ASM_CLOBBER("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    previous_direction = (s8)FIELD(entity, u8, 0x6D);
    if (func_800A9E70(entity, motion, monster, entity) != 0) {
        return;
    }

    {
        Callback callback = FIELD(entity, Callback, 0x8C);
        if (callback != 0) {
            callback(entity, motion, monster, entity);
        }
    }
    D_800E264C[FIELD(entity, u8, 0x9A)](entity, motion, monster, entity);

    if ((s16)previous_direction != (s8)FIELD(entity, u8, 0x6D)) {
        func_800AA36C(entity, motion, monster, entity);
    }

    flags = FIELD(monster, u16, 0x14);
    if (!(flags & 0x8000)) {
        direction_temp = (D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 9;
        state_direction = direction_temp & 7;
        lookup_direction = state_direction;
        compare_direction = state_direction;
        if (FIELD(entity, s16, 0x94) != compare_direction) {
            void *table = FIELD(monster, void *, 0x2C);
            if (table != 0) {
                register s32 dir_index ASM_REG("$2") = (s16)compare_direction * 4;   /* MATCH pin: load-bearing for the whole function shape */
                func_8003DB94(monster,
                              *(void **)(dir_index + (s32)table),
                              FIELD(monster, s8, 4));
            }
            FIELD(entity, s16, 0x94) = state_direction;
        }

        if (D_8006CCF8[lookup_direction] != 0) {
            u16 tail_flags;
            tail_flags = FIELD(monster, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_flags);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800D88E4();
        }
        ASM_KEEP(lookup_direction);   /* MATCH pin: keeps a statement from moving across a call/branch */
        VFIELD(monster, u16, 0x14) &= 0xFFFE;

        if (!(FIELD(actor, s32, 0x1C) & 0x20)) {
            if (!(VFIELD(monster, u16, 0x14) & 0x40)) {
                func_800478B8(monster);
                func_800D8930();
            }
        } else {
            VFIELD(monster, u16, 0x14) |= 0x7000;
        }

        func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)monster + 0xC);
        func_800D8954();
    }

    if (flags & 0x800) {
        FIELD(monster, u16, 0x14) = flags & 0x8FFF;
    } else {
        FIELD(monster, u16, 0x14) = flags | 0x7000;
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (FIELD(entity, u8, 0x9A) == 14) {
        s16 timer;
        timer = (s16)(--FIELD(entity, u16, 0xA0));
        if (timer == 2) {
            s32 index;
            FIELD(entity, u16, 0x98) |= 1;
            FIELD(monster, u8 *, 0x2C) = D_800E260C;
            index = ((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 7) & 0x1C;
            func_8003DB94(monster, *(void **)(D_800E260C + index), 0);
        }

        if (FIELD(entity, s16, 0xA0) == 0) {
            FIELD(motion, s32, 0x14) = (s32)0xFFE00000;
        }

        if ((u16)(FIELD(entity, u16, 0xA0) + 7) < 8) {
            FIELD(motion, s32, 0x14) += 0x40000;
            func_800D8A30();
        }
        FIELD(motion, s32, 0x14) = 0;

        if (FIELD(entity, s16, 0xA0) < -7) {
            FIELD(entity, u16, 0x98) &= 0xFFFE;
            FIELD(entity, u16, 0xA0) = (func_80069EF8() & 0x3F) | 0x40;
            func_800D8A78();
        }
    } else {
        FIELD(entity, u16, 0x98) &= 0xFFFE;
    }

    if (FIELD(entity, u16, 0x98) & 8) {
        FIELD(entity, u8, 0x9D) = 0;
        func_800D8AC4();
    }

    FIELD(motion, s32, 0x14) +=
        ((s8)FIELD(entity, u8, 0x9D) * 5) << 14;
    FIELD(entity, u8, 0x9D)++;
    ASM_USE(entity);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    FIELD(entity, s32, 0x90) += FIELD(motion, s32, 0x14);

    if (!(FIELD(entity, u16, 0x98) & 4)) {
        floor = func_800BCB04(FIELD(motion, u16, 2),
                              FIELD(motion, u16, 6),
                              (s16)(FIELD(actor, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            if (FIELD(entity, s16, 0x92) + FIELD(actor, s16, 0x88) < floor) {
                FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
                func_800D8B98();
            }
            if (floor >= FIELD(actor, s16, 0x88)) {
                FIELD(entity, s32, 0x90) = 0;
                FIELD(motion, s32, 0x14) = 0;
                FIELD(actor, s32, 0x1C) |= 0x08000000;
                FIELD(entity, u8, 0x9D) = 0;
                func_800D8B98();
            }

            FIELD(motion, s32, 0x14) = 0;
            FIELD(actor, s32, 0x1C) |= 0x08000000;
            FIELD(entity, u8, 0x9D) = 0;
            FIELD(entity, u16, 0x92) = floor - FIELD(actor, u16, 0x88);

            if (FIELD(actor, s32, 0x1C) & 0x40000000) {
                FIELD(actor, s32, 0x1C) &= 0xBFFFFFFF;
                floor = func_800BCB04((FIELD(monster, u8, 0x24) << 6) | 0x20,
                                      (FIELD(monster, u8, 0x25) << 6) | 0x20,
                                      (s16)(FIELD(actor, u16, 0x88) - 0x20));
                FIELD(entity, u16, 0x92) += FIELD(actor, u16, 0x88) - floor;
                FIELD(actor, u16, 0x88) = floor;
                func_800D8C18();
            }
            goto finish;
        }
    }

    FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
finish:
    FIELD(motion, u16, 0xA) =
        FIELD(actor, u16, 0x88) + FIELD(entity, u16, 0x92);
    FIELD(monster, u16, 0x14) |= 0x40;
    ASM_KEEP(entity);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
}
