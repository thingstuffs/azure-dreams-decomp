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

void func_8017103C(void *a0, void *a1, void *a2)
{
    register void *entity ASM_REG("$18") = a0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_8017103C_2 *motion = a1;
    void *monster = a2;
    S_8017103C_1 *actor = entity;
    register u32 raw_direction ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 direction ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 direction_copy ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 direction_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register void *call0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call2;
    void *call3;
    s32 direction_index;
    u16 flags;
    s16 floor;
    s16 actor_height;

    if (D_80083462 & 0x2000) {
        Callback first_callback;

        ASM_KEEP(entity);   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(actor);   /* MATCH pin: retail delay-slot contents depend on it */
        first_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (first_callback == (Callback)&D_801714B8) {
            first_callback(a0, a1, a2, a0);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    ASM_KEEP(entity);   /* MATCH pin: retail register colouring depends on it */

    call0 = entity;
    call1 = motion;
    call2 = monster;
    raw_direction = (*(volatile u8 *)((u8 *)entity + 0x6D));
    call3 = entity;
    raw_direction <<= 24;
    direction = (s32)raw_direction >> 24;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
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

    flags = ((S_8017103C_0 *)monster)->unk_14;
    if (!(flags & 0x8000)) {
        direction_value = D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        ASM_KEEP(direction);   /* MATCH pin: retail delay-slot fill depends on it */
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
                s32 value;
                s32 state = ((S_8017103C_0 *)monster)->unk_04;

                if (state != 0) {
                    goto nonzero_state;
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
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
                ((S_8017103C_0 *)monster)->unk_0E = value;
                ((S_8017103C_0 *)monster)->unk_0D = value;
                ((S_8017103C_0 *)monster)->unk_0C = value;
            } else {
                func_800A020C(actor->unk_1C,
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        if (flags & 0x0800) {
            ((S_8017103C_0 *)monster)->unk_14 = flags & 0x8FFF;
        } else {
            ((S_8017103C_0 *)monster)->unk_14 = flags | 0x7000;
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
        floor = func_800BCB04(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(actor->unk_88.u - 0x20));
        if (floor < 0x200) {
            actor_height = actor->unk_88.s;
            if (!((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor)) {
                goto resolve_floor;
            }

            actor->unk_1C &= 0xF7FFFFFF;
            goto check_floor_adjustment;

resolve_floor:
            if (floor >= actor_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
            } else {
                (*(s16 *)((u8 *)entity + 0x92)) = floor - actor->unk_88.u;
            }

            motion->unk_14 = 0;
            actor->unk_1C |= 0x08000000;
            (*(u8 *)((u8 *)entity + 0x9D)) = 0;

check_floor_adjustment:
            if (actor->unk_1C & 0x40000000) {
                actor->unk_1C &= 0xBFFFFFFF;
                floor = func_800BCB04(
                    (((S_8017103C_0 *)monster)->unk_24 << 6) | 0x20,
                    (((S_8017103C_0 *)monster)->unk_25 << 6) | 0x20,
                    (s16)(actor->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    actor->unk_88.u - floor;
                actor->unk_88.u = floor;
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

    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(monster);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(direction);   /* MATCH pin: retail delay-slot fill depends on it */
    ASM_KEEP(direction_copy);   /* MATCH pin: retail delay-slot fill depends on it */
}

/* MECHANISM: The 48-byte frame holds entity/motion/monster/actor in s2/s4/s1/s3
   and direction/direction_copy in s0/s5. Depinning raw_direction lets sra fill
   the first jal delay; a zero-arm entry barrier retains the bnez+j CFG and li slot. */
