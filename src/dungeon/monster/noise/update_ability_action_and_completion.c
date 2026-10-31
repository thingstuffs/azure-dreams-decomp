#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "sdk/libc.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void spawn_random_velocity_offset_effect(ObjectNodeHeader *parent, s16 effect_id, s32 effect_param, s32 unused, s16 x_offset, s16 y_offset, s16 z_offset); /* extern */
void noise_ability_resume_address(ActorRecord *motion, ObjectPosition *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor);
extern u8 noise_direction_frames[9];

/* Updates an actor's ability action, effects, and completion state. */
/* Starts a targeted Noise spell, emits batches of ten offset particles during casting, then restores idle
 * and status. */
void update_ability_action_and_completion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 next_effect;
    s16 effect_count;
    s32 ability_id;
    s32 normal_ability;
    s16 use_player;
    u16 effect_ticks;
    u16 finish_ticks;
    u8 *ability;
    s32 phase;
    void *target;
    SpriteFrameState *target_sprite;

    phase = body->action_phase.u;
    use_player = 0;
    switch (phase) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            ability_id = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (ability_id) {
            case 7:
                use_player = 1;
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 6:
                use_player = 1;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 5:
                use_player = 1;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        } else {
            normal_ability = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (normal_ability) {
            case 3:
                ability = (u8 *)actor + 0xE;
                break;
            case 2:
                ability = (u8 *)actor + 0xB;
                break;
            case 1:
                ability = (u8 *)actor + 8;
                break;
            default:
                ability = NULL;
                break;
            }
        }
        if (*ability != 0) {
            body->action_state_flags &= 0xFF7F;
            {
                s32 player_target = use_player;
                if (player_target) {
                    target = primary_actor_record;
                    actor->target = target;
                    {
                        target_sprite =
                            ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                        actor->target_tile_x = target_sprite->tile_x;
                        actor->target_tile_y = target_sprite->tile_y;
                    }
                } else {
                    u8 *ability_table;
                    u8 ability_kind;
                    u32 ability_entry;

                    ability_kind = *ability;
                    ability_table = (u8 *)item_action_definitions;
                    ability_entry = ability_kind * 20;
                    ability_entry += (u32)ability_table;
                    if (((u8 *)ability_entry)[0x12] == 2) {
                        target = actor->target;
                        if (target != NULL) {
                            {
                                target_sprite =
                                    ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                                actor->target_tile_x = target_sprite->tile_x;
                                actor->target_tile_y = target_sprite->tile_y;
                            }
                        }
                    } else {
                        actor->target = scan_actor_along_heading(actor, sprite->tile_x,
                                          sprite->tile_y,
                                          actor->facing, 0x10);
                        actor->target_tile_x = abs(actor->target_tile_x);
                        actor->target_tile_y = abs(actor->target_tile_y);
                    }
                }
            }
            if (create_actor_spell_effect(actor, ability, use_player, ((void *)body) + 0x98) == 0) {
                return;
            }
            body->action_timer.u = 0x13U;
            body->action_phase.u = (u8) (body->action_phase.u + 1);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)&primary_actor_record->unk_A4.value + 2)) = (u16) (primary_actor_record->unk_A4.halves.high.u - 1);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            body->unk_8C.handler = &noise_ability_resume_address;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
            return;
        }
    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags = (u16) (sprite->flags
                | 0x800);
            return;
        }
        sprite->flags = (u16) (sprite->flags & 0xF7FF);
        body->action_phase.u = (u8) (body->action_phase.u + 1);
        play_sound_if_enabled(0x703);
    case 2:
        effect_ticks = body->action_timer.u - 1;
        body->action_timer.u = effect_ticks;
        if ((effect_ticks << 0x10) <= 0 || (sprite->flags & 0xE000)) {
            body->action_state_flags = (u16) (body->action_state_flags | 0x80);
            body->action_phase.u = (u8) (body->action_phase.u + 1);
            sprite->flags = (u16) (sprite->flags
                | 0x800);
            body->action_timer.u = 0xFU;
        }
        if ((u32) (body->action_timer.u - 9) >= 6U) {
            return;
        }
        effect_count = 0;
        do {
            spawn_random_velocity_offset_effect(((ObjectNodeHeader *)body - 1), 0, 0xC0C0, (rand() & 0xFF) | 0x80, 0, 0, 0);
            next_effect = effect_count + 1;
            effect_count = next_effect;
        } while (next_effect < 0xA);
        return;
    case 3:
        if ((g_dungeon_status.active_actor) == 0) {
            body->action_timer.u = 0U;
        }
        finish_ticks = body->action_timer.u - 1;
        body->action_timer.u = finish_ticks;
        if ((finish_ticks << 0x10) <= 0) {
            body->action_timer.u = 0U;
            sprite->flags =
                (u16) (sprite->flags & 0xF7FF);
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if ((*(M2C_UNK * *)&sprite->frameTable) != noise_direction_frames) {
            sprite->frameTable = noise_direction_frames;
            select_sprite_entry(sprite, noise_direction_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            sprite->flags =
                (u16) (sprite->flags & 0xF7FF);
        }
        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        body->unk_8C.handler = &noise_ability_resume_address;
        advance_status_timers(actor);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    }
}
