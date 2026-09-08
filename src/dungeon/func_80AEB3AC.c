#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8014EBAC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_8014EBAC_0;   /* arg0 in func_8014EBAC */




typedef struct S_8014EBAC_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_8014EBAC_4;   /* global_base in func_8014EBAC */

typedef struct S_8014EBAC_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8014EBAC_5;   /* map_base in func_8014EBAC */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8014D728;
extern u8 D_80150DEC[];
extern u8 D_80150E0C[];
extern u8 D_80150E14[];

/* Updates the actor's hop toward its tile and completes the timed action. */
void func_8014EBAC(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 hop_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 hop_offset;
    s32 pos_y;
    s32 next_hop_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    u8 *global_base;
    u8 *map_base;

    state = ((S_8014EBAC_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150E0C;
    func_80047784(
        sprite,
        D_80150E0C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_8014EBAC_0 *)action)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_8014EBAC_0 *)action)->unk_9E.s = 5;
    ((S_8014EBAC_0 *)action)->unk_A4 = 0;
    ((S_8014EBAC_0 *)action)->unk_9B++;

state_one:
    hop_ticks = ((S_8014EBAC_0 *)action)->unk_9E.s;
    ((S_8014EBAC_0 *)action)->unk_90 -= ((S_8014EBAC_0 *)action)->unk_A4;
    if (hop_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        pos_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        target_x <<= 6;
        pos_x -= 0x20;

        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - pos_x) << 16) / hop_ticks;

        pos_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        pos_y -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
            ((S_8014EBAC_0 *)action)->unk_9E.s;

        ((S_8014EBAC_0 *)action)->unk_A4 =
            (-func_800644B8(((S_8014EBAC_0 *)action)->unk_9E.s * 0x199)) << 10;
    }

    height = ((S_8014EBAC_0 *)action)->unk_90;
    hop_offset = ((S_8014EBAC_0 *)action)->unk_A4;
    next_hop_ticks = ((S_8014EBAC_0 *)action)->unk_9E.u;
    height += hop_offset;
    next_hop_ticks -= 1;
    ((S_8014EBAC_0 *)action)->unk_9E.u = next_hop_ticks;
    ((S_8014EBAC_0 *)action)->unk_90 = height;
    if ((next_hop_ticks << 16) >= 0) {
        goto state_two;
    }

    ((S_8014EBAC_0 *)action)->unk_90 = 0;
    ((S_8014EBAC_0 *)action)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 |= 0x08000000;
    ((S_8014EBAC_0 *)action)->unk_9B++;

state_two:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x08000000) {
        ((S_8014EBAC_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150E14;
        func_80047784(
            sprite,
            D_80150E14[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_8014EBAC_0 *)action)->unk_9B++;
    }
    goto decrement_timer;

state_three:
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_80150DEC) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150DEC;
    func_80047784(
        sprite,
        D_80150DEC[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

decrement_timer:
    action_ticks = ((S_8014EBAC_0 *)action)->unk_96 - 1;
    ((S_8014EBAC_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_base = (u8 *)&D_80083460;
    if (((S_8014EBAC_4 *)global_base)->unk_08.s != 0) {
        ((S_8014EBAC_4 *)global_base)->unk_08.u--;
    }

    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
    if (actor_flags & 0x2000) {
        if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    map_base = D_80082E80;
    ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
        ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25,
        ((S_8014EBAC_5 *)map_base)->unk_24,
        ((S_8014EBAC_5 *)map_base)->unk_25,
        &facing_aux);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_8014EBAC_0 *)action)->unk_8C = &D_8014D728;
        func_800A9A04(actor);
    }
}
