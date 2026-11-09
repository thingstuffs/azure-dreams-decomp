#include "dungeon/monster/baloon_frames.h"
#include "shared/audio_commands.h"
#include "dungeon/monster/baloon.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "sdk/libc.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern void select_sprite_entry(void *, s32, s32);
extern void spawn_directional_random_velocity_effect(void *, s32);


extern u8 D_800E2398[8];


/* Updates the actor's item-use state, animation, and effects. */
/* Starts a targeted spell, settles to ground height, emits forward and surrounding particles, then
 * restores its hover. */
void update_actor_item_use(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 *item_slot;
    u32 stage;
    s32 flag;
    s16 effect_count;
    u32 state;
    ObjectNodeHeader *target;

    flag = 0;
    state = body->action_phase;
    switch (state) {
    case 0:
        if ((u32)actor->flags1C & ACTOR_PLAYER_SIDE) {
            u32 kind_index;

            kind_index = (actor->action_flags & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                flag = 1;
            case 2:
                item_slot = (u8 *)actor + 0xE;
                break;
            case 5:
                flag = 1;
            case 1:
                item_slot = (u8 *)actor + 0xB;
                break;
            case 4:
                flag = 1;
            case 0:
                item_slot = (u8 *)actor + 8;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind;

            action_kind = actor->action_flags & 0x3FFF;
            switch (action_kind) {
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
            body->action_state_flags &= 0xFF7F;
            {
                u8 is_special;
                SpriteFrameState *item_id;

                is_special = flag;
                if (is_special != 0) {
                    target = (ObjectNodeHeader *)primary_actor_record;
                    actor->target = target;
                    item_id = (target - 1)->sprite;
                    actor->target_tile_x = item_id->tile_x;
                    actor->target_tile_y = item_id->tile_y;
                } else {
                    item_id = (void *)(*item_slot);
                    if (item_action_definitions[((u8)item_id)].kind == 2) {
                        target = actor->target;
                        if (target != 0) {
                            item_id = (target - 1)->sprite;
                            actor->target_tile_x = item_id->tile_x;
                            actor->target_tile_y = item_id->tile_y;
                        }
                    } else {
                        s32 dx;
                        s32 dy;

                        dx = (s32)scan_actor_along_heading(
                            actor, sprite->tile_x, sprite->tile_y,
                            actor->facing, 0x10);
                        actor->target = (void *)dx;
                        dx = abs(actor->target_tile_x);
                        dy = abs(actor->target_tile_y);
                        actor->target_tile_x = dx;
                        actor->target_tile_y = dy;
                    }
                }
            }

            if (create_actor_spell_effect(actor, item_slot, flag,
                              (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_phase++;
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            g_dungeon_status.active_actor = 0;
            primary_actor_record->unk_A4.halves.high.u--;
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8)((u8)actor->pending_turn_updates - 1);
            body->unk_8C.address = update_actor_turn_behavior;
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->action_flags &= 0x7FFF;
            return;
        }

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase++;
        play_sound_if_enabled(0x703);

    case 2:
        body->action_phase++;
        body->action_state_flags &= 0xFFF7;
        actor->flags1C = (u32)((u32)actor->flags1C & (0xFFFBFFFF));
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;

    case 3:
        if (sprite->flags & 0x8000) {
            body->action_phase = 7;
            sprite->flags |= 0x6000;
            body->action_state_flags |= 0x80;
            return;
        }
        {
            s16 floor_height;

            floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                  ((u16)motion->y.w.i),
                                  (s16)((u16)actor->ground_height - 0x20));
            if ((body->unk_90.parts.high.s -
                 (s16)(floor_height - (u16)actor->ground_height)) != 0) {
                return;
            }
        }
        body->action_timer = 0;
        stage = body->action_phase;
        stage++;
        body->action_phase = stage;
        sprite->frameTable = D_800E2398;
        select_sprite_entry(sprite, D_800E2398[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        return;

    case 4:
    {
        s16 timer;

        timer = body->action_timer;
        body->action_timer = timer + 1;
        if (timer < 12 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        body->action_state_flags |= 0x80;
        sprite->flags |= 0x800;
        body->action_timer = 0x12;
        body->action_phase++;
        effect_count = 0;
        do {
            spawn_angled_random_velocity_effect((u8 *)body - 0x20,
                          actor->facing, 0xE0E0E0);
            effect_count++;
        } while ((s16)effect_count < 3);
        return;

    case 5:
        if ((g_dungeon_status.active_actor) == 0) {
            body->action_timer = 0;
        }
        if (body->action_timer >= 10) {
            effect_count = 0;
            do {
                spawn_angled_random_velocity_effect((u8 *)body - 0x20,
                              actor->facing, 0xE0E0E0);
                effect_count++;
            } while ((s16)effect_count < 3);
        }
        if ((u32)((u16)body->action_timer - 10) < 7) {
            s16 angle;

            for (angle = 0; angle < 0x1000; angle += 0x200) {
                if (angle != actor->facing) {
                    effect_count = 0;
                    do {
                        spawn_directional_random_velocity_effect(NODE_HEADER(body), angle);
                        effect_count++;
                    } while ((s16)effect_count <= 0);
                }
            }
        }
        {
            s16 timer;

            timer = body->action_timer - 1;
            body->action_timer = timer;
            if (timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        body->action_timer = 0;
        sprite->flags &= 0xF7FF;
        state = body->action_state_flags;
        stage = body->action_phase;
        stage++;
        state |= 8;
        body->action_phase = stage;
        body->action_state_flags = state;
        sprite->frameTable = baloon_fall_frames;
        select_sprite_entry(sprite, baloon_fall_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        return;

    case 6:
        if (body->unk_90.parts.high.s >= -0x1F) {
            body->unk_90.parts.high.u -= 4;
            return;
        }
        body->action_phase++;

    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (*(u8 * *)&sprite->frameTable != baloon_default_frames) {
            sprite->frameTable = baloon_default_frames;
            select_sprite_entry(
                sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->unk_9E = 0;
            body->action_state_flags |= 8;
            actor->flags1C = (u32)((u32)actor->flags1C | (0x40000));
            body->unk_90.parts.high.s = -0x20;
            sprite->flags &= 0xFFF3;
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            body->unk_8C.address = update_actor_turn_behavior;
            advance_status_timers(actor);
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->pending_turn_updates = (u8)((u8)actor->pending_turn_updates - 1);
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    }
}
