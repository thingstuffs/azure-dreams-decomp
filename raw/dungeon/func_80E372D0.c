#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80170EE4[];
extern Callback D_80176680[];

void func_80170AD0(void *a0, void *a1, void *a2)
{
    register void *entity ASM_REG("$18") = a0;
    register void *motion ASM_REG("$21") = a1;
    register void *monster ASM_REG("$20") = a2;
    register void *actor ASM_REG("$17") = entity;
    register s32 direction_index ASM_REG("$16");
    register s32 direction;
    register u32 old_direction_raw ASM_REG("$2");
    Callback callback;
    u16 flags;
    s16 floor;
    s16 actor_height;
    u8 kind;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(entity);
        ASM_KEEP(motion);
        ASM_KEEP(monster);
        ASM_KEEP(actor);
        first_callback = FIELD(entity, Callback, 0x8C);
        if (first_callback == (Callback)D_80170EE4) {
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

    old_direction_raw = FIELD(entity, volatile u8, 0x6D);
    kind = FIELD(entity, u8, 0x9A);
    old_direction_raw = old_direction_raw << 24;
    direction_index = (s32)old_direction_raw >> 24;
    if (kind != 0x17 && kind != 0x19) {
        if (func_800A9E70(entity, motion, monster, entity) != 0) {
            return;
        }
    }

    callback = FIELD(entity, Callback, 0x8C);
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    D_80176680[FIELD(entity, u8, 0x9A)](entity, motion, monster, actor);

    if ((s16)direction_index != FIELD(actor, s8, 0x6D)) {
        func_800AA36C(entity, motion, monster, actor);
    }

    flags = FIELD(monster, u16, 0x14);
    if (!(flags & 0x8000)) {
        s32 direction_value;

        direction_value =
            (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9;
        direction = direction_value & 7;
        direction_index = direction;

        if (FIELD(entity, s16, 0x94) != direction_index) {
            u8 *tile_map = FIELD(monster, u8 *, 0x2C);
            func_80047738(monster, tile_map[direction_index],
                          FIELD(monster, s8, 4));
            FIELD(entity, s16, 0x94) = direction;
        }

        if (D_8006CCF8[direction_index] != 0) {
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

        func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)monster + 0xC);
    } else {
        FIELD(monster, u16, 0x14) =
            (flags & 0x0800) ? (flags & 0x8FFF) : (flags | 0x7000);
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
                FIELD(actor, u32, 0x1C) &= 0xF7FFFFFF;
            } else {
                
                if (floor >= actor_height) {
                    FIELD(entity, s32, 0x90) = 0;
                } else {
                    FIELD(entity, s16, 0x92) = floor - FIELD(actor, u16, 0x88);
                }
    

                FIELD(motion, s32, 0x14) = 0;
                FIELD(entity, u8, 0x9D) = 0;
                FIELD(actor, u32, 0x1C) |= 0x08000000;
            }

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

    FIELD(actor, u32, 0x1C) &= 0xF7FFFFFF;

finish:
    FIELD(motion, u16, 0xA) =
        FIELD(actor, u16, 0x88) + FIELD(entity, u16, 0x92);
    FIELD(monster, u16, 0x14) |= 0x40;

    ASM_KEEP(entity);
    ASM_KEEP(motion);
    ASM_KEEP(monster);
    ASM_KEEP(actor);
    ASM_KEEP(direction_index);
    ASM_KEEP(direction);
}
