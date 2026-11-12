#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "dungeon/data.h"
#include "dungeon/monster/viper.h"

typedef struct S_80172F5C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172F5C_3;   /* rec in advance_motion_and_reset_action */

   /* arg2 in advance_motion_and_reset_action */

typedef struct S_80172F5C_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172F5C_7;   /* block in advance_motion_and_reset_action */



extern u8 viper_action_continuation_address[];

/* Advances an actor motion, waits for completion, and resets its action state. */
void advance_motion_and_reset_action(ActorRecord *state, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 saved_pos[3];
    u8 *motion;
    s16 use_player;
    ActorRecord *target;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    s32 wait_ticks;
    ObjectNodeHeader *action_state;
    SpriteFrameState *target_sprite;

    use_player = 0;
    switch (state->action_phase) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 7:
                use_player = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = 0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = 0;
                break;
            }
        }

        if (*motion != 0) {
            state->action_state_flags &= 0xFF7F;
            if (use_player != 0) {
                target = primary_actor_record;
                actor->target = target;
                target_sprite = NODE_HEADER(target)->sprite;
                actor->target_tile_x = target_sprite->tile_x;
                actor->target_tile_y = target_sprite->tile_y;
            } else if (item_action_definitions[*motion].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    target_sprite = NODE_HEADER(target)->sprite;
                    actor->target_tile_x = target_sprite->tile_x;
                    actor->target_tile_y = target_sprite->tile_y;
                }
            } else {
                actor->target =
                    scan_actor_along_heading(actor, sprite->tile_x, sprite->tile_y,
                                  actor->facing, 0x10);
                abs_x = abs(actor->target_tile_x);
                abs_y = abs(actor->target_tile_y);
                actor->target_tile_x = abs_x;
                actor->target_tile_y = abs_y;
            }
            saved_pos[0] = ((u16)transform->x.w.i);
            saved_pos[1] = ((u16)transform->y.w.i);
            saved_pos[2] = ((u16)transform->z.w.i);
            if (create_actor_spell_effect(actor, motion, use_player, (u8 *)state + 0x98) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            state->action_phase = state->action_phase + 1;
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4.value + 2)) = primary_actor_record->unk_A4.halves.high.u - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = actor->pending_turn_updates - 1;
        state->unk_8C.address = viper_action_continuation_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        state->action_phase = state->action_phase + 1;
    case 2:
        if ((sprite->unk_04 == 6 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            state->action_state_flags |= 0x80;
        }
        if ((sprite->unk_04 == 7 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            state->action_timer = 8;
        }
        wait_ticks = (u16)state->action_timer - 1;
        state->action_timer = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            state->action_timer = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);
        {
            u8 *direction_frames = viper_frame_set_2;

            if (*(unsigned char **)&sprite->frameTable != direction_frames) {
                (sprite->frameTable) = direction_frames;
                select_sprite_entry(sprite,
                    direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&g_dungeon_status.turn_scale;
        if (action_state->sprite != 0) {
            return;
        }
        ((S_80172F5C_7 *)action_state)->unk_0A = ((S_80172F5C_7 *)action_state)->unk_0A - 1;
        sprite->flags &= 0xF7FF;
        state->unk_8C.address = viper_action_continuation_address;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    }
}
