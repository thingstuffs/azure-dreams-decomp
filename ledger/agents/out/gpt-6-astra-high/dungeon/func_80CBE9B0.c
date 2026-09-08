#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801721B0_0 {
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
    s32 unk_A0;
} S_801721B0_0;   /* arg0 in func_801721B0 */



typedef struct S_801721B0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801721B0_3;   /* arg1 in func_801721B0 */

typedef struct S_801721B0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801721B0_4;   /* global in func_801721B0 */



extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A5DFC(void *, void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170F20[];
extern u8 D_801762D8[];
extern u8 D_801762E0[];

/* Animate a hop to the actor's tile and finish the action when its timer expires. */
void func_801721B0(void *action, void *motion, void *sprite, void *actor)
{
    s32 target_distance;
    s32 tile_origin_y;
    s32 hop_frames;
    s32 next_hop_frame;
    s32 actor_flags;
    u16 action_timer;
    s32 phase;
    u8 *dungeon_state;

    phase = ((S_801721B0_0 *)action)->unk_9B;
    if (phase == 1) {
        goto state_one;
    }
    if (phase >= 2) {
        goto check_state_two;
    }
    if (phase == 0) {
        goto state_zero;
    }
    goto common_update;

check_state_two:
    if (phase == 2) {
        goto state_two;
    }
    goto common_update;

state_zero:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_801762D8;
        func_80047784(
            sprite,
            D_801762D8[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >>
                         9) &
                        7],
            0);
        ((S_801721B0_0 *)action)->unk_98 |= 8;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xF7FFFFFF;
        ((S_801721B0_0 *)action)->unk_9E.s = 5;
        ((S_801721B0_0 *)action)->unk_A0 = 0;
        ((S_801721B0_0 *)action)->unk_9B++;
        goto state_one;
    }
    goto common_update;

state_one:
    hop_frames = ((S_801721B0_0 *)action)->unk_9E.s;
    ((S_801721B0_0 *)action)->unk_90 =
        ((S_801721B0_0 *)action)->unk_90 - ((S_801721B0_0 *)action)->unk_A0;
    if (hop_frames != 0) {
        ((S_801721B0_3 *)motion)->unk_0C =
            (((((Rec_D_80082E80 *)sprite)->unk_24 << 6) -
              ({ ((S_801721B0_3 *)motion)->unk_02 - 0x20; })) <<
             0x10) /
            hop_frames;
        ((S_801721B0_3 *)motion)->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) -
              (tile_origin_y = ((S_801721B0_3 *)motion)->unk_06 - 0x20)) <<
             0x10) /
            ((S_801721B0_0 *)action)->unk_9E.s;
        ((S_801721B0_0 *)action)->unk_A0 =
            (-func_800644B8(((S_801721B0_0 *)action)->unk_9E.s * 0x199)) << 9;
    }
    ((S_801721B0_0 *)action)->unk_90 =
        ((S_801721B0_0 *)action)->unk_90 + ((S_801721B0_0 *)action)->unk_A0;
    next_hop_frame = ((S_801721B0_0 *)action)->unk_9E.u - 1;
    ((S_801721B0_0 *)action)->unk_9E.s = next_hop_frame;
    if ((s16)next_hop_frame < 0) {
        ((S_801721B0_0 *)action)->unk_90 = 0;
        ((S_801721B0_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 |= 0x08000000;
        ((S_801721B0_0 *)action)->unk_9B++;
    }

state_two:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x08000000) {
        ((S_801721B0_0 *)action)->unk_98 &= 0xFFF7;
        ((S_801721B0_3 *)motion)->unk_14 = 0;
        ((S_801721B0_3 *)motion)->unk_10 = 0;
        ((S_801721B0_3 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                     ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(void * *)((u8 *)sprite + 0x2C)) = D_801762E0;
        func_80047784(
            sprite,
            D_801762E0[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >>
                         9) &
                        7],
            0);
        ((S_801721B0_0 *)action)->unk_9B++;
    }

common_update:
    action_timer = ((S_801721B0_0 *)action)->unk_96 - 1;
    ((S_801721B0_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 0x10) <= 0) {
        ((S_801721B0_3 *)motion)->unk_14 = 0;
        ((S_801721B0_3 *)motion)->unk_10 = 0;
        ((S_801721B0_3 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                     ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        dungeon_state = (u8 *)&D_80083460;
        if (((S_801721B0_4 *)dungeon_state)->unk_08 != 0) {
            ((S_801721B0_4 *)dungeon_state)->unk_08 = (u16)((S_801721B0_4 *)dungeon_state)->unk_08 - 1;
        }
        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
        if (actor_flags & 0x2000) {
            u16 status_flags;

            status_flags = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v;
            if (status_flags & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = status_flags & 0x7FFF;
            }
            goto coordinate_done;
        }
        if (actor_flags & 0x410) {
            goto coordinate_done;
        }
        if (!(actor_flags & 0x20000)) {
            goto coordinate_done;
        }
        ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
            ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &target_distance);

coordinate_done:
        func_800A5DFC(actor, motion);
        if ((func_800AD9B4(sprite, actor) << 0x10) > 0) {
            ((S_801721B0_0 *)action)->unk_8C = D_80170F20;
            func_800A9A04(actor);
        }
    }
}
