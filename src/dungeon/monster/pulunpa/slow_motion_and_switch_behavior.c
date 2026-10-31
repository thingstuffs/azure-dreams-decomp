#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern u8 pulunpa_action_resume_address[];
extern u8 pulunpa_variant_action_address[];
extern u8 D_80176318[];
extern u8 D_80176378[];

/* Slows directional motion, returns the entity to its tile, and switches behavior. */
void slow_motion_and_switch_behavior(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity)
{
    s32 mark_value;
    s32 tracked_entity;

    mark_value = 1;
    switch (body->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        body->action_phase.u++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (body->unk_A4.bytes[3] != 0) {
                begin_actor_display_action(body, motion, sprite, D_80176378);
                if (body->unk_A8.byte != 0) {
                    u8 *mark_base;

                    mark_base = ((u8 *)dungeon_actor_ring_anchor);
                    mark_base += body->unk_A8.byte;
                    mark_base[0xF9] = mark_value;
                }
                return;
            }
            begin_actor_display_action(body, motion, sprite, D_80176318);
            return;
        }

        if (sprite->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 2;
            return;
        }
        body->action_timer.s =
            (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) ? 8 : -1;
                        /* fall through */

    case 1:
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

        if (body->action_timer.s > 0) {
            body->action_timer.s = body->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.s = 0;
        }

        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (body->unk_A4.bytes[3] != 0) {
                begin_actor_display_action(body, motion, sprite, D_80176378);
                if (body->unk_A8.byte != 0) {
                    u8 *mark_base;

                    mark_base = ((u8 *)dungeon_actor_ring_anchor);
                    mark_base += body->unk_A8.byte;
                    mark_base[0xF9] = 1;
                }
                return;
            }
            begin_actor_display_action(body, motion, sprite, D_80176318);
            return;
        }
        body->action_timer.s = 8;
        body->action_phase.u++;
        return;

    case 2:
    {
        s32 x_step;
        s32 y_distance;
        s32 position_offset;
        s16 frames_left;
        u16 next_timer;

        frames_left = body->action_timer.s;
        if (frames_left > 0) {
            x_step = sprite->tile_x << 6;
            position_offset = motion->x.w.i - 0x20;
            x_step = (x_step - position_offset) << 16;
            x_step = x_step / frames_left;
            position_offset = motion->y.w.i - 0x20;
            motion->velocity_x = x_step;
            y_distance = (sprite->tile_y << 6) - position_offset;
            motion->velocity_y =
                (y_distance << 16) / body->action_timer.s;
        }

        next_timer = body->action_timer.u - 1;
        body->action_timer.s = next_timer;
        if ((s32)(next_timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        if (body->unk_A4.bytes[3] != 0) {
            body->unk_8C.address = pulunpa_variant_action_address;
        } else {
            body->unk_8C.address = pulunpa_action_resume_address;
        }
        return;
    }

    default:
        return;
    }
}
