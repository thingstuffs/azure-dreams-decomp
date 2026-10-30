#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"

extern void select_sprite_entry(void *, u8, s32);

extern u8 kid_action_resume_address[];
extern u8 kid_alt_direction_frames[];
extern u8 D_80175158[];

/* Updates directional hop motion and returns the actor to its tile on landing. */
void complete_directional_hop_to_tile(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s16 flight_timer;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;

    direction = (actor->movement_facing >> 9) & 7;

    switch (body->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, D_80175158);
            return;
        }

        if (sprite->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 2;
            return;
        }

        motion->velocity_x = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        motion->velocity_y = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        motion->velocity_z = 0x40000;
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        actor->flags1C &= 0xFFFBFFFF;
        body->action_phase.u++;

        flight_timer = -1;
        if (((u32)actor->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            flight_timer = 8;
        }
        body->action_timer.s = flight_timer;

        velocity_x = motion->velocity_x;
        rounded_velocity_x = velocity_x;
        if (velocity_x < 0) {
            rounded_velocity_x = velocity_x + 3;
        }
        velocity_y = motion->velocity_y;
        motion->velocity_x = velocity_x - (rounded_velocity_x >> 2);
        rounded_velocity_y = velocity_y;
        motion->velocity_y = velocity_y - (rounded_velocity_y / 4);
        return;

    case 1:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (body->action_timer.s > 0) {
            body->action_timer.u--;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.s = 0;
        }
        if (body->action_timer.s != 0) {
            return;
        }
        if (actor->hp == 0) {
            body->action_phase.u = 0;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, D_80175158);
            return;
        }
        body->action_timer.s = 8;
        body->action_phase.u++;
        return;

    case 2:
        motion->velocity_z = 0xFFFE0000;
        if (body->action_timer.s != 0) {
            s32 tile_delta;
            s32 position;

            tile_delta = sprite->tile_x << 6;
            position = motion->x.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            motion->velocity_x = tile_delta >> 1;
            tile_delta = sprite->tile_y << 6;
            position = motion->y.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            motion->velocity_y = tile_delta >> 1;
            motion->velocity_x += motion->velocity_x >> 1;
            motion->velocity_y += motion->velocity_y >> 1;
        }

        {
            s16 landing_timer = (u16)body->action_timer.s - 1;

            body->action_timer.s = landing_timer;
            if (landing_timer > 0) {
                return;
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        body->unk_90.value = 0;
        body->action_state_flags &= 0xFFF7;
        actor->flags1C |= ACTOR_GROUNDED;
        actor->flags1C |= 0x00040000;
        sprite->frameTable = kid_alt_direction_frames;
        select_sprite_entry(sprite,
            kid_alt_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        {
            DungeonGlobalStatus *global_state = &g_dungeon_status;

            if (((s32)global_state->pending_display_owner) == (u8 *)actor - 0x20) {
                (*(u32 *)&global_state->pending_display_owner) &= 0x7FFFFFFF;
            }
        }
        body->unk_8C.address = kid_action_resume_address;
        return;

    default:
        return;
    }
}
