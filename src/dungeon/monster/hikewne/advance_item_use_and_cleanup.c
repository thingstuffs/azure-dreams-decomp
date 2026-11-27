#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/actor.h"
#include "shared/audio_commands.h"
#include "dungeon/monster/hikewne.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "sdk/libc.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/item.h"
#include "dungeon/system.h"
#include "dungeon/data.h"
#include "dungeon/monster/hikewne_frames.h"

extern void create_tracking_fade_sprite(void *, ObjectPosition *, void *, void *);

extern u8 hikewne_item_use_direction_frames[];



   /* the 0x14 bytes before active in advance_item_use_and_cleanup, addressed as active[-1] */

   /* linked in advance_item_use_and_cleanup */

/* Advance item use through effect activation, actor animation, and cleanup. */
/* Starts a targeted spell, waits for loading, emits directional effects, and restores the actor after
 * either sequence. */
void advance_item_use_and_cleanup(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *actor, ActorRecord *item)
{
    register u8 *effect_slot;
    s16 is_special;
    s32 effect_special;
    s16 next_state;
    u8 state;
    ObjectNodeHeader *target;
    MovingTile *linked;

    is_special = 0;
    state = action->action_phase;
    switch (state) {
    case 0:
        if ((*(u32 *)((u8 *)item + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = (item->action_flags & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                is_special = 1;
            case 2:
                effect_slot = (u8 *)item + 0xE;
                break;
            case 5:
                is_special = 1;
            case 1:
                effect_slot = (u8 *)item + 0xB;
                break;
            case 4:
                is_special = 1;
            case 0:
                effect_slot = (u8 *)item + 8;
                break;
            default:
                effect_slot = 0;
                break;
            }
        } else {
            s32 item_kind;

            item_kind = item->action_flags & 0x3FFF;
            switch (item_kind) {
            case 3:
                effect_slot = (u8 *)item + 0xE;
                break;
            case 2:
                effect_slot = (u8 *)item + 0xB;
                break;
            case 1:
                effect_slot = (u8 *)item + 8;
                break;
            default:
                effect_slot = 0;
                break;
            }
        }

        if (*effect_slot != 0) {
            action->action_state_flags &= 0xFF7F;
            {
                s32 special_target;

                special_target = is_special;
                if (special_target != 0) {
                    target = (ObjectNodeHeader *)primary_actor_record;
                    item->target = target;
                    linked = (MovingTile *)(target - 1)->sprite;
                    item->target_tile_x = linked->tile_x;
                    item->target_tile_y = linked->tile_y;
                } else {
                    u8 effect_id;

                    effect_id = *effect_slot;
                    if (item_action_definitions[effect_id].kind == 2) {
                        target = item->target;
                        if (target != 0) {
                            linked = (MovingTile *)(target - 1)->sprite;
                            item->target_tile_x = linked->tile_x;
                            item->target_tile_y = linked->tile_y;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        target = scan_actor_along_heading(
                            item, actor->tile_x, actor->tile_y,
                            item->facing, 0x10);
                        item->target = target;
                        dx = abs(item->target_tile_x);
                        dy = abs(item->target_tile_y);
                        item->target_tile_x = dx;
                        item->target_tile_y = dy;
                    }
                }
            }

            effect_special = is_special;
            if (create_actor_spell_effect(item, effect_slot, effect_special, &action->action_state_flags) == 0) {
                return;
            }
            action->action_timer = 0;
            action->action_phase++;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if ((u32)(*effect_slot - 0x2E) >= 3) {
                return;
            }
            if (effect_special == 1) {
                return;
            }
            action->action_phase = 0x10;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(item);
        (*((u8 *)item + 0x6D))--;
        action->unk_8C.handler = update_hikewne_actor_behavior;
        item->target_tile_y = 0;
        item->target_tile_x = 0;
        item->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        action->action_phase++;

    case 2:
    {
        s16 timer;

        timer = action->action_timer;
        action->action_timer = timer + 1;
        if ((s16)timer < 8) {
            if (!(actor->flags & 0x8000)) {
                return;
            }
        }
    }
        next_state = action->action_phase;
        action->action_timer = 0;
        next_state++;
        action->action_phase = next_state;
        return;

    case 3:
        if (action->unk_A0.parts.high != 0) {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 15) {
                if (!(actor->flags & 0x8000)) {
                    return;
                }
            }
        }
        action->action_timer = 0;
        action->action_phase++;
        play_sound_if_enabled(0x703);
        (actor->frameTable) = hikewne_item_use_direction_frames;
        select_sprite_entry(actor,
            *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + item->facing + 0x100) >> 9) & 7) + (u32)hikewne_item_use_direction_frames)),
            0);
        return;

    case 4:
        create_tracking_fade_sprite(action, motion, actor, item);
        {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 3) {
                if (!(actor->flags & 0xE000)) {
                    return;
                }
            }
        }
        actor->flags |= 0x800;
        action->action_phase++;
        return;

    case 5:
        actor->flags |= 0x800;
        {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 10) {
                if (!(actor->flags & 0x8000)) {
                    return;
                }
            }
        }
        action->action_timer = 0;
        action->action_phase++;
        actor->flags &= 0xF7FF;
        return;

    case 6:
        action->action_timer = 0;
        action->action_state_flags |= 0x80;
        action->action_phase++;
        return;

    case 7:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        action->action_phase++;
        if (*(u8 **)&actor->frameTable == hikewne_direction_frames) {
            return;
        }
        {
            u8 *model = hikewne_direction_frames;

            (actor->frameTable) = model;
            select_sprite_entry(actor,
                model[((g_game_work.view.camera_rotation.parts.viewAngle + item->facing + 0x100) >> 9) & 7],
                0);
        }
        action->unk_9E = 0;
        action->unk_90.parts.high = -0x20;
        return;

    case 8:
    {

        if ((g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        action->unk_8C.handler = update_hikewne_actor_behavior;
        advance_status_timers(item);
        item->target_tile_y = 0;
        item->target_tile_x = 0;
        (*((u8 *)item + 0x6D))--;
        item->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
    }
        return;

    case 16:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        action->action_phase++;

    case 17:
    {
        s16 timer;

        timer = action->action_timer;
        action->action_timer = timer + 1;
        if ((s16)timer < 8 &&
            !(actor->flags & 0x8000)) {
            return;
        }
    }
        next_state = action->action_phase;
        action->action_timer = 0;
        next_state++;
        action->action_phase = next_state;
        return;

    case 18:
        if (action->unk_A0.parts.high != 0) {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 15 &&
                !(actor->flags & 0x8000)) {
                return;
            }
        }
        action->action_timer = 0;
        action->action_phase++;
        play_sound_if_enabled(0x703);
                    /* MATCH: the preceding eight-byte model table uses a distinct address expression in this arm. */
        (actor->frameTable) = (u8 *)((u32)hikewne_frame_set_17 - 8);
        select_sprite_entry(actor,
            *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + item->facing + 0x100) >> 9) & 7)
                + (u32)(u8 *)((u32)hikewne_frame_set_17 - 8))),
            0);
        return;

    case 19:
        create_tracking_fade_sprite(action, motion, actor, item);
        {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 2 &&
                !(actor->flags & 0xE000)) {
                return;
            }
        }
        actor->flags |= 0x800;
        next_state = action->action_phase;
        next_state++;
        action->action_phase = next_state;
        return;

    case 20:
        actor->flags |= 0x800;
        if ((action->action_timer) < 5) {
            create_tracking_fade_sprite(action, motion, actor, item);
        }
        {
            s16 timer;

            timer = action->action_timer;
            action->action_timer = timer + 1;
            if ((s16)timer < 10 &&
                !(actor->flags & 0x8000)) {
                return;
            }
        }
        action->action_timer = 0;
        action->action_phase++;
        actor->flags &= 0xF7FF;
        action->action_state_flags |= 0x80;
        return;

    case 21:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        action->action_timer = 0;
        action->action_phase++;
        {

            (actor->frameTable) = hikewne_frame_set_17;
            select_sprite_entry(actor,
                *((u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + item->facing + 0x100) >> 9) & 7)
                    + (u32)hikewne_frame_set_17)),
                0);
        }
        return;

    case 22:
    {
        s16 timer;

        timer = action->action_timer;
        action->action_timer = timer + 1;
        if ((s16)timer < 5) {
            return;
        }
    }
        next_state = action->action_phase;
        action->action_timer = 0;
        next_state++;
        action->action_phase = next_state;
        return;

    case 23:
        next_state = 6;
        action->action_timer = 0;
        action->action_phase = next_state;
        return;
    default:
        return;
    }

}
