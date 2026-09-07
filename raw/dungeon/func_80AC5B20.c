#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80171728;
extern Callback D_80174E5C[];

void func_80171320(void *a0, void *a1, void *a2)
{
    register void *entity ASM_REG("$17") = a0;
    register void *motion ASM_REG("$20") = a1;
    register void *monster ASM_REG("$19") = a2;
    register void *actor ASM_REG("$18") = entity;
    register s32 direction ASM_REG("$16");
    register s32 direction_copy ASM_REG("$21");
    register s32 direction_value ASM_REG("$2");
    Callback callback;
    u16 flags;
    s16 floor;
    s16 actor_height;
    s32 direction_index;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(entity);
        ASM_KEEP(motion);
        ASM_KEEP(monster);
        ASM_KEEP(actor);
        first_callback = FIELD(entity, Callback, 0x8C);
        if (first_callback == (Callback)&D_80171728) {
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

    direction_value = (s32)FIELD(entity, volatile u8, 0x6D) << 24;
    direction = direction_value >> 24;
    if (func_800A9E70(entity, motion, monster, entity) != 0) {
        return;
    }

    callback = FIELD(entity, Callback, 0x8C);
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    D_80174E5C[FIELD(entity, u8, 0x9A)](entity, motion, monster, entity);

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
                func_80047738(monster, tile_map[direction_index], FIELD(monster, s8, 4));
            }
            FIELD(entity, s16, 0x94) = direction;
        }

        if (D_8006CCF8[direction_copy] != 0) {
            FIELD(monster, u16, 0x14) |= 1;
        } else {
            FIELD(monster, u16, 0x14) &= 0xFFFE;
        }

        if (!(FIELD(actor, s32, 0x1C) & 0x20)) {
            if (!(FIELD(monster, u16, 0x14) & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            FIELD(monster, u16, 0x14) |= 0x7000;
        }

        func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)monster + 0xC);
    } else {
        if (flags & 0x0800) {
            FIELD(monster, u16, 0x14) = flags & 0x8FFF;
        } else {
            FIELD(monster, u16, 0x14) = flags | 0x7000;
        }
    }

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
            if (FIELD(entity, s16, 0x92) + actor_height < floor) {
                FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
                goto check_adjustment;
            }

            if (floor >= actor_height) {
                FIELD(entity, s32, 0x90) = 0;
            } else {
                FIELD(entity, s16, 0x92) = floor - FIELD(actor, u16, 0x88);
            }

            FIELD(motion, s32, 0x14) = 0;
            FIELD(actor, s32, 0x1C) |= 0x08000000;
            FIELD(entity, u8, 0x9D) = 0;

check_adjustment:
            if (FIELD(actor, s32, 0x1C) & 0x40000000) {
                FIELD(actor, s32, 0x1C) &= 0xBFFFFFFF;
                floor = func_800BCB04((FIELD(monster, u8, 0x24) << 6) | 0x20,
                                      (FIELD(monster, u8, 0x25) << 6) | 0x20,
                                      (s16)(FIELD(actor, u16, 0x88) - 0x20));
                FIELD(entity, s16, 0x92) += FIELD(actor, u16, 0x88) - floor;
                FIELD(actor, u16, 0x88) = floor;
                goto finish;
            }
            goto finish;
        }
    }

    FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;

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

/* MECHANISM: Preserve original a0-a2 and the entity base across the early callback ABI.
   Scope the s16 cast to the old-direction compare and reuse the pinned v0 scratch for lbu/sll/sra.
   Restore the dropped actor-flag clear CFG edge; its three words collapse the displacement cascade. */
