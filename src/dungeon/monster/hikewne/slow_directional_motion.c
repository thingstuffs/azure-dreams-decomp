#include "common.h"
#include "shared/sprite_frame_state.h"
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
} S_80173294_0;   /* arg0 in slow_directional_motion */

extern void set_record_integer_tile_center(void *, u8, u8);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_801714D4;
extern u8 D_80174148;

/* Slows directional motion, then recenters the entity on its tile. */
void slow_directional_motion(S_80173294_0 *motion_state, ObjectPosition *motion, Rec_D_80082E80 *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    switch (motion_state->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -*(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion->velocity_y =
            -*(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion_state->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, &D_80174148);
            return;
        }
        if (((SpriteFrameState *)tile_state)->flags & 0x8000) {
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
        x_speed_or_entity = motion->velocity_x;
        rounded_velocity = x_speed_or_entity;
        if (x_speed_or_entity < 0) {
            rounded_velocity = x_speed_or_entity + 3;
        }
        velocity_z = motion->velocity_y;
        motion->velocity_x = x_speed_or_entity - (rounded_velocity >> 2);

        rounded_velocity = velocity_z;
        motion->velocity_y = velocity_z - (rounded_velocity / 4);

        if (motion_state->unk_96.s > 0) {
            motion_state->unk_96.u = motion_state->unk_96.u - 1;
        } else if (((SpriteFrameState *)tile_state)->flags & 0x6000) {
            motion_state->unk_96.s = 0;
        }

        if (motion_state->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, &D_80174148);
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

            tile_coord = ((SpriteFrameState *)tile_state)->unk_24 << 6;
            offset_coord = motion->x.w.i;
            offset_coord -= 0x20;
            motion->velocity_x = ((tile_coord - offset_coord) << 15) / timer;

            offset_coord = motion->y.w.i;
            offset_coord -= 0x20;
            tile_coord = ((SpriteFrameState *)tile_state)->unk_25 << 6;
            motion->velocity_y =
                ((tile_coord - offset_coord) << 15) / motion_state->unk_96.s;
        }

        countdown = motion_state->unk_96.u - 1;
        motion_state->unk_96.p = countdown;
        if ((countdown << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)tile_state)->unk_24,
            ((SpriteFrameState *)tile_state)->unk_25);
        {

            x_speed_or_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (x_speed_or_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = x_speed_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C = &D_801714D4;
        return;

    default:
        return;
    }
}
