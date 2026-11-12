#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/item/actor_target.h"
#include "sdk/libc.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct {
    u32 words[12];
} Copy48;

extern u8 D_80171020[];
#include "dungeon/monster/saber.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

extern u8 D_80174E34[];

typedef struct S_80173230_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80173230_6;   /* (void *)special in advance_item_use_and_recovery */

typedef struct S_80173230_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80173230_7;   /* target in advance_item_use_and_recovery */


/* Advances item use, its visual effect, and the actor's recovery animation. */
/* Starts a targeted spell, creates an attached sprite effect and briefly changes the actor's palette, then
 * restores idle. */
void advance_item_use_and_recovery(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    SelectedItemActionEffectBody *effect_state;
    SpriteFrameState *target_sprite;
    u8 * effect_handle;
    s16 special_or_effect;
    GteOffset effect_offset;
    S_80173230_7 *item_slot;
    ObjectNodeHeader *action_object;
    s32 next_state;
    u8 state;
    ObjectNodeHeader *item_target;

    special_or_effect = 0;
    action_object = NODE_HEADER(body);
    state = body->action_phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if ((u32)actor->flags1C & ACTOR_PLAYER_SIDE) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                special_or_effect = 1;
                /* fallthrough */
            case 3:
                item_slot = (S_80173230_7 *)((u8 *)actor + 0xE);
                break;
            case 6:
                special_or_effect = 1;
                /* fallthrough */
            case 2:
                item_slot = (S_80173230_7 *)((u8 *)actor + 0xB);
                break;
            case 5:
                special_or_effect = 1;
                /* fallthrough */
            case 1:
                item_slot = (S_80173230_7 *)((u8 *)actor + 8);
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
            case 3:
                item_slot = (S_80173230_7 *)((u8 *)actor + 0xE);
                break;
            case 2:
                item_slot = (S_80173230_7 *)((u8 *)actor + 0xB);
                break;
            case 1:
                item_slot = (S_80173230_7 *)((u8 *)actor + 8);
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*(u8 *)item_slot != 0) {
            body->action_state_flags &= 0xFF7F;
            if ((s16)special_or_effect != 0) {
                item_target = (ObjectNodeHeader *)primary_actor_record;
                actor->target = item_target;
                target_sprite = (item_target - 1)->sprite;
                actor->target_tile_x = target_sprite->tile_x;
                actor->target_tile_y = target_sprite->tile_y;
            } else {
                u8 item_id = *(u8 *)item_slot;
                u8 *item_defs = item_action_definitions;
                if (item_defs[item_id * 20 + 0x12] == 2) {
                    item_target = actor->target;
                    if (item_target != 0) {
                        target_sprite = (item_target - 1)->sprite;
                        actor->target_tile_x = target_sprite->tile_x;
                        actor->target_tile_y = target_sprite->tile_y;
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

            if (create_actor_spell_effect(actor, item_slot, special_or_effect, (u8 *)body + 0x98) == 0) {
                return;
            }
            body->action_timer = 0x11;
            body->action_phase++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        g_dungeon_status.active_actor = 0;
        primary_actor_record->unk_A4.halves.high.u--;
        advance_status_timers(actor);
        actor->pending_turn_updates = actor->pending_turn_updates - 1;
        body->unk_8C.address = &saber_behavior_entry;
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        body->action_phase++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 timer;

            timer = body->action_timer - 1;
            body->action_timer = timer;
            if (timer == 0xB || (sprite->flags & 0xE000)) {
                effect_handle = allocate_list_node(0x112, &scene_object_list_anchor.next);
                if (effect_handle != 0) {
                    SpriteFrameState *actor_model;
                    u8 animation_id;

                    effect_state = NODE_BODY(effect_handle);
                    effect_state->ticks_remaining = 9;
                    ((S_80173230_6 *)((void *)effect_handle))->unk_10 = D_80171020;
                    effect_state->reference_position = motion;
                    effect_state->facing.u = (*(u16 *)((u8 *)actor + 0x2A));
                    item_slot = (S_80173230_7 *)((S_80173230_6 *)((void *)effect_handle))->unk_0C;
                    *(Copy48 *)item_slot = *(Copy48 *)sprite;
                    item_slot->unk_1E = 0x1000;
                    item_slot->unk_1C = 0x1000;
                    item_slot->unk_0E = 0x80;
                    item_slot->unk_0D = 0x80;
                    item_slot->unk_0C = 0x80;
                    register_node((void *)effect_handle, project_sprite_chain);
                    animation_id = D_80174E34[0];
                    item_slot->unk_2C = D_80174E34;
                    select_sprite_entry(item_slot, animation_id, 0);
                    item_slot->unk_10 = 0x20;
                    item_slot->unk_12 = 0xFF80;
                    item_slot->unk_14 |= 0x0C;

                    actor_model = action_object->sprite;
                    item_slot = (S_80173230_7 *)((S_80173230_6 *)((void *)effect_handle))->unk_08;
                    if (resolve_record_orientation_or_fallback(
                            actor_model->source, actor_model, &effect_offset.orientation, 1) != 0) {
                        item_slot->unk_02 = ((u16)motion->x.w.i);
                        item_slot->unk_06 = ((u16)motion->y.w.i);
                        item_slot->unk_0A = ((u16)motion->z.w.i);
                        item_slot->unk_02 += effect_offset.distance[0];
                        item_slot->unk_06 += effect_offset.distance[1];
                        item_slot->unk_0A += effect_offset.distance[2];
                    }
                }
            }

            if (body->action_timer == 0xB ||
                (sprite->flags & 0xE000)) {
                sprite->flags |= 0x800;
            }
            if (body->action_timer == 0 ||
                (sprite->flags & 0xE000)) {
                sprite->flags &= 0xF7FF;
            }
            if (body->action_timer <= 0 ||
                (sprite->flags & 0xE000)) {
                next_state = body->action_phase + 1;
                body->action_phase = next_state;
            }
        }
        return;

    case 3:
        if ((sprite->unk_04 == 3 &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            sprite->flags |= 0x800;
            body->action_timer = 0x14;
            body->action_state_flags |= 0x80;
            sprite->flags |= 0x100;
            body->unk_AC.halves.low.u = sprite->clut;
            sprite->clut = 0x7E80;
            body->action_phase++;
        }

    case 4:
        {
            s16 timer;

            if ((g_dungeon_status.active_actor) == 0) {
                body->action_timer = 0;
            }
            timer = body->action_timer - 1;
            body->action_timer = timer;
            if (timer <= 0) {
                body->action_timer = 0;
                sprite->flags &= 0xF7FF;
            }
            if (body->action_timer == 0x12) {
                sprite->flags &= 0xFEFF;
                sprite->clut = body->unk_AC.halves.low.u;
            }
            if (!(sprite->flags & 0xE000)) {
                return;
            }

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->flags &= 0xFEFF;
            sprite->clut = body->unk_AC.halves.low.u;

            if (*(u8 * *)&sprite->frameTable != saber_direction_frames) {
                u8 *animations;
                s32 direction;

                animations = saber_direction_frames;
                sprite->frameTable = animations;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
                sprite->flags &= 0xF7FF;
            }
            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            body->unk_8C.address = &saber_behavior_entry;
            advance_status_timers(actor);
            actor->target_tile_y = 0;
            actor->target_tile_x = 0;
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
            actor->action_flags &= 0x7FFF;
            play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        }
    }
}
