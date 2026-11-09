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

extern s32 select_sprite_entry();
extern void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, struct S_80170E18_3 *facing_source);

extern u8 D_80173EDC[8];

typedef struct S_8017256C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * p; u8 * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    s8 unk_72;
    s8 unk_73;
} S_8017256C_1;   /* arg3 in advance_actor_action_and_target */


typedef struct S_8017256C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017256C_5;   /* arg1 in advance_actor_action_and_target */

/* Advances an actor's action state, updating its target, animation, and completion. */
/* Starts a targeted Beldo spell, emits a sprite effect during its casting sequence, then recenters and
 * updates status. */
void advance_actor_action_and_target(ActorRecord *action, void *motion, SpriteFrameState *sprite, void *actor)
{
    register s32 is_special = 0;
    u8 *action_entry;
    u32 state;
    u32 prior_state;
    s32 kind;
    u32 kind_index;
    u16 ticks;
    s32 next_ticks;
    u8 *target_link;

    state = action->action_phase;
    switch (state) {
    case 0:
        if (((S_8017256C_1 *)actor)->unk_1C & ACTOR_PLAYER_SIDE) {
            kind_index = ((S_8017256C_1 *)actor)->unk_46 & 0x3FFF;
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
            kind = ((S_8017256C_1 *)actor)->unk_46 & 0x3FFF;
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
                    ((S_8017256C_1 *)actor)->unk_60.p = target_link;
                    kind = (s32)*(u8 * *)&((ObjectNodeHeader *)(target_link - 0x20))->sprite;

                    ((S_8017256C_1 *)actor)->unk_72 = ((SpriteFrameState *)kind)->tile_x;
                    ((S_8017256C_1 *)actor)->unk_73 = ((SpriteFrameState *)kind)->tile_y;
                } else if (item_action_definitions[*action_entry].kind == 2) {
                    target_link = ((S_8017256C_1 *)actor)->unk_60.p2;
                    if (target_link != 0) {
                        kind = (s32)*(u8 * *)&((ObjectNodeHeader *)(target_link - 0x20))->sprite;

                        ((S_8017256C_1 *)actor)->unk_72 = ((SpriteFrameState *)kind)->tile_x;
                        ((S_8017256C_1 *)actor)->unk_73 = ((SpriteFrameState *)kind)->tile_y;
                    }
                } else {
                    s32 x;
                    s32 abs_x;
                    s32 abs_y;
                    s32 y;

                    ((S_8017256C_1 *)actor)->unk_60.p = scan_actor_along_heading(
                        actor,
                        sprite->tile_x,
                        sprite->tile_y,
                        ((S_8017256C_1 *)actor)->unk_2A,
                        0x10);
                    abs_x = abs(((S_8017256C_1 *)actor)->unk_72);
                    abs_y = abs(((S_8017256C_1 *)actor)->unk_73);
                    ((S_8017256C_1 *)actor)->unk_72 = abs_x;
                    ((S_8017256C_1 *)actor)->unk_73 = abs_y;
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
        ((S_8017256C_1 *)actor)->unk_6D--;
        action->unk_8C.handler = &update_object_animation;
        ((S_8017256C_1 *)actor)->unk_73 = 0;
        ((S_8017256C_1 *)actor)->unk_72 = 0;
        ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
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
        if ((s16)action->unk_A0.parts.high != 0) {
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
            D_80173EDC[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
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
            beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        action->unk_9E = 0;
        action->unk_90.parts.high.s = -0x20;
        return;

    case 8:
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            action->unk_8C.handler = &update_object_animation;
            advance_status_timers(actor);
            ((S_8017256C_1 *)actor)->unk_6D--;
            ((S_8017256C_1 *)actor)->unk_73 = 0;
            ((S_8017256C_1 *)actor)->unk_72 = 0;
            ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
        return;
    default:
        return;
    }
}
