#include "modules/dungeon_resource08_slot0.h"
#include "shared/sprite_frame_state.h"

void * (*const resource08_slot0_entry0)(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id) = func_8017087C;
void (*const resource08_slot0_entry1)(void *entity, R08_80170A50_S_80170A28_2 *motion, void *part) = func_80170A50;

void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    R08_8017087C_S_8017087C_2 *part_a;
    SpriteFrameState *part_b;
    R08_8017087C_S_8017087C_1 *work;
    R08_8017087C_S_8017087C_4 *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    s8 saved_tile_x;
    s16 saved_part_id;
    s8 saved_tile_y;

    work = 0;
    saved_tile_x = tile_x;
    saved_part_id = part_id;
    saved_tile_y = tile_y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((R08_8017087C_S_8017087C_0 *)obj)->unk_10 = ((u8 *)func_80170A50);
        work->unk_13 = 0x8;
        register_node(obj, project_sprite_chain);

        part_a = ((R08_8017087C_S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((R08_8017087C_S_8017087C_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_tile_y;
        actor = work;
        part_b->frameTable = ((u8 *)D_80174C3C);
        part_b->unk_24 = saved_tile_x;

        if (kind == 1) {
            flags_or_roll = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = flags_or_roll;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            flags_or_roll = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = flags_or_roll;
            work->unk_1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = ((u8 *)D_80174C8C);
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((void *)update_actor_behavior_and_effect);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

void func_80170A50(void *entity, R08_80170A50_S_80170A28_2 *motion, void *part)
{
    void *entity_base = entity;
    s16 old_state;
    s32 state_or_direction;
    s16 direction_index;
    s16 direction_copy;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    u32 unused_tail;
    R08_80170A50_EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 entity_flags;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(R08_80170A50_EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (R08_80170A50_EntityCallback)((void *)update_actor_behavior_and_effect)) {
            {
                call_self = entity;
                callback(call_self, motion, part, call_self);
            }
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_part = part;
    old_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    call_self = entity;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        R08_80170A50_EntityCallback update_callback;
        update_callback = (*(R08_80170A50_EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    ((R08_80170A50_EntityCallback *)D_80174C94)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    if ((s16)old_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, part, entity);
    }

    part_flags = ((R08_80170A50_S_80170A28_0 *)part)->unk_14;
    if (!(part_flags & 0x8000)) {
        rounded_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        direction_index = state_or_direction;
        direction_copy = state_or_direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_copy) {
            if (((R08_80170A50_S_80170A28_0 *)part)->unk_2C != 0) {
                select_indirect_table_entry(part,
                              ((R08_80170A50_S_80170A28_0 *)part)->unk_2C[direction_copy],
                              ((R08_80170A50_S_80170A28_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            ((R08_80170A50_S_80170A28_0 *)part)->unk_14 |= 1;
        } else {
            ((R08_80170A50_S_80170A28_0 *)part)->unk_14 &= 0xFFFE;
        }
        if (!(((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C & 0x20)) {
            if (!(((R08_80170A50_S_80170A28_0 *)part)->unk_14 & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            ((R08_80170A50_S_80170A28_0 *)part)->unk_14 |= 0x7000;
        }
        apply_monster_koyaw_data(((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((R08_80170A50_S_80170A28_0 *)part)->unk_14 = new_part_flags;
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(s8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(s8 *)((u8 *)entity + 0x9D)) = (u8)(*(s8 *)((u8 *)entity + 0x9D)) + 1;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        ground_height = ((s16)sample_terrain_surface_height(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
        if (ground_height < 0x200) {
            base_height = (s16)((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
            } else if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            } else {
                motion->unk_14 = 0;
                ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height - ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88;
            }

            entity_flags = ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = ((s16)sample_terrain_surface_height(
                    (((R08_80170A50_S_80170A28_0 *)part)->unk_24 << 6) | 0x20,
                    (((R08_80170A50_S_80170A28_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88 - ground_height;
                ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_88 = ground_height;
            }
        } else {
            ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((R08_80170A50_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    }

    entity_base = (u8 *)entity_base + 0x88;
    motion->unk_0A =
        *(u16 *)entity_base + (*(u16 *)((u8 *)entity + 0x92));
    ((R08_80170A50_S_80170A28_0 *)part)->unk_14 |= 0x40;

    return;
}

void update_actor_behavior_and_effect(void *actor, EntityRec *position, SpriteFrameState *object, ActorRecord *actor_data)
{
    s32 distance;
    s16 effect_offset[3];
    s8 room_id;
    u16 action_state;
    u8 *anim_table;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_801715B4(actor, position, object, actor_data);
        return;
    }

    if (actor_data->mp == 0) {
        advance_actor_pending_action(actor, position, object, actor_data);
        if (object->frameTable == ((u8 *)D_80174C8C)) {
            return;
        }
        object->frameTable = ((u8 *)D_80174C84);
        select_sprite_entry(object,
            ((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)actor_data->flags1C) & 0x200) {
        if (object->frameTable == ((u8 *)D_80174C8C)) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            actor_data->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, position, object, ((u8 *)D_80174C84)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor_data->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, position, object, actor_data);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
            u32 idle_state;

            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = ((u8 *)D_80174C3C);
                if (object->frameTable != anim_table) {
                    object->frameTable = anim_table;
                    select_sprite_entry(object,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (actor_data->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, position, object, ((u8 *)D_80174C44)) != 0) {
                return;
            }
        }

        if (((u32)actor_data->flags1C) & 0x80000) {

            begin_actor_move_to_target_facing(actor, position, object, actor_data);
            func_80173F20(actor, position, object, actor_data);
            object->frameTable = ((u8 *)D_80174C34);
            select_sprite_entry(object,
                ((u8 *)D_80174C34)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
                0);
            return;
        }

        if ((can_entity_gain_level(actor_data) << 16) != 0) {
            if ((process_selected_actor_record(actor, position, object, actor_data) << 16) != 0) {
                func_80174470(actor, position, object, actor_data);
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(object->unk_24, object->unk_25));
    object->unk_26 = room_id;

    if (actor_data->pending_turn_updates > 0) {
        if (((u32)actor_data->flags1C) & 0x20) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (*(u16 *)&object->unk_24 == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_801717F8(actor, position, object, actor_data);
            return;
        }
        if (!(actor_data->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(actor_data,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172280(actor, position, object, 0) << 16) == 0) {
                return;
            }
            action_state = actor_data->action_flags | 0x4000;
            actor_data->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                func_801717F8(actor, position, object, actor_data);
                return;
            }
        }

        action_state = actor_data->action_flags & 0x3FFF;
        {
            u32 idx = action_state - 1;
            switch (idx) {

            case 7:
            case 8:
                if ((update_actor_animation_behavior_and_facing(actor, position, object, actor_data) << 16) != 0) {
                    return;
                }
                func_80172168(actor, position, object, actor_data);
                return;

            case 4:
            case 5:
            case 6:
            {
                ActorRecord *player;
                s16 facing;

                facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(object->unk_24),(s16)(object->unk_25),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                    &distance));
                player = primary_actor_record;
                actor_data->facing = facing;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, position, object, ((u8 *)D_80174C34), ((void *)update_actor_behavior_and_effect));
                    return;
                }
            }

            case 11:
                update_actor_status_and_mp(actor_data);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, position, object, ((u8 *)D_80174C34), ((void *)update_actor_behavior_and_effect));
                return;

            default:
                func_801717F8(actor, position, object, actor_data);
                return;
            }
        }
    }

    if (!(((u32)actor_data->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor_data->flags1C) & 0x430)) {

                if ((test_neighbor_position_relation(
                        object->unk_24, object->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(object->unk_24),(s16)(object->unk_25),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (object->flags & 0x40) {
        return;
    }

    anim_table = ((u8 *)D_80174C3C);
    if ((object->frameTable != anim_table) &&
        (object->frameTable != ((u8 *)D_80174C34))) {
        object->frameTable = anim_table;
        select_sprite_entry(object,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = 1;
    } else if (object->flags & 0x6000) {
        s16 anim_timer = ((Rec_func_800A9E70_arg0 *)actor)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = anim_timer;
        if (anim_timer < 0) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AA = (rand() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_AA < 2) {
            object->frameTable = ((u8 *)D_80174C3C);
        } else {
            object->frameTable = ((u8 *)D_80174C34);
        }
        select_sprite_entry(object,
            ((u8 *)object->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing + 0x100) >> 9) & 7],
            0);
    }

    if (!resolve_record_orientation_or_fallback(object->source, object, effect_offset, 1)) {
        return;
    }
    if (object->frameTable != ((u8 *)D_80174C3C)) {
        return;
    }

    {
        void *effect;
        void *sprite;
        void *tint;
        u8 *sprite_data;

        effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
        ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_pv.v = effect;
        object = effect;
        if (object == 0) {
            return;
        }
        register_node(object, project_sprite_chain);
        tint = (void *)0x00808080;
        ((ObjectNodeHeader *)object)->unk_10 = ((u8 *)D_800D79B0);
        ((ObjectPosition *)((ObjectNodeHeader *)object)->unk_08)->x.w.i =
            ((u16)position->x.w.i) + effect_offset[0];
        ((ObjectPosition *)((ObjectNodeHeader *)object)->unk_08)->y.w.i =
            ((u16)position->y.w.i) + effect_offset[1];
        ((ObjectPosition *)((ObjectNodeHeader *)object)->unk_08)->z.w.i =
            ((u16)position->z.w.i) + effect_offset[2];
        sprite = ((ObjectNodeHeader *)object)->unk_0C;
        sprite_data = ((u8 *)secondary_sprite);
        ((EntityRec *)((ObjectNodeHeader *)object + 1))->unk_9B = 0;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_1E = 0xC00;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_1C = 0xC00;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_0C = tint;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_00 = sprite_data;
        ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_14 |= 0xC;
        {
            s32 anim_data = ((R08_80170E7C_S_80170E7C_8 *)sprite_data)->unk_04;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_04 = 0;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_05 = 0;
            ((R08_80170E7C_S_80170E7C_7 *)sprite)->unk_08 = anim_data;
        }
    }
}


void func_801715B4(void *action, s32 action_id, SpriteFrameState *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((R08_801715B4_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((R08_801715B4_S_80171570_0 *)state)->unk_71.u <= ((R08_801715B4_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (*(u8 * *)&entity->frameTable != ((u8 *)D_80174C2C)) {
        entity->frameTable = ((u8 *)D_80174C2C);
        select_sprite_entry(
            entity,(s16)(((u8 *)D_80174C2C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_801715B4_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }

    x = entity->unk_24;
    y = entity->unk_25;
    tile_mask = 0x3000;
    if (((R08_801715B4_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, tile_mask);

    direction = ((s16)get_rounded_facing_and_rounding_flag((s16)(x),(s16)(y),(s16)(((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_74),(s16)(((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_7C),
        (u8 *)action + 0x98));
    move_result = ((s16)check_movement_clearance_and_height((s16)(direction), entity, state, 0x20));

    entity->unk_24 =
        ((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    entity->unk_25 =
        ((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((R08_801715B4_S_80171570_0 *)state)->unk_8A = (u16)((R08_801715B4_S_80171570_0 *)state)->unk_8A + 1;

    new_x = entity->unk_24;
    new_y = entity->unk_25;
    if (((R08_801715B4_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags((s16)(new_x),(s16)(new_y),(u16)(tile_mask));
    ((R08_801715B4_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(g_dungeon_status.flags & 0x80)
        && !(entity->flags & 0x8000)) {
        func_80171F40(action, action_id, entity, state);
        ((R08_801715B4_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((R08_801715B4_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((R08_801715B4_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((R08_801715B4_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}

void func_801717F8(void *move_data, void *context, void *position_data, void *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;

    if ((dungeon_flags & 0x4000) || ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)update_actor_animation_behavior_and_facing(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25);
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(((R08_801717F8_S_80171C34_7 *)(((R08_801717F8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R08_801717F8_S_80171C34_7 *)(((R08_801717F8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25,(s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((R08_801717F8_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((SpriteFrameState *)position_data)->unk_24 == (u16)target_x &&
                    ((SpriteFrameState *)position_data)->unk_25 == (u16)target_y) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (*(s8 *)&((SpriteFrameState *)position_data)->unk_26 >= 0 &&
               ((R08_801717F8_DungeonRecord *)dungeon_rooms)[*(s8 *)&((SpriteFrameState *)position_data)->unk_26].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25,(s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R08_801717F8_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &reference_tile_object;
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)test_neighbor_position_relation(
                    ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = ((R08_801717F8_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R08_801717F8_S_80171C34_8 *)((u8 *)actor_data + (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((SpriteFrameState *)position_data)->unk_24;
            ((R08_801717F8_S_80171C34_8 *)((u8 *)actor_data + (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((SpriteFrameState *)position_data)->unk_25;
            ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((SpriteFrameState *)position_data)->unk_24 += *x_step;
                ((SpriteFrameState *)position_data)->unk_25 += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(u16)((((R08_801717F8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != *(u16 *)&((SpriteFrameState *)position_data)->unk_24) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R08_801717F8_S_80171C34_5 *)move_data)->unk_9C.u = ((SpriteFrameState *)position_data)->unk_26;
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R08_801717F8_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((SpriteFrameState *)position_data)->unk_24 << 6) | 0x20,
        (((SpriteFrameState *)position_data)->unk_25 << 6) | 0x20,(s16)((s16)(((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R08_801717F8_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}

void func_80171F40(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80174C4C);
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}

s32 update_actor_animation_behavior_and_facing(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, sprite->unk_24, sprite->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = D_80174C3C;
        select_sprite_entry(sprite, (D_80174C3C)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


void func_80172168(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            sprite->frameTable = ((u8 *)D_80174C3C);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)D_80174C3C)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

s32 func_80172280(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_801717F8(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R08_80172280_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        func_801717F8(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R08_80172280_S_80172628_0 *)entity)->unk_71 = (u8) (((R08_80172280_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R08_80172280_S_80172628_0 *)entity)->unk_71 = (u8) (((R08_80172280_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R08_80172280_S_80172628_0 *)entity)->unk_46 = (u16) (((R08_80172280_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

void finish_actor_tile_move_then_resume_effect_behavior(R08_801723C4_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)update_actor_behavior_and_effect);
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}

void func_8017245C(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_base;

    state = ((R08_8017245C_S_80172478_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C54);
        select_sprite_entry(
            sprite,
            ((u8 *)D_80174C54)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_8017245C_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((R08_8017245C_S_80172478_0 *)action)->unk_98 |= 8;
        ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s = 5;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A4 = 0;
        ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s;
        ((R08_8017245C_S_80172478_0 *)action)->unk_90 -= ((R08_8017245C_S_80172478_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s;

            ((R08_8017245C_S_80172478_0 *)action)->unk_A4 =
                (-func_800644B8(((R08_8017245C_S_80172478_0 *)action)->unk_A8.s * 0x199)) << 10;
        }

        height_offset = ((R08_8017245C_S_80172478_0 *)action)->unk_90;
        arc_offset = ((R08_8017245C_S_80172478_0 *)action)->unk_A4;
        next_move_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_A8.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A8.u = next_move_ticks;
        ((R08_8017245C_S_80172478_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) >= 0) {
            break;
        }

        ((R08_8017245C_S_80172478_0 *)action)->unk_90 = 0;
        ((R08_8017245C_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
        ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s |= 0x08000000;
        ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;
        break;
    case 2:
        if (((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s & 0x08000000) {
            ((R08_8017245C_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C5C);
            select_sprite_entry(
                sprite,
                ((u8 *)D_80174C5C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_8017245C_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);

            ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;
        }
        break;
    }
    action_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_96 - 1;
    ((R08_8017245C_S_80172478_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((R08_8017245C_S_80172478_2 *)actor)->unk_46 & 0x8000) {
            ((R08_8017245C_S_80172478_2 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((R08_8017245C_S_80172478_2 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)sprite)->unk_24,(s16)((SpriteFrameState *)sprite)->unk_25,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                &direction_aux));
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((R08_8017245C_S_80172478_0 *)action)->unk_8C = ((void *)update_actor_behavior_and_effect);
        on_actor_status_updated(actor);
    }
}

void advance_a_timed_actor_animation_applies_completion_effects(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_behavior_and_effect;
        }
    }
}

void update_staged_movement_and_return_to_tile(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    s32 state;
    s32 direction_offset;
    s32 vertical_speed;
    u16 ticks_left;

    state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = 3;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            return;
        }

        direction_offset = (((((u16)actor->facing) >> 9) & 7) + 4) % 8;
        motion->velocity_x =
            dir_step_x[direction_offset] * 3 << 16;
        motion->velocity_y =
            dir_step_y[direction_offset] * 3 << 16;
        motion->velocity_z = 0;
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C34);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C34)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 1:
        motion->velocity_x -= motion->velocity_x >> 2;
        motion->velocity_y -= motion->velocity_y >> 2;
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C64);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C64)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 4;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 2:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C6C);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C6C)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0x14;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 3:
        ticks_left = ((R08_80172830_S_80172830_0 *)action)->unk_96;
        vertical_speed = motion->velocity_z;
        ticks_left--;
        ((R08_80172830_S_80172830_0 *)action)->unk_96 = ticks_left;
        if ((s16)ticks_left < 12) {
            vertical_speed += 0x1400;
        } else {
            vertical_speed += 0x20000;
        }
        motion->velocity_z = vertical_speed;
        ((R08_80172830_S_80172830_0 *)action)->unk_90 += vertical_speed;

        if ((s16)((R08_80172830_S_80172830_0 *)action)->unk_96 == 0x11) {
            s32 direction_step;
            s16 *x_steps;
            s16 *x_step;
            s16 *y_step;

            direction_offset = ((u16)actor->facing) >> 8;
            x_steps = dir_step_x;
            x_step = (s16 *)((u8 *)x_steps + (direction_offset & 0xE));
            direction_step = *x_step;
            motion->velocity_x =
                (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
            y_step = (s16 *)((u8 *)&dir_step_y + (direction_offset & 0xE));
            direction_step = *y_step;
            motion->velocity_z = 0xFFF70000;
            motion->velocity_y =
                (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
            ((R08_80172830_S_80172830_0 *)action)->unk_90 = 0;
            ((R08_80172830_S_80172830_0 *)action)->unk_98 |= 8;
        }

        if (((((SpriteFrameState *)sprite)->unk_04 == 3) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
        }

        if (((((SpriteFrameState *)sprite)->unk_04 == 5) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            motion->velocity_x =
                ((((((SpriteFrameState *)sprite)->unk_24 << 6) + 0x20) << 16) -
                 motion->x.v) / (s16)((R08_80172830_S_80172830_0 *)action)->unk_96;
            motion->velocity_y =
                ((((((SpriteFrameState *)sprite)->unk_25 << 6) + 0x20) << 16) -
                 motion->y.v) / (s16)((R08_80172830_S_80172830_0 *)action)->unk_96;
        }

        if (((s16)((R08_80172830_S_80172830_0 *)action)->unk_96 > 0) &&
            !(((SpriteFrameState *)sprite)->flags & 0x8000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion,(u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25);
        spend_actor_mp(actor, 0x100);
        (*(u8 * *)((u8 *)action + 0x8C)) = ((void *)update_actor_behavior_and_effect);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)action + 0x98)) &= 0xFFF7;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
            return;
        }
        ((void * *)actor_update_node_cursor)[0] = (u8 *)actor - 0x20;

        return;
    }
}

void update_item_activation_and_cleanup(void *action, ObjectPosition *motion, void *actor, ActorRecord *object) {
    u16 position[3];
    s16 is_special;
    u8 *item_slot;
    void *node;
    u8 state;

    is_special = 0;
    state = ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((((u32)object->flags1C)) & 0x2000) {
            u32 kind = ((object->action_flags) & 0x3FFF) - 1;
            switch (kind) {
            case 6: is_special = 1;
            case 2: item_slot = (u8 *)object + 0xE; break;
            case 5: is_special = 1;
            case 1: item_slot = (u8 *)object + 0xB; break;
            case 4: is_special = 1;
            case 0: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        } else {
            s32 kind = (object->action_flags) & 0x3FFF;
            switch (kind) {
            case 3: item_slot = (u8 *)object + 0xE; break;
            case 2: item_slot = (u8 *)object + 0xB; break;
            case 1: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        }

        if (*item_slot != 0) {

            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_existing;
                u32 item_def;

                use_existing = is_special;
                if (use_existing) {
                    node = primary_actor_record;
                    (object->target) = node;
                    {
                        item_def = (u32)((R08_80172CE8_S_80172CE8_1_pre *)node)[-1].unk_00;
                        (((u8)object->target_tile_x)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_24;
                        (((u8)object->target_tile_y)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_25;
                    }
                } else {
                    u8 *item_defs = item_action_definitions;
                    u8 item_id = *item_slot;
                    item_def = (item_id * 20 + item_defs)[0x12];
                    if (item_def == 2) {
                        node = (object->target);
                        if (node != 0) {
                            {
                                item_def = (u32)((R08_80172CE8_S_80172CE8_1_pre *)node)[-1].unk_00;
                                (((u8)object->target_tile_x)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_24;
                                (((u8)object->target_tile_y)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_25;
                            }

                        }
                    } else {



                        (object->target) = scan_monster_along_heading(
                            object,
                            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24,
                            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25,
                            (object->facing),
                            0x10);
                        object->target_tile_x = abs(object->target_tile_x);
                        object->target_tile_y = abs(object->target_tile_y);
                    }
                }

            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(object, item_slot, is_special, (u8 *)action + 0x98)) {
                ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(position, (s16)((*item_slot - 1) % 3));
                ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
                return;
            }
            return;

        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25);
        g_dungeon_status.active_actor = 0;
        {
            u8 *active_object = (u8 *)primary_actor_record;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
        }
        advance_status_timers(object);
        (((u8)object->pending_turn_updates))--;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_8C = ((void *)update_actor_behavior_and_effect);
        (((u8)object->target_tile_y)) = 0;
        (((u8)object->target_tile_x)) = 0;
        (object->action_flags) &= 0x7FFF;
        return;

    case 1:
        if (!(((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)actor + 0x2C)) = ((u8 *)D_80174C7C);
        select_sprite_entry(
            actor,
            ((u8 *)D_80174C7C)[((g_game_work.view.camera_rotation.parts.viewAngle + (object->facing) + 0x100) >> 9) & 7],
            0);
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
        return;

    case 2:
        if (get_cd_command_queue_depth()) {
            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            return;
        }
        ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
                        /* fall through */

    case 3:
        if ((((R08_80172CE8_S_80172CE8_3 *)actor)->unk_04 == 5 &&
            (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0x1000)) ||
            (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = 0x10;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 timer = ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 - 1;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = timer;
            if ((s16)timer <= 0) {
                ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = 0;
                ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
            }
        }

        if (!(((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25);

        if (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_2C != ((u8 *)D_80174C3C)) {
            (*(void * *)((u8 *)actor + 0x2C)) = ((u8 *)D_80174C3C);
            select_sprite_entry(
                actor,
                ((u8 *)D_80174C3C)[((g_game_work.view.camera_rotation.parts.viewAngle + (object->facing) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_8C = ((void *)update_actor_behavior_and_effect);
        advance_status_timers(object);
        if ((object->pending_turn_updates) > 0) {
            (((u8)object->pending_turn_updates))--;
        }
        (((u8)object->target_tile_y)) = 0;
        (((u8)object->target_tile_x)) = 0;
        (object->action_flags) &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;

    default:
        break;
    }

    return;
}

void advance_action_phase_and_process_actor(void *action, void *motion, void *sprite, void *entity)
{
    s32 state;
    s16 move_timer;
    s32 tracked_entity;

    state = ((R08_80173234_S_80173234_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C =
            -((s16 *)((s8 *)dir_step_x))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 =
            -((s16 *)((s8 *)dir_step_y))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_80174C74));
            return;
        }
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 0;
            ((R08_80173234_S_80173234_0 *)action)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x228) {
            move_timer = 8;
        } else {
            move_timer = -1;
        }
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = move_timer;

        ((R08_80173234_S_80173234_1 *)motion)->unk_0C -= ((R08_80173234_S_80173234_1 *)motion)->unk_0C / 4;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 -= ((R08_80173234_S_80173234_1 *)motion)->unk_10 / 4;
                        /* fall through */

    case 1:
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dir_step_x))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dir_step_y))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;

        if (((R08_80173234_S_80173234_0 *)action)->unk_96.s > 0) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = ((R08_80173234_S_80173234_0 *)action)->unk_96.u - 1;
        } else if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 0;
        }

        if (((R08_80173234_S_80173234_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_80174C74));
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C44);
        select_sprite_entry(
            sprite,
            ((u8 *)D_80174C44)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;
        return;

    case 2:
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dir_step_x))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dir_step_y))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            return;
        }

        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C44);
        select_sprite_entry(
            sprite,
            ((u8 *)D_80174C44)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 8;
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;
        return;

    case 3:
        move_timer = ((R08_80173234_S_80173234_0 *)action)->unk_96.s;
        if (move_timer != 0) {
            {
                s32 target_x = ((SpriteFrameState *)sprite)->unk_24 << 6;
                s32 current_x = ((R08_80173234_S_80173234_1 *)motion)->unk_00.at02.v - 0x20;
                ((R08_80173234_S_80173234_1 *)motion)->unk_0C = ((target_x - current_x) << 15) / move_timer;
            }
            {
                s32 target_y = ((SpriteFrameState *)sprite)->unk_25 << 6;
                s32 current_y = ((R08_80173234_S_80173234_1 *)motion)->unk_04.at02.v - 0x20;
                ((R08_80173234_S_80173234_1 *)motion)->unk_10 =
                    ((target_y - current_y) << 15) / ((R08_80173234_S_80173234_0 *)action)->unk_96.s;
            }
        }

        move_timer = ((R08_80173234_S_80173234_0 *)action)->unk_96.u - 1;
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = move_timer;
        if ((s32)(move_timer << 16) > 0) {
            return;
        }

        ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_00.at00.v = ((((SpriteFrameState *)sprite)->unk_24 << 6) + 0x20) << 16;
        ((R08_80173234_S_80173234_1 *)motion)->unk_04.at00.v = ((((SpriteFrameState *)sprite)->unk_25 << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        ((R08_80173234_S_80173234_0 *)action)->unk_8C = ((void *)update_actor_behavior_and_effect);
    }
}

void func_80173688(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

void func_801736A8(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}

void func_801736C8(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

void finish_actor_hop_and_grow_then_resume_effect_behavior(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}

void update_object_or_select_directional_data(void *controller, s32 actor_index, void *sprite, ActorRecord *actor)
{
    DungeonGlobalStatus *dungeon_status;
    s32 actor_flags;
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C8C);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_80174C8C)[((g_game_work.view.camera_rotation.parts.viewAngle
                             + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)--;
        }
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;

    case 1:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {
            void *anim_table;
            anim_table = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
            if (anim_table == ((u8 *)D_80174C34)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)D_80174C84);
            } else if (anim_table == ((u8 *)D_80174C84)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)D_80174C8C);
            }
            select_sprite_entry(
                sprite,(u8)(((u8 *)((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv)
                    [((g_game_work.view.camera_rotation.parts.viewAngle
                       + actor->facing + 0x100)
                      >> 9) & 7]),
                0);
        }

        if ((get_entity_effect_value(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C84);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                actor->flags1C &= ~0x200;
                ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)update_actor_behavior_and_effect);
                return;
            }
            {
                DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)++;
            }
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        } else {
            dungeon_status = &g_dungeon_status;
            if (!(dungeon_status->flags & 0x1000)
                && ((actor->unk_64 == 0)
                    || (begin_ready_actor_directional_action(controller, actor_index, sprite, 0) == 0))) {

                if (actor->mp == 0) {
                    if (dungeon_status->flags & 0x2008) {
                        return;
                    }
                    advance_actor_pending_action(controller, actor_index, sprite, actor);
                    return;
                }

                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    return;
                }
                actor_flags = actor->flags1C;
                if (actor_flags & 0x100) {
                    begin_pushed_actor_move(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    begin_actor_move_to_target_facing(controller, actor_index, sprite, actor);
                    func_80173F20(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor->pending_turn_updates == 0) {
                    return;
                }
                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    if ((check_entity_relation(
                             actor,
                             ((s32)primary_actor_record->previous_actor_header)
                                 + 0x20)
                         << 16)
                        != 0) {
                        return;
                    }
                }

                update_actor_status_and_mp(actor);
                on_actor_status_updated(actor);
                if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                    TileObject *room_base;
                    s32 room_id;
                    room_base = &reference_tile_object;
                    room_id = ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_s8;
                    if (((room_id == room_base->room_index)
                         && (room_id >= 0))
                        || (((s16)get_tile_chebyshev_distance(room_base, sprite)) < 2)) {
                        if (!(generate_random_value() & 7)) {
                            clear_slots_of_type(actor, 1);
                        }
                    }
                }
                if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                    return;
                }

                (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C84);
                select_sprite_entry(
                    sprite,(u8)(((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                                >> 9) & 7]),
                    0);
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                    actor->flags1C &= ~0x200;
                    ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)update_actor_behavior_and_effect);
                    return;
                }
                {
                    DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                    (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)++;
                }
                ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
                return;
            }
        }
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)--;
        }
        actor->flags1C &= ~0x200;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C84);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                        >> 9) & 7]),
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)update_actor_behavior_and_effect);
        return;

        return;
    }
}

void resume_actor_effect_behavior_after_status_animation(void *controller, void *context, void *sprite, ActorRecord *entity)
{
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)D_80174C8C);
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        select_sprite_entry(sprite,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C84);
            select_sprite_entry(sprite,
                ((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            (((u32)entity->flags1C)) |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            func_80173F20(controller, context, sprite, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C84);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C84)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~0x208;
            ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)update_actor_behavior_and_effect);
        }

        return;
    }
}

void func_80173F20(R08_80173F20_Actor *actor, s32 action, R08_80173F20_Entity *entity, R08_80173F20_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_behavior_and_effect);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80174C8C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174C2C);
        select_sprite_entry(entity,(s16)(((u8 *)D_80174C2C)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

void finish_thrown_actor_travel_and_floor_trap_then_resume_effect_behavior(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_behavior_and_effect;
        }
    }
}

void finish_actor_terrain_interpolation_then_resume_effect_behavior(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}

void create_four_directional_effects(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}

void finish_actor_fade_in_then_resume_effect_behavior(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_behavior_and_effect;
    }
}

s32 start_bank_actor_hit_reaction(void *initial_payload, s32 entry_data, R08_801740F4_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R08_801740F4_Scratchpad *scratch = (R08_801740F4_Scratchpad *)0x1F800000;
    R08_801740F4_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_80174D14)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R08_801740F4_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */

void advance_object_angle_and_height(u16 *record_data, s32 unused, R08_80174180_Object *object) {
    u16 height;

    object->field_1A += 0x320;
    height = object->field_1E + 0x200;
    object->field_1E = height;
    object->field_1C = height;
    if (height >= 0x2000) {
        record_data[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void create_tinted_rotated_sprite(s32 unused_0, R08_801741D0_S_801741D0_3 *source_pos, s32 unused_2, s8 green, u8 red_blue)
{
    void *node;
    R08_801741D0_S_801741D0_1 *sprite;
    R08_801741D0_S_801741D0_2 *position;
    u8 *node_params;

    node = allocate_flagged_object_node(0x212);
    if (node != NULL) {
        ((R08_801741D0_S_801741D0_0 *)node)->unk_10 = ((u8 *)advance_object_angle_and_height);
        register_node(node, project_sprite_chain);

        sprite = ((R08_801741D0_S_801741D0_0 *)node)->unk_0C;
        sprite->unk_10 = 0x60;
        sprite->unk_14 |= 0xC;

        position = ((R08_801741D0_S_801741D0_0 *)node)->unk_08;
        position->unk_02 = source_pos->unk_02;
        position->unk_06 = source_pos->unk_06;
        position->unk_0A = source_pos->unk_0A - 0x28;

        sprite = ((R08_801741D0_S_801741D0_0 *)node)->unk_0C;
        sprite->unk_1E = 0x400;
        sprite->unk_1C = 0x400;
        sprite->unk_06 = 6;
        node_params = (u8 *)node + 0x20;
        ((R08_801741D0_S_801741D0_0 *)node)->unk_20 = 0x70;
        node_params[1] = 0x10;
        node_params[2] = 0x10;
        sprite->unk_0D = green;
        sprite->unk_0C = red_blue;
        sprite->unk_0E = red_blue;
        sprite->unk_1A = rand() & 0xFFF;

        memcpy((u8 *)node + 0x48, ((u8 *)D_80174D08), 12);
        sprite->unk_08 = (u8 *)node + 0x48;
    }
}

void update_timed_effect_and_expire(void *effect, s32 x, s32 y)
{
    s32 ticks_left = *(s16 *)((u8 *)effect + 0x1A);

    if (ticks_left >= 16) {
        create_tinted_rotated_sprite(effect, x, y,(s8)(0x70), 16);
    } else {
        create_tinted_rotated_sprite(effect, x, y,(s8)(0x70),
                      ((15 - ticks_left) * 6 + 16) & 0xFF);
    }

    {
        s32 next_ticks;

        next_ticks = (u16)*(s16 *)((u8 *)effect + 0x1A) - 1;
        *(s16 *)((u8 *)effect + 0x1A) = next_ticks;
        if ((next_ticks << 16) <= 0) {
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}

void create_positioned_sprite_effect(M2C_UNK unused, EntityRec *source_pos, void *unused_context) {
    R08_801743BC_S_801743BC_0 *effect;
    SpriteFrameState *sprite;
    MovingPosition *effect_pos;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect->unk_3A = 0x2D;
        effect->unk_10 = ((void *)update_timed_effect_and_expire);
        register_node(effect, project_sprite_chain);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) ((u16)source_pos->x.w.i);
        effect_pos->unk_06 = (u16) ((u16)source_pos->y.w.i);
        effect_pos->unk_0A = (u16) ((u16)source_pos->z.w.i);
        sprite = effect->unk_0C;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.r = 0;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->flags = (u16) (sprite->flags | 0x80);
    }
}

void func_80174470(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)func_80174470);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)D_800DCF5E) = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}

void func_8017451C(u8 *task, void *context, u8 *input)
{
    s16 frames_left;
    GameWork *fade_state = &g_game_work;

    if (task[0x9A] == 0) {
        (*(s32 *)D_80174D1C) = *(s32 *)(input + 8);
        advance_sprite_animation_and_textures(input);
        if (*(u16 *)(input + 0x14) & 0xE000) {
            unlink_node(task - 0x20);
            *(s16 *)(task + 0x96) = 0x10;
            task[0x9A]++;
            return;
        }
    } else {
        fade_state->view.tint.parts.tint_r = (u8)(fade_state->view.tint.parts.tint_r +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_r) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_g = (u8)(fade_state->view.tint.parts.tint_g +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_g) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_b = (u8)(fade_state->view.tint.parts.tint_b +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_b) / *(s16 *)(task + 0x96)));

        frames_left = *(u16 *)(task + 0x96) - 1;
        *(s16 *)(task + 0x96) = frames_left;
        if (frames_left <= 0) {
            *(u16 *)(task - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}

void advance_effect_and_child_animation(void *effect_state, EntityRec *position, SpriteFrameState *entity, void *actor)
{
    u8 state;
    s32 effect_id;
    s32 direction;
    u8 mode;
    u16 angle;
    u16 saved_angle;
    R08_80174648_S_80174648_2 *effect_work = ((u8 *)(&g_game_work));
    state = ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B;
    if (state >= 9) {
        return;
    }
    switch (state) {
    case 0:
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
        return;

    case 1:
        run_cd_image_commands(((u8 *)D_80174CF4), ((u8 *)D_80174D18), 0);
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_B0 = 0;
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
        saved_angle = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
        ((R08_80174648_S_80174648_1 *)actor)->unk_8A = saved_angle;
        /* fallthrough */

    case 2:
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_80174648_S_80174648_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        mode = ((u8 *)((void * *)D_80174D1C))[-4];
        angle = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
        if ((mode == 0) || (direction != 2)) {
            if (direction == 2) {
                return;
            }
            ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        run_cd_image_commands((u8 *)((void * *)D_80174CFC) - 8, (u8 *)((void * *)D_80174D1C) - 4, 1);
        sound_set_cd_cue_parameters(0, ((s32 *)cd_cue_base)[0], 0x04000AD4, 0x05000CC4);
        effect_id = read_stream_cue_start_offset();
        Control_CD(0x15, effect_id, 0);
        ((u8 *)D_80174D19)[0] = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_80174D19));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
        ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;

    case 3:
        {
            s32 frames_left;
            u8 effect_ready;
            u8 *target_color;

            frames_left = ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u = frames_left - 1;
            if ((s16)(frames_left - 1) <= 0) {
                effect_ready = ((u8 *)D_80174D19)[0];
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u = frames_left;
                if (effect_ready != 0) {
                    ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
                    play_sound_if_enabled(0x300);
                    return;
                }
                return;
            }
            target_color = ((void * *)actor_effect_color_targets)[lookup_masked_byte_table(actor)];
            effect_work->unk_A8 += (((R08_80174648_S_80174648_3 *)target_color)->unk_00
                - effect_work->unk_A8) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            effect_work->unk_A9 += (((R08_80174648_S_80174648_3 *)target_color)->unk_01
                - effect_work->unk_A9) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            effect_work->unk_AA += (((R08_80174648_S_80174648_3 *)target_color)->unk_02
                - effect_work->unk_AA) / ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s;
            return;
        }

    case 4:
        {
            s16 variant;
            s32 color;
            s32 pos_z;

            effect_work = allocate_flagged_object_node(0x12);
            if (effect_work == 0) {
                return;
            }
            effect_work->unk_10.p = ((u8 *)func_8017451C);
            register_node(effect_work, ((u8 *)start_bank_actor_hit_reaction));
            color = 0x00808080;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_AC = effect_work;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_00 = position->x.v;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_04 = position->y.v;
            ((R08_80174648_S_80174648_9 *)(effect_work->unk_08))->unk_08 =
                (pos_z = position->z.v, ((s16 *)D_80174D14)[0] = 5, pos_z);
            effect_work = effect_work->unk_0C.p;
            effect_work->unk_1E = 0x1000;
            effect_work->unk_1C = 0x1000;
            effect_work->unk_0C.i = color;
            variant = lookup_masked_byte_table(actor) - 1;
            if (variant < 0) {
                variant = func_80069EF8() % 3;
            }
            select_record_entry_and_value(effect_work, ((u8 *)D_8014A000) + (s32)((void * *)D_80174CFC)[variant], 0);
            entity->flags |= 0x80;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            create_positioned_sprite_effect(effect_state, position, entity);
            return;
        }

    case 5:
        {
            effect_work = ((R08_80174648_S_80174648_0 *)effect_state)->unk_AC;
            effect_work = effect_work->unk_0C.p;
            if (effect_work->unk_14 & 0xE000) {
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
                ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
                decrement_monster_entry_count(((R08_80174648_S_80174648_1 *)actor)->unk_13, 3);
                update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
                unlink_entity_node(actor);
                effect_work = (u8 *)actor - 0x20;
                effect_work->unk_10.i |= 0x80000000;
            }
    case 6:
            if (((R08_80174648_S_80174648_0 *)effect_state)->unk_9B != 6) {
                return;
            }
        }

        {
            if (create_status_linked_render_effect(position, ((void * *)D_80174D1C)[0], ((s16 *)D_80174D14)[0], ((s32 *)D_800DCF5C)) == 0) {
                return;
            }
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            decrement_monster_entry_count(((R08_80174648_S_80174648_1 *)actor)->unk_13, 3);
            update_map_cell_flags_with_item_limit(entity->unk_24, entity->unk_25, 0x300);
            unlink_entity_node(actor);
            effect_work = (u8 *)actor - 0x20;
            effect_work->unk_10.i |= 0x80000000;
            return;
        }

    case 7:
        {
            s32 child_or_angle;
            R08_80174648_S_80174648_7 *child_sprite;
            s32 direction;

            if ((((R08_80174648_S_80174648_1 *)actor)->unk_60.p = advance_staged_entity_load(entity, actor)) == 0) {
                return;
            }
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s = 0x10;
            ((R08_80174648_S_80174648_0 *)effect_state)->unk_9B++;
            ((R08_80174648_S_80174648_10 *)(((R08_80174648_S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((R08_80174648_S_80174648_1 *)actor)->unk_2A.u;
            child_or_angle = ((R08_80174648_S_80174648_1 *)actor)->unk_60.i;
            child_sprite = ((R08_80174648_S_80174648_6_pre *)((void *)child_or_angle))[-1].unk_00;
            child_or_angle = ((R08_80174648_S_80174648_6 *)((void *)child_or_angle))->unk_2A;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + child_or_angle + 0x100) >> 9;
            direction &= 7;
            select_indirect_table_entry(child_sprite, ((R08_80174648_S_80174648_11 *)(child_sprite->unk_2C + direction))->unk_00,
                child_sprite->unk_04);
            child_sprite->unk_14 &= 0xFFFE;
        }

    case 8:
        {

            ((R08_80174648_S_80174648_0 *)effect_state)->unk_96.u--;
            if (((R08_80174648_S_80174648_0 *)effect_state)->unk_96.s > 0) {
                return;
            }
            ((R08_80174648_S_80174648_10 *)(((R08_80174648_S_80174648_1 *)actor)->unk_60.p))->unk_2A = ((R08_80174648_S_80174648_1 *)actor)->unk_8A;
            ((R08_80174648_S_80174648_0_pre *)effect_state)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((R08_80174648_S_80174648_1 *)actor)->unk_6D = 0;
        }
        }
}

void finish_actor_floor_trap_then_resume_effect_behavior(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_behavior_and_effect;
    }
}

void finish_actor_action_flag_propagation_then_resume_effect_behavior(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_actor_behavior_and_effect;
    }
}
