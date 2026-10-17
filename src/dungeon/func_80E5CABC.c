/* Relink of matched dungeon/func_80E38ABC; every changed retail word is a paired relocation. */
#define D_80170EE4 D_8014CEE4
#define D_801765F0 D_801525F0
#define D_801765F8 D_801525F8
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801722BC_0;   /* arg0 in func_8014E2BC */


extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A9A04(void *);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern s32 dungeonCheckActorFloorTrap(void *, void *);

extern u8 D_8014CEE4[];
extern u8 D_801525F0[];
extern u8 D_801525F8[];

/* Advance movement toward the target tile and finish the action when its timer expires. */
void func_8014E2BC(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 target_distance;
    s16 move_ticks;
    u16 timer_next;
    u8 phase;
    s32 actor_flags;
    s32 tile_delta;
    s32 axis_pos;
    DungeonGlobalStatus *action_counter;

    phase = ((S_801722BC_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        timer_next = ((S_801722BC_0 *)action)->unk_9E.s - 1;
        ((S_801722BC_0 *)action)->unk_9E.s = timer_next;
        if ((s16)timer_next > 0) {
            break;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801525F0;
        func_80047784(
            sprite,
            D_801525F0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_801722BC_0 *)action)->unk_9E.s = 5;
        ((S_801722BC_0 *)action)->unk_A0 = 0;
        ((S_801722BC_0 *)action)->unk_9B++;
                        /* fallthrough */

    case 1:
        ((S_801722BC_0 *)action)->unk_90 -= ((S_801722BC_0 *)action)->unk_A0;
        move_ticks = ((S_801722BC_0 *)action)->unk_9E.u;
        if (move_ticks != 0) {
            tile_delta = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            axis_pos = motion->x.w.i;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->unk_0C = (tile_delta << 16) / move_ticks;

            axis_pos = motion->y.w.i;
            tile_delta = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->unk_10 =
                (tile_delta << 16) / ((S_801722BC_0 *)action)->unk_9E.u;
            ((S_801722BC_0 *)action)->unk_A0 =
                (-func_800644B8(((S_801722BC_0 *)action)->unk_9E.u * 0x199)) << 9;
        }

        ((S_801722BC_0 *)action)->unk_90 += ((S_801722BC_0 *)action)->unk_A0;
        timer_next = ((S_801722BC_0 *)action)->unk_9E.s - 1;
        ((S_801722BC_0 *)action)->unk_9E.s = timer_next;
        if ((s16)timer_next < 0) {
            ((S_801722BC_0 *)action)->unk_90 = 0;
            ((S_801722BC_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_801722BC_0 *)action)->unk_9B++;
        }
                        /* fallthrough */

    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_801722BC_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                          ((Rec_D_80082E80 *)sprite)->unk_25);

            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801525F8;
            func_80047784(
                sprite,
                D_801525F8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)action)->unk_9B++;
        }
        break;
    }

    timer_next = ((S_801722BC_0 *)action)->unk_96 - 1;
    ((S_801722BC_0 *)action)->unk_96 = timer_next;
    if ((s16)timer_next <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)sprite)->unk_24,
                      ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);

        action_counter = &dungeonStatus;
        if (action_counter->unk_08 != 0) {
            (*(u16 *)&action_counter->unk_08)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->unk_46 & 0x8000) {
                actor->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing =
                    dungeonGetRoundedFacingAndRoundingFlag(((Rec_D_80082E80 *)sprite)->unk_24,
                                  ((Rec_D_80082E80 *)sprite)->unk_25,
                                  D_80082E80.tileX, D_80082E80.tileY, &target_distance);
            }
        }

        if ((dungeonCheckActorFloorTrap(sprite, actor) << 16) > 0) {
            ((S_801722BC_0 *)action)->unk_8C = D_8014CEE4;
            func_800A9A04(actor);
        }
    }
}
