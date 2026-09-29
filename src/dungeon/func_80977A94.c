#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173294_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; s16 p; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173294_0;   /* arg0 in func_80173294 */






extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_801714D4;
extern u8 D_80174148;

/* Slows directional motion, then recenters the entity on its tile. */
void func_80173294(S_80173294_0 *motion_state, EntityRec *motion, Rec_D_80082E80 *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    switch (motion_state->unk_9B) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C =
            -*(s16 *)((u8 *)((s8 *)dirStepX) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion->unk_10 =
            -*(s16 *)((u8 *)((s8 *)dirStepY) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion_state->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(motion_state, motion, tile_state, &D_80174148);
            return;
        }
        if (tile_state->unk_14.at00_u16.v & 0x8000) {
            motion_state->unk_96.s = 0;
            motion_state->unk_9B = 2;
            return;
        }
        timer = -1;
        if (((EntityRec *)entity)->flags1C & 0x228) {
            timer = 8;
        }
        motion_state->unk_96.s = timer;
        /* fall through */

    case 1:
        x_speed_or_entity = motion->unk_0C;
        rounded_velocity = x_speed_or_entity;
        if (x_speed_or_entity < 0) {
            rounded_velocity = x_speed_or_entity + 3;
        }
        velocity_z = motion->unk_10;
        motion->unk_0C = x_speed_or_entity - (rounded_velocity >> 2);

        rounded_velocity = velocity_z;
        if (velocity_z < 0) {
            rounded_velocity = velocity_z + 3;
        }
        motion->unk_10 = velocity_z - (rounded_velocity >> 2);

        if (motion_state->unk_96.s > 0) {
            motion_state->unk_96.u = motion_state->unk_96.u - 1;
        } else if (tile_state->unk_14.at00_u16.v & 0x6000) {
            motion_state->unk_96.s = 0;
        }

        if (motion_state->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(motion_state, motion, tile_state, &D_80174148);
            return;
        }
        motion_state->unk_96.s = 8;
        motion_state->unk_9B++;
        return;

    case 2:
        timer = motion_state->unk_96.s;
        if (timer != 0) {
            s32 tile_coord;
            s32 offset_coord;

            tile_coord = tile_state->unk_24 << 6;
            offset_coord = motion->x.w.i;
            offset_coord -= 0x20;
            motion->unk_0C = ((tile_coord - offset_coord) << 15) / timer;

            offset_coord = motion->y.w.i;
            offset_coord -= 0x20;
            tile_coord = tile_state->unk_25 << 6;
            motion->unk_10 =
                ((tile_coord - offset_coord) << 15) / motion_state->unk_96.s;
        }

        countdown = motion_state->unk_96.u - 1;
        motion_state->unk_96.p = countdown;
        if ((countdown << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, tile_state->unk_24,
            tile_state->unk_25);
        {

            x_speed_or_entity = ((s32)dungeonStatus.unk_10);
            if (x_speed_or_entity == (s32)((u8 *)entity - 0x20)) {
                dungeonStatus.unk_10 = x_speed_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C = &D_801714D4;
        return;

    default:
        return;
    }
}
