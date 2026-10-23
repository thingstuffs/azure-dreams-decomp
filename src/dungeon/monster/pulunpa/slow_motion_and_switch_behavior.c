#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C10_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xB];
    u8 unk_A7;
    u8 unk_A8;
} S_80172C10_0;   /* arg0 in slow_motion_and_switch_behavior */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
extern u8 D_80176318[];
extern u8 D_80176378[];

/* Slows directional motion, returns the entity to its tile, and switches behavior. */
void slow_motion_and_switch_behavior(S_80172C10_0 *state, ObjectPosition *motion, SpriteFrameState *tile, void *entity)
{
    s32 mark_value;
    s32 tracked_entity;

    mark_value = 1;
    switch (state->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        state->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (state->unk_A7 != 0) {
                begin_actor_display_action(state, motion, tile, D_80176378);
                if (state->unk_A8 != 0) {
                    u8 *mark_base;

                    mark_base = ((u8 *)dungeon_actor_ring_anchor);
                    mark_base += state->unk_A8;
                    mark_base[0xF9] = mark_value;
                }
                return;
            }
            begin_actor_display_action(state, motion, tile, D_80176318);
            return;
        }

        if (tile->flags & 0x8000) {
            state->unk_96.s = 0;
            state->unk_9B = 2;
            return;
        }
        state->unk_96.s =
            (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) ? 8 : -1;
                        /* fall through */

    case 1:
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

        if (state->unk_96.s > 0) {
            state->unk_96.s = state->unk_96.u - 1;
        } else if (tile->flags & 0x6000) {
            state->unk_96.s = 0;
        }

        if (state->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (state->unk_A7 != 0) {
                begin_actor_display_action(state, motion, tile, D_80176378);
                if (state->unk_A8 != 0) {
                    u8 *mark_base;

                    mark_base = ((u8 *)dungeon_actor_ring_anchor);
                    mark_base += state->unk_A8;
                    mark_base[0xF9] = 1;
                }
                return;
            }
            begin_actor_display_action(state, motion, tile, D_80176318);
            return;
        }
        state->unk_96.s = 8;
        state->unk_9B++;
        return;

    case 2:
    {
        s32 x_step;
        s32 y_distance;
        s32 position_offset;
        s16 frames_left;
        u16 next_timer;

        frames_left = state->unk_96.s;
        if (frames_left > 0) {
            x_step = tile->tile_x << 6;
            position_offset = motion->x.w.i - 0x20;
            x_step = (x_step - position_offset) << 16;
            x_step = x_step / frames_left;
            position_offset = motion->y.w.i - 0x20;
            motion->velocity_x = x_step;
            y_distance = (tile->tile_y << 6) - position_offset;
            motion->velocity_y =
                (y_distance << 16) / state->unk_96.s;
        }

        next_timer = state->unk_96.u - 1;
        state->unk_96.s = next_timer;
        if ((s32)(next_timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        if (state->unk_A7 != 0) {
            state->unk_8C = pulunpa_variant_action_address;
        } else {
            state->unk_8C = pulunpa_action_resume_address;
        }
        return;
    }

    default:
        return;
    }
}
