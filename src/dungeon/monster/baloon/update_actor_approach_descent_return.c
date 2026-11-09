#include "dungeon/monster/baloon_frames.h"
#include "common.h"
#include "dungeon/monster/baloon.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player.h"
#include "dungeon/player/item.h"
#include "engine/texture.h"
#include "engine/resource.h"
#include "dungeon/item/effect.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/system.h"
#include "dungeon/data.h"



typedef struct S_80175CD8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
} S_80175CD8_5;   /* globals in update_actor_approach_descent_return */


typedef struct WorldStatePage {
    u8 pad_0000[0x2090];
    s32 actionMode;
} WorldStatePage;

extern s32 dungeon_mode_state;
extern s16 floor_generation_state[3];
extern s16 current_dungeon_floor;
extern u8 scene_mode_code;

extern u8 D_80170940[];
extern u8 D_80170950[];
extern u8 D_80170988[];
extern u8 D_80170994[];
extern u8 D_801709B8[];

extern s32 get_entity_class(void *);
extern void select_sprite_entry(void *, u8, s32);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);

/* Updates the actor's approach, descent, and return sequence. */
/* Spends MP to descend with the player, then saves party state for a scene change or returns with a
 * message. */
void update_actor_approach_descent_return(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    /* MATCH: retain the raw action views and argument views for retail scheduling. */
    s32 slot;
    s32 companion_type;
    s32 facing;
    void *text_end;
    s32 ticks_left;
    s32 target_x;
    s32 target_y;
    s32 target_z;
    s32 approach_ticks;
    s32 return_ticks;
    s32 direction;
    void *text_start;
    u8 *companion;

    {
        u32 state = action->action_phase;

        switch (state) {
        case 0:
        {
            ActorRecord *effect_actor;
            s32 effect_flags;
            s32 tile_dx;
            s32 tile_dy;
            u8 target_tile_x;
            u8 sprite_tile_x;
            u8 sprite_tile_y;
            u8 target_tile_y;

            effect_actor = actor;
            effect_flags = 0x2000;
            target_tile_x = reference_tile_object.tile_position.parts.tile_x;
            sprite_tile_x = sprite->tile_x;
            sprite_tile_y = sprite->tile_y;
            tile_dx = target_tile_x - sprite_tile_x;
            target_tile_y = reference_tile_object.tile_position.parts.tile_y;
            tile_dx = __builtin_abs(tile_dx);
            tile_dy = target_tile_y - sprite_tile_y;
            tile_dy = __builtin_abs(tile_dy);
            action->action_timer = ((tile_dx + tile_dy) * 4) + 9;
            action->action_phase++;
            spend_actor_mp(effect_actor, effect_flags);
        }

            if (reference_tile_object.tile_position.parts.tile_x == sprite->tile_x) {
                if (reference_tile_object.tile_position.parts.tile_y > sprite->tile_y) {
                    direction = 2;
                } else {
                    direction = 6;
                }
            } else if (reference_tile_object.tile_position.parts.tile_y == sprite->tile_y) {
                direction = (sprite->tile_x >= reference_tile_object.tile_position.parts.tile_x) * 4;
            } else if (sprite->tile_x < reference_tile_object.tile_position.parts.tile_x) {
                if (sprite->tile_y < reference_tile_object.tile_position.parts.tile_y) {
                    direction = 1;
                } else {
                    direction = 7;
                }
            } else if (sprite->tile_y < reference_tile_object.tile_position.parts.tile_y) {
                direction = 3;
            } else {
                direction = 5;
            }
            (*(s16 *)((u8 *)actor + 0x2A)) = direction << 9;

            if ((dungeon_mode_state != 0) || (current_dungeon_floor != 0x28)) {
                if ((*((u8 *)&((EntityRec *)actor)->unk_10 + 1)) >= current_dungeon_floor) {
                    slot = 0;
                    do {
                        companion = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + slot * 4);
                        if ((companion != 0) && (companion != (u8 *)actor)) {
                            companion_type = get_entity_class(companion);
                            create_orbiting_teleport_effect(companion, actor_event_values[companion_type], (s16)slot, 0);
                        }
                        slot++;
                    } while (slot < 2);
                }
            }

        case 1:
            target_x = ((reference_tile_object.tile_position.parts.tile_x << 6) + 0x20) << 16;
            target_y = ((reference_tile_object.tile_position.parts.tile_y << 6) + 0x20) << 16;
            target_z = view_reference_entity.z.v - 0x600000;
            approach_ticks = (s16)action->action_timer;
            if (approach_ticks >= 0xE) {
                motion->velocity_x = (target_x
                    - motion->x.v) / (approach_ticks - 9);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 9);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 9);
            } else if (approach_ticks >= 0xB) {
                motion->velocity_x = (target_x
                    - motion->x.v) / (approach_ticks - 7);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 7);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 7);
            } else if (approach_ticks >= 5) {
                motion->velocity_x = (target_x
                    - motion->x.v) / (approach_ticks - 2);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 2);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 2);
            } else {
                motion->velocity_x = (target_x
                    - motion->x.v) / approach_ticks;
                motion->velocity_y = (target_y - motion->y.v) /
                    (s16)action->action_timer;
                motion->velocity_z = (target_z - action->unk_90.value) /
                    (s16)action->action_timer;
            }
            ticks_left = action->action_timer - 1;
            action->action_timer = ticks_left;
            if ((ticks_left << 16) != 0) {
                return;
            }
            action->action_timer = 0;
            action->action_phase++;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            return;

        case 2:
            sprite->frameTable = baloon_hop_frames;
            facing = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            select_sprite_entry(sprite, baloon_hop_frames[facing & 7], 0);
            action->action_timer = 0;
            action->action_phase++;
            clear_player_linked_action_flags();
            return;

        case 3:
        {
            u16 old_timer = action->action_timer;

            action->action_timer = old_timer + 1;
            if ((s16)old_timer < 7) {
                return;
            }
        }
            action->action_phase++;
            {
                ActorRecord *player = dungeon_actor_ring_anchor;

                action->action_timer = 0;
                player->flags14 |= 0x100000;
            }
            play_sound_if_enabled(0x603);
            return;

        case 4:
        {
            ObjectPosition *scene = ((&view_reference_entity));
            s32 fall_speed = (s32)0xFFF40000;

            motion->velocity_z = fall_speed;
            scene->z.v += fall_speed;
        }
            {
                u16 old_timer = action->action_timer;

                action->action_timer = old_timer + 1;
                if ((s16)old_timer < 0x1B) {
                    return;
                }
            }
            action->action_timer = 0;

            if ((((WorldStatePage *)0x80010000)->actionMode == 0) && (current_dungeon_floor == 0x28)) {
                action->action_phase = 7;
            } else if ((*((u8 *)&((EntityRec *)actor)->unk_10 + 1)) >= current_dungeon_floor) {
                action->action_phase++;
            } else {
                action->action_phase = 7;
            }
            return;

        case 5:
            action->action_timer = 0;
            action->action_phase++;
            return;

        case 6:
            snapshot_inventory_and_familiars((dungeon_actor_ring_anchor));
            snapshot_inventory_familiar_records();
            check_action_boundary_and_set_flag();
            {
                u8 *scene_page;
                u8 *counter_page;
                s16 *floor_stats;
                u8 map_id;
                s32 visit_count;
                s32 floor_count;
                s32 next_visit;
                s32 next_floor;

                scene_page = &scene_mode_code;
                counter_page = (u8 *)0x80010000;
                floor_stats = floor_generation_state;
                map_id = *scene_page;

                visit_count = *(s32 *)(counter_page + 0x234);
                floor_count = *(u16 *)((u8 *)floor_stats + 4);
                next_visit = visit_count + 1;
                next_floor = floor_count + 1;
                *(s32 *)(counter_page + 0x234) = next_visit;
                *(u16 *)((u8 *)floor_stats + 4) = next_floor;
                request_scene_dispatch_state(map_id);
            }
            mark_sprite_resources_for_purge();
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            action->action_timer = 0;
            action->action_phase = 0x14;
            actor->action_flags &= 0x7FFF;
            break;

        case 7:
        {
            ActorRecord *player = dungeon_actor_ring_anchor;
            ObjectPosition *scene;
            u8 *scene_base;
            u32 player_flags;
            u16 height;

            player_flags = ((u32)player->flags14) & 0xFFEFFFFF;

            scene_base = ((u8 *)(&scene_object_list_anchor));
            scene = scene_base + 0x20;
            player->flags14 = player_flags;
            height = ((u16)view_reference_entity.z.w.i) - ((u16)((S_80175CD8_5 *)scene)->unk_88);
            player->unk_90.parts.high.s = height;
            ((S_80175CD8_5 *)scene)->unk_88 = height;
            ((S_80175CD8_5 *)scene)->unk_1C |= 0x40000000;
        }
            (*(s16 *)((u8 *)action + 0x96)) = 0x28;
            action->action_phase++;

            if ((dungeon_mode_state != 0) || (current_dungeon_floor != 0x28)) {
                text_start = get_unused_text_buffer();
                text_end = expand_text_control_codes(D_80170940, text_start);
                text_end = write_text_byte_and_advance(0xA, text_end);
                text_end = expand_text_control_codes(D_80170950, text_end);
                text_end = write_text_byte_and_advance(0xA, text_end);
                text_end = expand_text_control_codes(D_80170988, text_end);
                text_end = append_entity_display_text(actor, text_end);
                text_end = expand_text_control_codes(D_80170994, text_end);
            } else {
                text_start = get_unused_text_buffer();
                text_end = expand_text_control_codes(D_801709B8, text_start);
            }
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(text_start);

        case 8:
            target_x = ((sprite->tile_x << 6) + 0x20) << 16;
            target_y = ((sprite->tile_y << 6) + 0x20) << 16;
            target_z = (action->unk_B4.halves.low.s - 0x20) << 16;
            return_ticks = (s16)action->action_timer;
            if (return_ticks >= 0xE) {
                motion->velocity_x = (target_x - motion->x.v) / (return_ticks
                    - 9);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 9);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 9);
            } else if (return_ticks >= 0xB) {
                motion->velocity_x = (target_x - motion->x.v) / (return_ticks
                    - 7);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 7);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 7);
            } else if (return_ticks >= 5) {
                motion->velocity_x = (target_x - motion->x.v) / (return_ticks
                    - 2);
                motion->velocity_y = (target_y - motion->y.v) /
                    ((s16)action->action_timer - 2);
                motion->velocity_z = (target_z - action->unk_90.value) /
                    ((s16)action->action_timer - 2);
            } else {
                motion->velocity_x = (target_x - motion->x.v) / return_ticks;
                motion->velocity_y = (target_y - motion->y.v) /
                    (s16)action->action_timer;
                motion->velocity_z = (target_z - action->unk_90.value) /
                    (s16)action->action_timer;
            }

            ticks_left = action->action_timer - 1;
            action->action_timer = ticks_left;
            if ((ticks_left << 16) != 0) {
                return;
            }
            action->action_timer = 0;
            action->action_phase++;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            return;

        case 9:
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            action->unk_8C.word_ptr = update_actor_turn_behavior;
            action->action_id = 0xE;
            g_dungeon_status.active_actor = 0;
            actor->flags1C |= 0x40000;
            action->action_state_flags &= 0xFFF7;
            sprite->frameTable = baloon_default_frames;
            facing = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
            select_sprite_entry(sprite, baloon_default_frames[facing & 7], 0);
            sprite->frame_ticks = 1;
            action->unk_A0.parts.high = 0;
            action->unk_9E = 0;
            action->unk_90.parts.high.s = -0x20;
            actor->ground_height = action->unk_B4.halves.low.u;
            motion->x.w.i = (sprite->tile_x << 6) + 0x20;
            motion->y.w.i = (sprite->tile_y << 6) + 0x20;
            motion->z.w.i = ((u16)actor->ground_height) +
                action->unk_90.parts.high.u - action->unk_A0.parts.high;

            actor->action_flags &= 0x7FFF;

        case 20:
        default:
            break;
        }
    }
    return;
}

#undef FIELD
