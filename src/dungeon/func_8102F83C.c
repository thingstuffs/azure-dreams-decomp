#include "common.h"


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


typedef struct S_8017103C_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8017103C_0;   /* monster in func_8017103C */

typedef struct S_8017103C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8017103C_1;   /* actor in func_8017103C */

typedef struct S_8017103C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017103C_2;   /* motion in func_8017103C */

/* Runs entity callbacks, updates monster appearance, and advances motion with floor collision. */
void func_8017103C(void *entity_arg, void *motion_arg, void *monster_arg)
{
    register void *entity ASM_REG("$18") = entity_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_8017103C_2 *motion = motion_arg;
    void *monster = monster_arg;
    S_8017103C_1 *actor = entity;
    u32 raw_direction;
    register s32 direction ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 direction_copy ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 facing_angle ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *call_entity;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_motion;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_monster;
    void *call_context;
    s32 direction_index;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        first_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (first_callback == (Callback)&D_801714B8) {
            first_callback(entity_arg, motion_arg, monster_arg, entity_arg);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    call_entity = entity;
    call_motion = motion;
    call_monster = monster;
    raw_direction = (*(volatile u8 *)((u8 *)entity + 0x6D));
    call_context = entity;
    raw_direction <<= 24;
    direction = (s32)raw_direction >> 24;
    if (func_800A9E70(call_entity, call_motion, call_monster, call_context) != 0) {
        return;
    }

    {
        Callback callback;

        callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (callback != 0) {
            callback(entity, motion, monster, entity);
        }
    }
    D_80176138[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, monster, entity);
    }

    monster_flags = ((S_8017103C_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        facing_angle = D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (facing_angle >> 9) & 7;
        ASM_KEEP(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((S_8017103C_0 *)monster)->unk_2C;

            if (tile_map != 0) {
                func_80047738(monster, tile_map[direction_index],
                              ((S_8017103C_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (D_8006CCF8[direction_copy] != 0) {
            ((S_8017103C_0 *)monster)->unk_14 |= 1;
        } else {
            ((S_8017103C_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(actor->unk_1C & 0x20)) {
            if (!(((S_8017103C_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((S_8017103C_0 *)monster)->unk_14 |= 0x7000;
        }

        if (!(actor->unk_1C & 0x10000000)) {
            if ((func_80042900(actor, 1) << 16) != 0) {
                s32 shade;
                s32 monster_state = ((S_8017103C_0 *)monster)->unk_04;

                if (monster_state != 0) {
                    goto nonzero_state;
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
                shade = 0x80;
                goto set_state_bytes;
nonzero_state:
                if (monster_state == 1) {
                    goto state_value_64;
                }
                if (monster_state == 2) {
                    shade = 0x50;
                    goto set_state_bytes;
                }
                if (monster_state != 3) {
                    goto flags_done;
                }
state_value_64:
                shade = 0x64;
set_state_bytes:
                ((S_8017103C_0 *)monster)->unk_0E = shade;
                ((S_8017103C_0 *)monster)->unk_0D = shade;
                ((S_8017103C_0 *)monster)->unk_0C = shade;
            } else {
                func_800A020C(actor->unk_1C,
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        if (monster_flags & 0x0800) {
            ((S_8017103C_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((S_8017103C_0 *)monster)->unk_14 = monster_flags | 0x7000;
        }
    }

flags_done:
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
                              (s16)(actor->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = actor->unk_88.s;
            if (!((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height)) {
                goto resolve_floor;
            }

            actor->unk_1C &= 0xF7FFFFFF;
            goto check_floor_adjustment;

resolve_floor:
            if (floor_height >= actor_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
            } else {
                (*(s16 *)((u8 *)entity + 0x92)) = floor_height - actor->unk_88.u;
            }

            motion->unk_14 = 0;
            actor->unk_1C |= 0x08000000;
            (*(u8 *)((u8 *)entity + 0x9D)) = 0;

check_floor_adjustment:
            if (actor->unk_1C & 0x40000000) {
                actor->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (((S_8017103C_0 *)monster)->unk_24 << 6) | 0x20,
                    (((S_8017103C_0 *)monster)->unk_25 << 6) | 0x20,
                    (s16)(actor->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    actor->unk_88.u - floor_height;
                actor->unk_88.u = floor_height;
            }
            goto finish;
        }
    }

clear_falling:
    actor->unk_1C &= 0xF7FFFFFF;

finish:
    motion->unk_0A =
        actor->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((S_8017103C_0 *)monster)->unk_14 |= 0x40;

    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(monster);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(direction);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(direction_copy);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: The 48-byte frame holds entity/motion/monster/actor in s2/s4/s1/s3
   and direction/direction_copy in s0/s5. Depinning raw_direction lets sra fill
   the first jal delay; a zero-arm entry barrier retains the bnez+j CFG and li slot. */
