/* Relink of matched dungeon/func_80CBE9B0; every changed retail word is a paired relocation. */
#define dungeonAnimateHopToActorTile func_801661B0
#define D_80170F20 D_80164F20
#define D_801762D8 D_8016A2D8
#define D_801762E0 D_8016A2E0
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_800A5DFC_arg1.h"

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
} S_801721B0_0;   /* arg0 in func_801661B0 */


typedef struct S_801721B0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801721B0_4;   /* global in func_801661B0 */


extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A5DFC(void *, void *);
extern void func_800A9A04(void *);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern s32 dungeonCheckActorFloorTrap(void *, void *);

extern u8 D_80164F20[];
extern u8 D_8016A2D8[];
extern u8 D_8016A2E0[];

/* Animate a hop to the actor's tile and finish the action when its timer expires. */
void func_801661B0(void *action, void *motion, void *sprite, void *actor)
{
    s32 target_distance;
    s32 tile_origin_y;
    s32 hop_frames;
    s32 next_hop_frame;
    s32 actor_flags;
    u16 action_timer;
    s32 phase;

    phase = ((S_801721B0_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016A2D8;
            func_80047784(
                sprite,
                D_8016A2D8[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >>
                            9) &
                           7],
                0);
            ((S_801721B0_0 *)action)->unk_98 |= 8;
            ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
            ((S_801721B0_0 *)action)->unk_9E.s = 5;
            ((S_801721B0_0 *)action)->unk_A0 = 0;
            ((S_801721B0_0 *)action)->unk_9B++;
        } else {
            break;
        }
                        /* fallthrough */

    case 1:
        hop_frames = ((S_801721B0_0 *)action)->unk_9E.s;
        ((S_801721B0_0 *)action)->unk_90 =
            ((S_801721B0_0 *)action)->unk_90 - ((S_801721B0_0 *)action)->unk_A0;
        if (hop_frames != 0) {
            ((Rec_func_800A5DFC_arg1 *)motion)->unk_0C =
                (((((Rec_D_80082E80 *)sprite)->unk_24 << 6) -
                  ({ ((Rec_func_800A5DFC_arg1 *)motion)->unk_02 - 0x20; })) <<
                 0x10) /
                hop_frames;
            ((Rec_func_800A5DFC_arg1 *)motion)->unk_10 =
                (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) -
                  (tile_origin_y = ((Rec_func_800A5DFC_arg1 *)motion)->unk_06 - 0x20)) <<
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
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((S_801721B0_0 *)action)->unk_9B++;
        }

                        /* fallthrough */

    case 2:
        if (((EntityRec *)actor)->flags1C & 0x08000000) {
            ((S_801721B0_0 *)action)->unk_98 &= 0xFFF7;
            ((Rec_func_800A5DFC_arg1 *)motion)->unk_14 = 0;
            ((Rec_func_800A5DFC_arg1 *)motion)->unk_10 = 0;
            ((Rec_func_800A5DFC_arg1 *)motion)->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                          ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016A2E0;
            func_80047784(
                sprite,
                D_8016A2E0[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >>
                            9) &
                           7],
                0);
            ((S_801721B0_0 *)action)->unk_9B++;
        }

    }

    action_timer = ((S_801721B0_0 *)action)->unk_96 - 1;
    ((S_801721B0_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 0x10) <= 0) {
        ((Rec_func_800A5DFC_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_800A5DFC_arg1 *)motion)->unk_10 = 0;
        ((Rec_func_800A5DFC_arg1 *)motion)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                      ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);
        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08 = (u16)dungeonStatus.unk_08 - 1;
        }
        actor_flags = ((EntityRec *)actor)->flags1C;
        if (actor_flags & 0x2000) {
            u16 status_flags;

            status_flags = ((EntityRec *)actor)->unk_46;
            if (status_flags & 0x8000) {
                ((EntityRec *)actor)->unk_46 = status_flags & 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((EntityRec *)actor)->facing = dungeonGetRoundedFacingAndRoundingFlag(
                    ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &target_distance);
            }
        }
        func_800A5DFC(actor, motion);
        if ((dungeonCheckActorFloorTrap(sprite, actor) << 0x10) > 0) {
            ((S_801721B0_0 *)action)->unk_8C = D_80164F20;
            func_800A9A04(actor);
        }
    }
}
