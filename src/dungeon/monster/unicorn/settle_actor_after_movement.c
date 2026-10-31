#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/unicorn/settle_actor_after_movement.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

/* Advance the actor movement animation and settle it onto its destination tile. */
void settle_actor_after_movement(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 direction_x;
    s32 direction_y;
    s32 direction_offset;
    s32 state;
    s32 next_state;

    direction_offset = ((u16)actor->facing >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    direction_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    body->action_timer.u--;
    state = body->action_phase.u;

    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        (sprite->frameTable) = &D_80174D7C;
        select_sprite_entry(
            sprite,
            *(&D_80174D7C +
              (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
            0);
        {
            s32 shifted_x = direction_x << 19;
            motion->velocity_x = (direction_x << 17) - shifted_x;
        }
        {
            s32 shifted_y = direction_y << 19;
            motion->velocity_y = (direction_y << 17) - shifted_y;
        }
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->action_timer.u = 4;
        motion->velocity_z = (s32)0xFFFC0000;
        body->action_phase.u = body->action_phase.u + 1;
        return;

    case 1:
        body->unk_90.value += motion->velocity_z;
        motion->velocity_z += motion->velocity_z >> 2;
        if (body->action_timer.s > 0) {
            return;
        }

        (sprite->frameTable) = &D_80174D84;
        select_sprite_entry(
            sprite,
            *(&D_80174D84 +
              (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
            0);
        next_state = body->action_phase.u;
        body->action_timer.u = 8;
        body->action_phase.u = next_state + 1;
        return;

    case 2:
    {
        s32 velocity_x = motion->velocity_x;
        s32 velocity_y = motion->velocity_y;
        s32 velocity_z = motion->velocity_z;

        motion->velocity_x = velocity_x - (velocity_x >> 3);
        motion->velocity_y = velocity_y - (velocity_y >> 3);
        motion->velocity_z = velocity_z - (velocity_z >> 3);
    }
        if (body->action_timer.s == 4) {
            motion->velocity_x = 0;
            motion->velocity_y = 0;
            motion->velocity_z = 0;
        }
        if (body->action_timer.s > 0) {
            return;
        }
        body->action_timer.u = 4;
        motion->velocity_x = direction_x << 18;
        motion->velocity_y = direction_y << 18;
        play_sound_if_enabled(0x809);
        body->action_phase.u = body->action_phase.u + 1;
        return;

    case 3:
        body->unk_90.value += 0xC0000;
        motion->velocity_x += direction_x << 18;
        motion->velocity_y += direction_y << 18;
        if (body->action_timer.s > 0) {
            return;
        }
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        body->action_phase.u = body->action_phase.u + 1;
        return;

    case 4:
        body->unk_90.value += 0xC0000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = &D_80174D8C;
        select_sprite_entry(
            sprite,
            *(&D_80174D8C +
              (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
            0);
        motion->velocity_z = 0;
        body->unk_90.value = 0;
        body->action_state_flags &= 0xFFF7;
        actor->flags1C |= ACTOR_GROUNDED;
        body->action_phase.u = 0xFF;
        return;

    case 0xFF:
    {
        s32 tile_x = sprite->tile_x << 6;
        s32 position_x = motion->x.w.i - 0x20;
        motion->velocity_x = ((tile_x - position_x) << 15) >> 1;
    }
        {
            s32 tile_y = sprite->tile_y << 6;
            s32 position_y = motion->y.w.i - 0x20;
            motion->velocity_y = ((tile_y - position_y) << 15) >> 1;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.address = &unicorn_action_continuation_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
        } else {
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }

    }
}
