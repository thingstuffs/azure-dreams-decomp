#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801730C4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
    u8 pad_AA[0x6];
    u8 unk_B0;
} S_801730C4_0;   /* arg0 in func_801730C4 */


typedef struct S_801730C4_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801730C4_2;   /* arg3 in func_801730C4 */


typedef struct S_801730C4_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801730C4_4;   /* global in func_801730C4 */



extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);
extern void func_801708B8(void *, void *, void *);

extern u8 D_800E23E0[];
extern u8 D_800E2458[];
extern u8 D_800E2460[];
extern u8 D_80171A80[];

/* Updates timed actor movement, landing animations, and the next action. */
void func_801730C4(void *action, void *motion, void *sprite, void *actor)
{
    s32 target_distance;
    s32 phase;

    phase = ((S_801730C4_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        {
            u8 *anim_table = D_800E2458;

            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                anim_table[((gameWork.view.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                1);
        }
        ((S_801730C4_0 *)action)->unk_98 |= 8;
        ((S_801730C4_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801730C4_0 *)action)->unk_A8 = 5;
        ((S_801730C4_0 *)action)->unk_A4 = 0;
        ((S_801730C4_0 *)action)->unk_9B++;
        /* fallthrough */
    case 1:
        {
            s32 move_ticks;
            s16 next_move_ticks;

            move_ticks = ((S_801730C4_0 *)action)->unk_A8;
            ((S_801730C4_0 *)action)->unk_90.at00.v -= ((S_801730C4_0 *)action)->unk_A4;
            if (move_ticks != 0) {
                s32 tile_delta;
                s32 axis_pos;

                tile_delta = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                axis_pos = ((EntityRec *)motion)->x.w.i;
                axis_pos -= 0x20;
                tile_delta -= axis_pos;
                ((EntityRec *)motion)->unk_0C = (tile_delta << 16) / move_ticks;

                axis_pos = ((EntityRec *)motion)->y.w.i;
                tile_delta = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                axis_pos -= 0x20;
                tile_delta -= axis_pos;
                ((EntityRec *)motion)->unk_10 =
                    (tile_delta << 16) / ((S_801730C4_0 *)action)->unk_A8;
                ((S_801730C4_0 *)action)->unk_A4 =
                    -func_800644B8(((S_801730C4_0 *)action)->unk_A8 * 0x199) << 9;
            }

            ((S_801730C4_0 *)action)->unk_90.at00.v += ((S_801730C4_0 *)action)->unk_A4;
            next_move_ticks = (u16)((S_801730C4_0 *)action)->unk_A8 - 1;
            ((S_801730C4_0 *)action)->unk_A8 = next_move_ticks;
            if (next_move_ticks < 0) {
                ((S_801730C4_0 *)action)->unk_90.at02.v = -0x10;
                ((S_801730C4_0 *)action)->unk_98 &= 0xFFF7;
                ((S_801730C4_2 *)actor)->unk_1C.s |= 0x08000000;
                ((S_801730C4_0 *)action)->unk_9B++;
            }
        }
        /* fallthrough */
    case 2:
        if (((S_801730C4_2 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801730C4_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            {
                u8 *anim_table = D_800E2460;

                (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_801730C4_0 *)action)->unk_9B++;
        }
        break;
    case 3:
        {
        u8 *anim_table = D_800E23E0;

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != anim_table) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(sprite,
                anim_table[((gameWork.view.viewAngle + ((S_801730C4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_801730C4_0 *)action)->unk_B0 == 0) {
                func_801708B8(action, motion, sprite);
            }
        }
    }
    break;
    }

    {
        u16 action_ticks;

        action_ticks = ((S_801730C4_0 *)action)->unk_96 - 1;
        ((S_801730C4_0 *)action)->unk_96 = action_ticks;
        if ((action_ticks << 16) > 0) {
            return;
        }
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x10);
    func_800A4ACC(actor);
    {

        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 = (u16)dungeonStatus.unk_08 - 1;
        }
    }
    {
        s32 actor_flags = ((S_801730C4_2 *)actor)->unk_1C.u;

        if (actor_flags & 0x2000) {
            if (((S_801730C4_2 *)actor)->unk_46 & 0x8000) {
                ((S_801730C4_2 *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((S_801730C4_2 *)actor)->unk_2A = func_800A0818(
                    ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &target_distance);
            }
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) <= 0) {
        return;
    }
    ((S_801730C4_0 *)action)->unk_8C = D_80171A80;
    func_800A9A04(actor);
}
