#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/monster/kid.h"
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "dungeon/effect/particle.h"
#include "dungeon/monster/kid_frames.h"

typedef struct S_80172D74_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80172D74_5;   /* part20 in advance_item_action_sequence */
extern void select_sprite_entry(void *, s32, s32);

extern u8 kid_action_resume_address[];
extern u8 D_80175168[];

/* Advances an item action through setup, animation, movement, and cleanup. */
/* Starts a targeted spell and source effect, animates a backward step, then returns to its tile and
 * restores idle. */
void advance_item_action_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    void *owner;
    S_80172D74_5 *owner_flags;
    SpriteFrameState *owner_sprite;
    u8 *item_slot;
    ObjectNodeHeader *entity;
    SpriteFrameState *position;
    s32 special_item;
    s32 step_x;
    s32 step_z;
    s32 next_state;
    u8 state_value;

    special_item = 0;
    {
        u32 direction_index = ((u16)actor->facing >> 8) & 0xE;

        owner = action->unk_A4.address;
        owner_flags = (S_80172D74_5 *)((u8 *)owner + 0x20);
        step_x = dir_step_x[direction_index >> 1];
        step_z = dir_step_y[direction_index >> 1];
        owner_sprite = (u8 *)owner + 0x28;
    }
    action->action_timer--;
    switch (action->action_phase) {
    case 0:
        if (actor->flags1C & ACTOR_PLAYER_SIDE) {
            s32 kind_index = (actor->action_flags & ACTOR_ACTION_CODE_MASK) - 1;

            switch (kind_index) {
            case 6:
                special_item = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                special_item = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                special_item = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->action_flags & ACTOR_ACTION_CODE_MASK) {
            case 3:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 2:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 1:
                item_slot = (u8 *)actor + 8;
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            action->action_state_flags &= 0xFF7F;
            {
                s16 special_test;

                special_test = special_item;
                if (special_test != 0) {
                    entity = (ObjectNodeHeader *)primary_actor_record;
                    actor->target = entity;
                    position = (entity - 1)->sprite;
                    actor->target_tile_x = position->tile_x;
                    actor->target_tile_y = position->tile_y;
                } else {
                    u8 *item_defs = item_action_definitions;
                    u8 item_id = *item_slot;

                    if (item_defs[item_id * 20 + 0x12] == 2) {
                        entity = actor->target;

                        if (entity != 0) {
                            position = (entity - 1)->sprite;
                            actor->target_tile_x = position->tile_x;
                            actor->target_tile_y = position->tile_y;
                        }
                    } else {
                        position = scan_actor_along_heading(actor,
                            sprite->tile_x, sprite->tile_y,
                            actor->facing, 0x10);
                        actor->target = position;
                        actor->target_tile_x = abs(actor->target_tile_x);
                        actor->target_tile_y = abs(actor->target_tile_y);
                    }
                }
            }

            owner_flags->unk_04 &= 0x7FFF;
            (owner_sprite->frameTable) = D_80175168;
            select_sprite_entry(owner_sprite,
                D_80175168[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (!create_actor_spell_effect(actor, item_slot, special_item, (u8 *)action + 0x98)) {
                return;
            }
            sprite->flags &= 0xF7FF;
            create_source_positioned_object(motion, 3);
            play_sound_if_enabled(0x703);
            state_value = action->action_phase;
            action->action_timer = 6;
            action->action_phase = state_value + 1;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        {
            void *player = primary_actor_record;

            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)player + 0xA6))--;
        }
        advance_status_timers(actor);
        (*(u8 *)&actor->pending_turn_updates)--;
        action->unk_8C.address = kid_action_resume_address;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x0800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->action_phase++;

    case 2:
        if ((s16)(action->action_timer) > 0 &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        action->action_timer = 7;
        action->action_state_flags |= 0x80;
        if (sprite->flags & 0x8000) {
            next_state = 0x10;
            action->action_phase = next_state;
            return;
        }
        action->action_phase = action->action_phase + 1;
        return;

    case 3:
        if ((s16)(action->action_timer) < 4) {
            motion->velocity_x = -step_x << 18;
            motion->velocity_y = -step_z << 18;
        }
        if ((s16)(action->action_timer) > 0) {
            return;
        }
        next_state = 4;
        action->action_timer = next_state;
        next_state = 0x10;
        action->action_phase = next_state;
        return;

    case 16:
    {
        s32 target_x = sprite->tile_x << 6;
        s32 current_x = motion->x.w.i - 0x20;

        motion->velocity_x = (target_x - current_x) << 14;
    }
        {
            s32 target_z = sprite->tile_y << 6;
            s32 current_z = motion->y.w.i - 0x20;

            motion->velocity_y = (target_z - current_z) << 14;
        }
        if (!(owner_sprite->flags & 0x8000) &&
            (s16)(action->action_timer) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        {
            u8 *animation = sprite->frameTable;
            u8 *next_animation = kid_direction_frames;

            if (animation != kid_direction_frames) {
                u8 *alternate_animation = kid_alt_direction_frames;

                if (animation != alternate_animation && (sprite->flags & 0x6000)) {
                    owner_flags->unk_04 |= 0x8000;
                    action->unk_A8.u = 0;
                    if (*(u8 **)&sprite->frameTable == kid_frame_set_1) {
                        next_animation = alternate_animation;
                    }
                    (sprite->frameTable) = next_animation;
                    select_sprite_entry(sprite,
                        next_animation[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
            }
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        sprite->flags &= 0xF7FF;
        action->unk_8C.address = kid_action_resume_address;
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            (*(u8 *)&actor->pending_turn_updates)--;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
}
