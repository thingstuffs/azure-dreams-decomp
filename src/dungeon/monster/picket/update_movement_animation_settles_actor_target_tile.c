#include "common.h"
#include "dungeon/monster/picket.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

typedef struct Node Node;

extern Node *actor_update_node_cursor[];
extern u8 picket_action_resume_address[];
extern u8 picket_frame_set_7;

/* Updates movement animation and settles the actor at its target tile. */
void update_movement_animation_settles_actor_target_tile(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 state;
    s32 direction_offset;
    s32 direction_x;
    s32 direction_y;
    u16 frames_left;

    direction_offset = ((u16)actor->facing >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    direction_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    state = body->action_phase.u;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        sprite->frameTable = &picket_frame_set_7;
        select_sprite_entry(sprite,
            *(&picket_frame_set_7 +
              (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
            0);
        body->action_phase.u++;
        return;
    case 1:
        if ((sprite->unk_04 == state &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            play_sound_if_enabled(0x808);
            body->unk_90.value = 0;
            body->action_state_flags |= 8;
            motion->velocity_z = (s32)0xFFF50000;
            body->action_timer.u = 4;
            motion->velocity_x = (direction_x << 23) / 5;
            motion->velocity_y = (direction_y << 23) / 5;
            body->action_phase.u++;
        }
        return;
    case 2:
        frames_left = body->action_timer.u - 1;
        body->action_timer.u = frames_left;
        if ((s16)frames_left == 3) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }

        motion->velocity_z += (5 - body->action_timer.s) << 16;
        if (body->action_timer.s < 3) {
            motion->velocity_z = 0;
        }
        motion->velocity_x -= (motion->velocity_x << 2) / 5;
        motion->velocity_y -= (motion->velocity_y << 2) / 5;
        if (body->action_timer.s > 0) {
            return;
        }
        motion->velocity_z = 0;
        body->action_phase.u = 0xFF;
        body->action_state_flags &= 0xFFF7;
        return;
    case 0xFF:
    {
        s32 target_x = sprite->tile_x << 6;
        s32 current_x = motion->x.w.i - 0x20;

        motion->velocity_x = (target_x - current_x) << 14;
    }
        {
            s32 target_y = sprite->tile_y << 6;
            s32 current_y = motion->y.w.i - 0x20;

            motion->velocity_y = (target_y - current_y) << 14;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.address = picket_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        } else {
            actor_update_node_cursor[0] = (Node *)((u8 *)actor - 0x20);
        }
        return;
    default:
        return;
    }
}
