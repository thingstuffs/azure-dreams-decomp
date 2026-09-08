#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);


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


typedef struct S_80171320_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171320_0;   /* monster in func_80171320 */

typedef struct S_80171320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80171320_1;   /* actor in func_80171320 */

typedef struct S_80171320_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171320_2;   /* motion in func_80171320 */

/* Runs entity callbacks, updates monster facing, and applies motion and floor collision. */
void func_80171320(void *entity_arg, void *motion_arg, void *monster_arg)
{
    void *entity = entity_arg;
    S_80171320_2 *motion = motion_arg;
    void *monster = monster_arg;
    register void *actor ASM_REG("$18") = entity;   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 direction ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 direction_copy ASM_REG("$21");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 direction_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s32 direction_index;

    if (D_80083462 & 0x2000) {
        Callback early_callback;

        ASM_KEEP(actor);   /* MATCH pin: retail register colouring depends on it */
        early_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (early_callback == (Callback)&D_80171728) {
            early_callback(entity_arg, motion_arg, monster_arg, entity_arg);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(actor);   /* MATCH pin: retail register colouring depends on it */

    direction_value = (s32)(*(volatile u8 *)((u8 *)entity + 0x6D)) << 24;
    direction = direction_value >> 24;
    if (func_800A9E70(entity, motion, monster, entity) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    D_80174E5C[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, monster, entity);
    }

    monster_flags = ((S_80171320_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        direction_value = D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        ASM_KEEP(direction);   /* MATCH pin: retail delay-slot fill depends on it */
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((S_80171320_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                func_80047738(monster, tile_map[direction_index], ((S_80171320_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (D_8006CCF8[direction_copy] != 0) {
            ((S_80171320_0 *)monster)->unk_14 |= 1;
        } else {
            ((S_80171320_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((S_80171320_1 *)actor)->unk_1C & 0x20)) {
            if (!(((S_80171320_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((S_80171320_0 *)monster)->unk_14 |= 0x7000;
        }

        func_800A020C(((S_80171320_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            ((S_80171320_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((S_80171320_0 *)monster)->unk_14 = monster_flags | 0x7000;
        }
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        floor_height = func_800BCB04(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((S_80171320_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80171320_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                ((S_80171320_1 *)actor)->unk_1C &= 0xF7FFFFFF;
                goto check_adjustment;
            }

            if (floor_height >= actor_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
            } else {
                (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((S_80171320_1 *)actor)->unk_88.u;
            }

            motion->unk_14 = 0;
            ((S_80171320_1 *)actor)->unk_1C |= 0x08000000;
            (*(u8 *)((u8 *)entity + 0x9D)) = 0;

check_adjustment:
            if (((S_80171320_1 *)actor)->unk_1C & 0x40000000) {
                ((S_80171320_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04((((S_80171320_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((S_80171320_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((S_80171320_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((S_80171320_1 *)actor)->unk_88.u - floor_height;
                ((S_80171320_1 *)actor)->unk_88.u = floor_height;
                goto finish;
            }
            goto finish;
        }
    }

    ((S_80171320_1 *)actor)->unk_1C &= 0xF7FFFFFF;

finish:
    motion->unk_0A =
        ((S_80171320_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((S_80171320_0 *)monster)->unk_14 |= 0x40;

    ASM_KEEP(entity);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(monster);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(direction);   /* MATCH pin: retail delay-slot fill depends on it */
    ASM_KEEP(direction_copy);   /* MATCH pin: retail delay-slot fill depends on it */
}

