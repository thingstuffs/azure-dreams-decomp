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
extern int abs(int);

typedef struct S_80172A04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172A04_0;   /* arg0 in advance_actor_motion_sequence */

typedef struct S_80172A04_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172A04_3;   /* rec in advance_actor_motion_sequence */

   /* arg2 in advance_actor_motion_sequence */

typedef struct S_80172A04_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172A04_7;   /* block in advance_actor_motion_sequence */


extern void select_sprite_entry(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void *create_actor_spell_effect(void *actor, void *effect_record, s16 mode, void *context);
extern void create_two_row_object_group(void *, s16);

extern u8 battnel_action_resume_address[];
#include "dungeon/monster/battnel.h"
#include "dungeon/item.h"

/* Advances an actor motion through setup, playback, and completion. */
void advance_actor_motion_sequence(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 effect_pos[4];
    u8 *motion;
    s16 special_motion;
    ActorRecord *target;
    s32 ticks_left;
    ObjectNodeHeader *action_state;

    special_motion = 0;
    switch (state->action_phase.u) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 7:
                special_motion = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                special_motion = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                special_motion = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
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
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            state->action_state_flags &= 0xFF7F;
            {
                s16 use_special = special_motion;
                if (use_special != 0) {
                    target = primary_actor_record;
                    actor->target = target;
                    action_state = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                    actor->target_tile_x = ((S_80172A04_3 *)action_state)->unk_24;
                    actor->target_tile_y = ((S_80172A04_3 *)action_state)->unk_25;
                } else if (item_action_definitions[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_state = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                        actor->target_tile_x = ((S_80172A04_3 *)action_state)->unk_24;
                        actor->target_tile_y = ((S_80172A04_3 *)action_state)->unk_25;
                    }
                } else {
                    actor->target =
                        scan_actor_along_heading(actor, sprite->tile_x, sprite->tile_y,
                                      actor->facing, 0x10);
                    actor->target_tile_x = abs(actor->target_tile_x);
                    actor->target_tile_y = abs(actor->target_tile_y);
                }
            }
            effect_pos[0] = ((u16)position->x.w.i);
            effect_pos[1] = ((u16)position->y.w.i);
            effect_pos[2] = ((u16)position->z.w.i);
            position = (void *)create_actor_spell_effect(actor, motion, special_motion, (u8 *)state + 0x98);
            if (position == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(effect_pos, (*motion - 1) % 3);
            state->action_phase.u = state->action_phase.u + 1;
            return;
        }

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4 + 2)) = (*(u16 *)((u8 *)primary_actor_record + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        state->unk_8C.address = battnel_action_resume_address;
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
        state->action_phase.u = state->action_phase.u + 1;
                                /* fallthrough */
    case 2:
        if ((sprite->unk_04 == 4 && (sprite->flags & 0x1000)) ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            state->action_timer.u = 0x6;
            state->action_state_flags |= 0x80;
        }
        ticks_left = state->action_timer.u - 1;
        state->action_timer.u = ticks_left;
        if ((s16)ticks_left <= 0) {
            state->action_timer.u = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        {
            u8 *direction_table = battnel_direction_frames;

            if (*(unsigned char **)&sprite->frameTable != direction_table) {
                (sprite->frameTable) = direction_table;
                select_sprite_entry(sprite,
                    direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&g_dungeon_status.turn_scale;
        if (action_state->sprite != 0) {
            return;
        }
        ((S_80172A04_7 *)action_state)->unk_0A = ((S_80172A04_7 *)action_state)->unk_0A - 1;
        sprite->flags &= 0xF7FF;
        state->unk_8C.address = battnel_action_resume_address;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    }
}
