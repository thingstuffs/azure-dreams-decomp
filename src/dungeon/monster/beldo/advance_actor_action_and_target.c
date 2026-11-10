#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/entity.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/data.h"

struct S_80170E18_3;

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0xA6];
    u16 field_A6;
} D800814A8FieldView_81252D6C;

extern void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, ActorRecord *facing_source);

extern u8 D_80173EDC[8];

typedef struct S_8017256C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017256C_5;   /* arg1 in advance_actor_action_and_target */

/* Advances an actor's action state, updating its target, animation, and completion. */
/* Starts a targeted Beldo spell, emits a sprite effect during its casting sequence, then recenters and
 * updates status. */
void advance_actor_action_and_target(ActorRecord *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    register s32 is_special = 0;
    u8 *action_entry;
    u32 state;
    u32 prior_state;
    s32 kind;
    u32 kind_index;
    u16 ticks;
    s32 next_ticks;
    void *target_link;

    state = action->action_phase;
    switch (state) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            kind_index = actor->action_flags & 0x3FFF;
            switch (kind_index) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                action_entry = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                action_entry = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                action_entry = (u8 *)actor + 8;
                break;
            default:
                action_entry = 0;
                break;
            }
        } else {
            kind = actor->action_flags & 0x3FFF;
            switch (kind) {
            case 3:
                action_entry = (u8 *)actor + 0xE;
                break;
            case 2:
                action_entry = (u8 *)actor + 0xB;
                break;
            case 1:
                action_entry = (u8 *)actor + 8;
                break;
            default:
                action_entry = 0;
                break;
            }
        }
        if (*action_entry != 0) {
            action->action_state_flags &= 0xFF7F;
            {
                u8 use_player_target = is_special;

                if (use_player_target) {
                    target_link = primary_actor_record;
                    actor->target = target_link;
                    kind = (s32)*(u8 * *)&((ObjectNodeHeader *)(target_link - 0x20))->sprite;

                    actor->target_tile_x = ((SpriteFrameState *)kind)->tile_x;
                    actor->target_tile_y = ((SpriteFrameState *)kind)->tile_y;
                } else if (item_action_definitions[*action_entry].kind == 2) {
                    target_link = actor->target;
                    if (target_link != 0) {
                        kind = (s32)*(u8 * *)&((ObjectNodeHeader *)(target_link - 0x20))->sprite;

                        actor->target_tile_x = ((SpriteFrameState *)kind)->tile_x;
                        actor->target_tile_y = ((SpriteFrameState *)kind)->tile_y;
                    }
                } else {
                    s32 x;
                    s32 abs_x;
                    s32 abs_y;
                    s32 y;

                    actor->target = scan_actor_along_heading(
                        actor,
                        sprite->tile_x,
                        sprite->tile_y,
                        actor->facing,
                        0x10);
                    abs_x = abs(actor->target_tile_x);
                    abs_y = abs(actor->target_tile_y);
                    actor->target_tile_x = abs_x;
                    actor->target_tile_y = abs_y;
                }
            }
            if (create_actor_spell_effect(actor, action_entry, is_special, (u8 *)action + 0x98) == 0) {
                return;
            }
            action->action_timer = 0;
            action->action_phase++;
            ((S_8017256C_5 *)motion)->unk_14 = 0;
            ((S_8017256C_5 *)motion)->unk_10 = 0;
            ((S_8017256C_5 *)motion)->unk_0C = 0;
            return;
        }
        ((S_8017256C_5 *)motion)->unk_14 = 0;
        ((S_8017256C_5 *)motion)->unk_10 = 0;
        ((S_8017256C_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        actor->pending_turn_updates--;
        action->unk_8C.handler = &update_object_animation;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase++;
        play_sound_if_enabled(0x703);

    case 2:
        ticks = action->action_timer;
        next_ticks = ticks + 1;
        action->action_timer = next_ticks;
        if ((s16)ticks < 8 && !(sprite->flags & 0x8000)) {
            return;
        }
        prior_state = action->action_phase;

        action->action_timer = 0;
        action->action_phase = prior_state + 1;
        return;

    case 3:
        if (action->unk_A0.parts.high != 0) {
            ticks = action->action_timer;
            next_ticks = ticks + 1;
            action->action_timer = next_ticks;
            if ((s16)ticks < 15 && !(sprite->flags & 0x8000)) {
                return;
            }
        }
        action->action_timer = 0;
        action->action_phase++;
        play_sound_if_enabled(0x703);
        (sprite->frameTable) = D_80173EDC;
        select_sprite_entry(
            sprite,
            D_80173EDC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        return;

    case 4:
        create_effect_from_sprite_and_facing(action, motion, sprite, actor);
        ticks = action->action_timer;
        next_ticks = ticks + 1;
        action->action_timer = next_ticks;
        if ((s16)ticks < 3 && !(sprite->flags & 0xE000)) {
            return;
        }
        sprite->flags |= 0x800;
        prior_state = action->action_phase;
        action->action_phase = prior_state + 1;
        return;

    case 5:
        sprite->flags |= 0x800;
        ticks = action->action_timer;
        next_ticks = ticks + 1;
        action->action_timer = next_ticks;
        if ((s16)ticks < 10 && !(sprite->flags & 0x8000)) {
            return;
        }
        action->action_timer = 0;
        action->action_phase++;
        sprite->flags &= 0xF7FF;
        return;

    case 6:
        action->action_state_flags |= 0x80;
        action->action_timer = 0;
        action->action_phase++;
        return;

    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        ((S_8017256C_5 *)motion)->unk_14 = 0;
        ((S_8017256C_5 *)motion)->unk_10 = 0;
        ((S_8017256C_5 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        action->action_phase++;
        if (*(u8 **)&sprite->frameTable == beldo_frame_set_1) {
            return;
        }
        (sprite->frameTable) = beldo_frame_set_1;
        select_sprite_entry(
            sprite,
            beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->unk_9E = 0;
        action->unk_90.parts.high = -0x20;
        return;

    case 8:
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            action->unk_8C.handler = &update_object_animation;
            advance_status_timers(actor);
            actor->pending_turn_updates--;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
        return;
    default:
        return;
    }
}
