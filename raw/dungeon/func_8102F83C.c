#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 func_80042900();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801714B8;
extern Callback D_80176138[];

void func_8017103C(void *a0, void *a1, void *a2)
{
    register void *entity ASM_REG("$18") = a0;
    register void *motion ASM_REG("$20") = a1;
    register void *monster ASM_REG("$17") = a2;
    register void *actor ASM_REG("$19") = entity;
    register u32 raw_direction ASM_REG("$2");
    register s32 direction ASM_REG("$16");
    register s32 direction_copy ASM_REG("$21");
    register s32 direction_value ASM_REG("$2");
    register void *call0 ASM_REG("$4");
    register void *call1 ASM_REG("$5");
    register void *call2 ASM_REG("$6");
    register void *call3 ASM_REG("$7");
    s32 direction_index;
    u16 flags;
    s16 floor;
    s16 actor_height;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(entity);
        ASM_KEEP(motion);
        ASM_KEEP(monster);
        ASM_KEEP(actor);
        first_callback = FIELD(entity, Callback, 0x8C);
        if (first_callback == (Callback)&D_801714B8) {
            first_callback(a0, a1, a2, a0);
        } else {
            FIELD(entity, u8, 0x71) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(entity);
    ASM_KEEP(motion);
    ASM_KEEP(monster);
    ASM_KEEP(actor);

    call0 = entity;
    call1 = motion;
    call2 = monster;
    raw_direction = FIELD(entity, volatile u8, 0x6D);
    call3 = entity;
    raw_direction <<= 24;
    direction = (s32)raw_direction >> 24;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
        return;
    }

    {
        register Callback callback ASM_REG("$2");

        callback = FIELD(entity, Callback, 0x8C);
        if (callback != 0) {
            callback(entity, motion, monster, entity);
        }
    }
    D_80176138[FIELD(entity, u8, 0x9A)](entity, motion, monster, entity);

    if ((s16)direction != FIELD(entity, s8, 0x6D)) {
        func_800AA36C(entity, motion, monster, entity);
    }

    flags = FIELD(monster, u16, 0x14);
    if (!(flags & 0x8000)) {
        direction_value = D_80083228 + FIELD(entity, s16, 0x2A) + 0x100;
        ASM_KEEP(direction_value);
        direction = (direction_value >> 9) & 7;
        ASM_KEEP(direction);
        direction_index = direction;
        direction_copy = direction;

        if (FIELD(entity, s16, 0x94) != direction_index) {
            u8 *tile_map = FIELD(monster, u8 *, 0x2C);

            if (tile_map != 0) {
                func_80047738(monster, tile_map[direction_index],
                              FIELD(monster, s8, 4));
            }
            FIELD(entity, s16, 0x94) = direction;
        }

        if (D_8006CCF8[direction_copy] != 0) {
            FIELD(monster, u16, 0x14) |= 1;
        } else {
            FIELD(monster, u16, 0x14) &= 0xFFFE;
        }

        if (!(FIELD(actor, u32, 0x1C) & 0x20)) {
            if (!(FIELD(monster, u16, 0x14) & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            FIELD(monster, u16, 0x14) |= 0x7000;
        }

        if (!(FIELD(actor, u32, 0x1C) & 0x10000000)) {
            if ((func_80042900(actor, 1) << 16) != 0) {
                s32 value;
                s32 state = FIELD(monster, s8, 4);

                if (state != 0) {
                    goto nonzero_state;
                }
                ASM_SCHED_BARRIER();
                value = 0x80;
                goto set_state_bytes;
nonzero_state:
                if (state == 1) {
                    goto state_value_64;
                }
                if (state == 2) {
                    value = 0x50;
                    goto set_state_bytes;
                }
                if (state != 3) {
                    goto flags_done;
                }
state_value_64:
                value = 0x64;
set_state_bytes:
                FIELD(monster, u8, 0xE) = value;
                FIELD(monster, u8, 0xD) = value;
                FIELD(monster, u8, 0xC) = value;
            } else {
                func_800A020C(FIELD(actor, u32, 0x1C),
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        if (flags & 0x0800) {
            FIELD(monster, u16, 0x14) = flags & 0x8FFF;
        } else {
            FIELD(monster, u16, 0x14) = flags | 0x7000;
        }
    }

flags_done:
    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (FIELD(entity, u16, 0x98) & 8) {
        FIELD(entity, u8, 0x9D) = 0;
    } else {
        FIELD(motion, s32, 0x14) += FIELD(entity, s8, 0x9D) * 0x14000;
        FIELD(entity, u8, 0x9D)++;
    }

    FIELD(entity, s32, 0x90) += FIELD(motion, s32, 0x14);

    if (!(FIELD(entity, u16, 0x98) & 4)) {
        floor = func_800BCB04(FIELD(motion, u16, 2),
                              FIELD(motion, u16, 6),
                              (s16)(FIELD(actor, u16, 0x88) - 0x20));
        if (floor < 0x200) {
            actor_height = FIELD(actor, s16, 0x88);
            if (!(FIELD(entity, s16, 0x92) + actor_height < floor)) {
                goto resolve_floor;
            }

            FIELD(actor, u32, 0x1C) &= 0xF7FFFFFF;
            goto check_floor_adjustment;

resolve_floor:
            if (floor >= actor_height) {
                FIELD(entity, s32, 0x90) = 0;
            } else {
                FIELD(entity, s16, 0x92) = floor - FIELD(actor, u16, 0x88);
            }

            FIELD(motion, s32, 0x14) = 0;
            FIELD(actor, u32, 0x1C) |= 0x08000000;
            FIELD(entity, u8, 0x9D) = 0;

check_floor_adjustment:
            if (FIELD(actor, u32, 0x1C) & 0x40000000) {
                FIELD(actor, u32, 0x1C) &= 0xBFFFFFFF;
                floor = func_800BCB04(
                    (FIELD(monster, u8, 0x24) << 6) | 0x20,
                    (FIELD(monster, u8, 0x25) << 6) | 0x20,
                    (s16)(FIELD(actor, u16, 0x88) - 0x20));
                FIELD(entity, s16, 0x92) +=
                    FIELD(actor, u16, 0x88) - floor;
                FIELD(actor, u16, 0x88) = floor;
            }
            goto finish;
        }
    }

clear_falling:
    FIELD(actor, u32, 0x1C) &= 0xF7FFFFFF;

finish:
    FIELD(motion, u16, 0xA) =
        FIELD(actor, u16, 0x88) + FIELD(entity, u16, 0x92);
    FIELD(monster, u16, 0x14) |= 0x40;

    ASM_KEEP(entity);
    ASM_KEEP(motion);
    ASM_KEEP(monster);
    ASM_KEEP(actor);
    ASM_KEEP(direction);
    ASM_KEEP(direction_copy);
}

/* MECHANISM: The 48-byte frame holds entity/motion/monster/actor in s2/s4/s1/s3
   and direction/direction_copy in s0/s5. Depinning raw_direction lets sra fill
   the first jal delay; a zero-arm entry barrier retains the bnez+j CFG and li slot. */
