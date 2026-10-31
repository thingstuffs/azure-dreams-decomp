#include "shared/actor_property_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/tyrant/update_entity_callbacks_directional_animation_movement_ground_contact.h"
#include "engine/entity.h"
#include "dungeon/item.h"

/* Updates entity callbacks, directional animation, movement, and ground contact. */
void update_entity_callbacks_directional_animation_movement_ground_contact(ActorRecord *body, TrailMotion *motion, SpriteFrameState *sprite)
{
    T_80170AA4_S_80170AA4_1 *entity = (T_80170AA4_S_80170AA4_1 *)body;
    s16 state_direction;
    s32 direction_index;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    s32 previous_state;
    s32 previous_state_2;
    ActorActionHandler callback;
    s32 view_angle;
    s32 ground_height;
    s16 base_height;
    s32 previous_direction;
    s32 entity_flags;
    s32 current_state;
    s32 wobble;
    s32 wobble_base;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (g_dungeon_status.flags & 0x2000) {
        callback = body->unk_8C.handler;
        if (callback == (ActorActionHandler)&update_dungeon_actor_behavior) {
            call_self = body;
            callback(call_self, motion, sprite, call_self);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }

    call_entity = body;
    call_motion = motion;
    call_part = sprite;
    previous_state_2 = (*((u8 *)body + 0x6D));
    call_self = body;
    state_direction = (s8)previous_state_2;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        ActorActionHandler update_callback;
        update_callback = body->unk_8C.handler;
        if (update_callback != 0) {
            update_callback(body, motion, sprite, body);
        }
    }
    tyrant_callbacks[body->action_id.u](body, motion, sprite, body);

    previous_state = (s32)state_direction << 16;
    current_state = body->pending_turn_updates;
    previous_state >>= 16;
    if (previous_state != current_state) {
        try_move_actor_to_valid_position(body, motion, sprite, body);
    }

    if (body->action_state_flags & 0x8000) {
        wobble = body->unk_AC.halves.low.u + 1;
        body->unk_AC.halves.low.s = wobble;
        if (((s16)wobble >> 2) >= 2) {
            body->unk_AC.halves.low.s = -8;
            play_sound_if_enabled(0x60B);
        }
        wobble = body->unk_AC.halves.low.u;
        wobble_base = body->unk_A4.halves.high.u;
        wobble = (s16)wobble >> 2;
        if (wobble < 0) {
            wobble = -wobble;
        }
        wobble_base += wobble;
        sprite->clut = wobble_base;
    } else if ((body->flags14 & ACTOR_ELEMENT_MASK) != body->unk_AA) {
        update_owner_class_bits(body);
        body->unk_AA = (*(u16 *)((u8 *)body + 0x14)) & ACTOR_ELEMENT_MASK;
    }

    part_flags = sprite->flags;
    if (!(part_flags & 0x8000)) {
        view_angle = g_game_work.view.camera_rotation.parts.viewAngle + entity->unk_2A + 0x100;
        state_direction = (view_angle >> 9) & ACTOR_ELEMENT_MASK;
        previous_direction = body->unk_94;
        direction_index = (u16)state_direction;
        if (previous_direction != state_direction) {
            if (*(u8 **)&sprite->frameTable != 0) {
                select_indirect_table_entry(sprite,
                              (*(u8 **)&sprite->frameTable)[state_direction],
                              sprite->unk_04);
            }
            body->unk_94 = state_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
        if (!(entity->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
        }
        apply_monster_koyaw_data(entity->unk_1C, (u8 *)sprite + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        sprite->flags = new_part_flags;
    }
    motion->x.unk_00 += motion->velocity_x;
    motion->y.unk_04 += motion->velocity_y;

    if (body->action_state_flags & 8) {
        body->unk_9D.s = 0;
    } else {
        motion->unk_14 += body->unk_9D.s * 0x14000;
        body->unk_9D.s = (u8)body->unk_9D.s + 1;
    }
    body->unk_90.value += motion->unk_14;

    if (!(body->action_state_flags & 4)) {
        ground_height = sample_terrain_surface_height(motion->x.unk_02.unk_02,
                               motion->y.unk_06.unk_06,
                               (s16)(entity->unk_88 - 0x20));
        if ((s16)ground_height < 0x200) {
            base_height = (s16)entity->unk_88;
            if (body->unk_90.parts.high.s + base_height < (s16)ground_height) {
                entity->unk_1C &= 0xF7FFFFFF;
            } else {
                if ((s16)ground_height >= base_height) {
                    body->unk_90.value = 0;
                    motion->unk_14 = 0;
                    entity->unk_1C |= 0x08000000;
                    body->unk_9D.s = 0;
                } else {
                    motion->unk_14 = 0;
                    entity->unk_1C |= 0x08000000;
                    body->unk_9D.s = 0;
                    body->unk_90.parts.high.s = ground_height - entity->unk_88;
                }
            }
            entity_flags = entity->unk_1C;
            if (entity_flags & 0x40000000) {
                entity->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = sample_terrain_surface_height(
                    (sprite->tile_x << 6) | 0x20,
                    (sprite->tile_y << 6) | 0x20,
                    (s16)(entity->unk_88 - 0x20));
                body->unk_90.parts.high.s +=
                    entity->unk_88 - ground_height;
                entity->unk_88 = ground_height;
            }
        } else {
            entity->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        entity->unk_1C &= 0xF7FFFFFF;
    }

    motion->z =
        entity->unk_88 + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

    return;
}
