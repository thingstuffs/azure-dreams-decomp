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
#include "shared/object_links.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

typedef struct S_8016C190_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016C190_0;   /* arg0 in advance_selected_actor_action */

   /* the 0x14 bytes before v0 in advance_selected_actor_action, addressed as v0[-1] */
typedef struct S_8016C190_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8016C190_5;   /* control in advance_selected_actor_action */


extern s32 abs(s32);
extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);

extern void beldo_large_action_resume_address(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
extern u8 beldo_large_frame_set_2[];
extern u8 beldo_large_frame_set_5[];
extern u8 beldo_large_frame_set_1[];
extern u8 beldo_large_frame_set_3[];

/* Advances the selected actor action through targeting, animation, and cleanup. */
/* Starts Beldo's targeted spell with an eight-tick casting wait, then restores the current form's idle
 * frames and status. */
void advance_selected_actor_action(ActorRecord *action, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 action_state;
    u8 *action_slot;
    u8 *direction_table;
    u8 *action_control;
    s32 target_mode;
    s32 flagged_action;
    s32 action_kind;
    s32 action_value;
    s32 target_y;
    s32 magnitude_x;
    s16 mode_copy;
    void *current_table;

    action_state = action->action_phase.u;
    target_mode = 0;

    switch (action_state) {
    case 0:
        if (((u32)actor->flags1C) & ACTOR_PLAYER_SIDE) {
            flagged_action = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (flagged_action) {
            case 7:
                target_mode = 1;
                /* fall through */
            case 3:
                action_slot = (u8 *)actor + 0xE;
                break;
            case 6:
                target_mode = 1;
                /* fall through */
            case 2:
                action_slot = (u8 *)actor + 0xB;
                break;
            case 5:
                target_mode = 1;
                /* fall through */
            case 1:
                action_slot = (u8 *)actor + 8;
                break;
            default:
                action_slot = 0;
                break;
            }
        } else {
            action_kind = actor->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action_kind) {
            case 3:
                action_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                action_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                action_slot = (u8 *)actor + 8;
                break;
            default:
                action_slot = 0;
                break;
            }
        }
        if (*action_slot != 0) {
            action_value = action->action_state_flags & 0xFF7F;
            action->action_state_flags = action_value;
            mode_copy = target_mode;
            if (mode_copy != 0) {
                action_value = (s32)primary_actor_record;
                actor->target = (void *)action_value;
                action_control = (u8 *)((SpriteLinkPrefixView *)action_value)[-1].sprite;
                actor->target_tile_x = action_control[0x24];
                actor->target_tile_y = action_control[0x25];
            } else {
                u8 *action_defs = item_action_definitions;
                action_value = (s32)(action_defs + *action_slot * 20);
                if (((u8 *)action_value)[0x12] == 2) {
                    action_value = (s32)actor->target;
                    if (action_value != 0) {
                        action_control = (u8 *)((SpriteLinkPrefixView *)action_value)[-1].sprite;
                        actor->target_tile_x = action_control[0x24];
                        actor->target_tile_y = action_control[0x25];
                    }
                } else {
                    actor->target = scan_actor_along_heading(
                        actor,
                        sprite->tile_x,
                        sprite->tile_y,
                        actor->facing,
                        0x10);
                    magnitude_x = abs(actor->target_tile_x);
                    target_y = abs(actor->target_tile_y);
                    actor->target_tile_x = magnitude_x;
                    actor->target_tile_y = target_y;
                }
            }

            if (create_actor_spell_effect(actor, action_slot, target_mode,
                              (u16 *)((u8 *)action + 0x98)) != 0) {
                action->action_timer.s = 8;
                action->action_phase.u++;
            }
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        action->unk_8C.address = beldo_large_action_resume_address;
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
        action->action_phase.u++;
        play_sound_if_enabled(0x703);
                        /* fall through */

    case 2:
        action->action_timer.u--;
        if ((s16)action->action_timer.u > 0 &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        action->action_state_flags |= 0x80;
        action->action_phase.u++;
        return;

    case 3:
        if ((g_dungeon_status.active_actor) == 0) {
            action->action_timer.s = 0;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        transform->velocity_z = 0;
        transform->velocity_y = 0;
        transform->velocity_x = 0;
        set_record_integer_tile_center(transform, sprite->tile_x, sprite->tile_y);

        switch (action->unk_AC.byte) {
        case 0:
            current_table = sprite->frameTable;
            direction_table = beldo_large_frame_set_2;
            if ((u8 *)current_table != direction_table) {
                (sprite->frameTable) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 1:
            current_table = sprite->frameTable;
            direction_table = beldo_large_frame_set_5;
            if ((u8 *)current_table != direction_table) {
                (sprite->frameTable) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 2:
            current_table = sprite->frameTable;
            direction_table = beldo_large_frame_set_1;
            if ((u8 *)current_table != direction_table) {
                (sprite->frameTable) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        case 3:
            current_table = sprite->frameTable;
            direction_table = beldo_large_frame_set_3;
            if ((u8 *)current_table != direction_table) {
                (sprite->frameTable) = direction_table;
                select_sprite_entry(sprite, *(u8 *)((unsigned long)(((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (unsigned long)direction_table), 0);
            }
            break;
        default:
            break;
        }

        action_control = (u8 *)&g_dungeon_status.turn_scale;
        if (((ObjectNodeHeader *)action_control)->sprite != 0) {
            return;
        }
        ((S_8016C190_5 *)action_control)->unk_0A--;
        action->unk_8C.address = beldo_large_action_resume_address;
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;

    default:
        return;
    }
}
