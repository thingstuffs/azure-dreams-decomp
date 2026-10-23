#include "shared/sprite_frame_state.h"
#include "dungeon/monster/tyrant/update_entity_callbacks_directional_animation_movement_ground_contact.h"
#include "engine/entity.h"

/* Updates entity callbacks, directional animation, movement, and ground contact. */
void update_entity_callbacks_directional_animation_movement_ground_contact(void *actor, TrailMotion *motion, SpriteFrameState *part)
{
    void *entity = actor;
    s16 state_direction;
    s32 direction_index;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    s32 previous_state;
    s32 previous_state_2;
    T_80170AA4_EntityCallback callback;
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
        callback = (*(T_80170AA4_EntityCallback *)((u8 *)actor + 0x8C));
        if (callback == (T_80170AA4_EntityCallback)&update_dungeon_actor_behavior) {
            call_self = actor;
            callback(call_self, motion, part, call_self);
            return;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        return;
    }

    call_entity = actor;
    call_motion = motion;
    call_part = part;
    previous_state_2 = (*(u8 *)((u8 *)actor + 0x6D));
    call_self = actor;
    state_direction = (s8)previous_state_2;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        T_80170AA4_EntityCallback update_callback;
        update_callback = (*(T_80170AA4_EntityCallback *)((u8 *)actor + 0x8C));
        if (update_callback != 0) {
            update_callback(actor, motion, part, actor);
        }
    }
    tyrant_callbacks[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, part, actor);

    previous_state = (s32)state_direction << 16;
    current_state = (*(s8 *)((u8 *)actor + 0x6D));
    previous_state >>= 16;
    if (previous_state != current_state) {
        try_move_actor_to_valid_position(actor, motion, part, actor);
    }

    if ((*(u16 *)((u8 *)actor + 0x98)) & 0x8000) {
        wobble = (*(u16 *)((u8 *)actor + 0xAC)) + 1;
        (*(s16 *)((u8 *)actor + 0xAC)) = wobble;
        if (((s16)wobble >> 2) >= 2) {
            (*(s16 *)((u8 *)actor + 0xAC)) = -8;
            play_sound_if_enabled(0x60B);
        }
        wobble = (*(u16 *)((u8 *)actor + 0xAC));
        wobble_base = (*(u16 *)((u8 *)actor + 0xA6));
        wobble = (s16)wobble >> 2;
        if (wobble < 0) {
            wobble = -wobble;
        }
        wobble_base += wobble;
        part->clut = wobble_base;
    } else if (((*(s32 *)((u8 *)actor + 0x14)) & 7) != (*(s16 *)((u8 *)actor + 0xAA))) {
        update_owner_class_bits(actor);
        (*(s16 *)((u8 *)actor + 0xAA)) = (*(u16 *)((u8 *)actor + 0x14)) & 7;
    }

    part_flags = part->flags;
    if (!(part_flags & 0x8000)) {
        view_angle = g_game_work.view.camera_rotation.parts.viewAngle + ((T_80170AA4_S_80170AA4_1 *)entity)->unk_2A + 0x100;
        state_direction = (view_angle >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)actor + 0x94));
        direction_index = (u16)state_direction;
        if (previous_direction != state_direction) {
            if (*(u8 **)&part->frameTable != 0) {
                select_indirect_table_entry(part,
                              (*(u8 **)&part->frameTable)[state_direction],
                              part->unk_04);
            }
            (*(s16 *)((u8 *)actor + 0x94)) = state_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            part->flags |= 1;
        } else {
            part->flags &= 0xFFFE;
        }
        if (!(((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C & 0x20)) {
            if (!(part->flags & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            part->flags |= 0x7000;
        }
        apply_monster_koyaw_data(((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        part->flags = new_part_flags;
    }
    motion->x.unk_00 += motion->velocity_x;
    motion->y.unk_04 += motion->velocity_y;

    if ((*(u16 *)((u8 *)actor + 0x98)) & 8) {
        (*(s8 *)((u8 *)actor + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
        (*(s8 *)((u8 *)actor + 0x9D)) = (u8)(*(s8 *)((u8 *)actor + 0x9D)) + 1;
    }
    (*(s32 *)((u8 *)actor + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)actor + 0x98)) & 4)) {
        ground_height = sample_terrain_surface_height(motion->x.unk_02.unk_02,
                               motion->y.unk_06.unk_06,
                               (s16)(((T_80170AA4_S_80170AA4_1 *)entity)->unk_88 - 0x20));
        if ((s16)ground_height < 0x200) {
            base_height = (s16)((T_80170AA4_S_80170AA4_1 *)entity)->unk_88;
            if ((*(s16 *)((u8 *)actor + 0x92)) + base_height < (s16)ground_height) {
                ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C &= 0xF7FFFFFF;
            } else {
                if ((s16)ground_height >= base_height) {
                    (*(s32 *)((u8 *)actor + 0x90)) = 0;
                    motion->unk_14 = 0;
                    ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C |= 0x08000000;
                    (*(s8 *)((u8 *)actor + 0x9D)) = 0;
                } else {
                    motion->unk_14 = 0;
                    ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C |= 0x08000000;
                    (*(s8 *)((u8 *)actor + 0x9D)) = 0;
                    (*(s16 *)((u8 *)actor + 0x92)) = ground_height - ((T_80170AA4_S_80170AA4_1 *)entity)->unk_88;
                }
            }
            entity_flags = ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = sample_terrain_surface_height(
                    (part->tile_x << 6) | 0x20,
                    (part->tile_y << 6) | 0x20,
                    (s16)(((T_80170AA4_S_80170AA4_1 *)entity)->unk_88 - 0x20));
                (*(s16 *)((u8 *)actor + 0x92)) +=
                    ((T_80170AA4_S_80170AA4_1 *)entity)->unk_88 - ground_height;
                ((T_80170AA4_S_80170AA4_1 *)entity)->unk_88 = ground_height;
            }
        } else {
            ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((T_80170AA4_S_80170AA4_1 *)entity)->unk_1C &= 0xF7FFFFFF;
    }

    motion->z =
        ((T_80170AA4_S_80170AA4_1 *)entity)->unk_88 + (*(u16 *)((u8 *)actor + 0x92));
    part->flags |= 0x40;

    return;
}
