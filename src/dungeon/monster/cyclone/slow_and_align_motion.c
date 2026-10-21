#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173770_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173770_0;   /* arg0 in slow_and_align_motion */

extern void set_record_integer_tile_center(void *, u8, u8);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_80171094;
extern u8 D_801764B0;

/* Slows directional motion, then aligns the entity to its tile and finishes the motion state. */
void slow_and_align_motion(S_80173770_0 *motion_state, ObjectPosition *motion, SpriteFrameState *tile, EntityRec *entity)
{
    s16 frames_left;
    s32 velocity_or_entity;
    s32 y_velocity;
    s32 division_bias;
    s32 state;
    s32 next_timer;

    state = motion_state->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((entity->unk_6A >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((entity->unk_6A >> 8) & 0xE)) << 19;
        motion_state->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile, &D_801764B0);
            return;
        }
        if (tile->flags & 0x8000) {
            motion_state->unk_96.s = 0;
            motion_state->unk_9B = 2;
            return;
        }
        frames_left = -1;
        if (entity->flags1C & 0x228) {
            frames_left = 8;
        }
        motion_state->unk_96.s = frames_left;
    case 1:
        velocity_or_entity = motion->velocity_x;
        division_bias = velocity_or_entity;
        if (velocity_or_entity < 0) {
            division_bias = velocity_or_entity + 3;
        }
        y_velocity = motion->velocity_y;
        motion->velocity_x = velocity_or_entity - (division_bias >> 2);

        division_bias = y_velocity;
        motion->velocity_y = y_velocity - (division_bias / 4);

        if (motion_state->unk_96.s > 0) {
            motion_state->unk_96.u = motion_state->unk_96.u - 1;
        } else if (tile->flags & 0x6000) {
            motion_state->unk_96.s = 0;
        }

        if (motion_state->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile, &D_801764B0);
            return;
        } else {
            motion_state->unk_96.s = 8;
            motion_state->unk_9B++;
            return;
        }
    case 2:
        frames_left = motion_state->unk_96.s;
        if (frames_left > 0) {
            s32 tile_coord;
            s32 coord_offset;

            tile_coord = tile->unk_24 << 6;
            coord_offset = motion->x.w.i;
            coord_offset -= 0x20;
            motion->velocity_x = ((tile_coord - coord_offset) << 16) / frames_left;

            coord_offset = motion->y.w.i;
            coord_offset -= 0x20;
            tile_coord = tile->unk_25 << 6;
            motion->velocity_y =
                ((tile_coord - coord_offset) << 16) / motion_state->unk_96.s;
        }

        next_timer = motion_state->unk_96.u - 1;
        motion_state->unk_96.u = next_timer;
        if ((next_timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->unk_24,
            tile->unk_25);
        {

            velocity_or_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (velocity_or_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = velocity_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C = &D_80171094;
    default:
        return;
    }
}
