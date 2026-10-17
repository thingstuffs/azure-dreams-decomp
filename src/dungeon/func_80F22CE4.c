/* Relink of matched dungeon/func_80F34BD4; every changed retail word is a paired relocation. */
#define D_80170E94 D_80158F74
#define D_80174A94 D_8015BD48
#define D_80174A9C D_8015BD50
/* Relink of matched dungeon/func_80CC1724; every changed retail word is a paired relocation. */
#define D_80173B98 D_80158F74
#define D_80176338 D_8015BD48
#define D_80176340 D_8015BD50
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80174F24_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_80174F24_0;   /* arg0 in func_8015A4E4 */

typedef struct S_80174F24_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80174F24_1;   /* arg2 in func_8015A4E4 */


typedef struct S_80174F24_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174F24_3;   /* arg1 in func_8015A4E4 */


extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void dungeonSetRecordIntegerTileCenter(void *, s32, s32);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A9A04(void *);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern s32 dungeonCheckActorFloorTrap(void *, void *);

extern s32 D_80158F74;
extern u8 D_8015BD48[];
extern u8 D_8015BD50[];

/* Updates the actor's movement animation and finishes the timed action. */
void func_8015A4E4(void *action, void *motion_arg, void *unit, void *actor)
{
    s32 direction_aux;
    u8 move_state;

    move_state = ((S_80174F24_0 *)action)->unk_9B;
    switch (move_state) {
    case 0:
        if (((S_80174F24_1 *)unit)->unk_14 & 0x6000) {
            u8 *direction_table = D_8015BD48;

            (*(u8 * *)((u8 *)unit + 0x2C)) = direction_table;
            func_80047784(unit,
                direction_table[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)action)->unk_98 |= 8;
            ((EntityRec *)actor)->flags1C &= ~0x08000000;
            ((S_80174F24_0 *)action)->unk_9E.s = 5;
            ((S_80174F24_0 *)action)->unk_A0 = 0;
            ((S_80174F24_0 *)action)->unk_9B++;
        } else {
            break;
        }
                        /* fall through */

    case 1:
    {
        s16 move_ticks;
        s32 target_delta;
        s32 axis_pos;
        s32 x_velocity;

        ((S_80174F24_0 *)action)->unk_90 -= ((S_80174F24_0 *)action)->unk_A0;
        move_ticks = ((S_80174F24_0 *)action)->unk_9E.s;
        if (move_ticks != 0) {
            target_delta = ((S_80174F24_1 *)unit)->unk_24 << 6;
            axis_pos = ((S_80174F24_3 *)motion_arg)->unk_02 - 0x20;
            target_delta -= axis_pos;
            x_velocity = (target_delta << 16) / move_ticks;

            axis_pos = ((S_80174F24_3 *)motion_arg)->unk_06;
            ((S_80174F24_3 *)motion_arg)->unk_0C = x_velocity;
            axis_pos -= 0x20;
            target_delta = ((S_80174F24_1 *)unit)->unk_25 << 6;
            target_delta -= axis_pos;
            ((S_80174F24_3 *)motion_arg)->unk_10 =
                (target_delta << 16) / ((S_80174F24_0 *)action)->unk_9E.s;

            ((S_80174F24_0 *)action)->unk_A0 =
                (-func_800644B8(((S_80174F24_0 *)action)->unk_9E.s * 409)) << 9;
        }

        ((S_80174F24_0 *)action)->unk_90 += ((S_80174F24_0 *)action)->unk_A0;
        move_ticks = ((S_80174F24_0 *)action)->unk_9E.u - 1;
        ((S_80174F24_0 *)action)->unk_9E.s = move_ticks;
        if (move_ticks < 0) {
            ((S_80174F24_0 *)action)->unk_90 = 0;
            ((S_80174F24_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((S_80174F24_0 *)action)->unk_9B++;
        }
    }
                        /* fall through */

    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & 0x08000000) {
            u8 *direction_table;

            ((S_80174F24_0 *)action)->unk_98 &= 0xFFF7;
            ((S_80174F24_3 *)motion_arg)->unk_14 = 0;
            ((S_80174F24_3 *)motion_arg)->unk_10 = 0;
            ((S_80174F24_3 *)motion_arg)->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion_arg,
                ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25);
            direction_table = D_8015BD50;
            (*(u8 * *)((u8 *)unit + 0x2C)) = direction_table;
            func_80047784(unit,
                direction_table[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)action)->unk_9B++;
        }
        break;

    default:
        break;
    }

    {
        s16 action_ticks;
        u32 actor_flags;

        action_ticks = ((S_80174F24_0 *)action)->unk_96.s - 1;
        ((S_80174F24_0 *)action)->unk_96.u = action_ticks;
        if (action_ticks > 0) {
            return;
        }

        ((S_80174F24_3 *)motion_arg)->unk_14 = 0;
        ((S_80174F24_3 *)motion_arg)->unk_10 = 0;
        ((S_80174F24_3 *)motion_arg)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion_arg,
            ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25);
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);

        if (dungeonStatus.unk_08 != 0) {
            dungeonStatus.unk_08--;
        }

        actor_flags = ((u32)((EntityRec *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((EntityRec *)actor)->unk_46 & 0x8000) {
                ((EntityRec *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((EntityRec *)actor)->facing = dungeonGetRoundedFacingAndRoundingFlag(
                    ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
            }
        }

        if ((dungeonCheckActorFloorTrap(unit, actor) << 16) > 0) {
            ((S_80174F24_0 *)action)->unk_8C = &D_80158F74;
            func_800A9A04(actor);
        }
    }
}
