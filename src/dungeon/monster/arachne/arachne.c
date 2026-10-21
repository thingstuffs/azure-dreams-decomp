#include "modules/dungeon_resource12_slot0.h"
#include "shared/sprite_frame_state.h"

void * (*const resource12_slot0_entry0)(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) = func_8017087C;
void (*const resource12_slot0_entry1)(void *entity, R12_80170A44_S_80170A28_2 *motion, void *part) = create_directional_template_effect;

void *func_8017087C(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    R12_8017087C_Work *work;
    void *obj;
    R12_8017087C_S_8017087C_1 *part_a;
    SpriteFrameState *part_b;
    void *resource;
    R12_8017087C_Work *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;
    void *call_a1;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (R12_8017087C_Work *)((u8 *)obj + 0x20);
        ((R12_8017087C_S_8017087C_0 *)obj)->unk_10 = ((u8 *)create_directional_template_effect);
        work->byte13 = 0xC;
        register_node(obj, project_sprite_chain);

        resource = ((u8 *)D_80175A54);
        part_a = ((R12_8017087C_S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((R12_8017087C_S_8017087C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->frameTable = resource;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            work->flags14 = left;
            work->flags1c = right;
        } else if (kind >= 2) {
            left = work->flags14 | 0x2000;
            right = work->flags1c | 0x2000;
            work->flags14 = left;
            work->flags1c = right;
        } else {
            call_a1 = obj;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(work->flags14 & 0x200)) {
                    call_a1 = part_a;
                    left = generate_random_value();
                    call_a1 = obj;
                    if (left & 1) {
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = ((u8 *)D_80175A9C);
                    }
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, spawn_flags);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = ((void *)update_actor_state_and_select_target);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

void create_directional_template_effect(void *entity, R12_80170A44_S_80170A28_2 *motion, void *part)
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
    R12_80170A44_EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 entity_flags;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(R12_80170A44_EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (R12_80170A44_EntityCallback)((void *)update_actor_state_and_select_target)) {
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
        R12_80170A44_EntityCallback update_callback;
        update_callback = (*(R12_80170A44_EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    ((R12_80170A44_EntityCallback *)D_80175AAC)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    if ((s16)old_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, part, entity);
    }

    part_flags = ((R12_80170A44_S_80170A28_0 *)part)->unk_14;
    if (!(part_flags & 0x8000)) {
        rounded_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        direction_index = state_or_direction;
        direction_copy = state_or_direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_copy) {
            if (((R12_80170A44_S_80170A28_0 *)part)->unk_2C != 0) {
                select_indirect_table_entry(part,
                              ((R12_80170A44_S_80170A28_0 *)part)->unk_2C[direction_copy],
                              ((R12_80170A44_S_80170A28_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            ((R12_80170A44_S_80170A28_0 *)part)->unk_14 |= 1;
        } else {
            ((R12_80170A44_S_80170A28_0 *)part)->unk_14 &= 0xFFFE;
        }
        if (!(((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C & 0x20)) {
            if (!(((R12_80170A44_S_80170A28_0 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((R12_80170A44_S_80170A28_0 *)part)->unk_14 |= 0x7000;
        }
        apply_monster_koyaw_data(((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((R12_80170A44_S_80170A28_0 *)part)->unk_14 = new_part_flags;
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
                               (s16)(((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
        if (ground_height < 0x200) {
            base_height = (s16)((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
            } else if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            } else {
                motion->unk_14 = 0;
                ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height - ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88;
            }

            entity_flags = ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = ((s16)sample_terrain_surface_height(
                    (((R12_80170A44_S_80170A28_0 *)part)->unk_24 << 6) | 0x20,
                    (((R12_80170A44_S_80170A28_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88 - ground_height;
                ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_88 = ground_height;
            }
        } else {
            ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((R12_80170A44_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    }

    entity_base = (u8 *)entity_base + 0x88;
    motion->unk_0A =
        *(u16 *)entity_base + (*(u16 *)((u8 *)entity + 0x92));
    ((R12_80170A44_S_80170A28_0 *)part)->unk_14 |= 0x40;

    return;
}

void update_actor_state_and_select_target(void *entity, void *context, void *sprite, void *actor)
{
    u8 *effect_table;
    s32 next_state;
    s16 path_distance;
    s16 target_angle;
    s32 actor_flags;
    s32 action_index;
    s8 tile_id;
    s32 current_state;
    u16 action_flags;
    ActorRecord *owner;

    if (g_dungeon_status.flags & 0x1000) {
        ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 14;
        advance_actor_path_script_step(entity, context, sprite, actor);
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_25 == 0) {
        advance_actor_pending_action(entity, context, sprite, actor);
        if (((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_80175A9C)) {
            return;
        }
        {
            u8 *effects = ((u8 *)D_80175A94);
            ((SpriteFrameState *)sprite)->frameTable = effects;
            select_sprite_entry(
                sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                0);
        }
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_80175A9C)) {
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 13;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9B = 1;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_8C = 0;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, ((u8 *)D_80175A94)) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x100) {
            begin_pushed_actor_move(entity, context, sprite, actor);
            return;
        }

        current_state = ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = ((u8 *)D_80175A54);

            if (((SpriteFrameState *)sprite)->frameTable != effect) {
                ((SpriteFrameState *)sprite)->frameTable = effect;
                select_sprite_entry(
                    sprite,(u8)(effect[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((R12_80170E70_S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, ((u8 *)D_80175A5C)) != 0) {
                return;
            }
        }

        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            func_80173D64(entity, context, sprite, actor);
            return;
        }

        if ((s16)can_entity_gain_level(actor) != 0) {
            if ((s16)process_selected_actor_record(entity, context, sprite, actor) != 0) {
                func_8017526C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = ((s8)find_active_rect_containing_point((u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25));
    ((SpriteFrameState *)sprite)->unk_26 = tile_id;

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x20) {
            update_actor_status_and_food(actor);
            return;
        }
        if (*(u16 *)&((SpriteFrameState *)sprite)->unk_24 == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8017162C(entity, context, sprite, actor);
            return;
        }

        action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        actor, (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8017162C(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((R12_80170E70_S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_80171DD8(entity, context, sprite, actor) != 0) {
                return;
            }
            select_and_start_target_action(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = ((s16)get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_distance));
            owner = primary_actor_record;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)update_actor_state_and_select_target));
                return;
            }

        case 11:
            update_actor_status_and_food(actor);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)update_actor_state_and_select_target));
            return;

        default:
            func_8017162C(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((dungeon_rooms[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)compare_monster_neighbor_values((u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25,(u8)(reference_tile_object.tile_position.parts.tile_x),(u8)(reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
                        ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &path_distance));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((SpriteFrameState *)sprite)->flags & 0x40) {
        return;
    }
    effect_table = ((u8 *)D_80175A54);
    if (((SpriteFrameState *)sprite)->frameTable == effect_table) {
        return;
    }
    {
        u8 *effects = effect_table;
        ((SpriteFrameState *)sprite)->frameTable = effects;
        select_sprite_entry(
            sprite,(u8)(effects[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
            0);
    }
}

void advance_actor_path_script_step(void *controller, void *context, void *entity, void *path_state)
{
    void *state = path_state;
    s32 move_flags;
    s16 direction;
    s16 move_result;
    s16 x;
    s32 y;
    s32 control_flags;

    if (((R12_801713D4_S_8017139C_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((R12_801713D4_S_8017139C_0 *)state)->unk_71.u <= ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s) {
        return;
    }

    if (*(u8 * *)&((SpriteFrameState *)entity)->frameTable != ((u8 *)D_80175A4C)) {
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A4C);
        select_sprite_entry(
            entity,
            ((u8 *)D_80175A4C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_801713D4_S_8017139C_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((SpriteFrameState *)entity)->unk_24;
    y = ((SpriteFrameState *)entity)->unk_25;
    move_flags = 0x3000;
    if (((R12_801713D4_S_8017139C_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    direction = ((s16)get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_74,
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)controller + 0x98));
    move_result = ((s16)check_movement_clearance_and_height(direction, entity, state, 0x20));

    ((SpriteFrameState *)entity)->unk_24 =
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((SpriteFrameState *)entity)->unk_25 =
        ((R12_801713D4_S_8017139C_3 *)((u8 *)state + ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.s))->unk_7C;
    ((R12_801713D4_S_8017139C_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((SpriteFrameState *)entity)->unk_24;
        s32 next_y = ((SpriteFrameState *)entity)->unk_25;

        if (((R12_801713D4_S_8017139C_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    ((R12_801713D4_S_8017139C_0 *)state)->unk_2A = direction;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(((SpriteFrameState *)entity)->flags & 0x8000)) {
            advance_linked_actor_motion_script(controller, context, entity, state);
        } else {
            ((R12_801713D4_S_8017139C_2 *)controller)->unk_9A = 0xF;
        }
    } else {
        control_flags = ((R12_801713D4_S_8017139C_2 *)controller)->unk_98;
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_9A = 0xF;
        control_flags &= ~8;
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_98 = control_flags;
    }
    ((R12_801713D4_S_8017139C_2 *)controller)->unk_8C = 0;
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 0;
        return;
    }

    ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 8;
    {
        s32 step_count = ((R12_801713D4_S_8017139C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((R12_801713D4_S_8017139C_2 *)controller)->unk_96 = 8 / step_count;
        }
    }
}

void func_8017162C(void *move_data, void *context, void *position_data, void *actor_data)
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

    if ((dungeon_flags & 0x4000) || ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)func_80171DD8(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25);
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(((R12_8017162C_S_80171C34_7 *)(((R12_8017162C_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R12_8017162C_S_80171C34_7 *)(((R12_8017162C_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25,(s16)(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((R12_8017162C_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((SpriteFrameState *)position_data)->unk_24 == (u16)target_x &&
                    ((SpriteFrameState *)position_data)->unk_25 == (u16)target_y) {
                    ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)compare_monster_neighbor_values(
                        ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((R12_8017162C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (*(s8 *)&((SpriteFrameState *)position_data)->unk_26 >= 0 &&
               ((R12_8017162C_DungeonRecord *)dungeon_rooms)[*(s8 *)&((SpriteFrameState *)position_data)->unk_26].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((R12_8017162C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->unk_24,(u8)((SpriteFrameState *)position_data)->unk_25,(s16)(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R12_8017162C_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &reference_tile_object;
            ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)compare_monster_neighbor_values(
                    ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(s16)((s16)(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((R12_8017162C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = ((R12_8017162C_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R12_8017162C_S_80171C34_8 *)((u8 *)actor_data + (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((SpriteFrameState *)position_data)->unk_24;
            ((R12_8017162C_S_80171C34_8 *)((u8 *)actor_data + (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((SpriteFrameState *)position_data)->unk_25;
            ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((SpriteFrameState *)position_data)->unk_24, ((SpriteFrameState *)position_data)->unk_25,
                (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((SpriteFrameState *)position_data)->unk_24 += *x_step;
                ((SpriteFrameState *)position_data)->unk_25 += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)((SpriteFrameState *)position_data)->unk_24,(s16)((SpriteFrameState *)position_data)->unk_25,(u16)((((R12_8017162C_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != *(u16 *)&((SpriteFrameState *)position_data)->unk_24) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->unk_58 + 0x20)) != 0) {
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
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R12_8017162C_S_80171C34_5 *)move_data)->unk_9C.u = ((SpriteFrameState *)position_data)->unk_26;
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R12_8017162C_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((SpriteFrameState *)position_data)->unk_24 << 6) | 0x20,
        (((SpriteFrameState *)position_data)->unk_25 << 6) | 0x20,(s16)((s16)(((R12_8017162C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R12_8017162C_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}

void advance_linked_actor_motion_script(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = ((u8 *)D_80175A64);
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}

s32 func_80171DD8(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor)
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

    target_angle = place_actor_at_directional_neighbor(actor, sprite->unk_24, sprite->unk_25, actor->facing);
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
        sprite->frameTable = D_80175A54;
        select_sprite_entry(sprite, (D_80175A54)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


void select_and_start_target_action(void *action_state, void *action_context, void *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(s32 **)((u8 *)sprite + 0x2C)) = ((u8 *)D_80175A54);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)D_80175A54)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

s32 func_801720B4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_8017162C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        func_8017162C(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R12_801720B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R12_801720B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R12_801720B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R12_801720B4_S_80172628_0 *)entity)->unk_46 = (u16) (((R12_801720B4_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

void finish_actor_tile_move_then_select_target(R12_801721F8_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)update_actor_state_and_select_target);
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}

void complete_actor_arc_movement(void *action, void *motion, void *map_actor, void *actor) {
    s32 target_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((R12_80172290_S_80172290_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)map_actor)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)map_actor)->frameTable = ((u8 *)D_80175A6C);
        select_sprite_entry(
            map_actor,
            ((u8 *)D_80175A6C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((R12_80172290_S_80172290_0 *)action)->unk_98 |= 8;
        ((ObjectPosition *)motion)->velocity_z = 0xFFF00000;
        ((ActorRecord *)actor)->flags1C &= 0xF7FFFFFF;
        ((R12_80172290_S_80172290_0 *)action)->unk_A0 = 0;
        ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        frames_left = ((R12_80172290_S_80172290_0 *)action)->unk_96.s;
        ((R12_80172290_S_80172290_0 *)action)->unk_90 -= ((R12_80172290_S_80172290_0 *)action)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)map_actor)->unk_24 << 6;
                s32 current_x = ((ObjectPosition *)motion)->x.w.i - 0x20;

                ((ObjectPosition *)motion)->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)map_actor)->unk_25 << 6;
                s32 current_y = ((ObjectPosition *)motion)->y.w.i - 0x20;

                ((ObjectPosition *)motion)->velocity_y = ((target_y - current_y) << 16) /
                    ((R12_80172290_S_80172290_0 *)action)->unk_96.s;
            }
            ((R12_80172290_S_80172290_0 *)action)->unk_A0 += ((ObjectPosition *)motion)->velocity_z;
            ((ObjectPosition *)motion)->velocity_z += 0x40000;
        }
        ((R12_80172290_S_80172290_0 *)action)->unk_90 += ((R12_80172290_S_80172290_0 *)action)->unk_A0;
        if (((R12_80172290_S_80172290_0 *)action)->unk_96.s < 0) {
            ((R12_80172290_S_80172290_0 *)action)->unk_90 = 0;
            ((R12_80172290_S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= 0x08000000;
            ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & 0x08000000) {
            ((R12_80172290_S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((ObjectPosition *)motion)->velocity_z = 0;
            ((ObjectPosition *)motion)->velocity_y = 0;
            ((ObjectPosition *)motion)->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)map_actor)->unk_24, ((SpriteFrameState *)map_actor)->unk_25);
            ((SpriteFrameState *)map_actor)->frameTable = ((u8 *)D_80175A74);
            select_sprite_entry(
                map_actor,
                ((u8 *)D_80175A74)[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
        }
        break;
    }

    next_timer = ((R12_80172290_S_80172290_0 *)action)->unk_96.u - 1;
    ((R12_80172290_S_80172290_0 *)action)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((ObjectPosition *)motion)->velocity_z = 0;
        ((ObjectPosition *)motion)->velocity_y = 0;
        ((ObjectPosition *)motion)->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)map_actor)->unk_24, ((SpriteFrameState *)map_actor)->unk_25);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {
            u32 count;
            s32 signed_count;

            signed_count = g_dungeon_status.activity_counts.parts.pending_movement_count;
            count = ((u16)g_dungeon_status.activity_counts.parts.pending_movement_count);

            if (signed_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count = count - 1;
            }
        }

        actor_flags = ((u32)((ActorRecord *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((ActorRecord *)actor)->action_flags & 0x8000) {
                ((ActorRecord *)actor)->action_flags &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((ActorRecord *)actor)->facing = ((s16)get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)map_actor)->unk_24, ((SpriteFrameState *)map_actor)->unk_25,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance));
            }
        }

        if ((check_actor_floor_trap(map_actor, actor) << 16) > 0) {
            ((R12_80172290_S_80172290_0 *)action)->unk_8C = ((void *)update_actor_state_and_select_target);
            on_actor_status_updated(actor);
        }
    }
}

void check_boss_effect_threshold(Resource12CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_select_target;
        }
    }
}

void advance_action_and_spawn_effect(void *action, void *motion, void *entity, void *actor) {
    s16 effect_offset[3];
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 state;
    s32 timer;
    u8 next_state;
    s32 shifted_timer;
    void *action_actor;
    void *effect;
    u8 *effect_data;

    state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.s;
    dir_offset = (((R12_80172654_S_80172654_1 *)actor)->unk_2A.s >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + dir_offset);
    dir_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + dir_offset);
    timer = ((R12_80172654_S_80172654_0 *)action)->unk_96.s - 1;
    ((R12_80172654_S_80172654_0 *)action)->unk_96.s = timer;

    switch (state) {
    case 0:
        action_actor = actor;
        if (((SpriteFrameState *)entity)->flags & 0x8000) {
            ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = 0xFF;
            ((SpriteFrameState *)entity)->flags |= 0x6000;
            resolve_attack_damage_and_effects(action_actor, entity,(s16)(((R12_80172654_S_80172654_3 *)action_actor)->unk_2A),(s16)(1));
            return;
        }
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C = (-dir_x) << 17;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 = (-dir_y) << 17;
        ((R12_80172654_S_80172654_4 *)motion)->unk_14 = 0;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A4C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        timer = 8;
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = timer;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 1:
        shifted_timer = timer << 16;
        if (shifted_timer > 0)
            return;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 = 0;
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C = 0;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A8C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A8C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 2:
        if (((((SpriteFrameState *)entity)->unk_04 == 4) &&
             (((SpriteFrameState *)entity)->flags & 0x1000)) ||
            (((SpriteFrameState *)entity)->flags & 0x8000)) {
            ((SpriteFrameState *)entity)->flags |= 0x800;
            ((R12_80172654_S_80172654_0 *)action)->unk_96.s = 0x10;
            if (resolve_record_orientation_or_fallback(*(s32 *)&((SpriteFrameState *)entity)->source, entity, effect_offset,(s16)(0)) == 0) {
                effect_offset[2] = 0;
                effect_offset[1] = 0;
                effect_offset[0] = 0;
            }
            effect = allocate_list_node(0x12, ((u8 *)(&scene_object_list_anchor)));
            if (effect != NULL) {
                register_node(effect, ((u8 *)build_linked_curved_wireframe_grid));
                ((R12_80172654_S_80172654_5 *)effect)->unk_10 = ((u8 *)dim_effect_after_delay);
                ((R12_80172654_S_80172654_5 *)effect)->unk_20 = ((R12_80172654_S_80172654_4 *)motion)->unk_00.at02.v + effect_offset[0];
                effect_data = (u8 *)effect + 0x20;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_02 = ((R12_80172654_S_80172654_4 *)motion)->unk_04.at02.v + effect_offset[1];
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_04 = ((R12_80172654_S_80172654_4 *)motion)->unk_0A + effect_offset[2];
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_08 = 0xC0C0C0;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_0E = 8;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_12 =
                    sample_terrain_surface_height(((((SpriteFrameState *)entity)->unk_24 + dir_x) << 6) & 0xFFC0,
                                  ((((SpriteFrameState *)entity)->unk_25 + dir_y) << 6) & 0xFFC0,(s16)((s16)(((R12_80172654_S_80172654_4 *)motion)->unk_0A - 0x80))) -
                    ((R12_80172654_S_80172654_4 *)motion)->unk_0A;
                ((R12_80172654_S_80172654_6 *)effect_data)->unk_10 = ((R12_80172654_S_80172654_1 *)actor)->unk_2A.s;
            }
            next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
            next_state += 1;
            ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
            return;
        }
        return;
    case 3:
        if ((s16)timer == 0xA) {
            resolve_attack_damage_and_effects(actor, entity,(s16)(((R12_80172654_S_80172654_1 *)actor)->unk_2A.u),(s16)(1));
            play_sound_if_enabled(0x813);
        }
        if (((R12_80172654_S_80172654_0 *)action)->unk_96.u > 0)
            return;
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = 8;
        ((SpriteFrameState *)entity)->flags &= 0xF7FF;
        next_state = ((R12_80172654_S_80172654_0 *)action)->unk_9B.u;
        next_state += 1;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = next_state;
        return;
    case 4:
        if ((timer << 16) > 0)
            return;
        ((SpriteFrameState *)entity)->frameTable = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(u8)(((u8 *)D_80175A4C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80172654_S_80172654_1 *)actor)->unk_2A.u + 0x100) >> 9) & 7]),
            0);
        ((R12_80172654_S_80172654_0 *)action)->unk_96.s = state;
        ((R12_80172654_S_80172654_0 *)action)->unk_9B.s = 0xFF;
        return;
    case 0xFF:
        ((R12_80172654_S_80172654_4 *)motion)->unk_0C =
            (s32)((((((SpriteFrameState *)entity)->unk_24 << 6) + 0x20) << 16) -
                  ((R12_80172654_S_80172654_4 *)motion)->unk_00.at00.v) >> 1;
        ((R12_80172654_S_80172654_4 *)motion)->unk_10 =
            (s32)((((((SpriteFrameState *)entity)->unk_25 << 6) + 0x20) << 16) -
                  ((R12_80172654_S_80172654_4 *)motion)->unk_04.at00.v) >> 1;
        if ((((SpriteFrameState *)entity)->flags & 0xE000) ||
            (((R12_80172654_S_80172654_0 *)action)->unk_96.u <= 0)) {
            ((R12_80172654_S_80172654_4 *)motion)->unk_14 = 0;
            ((R12_80172654_S_80172654_4 *)motion)->unk_10 = 0;
            ((R12_80172654_S_80172654_4 *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion,(u8)((SpriteFrameState *)entity)->unk_24,(u8)((SpriteFrameState *)entity)->unk_25);
            spend_actor_mp(actor, 0x100);
            ((R12_80172654_S_80172654_0 *)action)->unk_8C = ((void *)update_actor_state_and_select_target);
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (((R12_80172654_S_80172654_1 *)actor)->unk_6D == 0) {
                ((R12_80172654_S_80172654_1 *)actor)->unk_46 &= 0x7FFF;
                return;
            }
            (*(void * *)actor_update_node_cursor) = (u8 *)actor - 0x20;
        }
        return;
    default:
        return;
    }
}

void advance_actor_motion_and_wait(void *action, void *transform, void *sprite, ActorRecord *actor)
{
    u16 saved_pos[4];
    u8 *motion;
    s16 special_motion;
    void *target;
    s32 wait_ticks;
    u8 *action_state;

    special_motion = 0;
    switch (((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->action_flags & 0x3FFF) {
            case 7:
                special_motion = 1;
                /* fallthrough */
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 6:
                special_motion = 1;
                /* fallthrough */
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 5:
                special_motion = 1;
                /* fallthrough */
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        } else {
            switch (actor->action_flags & 0x3FFF) {
            case 3:
                motion = (u8 *)actor + 0xE;
                break;
            case 2:
                motion = (u8 *)actor + 0xB;
                break;
            case 1:
                motion = (u8 *)actor + 8;
                break;
            default:
                motion = (u8 *)0;
                break;
            }
        }

        if (*motion != 0) {
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s16 use_special = special_motion;
                if (use_special != 0) {
                    target = primary_actor_record;
                    actor->target = target;
                    action_state = ((R12_80172AF8_S_80172AF8_2_pre *)target)[-1].unk_00;
                    actor->target_tile_x = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_24;
                    actor->target_tile_y = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_25;
                } else if (item_action_definitions[*motion].kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        action_state = ((R12_80172AF8_S_80172AF8_2_pre *)target)[-1].unk_00;
                        actor->target_tile_x = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_24;
                        actor->target_tile_y = ((R12_80172AF8_S_80172AF8_3 *)action_state)->unk_25;
                    }
                } else {
                    actor->target =
                        scan_monster_along_heading(actor,(u8)(((SpriteAnimationTableView *)sprite)->unk_24),(u8)(((SpriteAnimationTableView *)sprite)->unk_25),(s16)(actor->facing), 0x10);
                    actor->target_tile_x = abs(actor->target_tile_x);
                    actor->target_tile_y = abs(actor->target_tile_y);
                }
            }
            saved_pos[0] = ((u16)((EntityRec *)transform)->x.w.i);
            saved_pos[1] = ((u16)((EntityRec *)transform)->y.w.i);
            saved_pos[2] = ((u16)((EntityRec *)transform)->z.w.i);
            transform = (void *)create_actor_spell_effect(actor, motion,(s16)(special_motion), (u8 *)action + 0x98);
            if (transform == 0) {
                return;
            }
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(saved_pos,(s16)((*motion - 1) % 3));
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B + 1;
            return;
        }

        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)(((SpriteAnimationTableView *)sprite)->unk_24),(u8)(((SpriteAnimationTableView *)sprite)->unk_25));
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)&primary_actor_record->unk_A4 + 2)) = (*(u16 *)((u8 *)primary_actor_record + 0xA6)) - 1;
        advance_status_timers(actor);
        actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_8C = ((u8 *)update_actor_state_and_select_target);
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            return;
        }
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_9B + 1;
                                /* fallthrough */
    case 2:
        if ((((SpriteAnimationTableView *)sprite)->unk_04 == 4 && (((SpriteAnimationTableView *)sprite)->unk_14 & 0x1000)) ||
            (((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000)) {
            ((SpriteAnimationTableView *)sprite)->unk_14 |= 0x800;
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = 0x20;
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_98 |= 0x80;
        }
        wait_ticks = ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 - 1;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = wait_ticks;
        if ((s16)wait_ticks <= 0) {
            ((R12_80172AF8_S_80172AF8_0 *)action)->unk_96 = 0;
            ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        }
        if ((((SpriteAnimationTableView *)sprite)->unk_14 & 0xE000) == 0) {
            return;
        }
        ((EntityRec *)transform)->flags14 = 0;
        ((EntityRec *)transform)->unk_10 = 0;
        ((EntityRec *)transform)->unk_0C = 0;
        set_record_integer_tile_center(transform,(u8)(((SpriteAnimationTableView *)sprite)->unk_24),(u8)(((SpriteAnimationTableView *)sprite)->unk_25));
        {
            u8 *idle_frames = ((u8 *)D_80175A54);

            if (((SpriteAnimationTableView *)sprite)->unk_2C != idle_frames) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = idle_frames;
                select_sprite_entry(sprite,
                    idle_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        action_state = (u8 *)&g_dungeon_status.turn_scale;
        if (((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0C != 0) {
            return;
        }
        ((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0A = ((R12_80172AF8_S_80172AF8_7 *)action_state)->unk_0A - 1;
        ((SpriteAnimationTableView *)sprite)->unk_14 &= 0xF7FF;
        ((R12_80172AF8_S_80172AF8_0 *)action)->unk_8C = ((u8 *)update_actor_state_and_select_target);
        advance_status_timers(actor);
        if (actor->pending_turn_updates > 0) {
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
        actor->target_tile_y = 0;
        actor->target_tile_x = 0;
        actor->action_flags &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        break;
    }
}

void apply_knockback_then_restore_target_selection(R12_80172FE8_S_801730B8_1 *action, ObjectPosition *motion, SpriteFrameState *entity, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_addr;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;
    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 18;
        action->unk_9B++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, ((s32 *)D_80175A94));
            return;
        }
        if (entity->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)source)->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, ((s32 *)D_80175A94));
            return;
        } else {
            action->unk_96.s = 8;
            action->unk_9B++;
        }
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_x = entity->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->unk_24, entity->unk_25);

        tracked_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_addr & 0x7FFFFFFF;
        }
        action->unk_8C = ((void *)update_actor_state_and_select_target);
        return;

    default:
        return;
    }
}

void advance_entity_fade_effect(R12_801732EC_EffectState *effect, void *unused, R12_801732EC_Entity *entity, R12_801732EC_Object *object) {
    s32 state;
    s32 object_status;
    s32 status_mask;
    s32 direction_index;
    s32 fade_delta;
    s32 strength;
    s16 countdown;
    u16 timer;
    u8 x;
    u8 y;

    state = effect->state;
    switch (state) {
    case 0:
        if (*(s16 *)(((u8 *)(&g_dungeon_status)) + 0xA) != 0) {
            return;
        }
        effect->state = 1;
                        /* fallthrough */
    case 1:
        object_status = object->field14;
        if (object_status & 0x4000) {
            status_mask = object_status & 0x20000000;
            if (status_mask == 0) {
                announce_familiar_defeat(object);
            }
        }
        play_sound_if_enabled(0x805);
        entity->field10 = 0x20;
        entity->flags |= 0xC;
        entity->field12 -= 0x80;
        object->flags |= 0x10000000;
        entity->value = 0x808080;
        effect->state++;
        return;
    case 2:
        entity->value += 0xFFF7F7F8;
        if (!(entity->flags & 0x6000)) {
            return;
        }
        object->flags |= 0x10000000;
        entity->table = ((u8 *)D_80175AA4);
        effect->timer = 0x80;
        effect->countdown = 0;
        direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + object->angle + 0x100) >> 9) & 7;
        select_sprite_entry(entity,(u8)(entity->table[direction_index]), 0);
        effect->state++;
        return;
    case 3:
        fade_delta = 0xFFF7F7F8;
        object->flags |= 0x10000000;
        entity->value += fade_delta;
        if ((entity->field10 == 0x20) && ((u8)entity->value < 0x40)) {
            entity->field10 = 0x60;
            entity->value = 0xF0F0F0;
        }
        countdown = effect->countdown - 1;
        effect->countdown = countdown;
        if (countdown >= 0) {
            entity->flags |= 0x800;
        } else {
            entity->flags &= 0xF7FF;
            timer = effect->timer + 0x60;
            effect->timer = timer;
            effect->countdown = (u16)((s32)(timer << 16) >> 24);
        }
        if ((entity->type == 2) && (entity->flags & 0x1000)) {
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + object->angle + 0x100) >> 9) & 7;
            select_sprite_entry(entity,(u8)(entity->table[direction_index]), 0);
        }
        if ((u8)entity->value < 0x11) {
            if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)object - 0x20)) {
                *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
            }
            distribute_experience_and_report_gains(object);
            detach_record_and_update_slot_state(object);
            x = entity->x;
            y = entity->y;
            strength = 0x3000;
            if (object->flags & 0x2000) {
                strength = 0x300;
            }
            update_map_cell_flags_with_item_limit((u8)(x),(u8)(y), strength);
            unlink_entity_node(object);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        return;
    default:
        return;
    }
}

void advance_familiar_defeat_sequence(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}

void func_80173634(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

void finish_actor_hop_and_grow_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}

void func_8017368C(void *in_controller, void *in_context, void *sprite, void *in_actor)
{
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B;
    switch (state) {
    case 0:
        if (((R12_8017368C_S_80173358_1 *)sprite)->unk_14 & 0xE000) {
            u8 *direction_anims;
            DungeonGlobalStatus *system_base;

            direction_anims = ((u8 *)D_80175A9C);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_8017368C_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B++;
        }
        return;

    case 1:
        if ((get_entity_effect_value(actor, 1) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &g_dungeon_status;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((R12_8017368C_S_80173358_2 *)actor)->unk_64 != 0) &&
                (begin_ready_actor_directional_action(in_controller, context, sprite, 0) != 0)) {
                return;
            }

            if (((R12_8017368C_S_80173358_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_controller, context, sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((R12_8017368C_S_80173358_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_controller, context, sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_controller, context, sprite, actor);
                func_80173D64(in_controller, context, sprite, actor);
                return;
            }

            if (((R12_8017368C_S_80173358_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                    (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &reference_tile_object;
                coordinate = ((R12_8017368C_S_80173358_1 *)sprite)->unk_26;
                if ((((coordinate == origin->room_index) &&
                    (coordinate >= 0)) ||
                    (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, 1);
                }
            }

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = ((u8 *)D_80175AA4);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_8017368C_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        sprite = (u8 *)sprite + 0x14;
        if (!(*(u16 *)sprite & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)++;
            ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B++;
            return;
        }
        break;

    case 2:
        if (!(((R12_8017368C_S_80173358_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
        }

        break;
    default:
        return;
    }
    ((R12_8017368C_S_80173358_2 *)actor)->unk_1C &= ~0x200;
    in_controller = (u8 *)in_controller + 0x8C;
    *(void **)in_controller = ((u8 *)update_actor_state_and_select_target);
}

void resume_actor_target_selection_after_status_animation(void *controller, void *context, void *sprite, ActorRecord *entity)
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
        direction_anims = ((u8 *)D_80175A9C);
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

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80175A94);
            select_sprite_entry(sprite,
                ((u8 *)D_80175A94)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
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
            func_80173D64(controller, context, sprite, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (entity->mp == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80175A94);
        select_sprite_entry(sprite,
            ((u8 *)D_80175A94)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
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
            ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)update_actor_state_and_select_target);
        }

        return;
    }
}

void func_80173D64(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_state_and_select_target);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_80175A9C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80175A4C);
        select_sprite_entry(entity,(s16)(((u8 *)D_80175A4C)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

void finish_thrown_actor_travel_and_floor_trap_then_select_target(Resource12CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_select_target;
        }
    }
}

void finish_actor_terrain_interpolation_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}

void finish_spinning_actor_fall_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}

void finish_actor_fade_in_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_state_and_select_target;
    }
}

void dim_effect_after_delay(void *effect) {
    s16 state;
    u16 timer;

    state = *(s16 *)((u8 *)effect + 0xC);
    switch (state) {
    case 0:
        timer = *(u16 *)((u8 *)effect + 0xE) - 1;
        *(u16 *)((u8 *)effect + 0xE) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        *(u16 *)((u8 *)effect + 0xC) += 1;
        return;

    case 1:
        if (*(u8 *)((u8 *)effect + 8) < 0x11) {
            ObjectFlagBlock *flags = &object_flag_block;

            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            flags->flags |= 0x8000;
            return;
        } else {
            *(s32 *)((u8 *)effect + 8) += 0xFFEFEFF0;
            return;
        }
    }
}

s32 build_linked_curved_wireframe_grid(u8 *node, s32 next_node, s32 callback_arg2)
{
    R12_80173FDC_Frame frame;
    u8 *effect;
    u8 *vertex_depths;
    u8 *transform_work;
    u8 *depth_base;
    u8 *xy_base;
    u8 *xy_row;
    u8 *ring_depth_row;
    u8 *vertical_xy_row;
    u8 *screen_xy;
    R12_80173FDC_GridPoint *point_base;
    u8 *vertical_depth_row;
    u8 *ring_xy;
    R12_80173FDC_LineG2 *line;
    u8 *tpage;
    u8 *display;
    s32 row;
    s32 col;
    s32 ot_index;
    s32 sin_angle;
    s32 cos_angle;
    s32 addr_mask;
    u8 **display_root = (u8 **)((u8 *)(&g_game_work));

    screen_xy = (u8 *)0x1F800000;
    vertex_depths = (u8 *)0x1F800100;
    transform_work = (u8 *)0x1F800180;
    addr_mask = 0x00FFFFFF;

    for (;;) {
        (frame.desc).points0 = &(frame.points)[0][0];
        (frame.desc).points1 = &(frame.points)[0][0];
        (frame.desc).zero = 0;
        (frame.desc).angle = ((R12_80173FDC_S_80173FDC_0 *)node)->unk_10 - 0x400;
        effect = node;
        if (*(s32 *)screen_xy && next_node) {
            /* retail evidence (decision 45, docs/evidence/r97_decisions.md): both operands of this test are loaded in retail's
               compilation and the arm compiled away. next_node: the tail's successor load (lw $5,8($5)) survives as this test's
               operand (lane r118_fable_f4). The scratchpad word: jump2 deleted it with the branch; its fingerprint is the empty
               load-delay slot after the (frame.desc).angle field load (sched2 cannot issue the effect store there while this load waits on
               the angle store), and the branch's label is why node is reloaded for ((s16)func_80065F90(lane r118_opus_o9; JP build:
               this placement matches JP at stock 2.7.2)). The arm reconstructs a conditional update of a local nothing reads; the
               bytes fix the test's shape (a scratchpad word, then next_node), not its meaning. The second parameter is the
               loop-carried successor field the tail reloads. */
            row = 0;
        }
        (frame.desc).value = ((s16)func_80065F90(((R12_80173FDC_S_80173FDC_0 *)node)->unk_12, 0x40));
        row = 0;
grid_row:
        col = 7;
grid_loop:
        {
            R12_80173FDC_GridPoint *point;
            s32 angle;
            s32 point_offset;

            next_node = row * ((8 - ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_0E) << 4);
            point_base = &(frame.points)[0][0];
            point_offset = col << 3;
            point_offset += row << 6;
            point = (R12_80173FDC_GridPoint *)((u8 *)point_base + point_offset);

            if (next_node < 0) {
                next_node += 7;
            }
            point->y = next_node >> 3;
            angle = col << 9;
            sin_angle = func_800644B8(angle);
            point->x = (sin_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
            cos_angle = func_80064584(angle);
            point->z = (cos_angle * func_800644B8(
                ((s32)((u32)point->y << 16) >> 12) + 0x800)) >> 18;
        }
        col--;
        if (col >= 0) {
            goto grid_loop;
        }
        row++;
        if (row < 8) {
            goto grid_row;
        }

        (frame.desc).count = 0x40;
        (frame.desc).header = *(R12_80173FDC_Header8 *)effect;
        (frame.desc).one = 1;
        transform_rotated_vertices(&(frame.desc));

        {
            u8 *vertex_depth;
            u8 *xy;

            func_80065770((frame.points), screen_xy, vertex_depths, transform_work, transform_work, (frame.desc).count);
            row = 0x38;
            vertical_xy_row = screen_xy + 0xE0;
            vertical_depth_row = vertex_depths + 0x70;
            while (row > 0) {
                col = 7;
                xy = vertical_xy_row + 0x1C;
                vertex_depth = vertical_depth_row + 0x0E;
                while (col >= 0) {
                    ot_index = ((s16)((R12_80173FDC_S_80173FDC_2 *)vertex_depth)->unk_00 +
                        (s16)((R12_80173FDC_S_80173FDC_2_pre *)vertex_depth)[-1].unk_00) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * *)display_root;
                        line = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * *)display_root;
                        tpage = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,(u16)(((u16)func_80066460(0, 1, 0, 0))), 0);

                        line->color0 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((R12_80173FDC_S_80173FDC_4 *)xy)->unk_00;
                        line->xy1 = ((R12_80173FDC_S_80173FDC_4_pre *)xy)[-1].unk_00;

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 = (((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    xy -= 4;
                    vertex_depth -= 2;
                    col--;
                }
                vertical_depth_row -= 0x10;
                vertical_xy_row -= 0x20;
                row -= 8;
            }
        }

        {
            u8 *ring_depth;

            row = 0x30;
            xy_row = screen_xy + 0xC0;
            ring_depth_row = vertex_depths + 0x60;
            while (row > 0) {
                depth_base = ring_depth_row;
                ring_xy = xy_row + 0x1C;
                xy_base = xy_row;
                col = 7;
                ring_depth = ring_depth_row + 0x0E;
                while (col >= 0) {
                    s32 next_col = (col + 1) & 7;
                    ot_index = ((s16)((R12_80173FDC_S_80173FDC_6 *)ring_depth)->unk_00 +
                        (*(s16 *)((u8 *)depth_base + next_col * 2))) >> 3;
                    if ((u32)ot_index < 0x1E0) {
                        display = *(u8 * *)display_root;
                        line = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = (u8 *)line + 0x14;

                        display = *(u8 * *)display_root;
                        tpage = ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2;
                        ((R12_80173FDC_S_80173FDC_3 *)display)->unk_8D0.p2 = tpage + 0x0C;

                        func_80067F20(tpage, 0, 0,(u16)(((u16)func_80066460(0, 1, 0, 0))), 0);

                        line->color0 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        line->color1 = ((R12_80173FDC_S_80173FDC_1 *)effect)->unk_08;
                        func_800667D0(line);
                        func_80066640(line, 1);

                        line->xy0 = ((R12_80173FDC_S_80173FDC_7 *)ring_xy)->unk_00;
                        line->xy1 = (*(u32 *)((u8 *)xy_base + next_col * 4));

                        line->tag = (line->tag & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)line & addr_mask);

                        ((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 = (((R12_80173FDC_S_80173FDC_5 *)tpage)->unk_00 & 0xFF000000) |
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & addr_mask);
                        (*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) =
                            ((*(u32 *)((u8 *)(((R12_80173FDC_RootSlot *)display_root)->ptr) + 0xB0 + ot_index * 4)) & 0xFF000000) |
                            ((u32)tpage & addr_mask);
                    }
                    ring_xy -= 4;
                    ring_depth -= 2;
                    col--;
                }
                xy_row -= 0x20;
                ring_depth_row -= 0x10;
                row -= 8;
            }
        }

        {

            next_node = (s32)((R12_80173FDC_S_80173FDC_0_pre *)node)[-1].unk_00;
            if (next_node == 0) {
                break;
            }
            node = (u8 *)next_node + 0x20;
            next_node = (s32)((R12_80173FDC_S_80173FDC_8 *)next_node)->unk_08;
        }
    }
    return 0;
}

s32 func_8017458C(void *initial_payload, s32 entry_data, R12_8017458C_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R12_8017458C_Scratchpad *scratch = (R12_8017458C_Scratchpad *)0x1F800000;
    R12_8017458C_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_80175B20)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R12_8017458C_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */

void transform_and_queue_line_packets(R12_80174618_S_80174618_4 *endpoints, R12_80174618_S_80174618_1 *position, void *render_params, s16 depth_bias)
{
    u8 *line_packet;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *draw_packet;
    GameWork *work_base;
    u8 *context;
    u8 *screen_start;
    u8 *screen_end;
    u8 *start_vertex;
    u8 *depth_cue;
    u8 *transform_flags;
    u16 flags;
    u16 field_value;
    s32 color_word;
    u16 end_z;
    s32 depth_index;
    R12_80174618_MATRIX matrix;
    R12_80174618_EMPTY_ARG no_arg;

    context = (u8 *)&g_game_work;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_24.s = *(u8 **)context + 0xB0;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_88 = position->unk_02;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_8C = position->unk_06;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_90 = position->unk_0A;
    ((R12_80174618_S_80174618_2 *)render_params)->unk_14 |= 0x8000;

    func_800649A0();

    ((R12_80174618_S_80174618_0 *)scratch)->unk_3C = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_38 = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_34 = 0x2000;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A4 = ((R12_80174618_S_80174618_2 *)render_params)->unk_16;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A8 = ((R12_80174618_S_80174618_2 *)render_params)->unk_1A;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_A6 = ((R12_80174618_S_80174618_2 *)render_params)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    depth_cue = scratch + 0xD0;
    transform_flags = scratch + 0xD4;
    start_vertex = scratch + 0xB0;

    field_value = ((R12_80174618_S_80174618_2 *)render_params)->unk_14;
    context = *(u8 **)context;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_28 = field_value;
    line_packet = ((GpuContext *)context)->packetCursor;
    ((GpuContext *)context)->packetCursor = line_packet + 0x10;

    field_value = endpoints->unk_64;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C0 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B0 = field_value;
    field_value = endpoints->unk_6A;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C8 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B8 = field_value;
    field_value = endpoints->unk_66;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C2 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B2 = field_value;
    field_value = endpoints->unk_6C;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_CA = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_BA = field_value;
    field_value = endpoints->unk_68;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_C4 = field_value;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_B4 = field_value;
    end_z = endpoints->unk_6E;
    screen_start = line_packet + 8;
    screen_end = line_packet + 0xC;
    work_base = &g_game_work;
    depth_index = func_80065590(start_vertex, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          screen_start, screen_end,
                          screen_start, screen_end,
                          depth_cue, transform_flags,
                          (((R12_80174618_S_80174618_0 *)scratch)->unk_CC = end_z,
                           ((R12_80174618_S_80174618_0 *)scratch)->unk_BC = end_z,
                           no_arg));
    depth_index = depth_index - depth_bias - 6;
    ((R12_80174618_S_80174618_0 *)scratch)->unk_100 = depth_index;
    flags = ((R12_80174618_S_80174618_0 *)scratch)->unk_28;

    if (flags & 8) {
        u8 color_code;
        if (flags & 4) {
            color_code = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v | 2;
        } else {
            color_code = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v & 0xFD;
        }
        ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at03.v = color_code;
    }

    color_word = ((R12_80174618_S_80174618_2 *)render_params)->unk_0C.at00.v;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_00.at03.v = 3;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at00.v = color_word;
    ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at03.v = 0x40;
    flags = ((R12_80174618_S_80174618_0 *)scratch)->unk_28;
    if (flags & 8) {
        s32 line_code = flags & 4;
        if (line_code) {
            line_code = 0x42;
        } else {
            line_code = 0x40;
        }
        ((R12_80174618_S_80174618_5 *)line_packet)->unk_04.at03.v = line_code;
    }

    {
        u8 *draw_context;
        ((R12_80174618_P_TAG *)line_packet)->addr = ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr;
        ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr = (u32)line_packet;

        draw_context = work_base->draw_buffer;
        draw_packet = ((GpuContext *)draw_context)->packetCursor;
        ((GpuContext *)draw_context)->packetCursor = draw_packet + 0xC;
        func_80067F20(draw_packet, 0, 0, (u16)func_80066460(0, 1, 0, 0), 0);

        ((R12_80174618_P_TAG *)draw_packet)->addr = ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr;
        ((R12_80174618_P_TAG *)&((R12_80174618_S_80174618_0 *)scratch)->unk_24.u[((R12_80174618_S_80174618_0 *)scratch)->unk_100])->addr = (u32)draw_packet;

        func_80064A40();
    }
}

s32 queue_line_packets_for_node_chain(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        transform_and_queue_line_packets(state, context, data,(s16)(0));
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((R12_80174954_Func800C138CData *)next_node)->context;
        data = ((R12_80174954_Func800C138CData *)next_node)->data;
    }
}

void update_turning_fade_effect_and_model(void *record_data) {
    u16 remaining_count;

    remaining_count = ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((R12_801749A8_S_801748F0_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((R12_801749A8_S_801748F0_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}

void build_animated_spherical_wireframe(void *effect, void *origin, void *tint) {
    s16 ring_angles[10];
    s32 coordinate;
    u32 scale;
    s32 y_coordinate;
    s32 state_m;
    s16 vertices[10][6][3];
    register void *object_origin;
    void *line_data;
    s16 *closing_angle;
    s16 next_angle_index;
    s16 next_meridian;
    s16 next_ring;
    s16 remaining_ticks;
    s16 opening_angle;
    s16 next_opening_ring;
    s16 next_opening_sector;
    s16 closing_angle_value;
    s16 next_closing_ring;
    s16 next_closing_sector;
    s16 prev_angle_index;
    s16 phase;
    s16 meridian;
    s16 ring_sector;
    s16 sector;
    s16 ring;
    s16 ring_index;
    s16 next_segment;
    s32 sector_offset;
    s32 segment_index;
    s32 opening_azimuth;
    s32 closing_azimuth;
    s32 opening_sector_radius;
    s32 closing_sector_radius;
    s32 vertex_base_or_offset;
    s32 radius;
    s32 vertex_offset;
    register s32 signed_ring_index;
    s32 ring_index_shifted;
    u16 closing_progress;
    u16 opening_progress;
    u16 old_phase;
    SpriteFrameState *meridian_render;
    void *segment_start;
    SpriteFrameState *ring_render;
    void *meridian_line;
    void *opening_vertex;
    void *closing_vertex;
    void *sector_or_ring_start;
    void *meridian_object;
    void *segment_end;
    void *ring_object;
    void *next_vertex;
    void *current_vertex;
    void *opening_angle_slot;
    void *closing_angle_slot;
    void *meridian_origin;
    void *ring_origin;
    register void *ring_data;

    object_origin = origin;
    phase = ((R12_801749EC_S_801749EC_0 *)effect)->unk_06;
    if (phase != 1) {
        if (phase < 2) {
        if (phase == 0) {
        s16 *angle_base;
        s32 angle_limit;
        scale = 0x1E;
        ring_index = 1;
        angle_base = ring_angles;
        angle_limit = 0x400;
        ring_angles[0] = (0 - ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C) + 0x400;
        do {
            opening_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
            opening_angle = ((R12_801749EC_S_801749EC_2_pre *)opening_angle_slot)[-1].unk_00 + 0xCC;
            ((R12_801749EC_S_801749EC_2 *)opening_angle_slot)->unk_00 = opening_angle;
            if (opening_angle >= 0x401) {
                ((R12_801749EC_S_801749EC_2 *)opening_angle_slot)->unk_00 = angle_limit;
            }
            next_angle_index = ring_index + 1;
            ring_index = next_angle_index;
        } while (next_angle_index < 0xA);
        for (ring_index = 0; ring_index < 10; ring_index++) {
            for (sector = 0; sector < 6; sector++) {
                coordinate = func_800644B8(ring_angles[ring_index]);
                radius = scale;
                state_m = radius * coordinate;
                vertices[ring_index][sector][2] = state_m >> 0xC;
                state_m = radius * func_80064584(ring_angles[ring_index]);
                opening_azimuth = sector * 682;
                opening_sector_radius = state_m >> 0xC;
                state_m = (s16) opening_sector_radius * func_80064584(opening_azimuth);
                vertices[ring_index][sector][0] = state_m >> 0xC;
                state_m = (s16) opening_sector_radius * func_800644B8(opening_azimuth);
                vertices[ring_index][sector][1] = state_m >> 0xC;
            }
        }
        opening_progress = ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C + 0x64;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = opening_progress;
        if ((s16) opening_progress >= 0x800) {
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0x800U;
        }
        if (((R12_801749EC_S_801749EC_1 *)effect)->unk_08 < 0x16) {
            old_phase = ((R12_801749EC_S_801749EC_1 *)effect)->unk_06;
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0U;
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_06 = old_phase + 1;
        }
        }
        }
    } else {
        {
        s16 *angle_base;
        s32 angle_limit;
        scale = 0x1E;
        ring_index = 8;
        angle_base = ring_angles;
        angle_limit = -0x400;
        ring_angles[9] = (0 - ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C) + 0x400;
        do {
            closing_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
            closing_angle_value = ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_02 - 0xCC;
            ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_00 = closing_angle_value;
            if (closing_angle_value < -0x400) {
                ((R12_801749EC_S_801749EC_4 *)closing_angle_slot)->unk_00 = angle_limit;
            }
            prev_angle_index = ring_index - 1;
            ring_index = prev_angle_index;
        } while ((prev_angle_index << 0x10) != 0);
        for (ring_index = 0; ring_index < 10; ring_index++) {
            for (sector = 0; sector < 6; sector++) {
                coordinate = func_800644B8(ring_angles[ring_index]);
                radius = scale;
                state_m = radius * coordinate;
                vertices[ring_index][sector][2] = state_m >> 0xC;
                state_m = radius * func_80064584(ring_angles[ring_index]);
                closing_azimuth = sector * 682;
                closing_sector_radius = state_m >> 0xC;
                state_m = (s16) closing_sector_radius * func_80064584(closing_azimuth);
                vertices[ring_index][sector][0] = state_m >> 0xC;
                state_m = (s16) closing_sector_radius * func_800644B8(closing_azimuth);
                vertices[ring_index][sector][1] = state_m >> 0xC;
            }
        }
        closing_progress = ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C + 0x64;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = closing_progress;
        if ((s16) closing_progress >= 0x800) {
            ((R12_801749EC_S_801749EC_1 *)effect)->unk_0C = 0x800U;
        }
        }
    }
    for (meridian = 0; meridian < 6; meridian++) {
        for (sector = 0; sector < 9; sector++) {
        meridian_object = func_8003FC64(0x212);
        if (meridian_object != NULL) {
            meridian_line = meridian_object + 0x20;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_1A = 1;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_1C = 1;
            ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_10 = ((u8 *)update_turning_fade_effect_and_model);
            register_node(meridian_object, &queue_line_packets_for_node_chain);
            meridian_render = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_0C;
            meridian_render->tpage_abr = 0x20;
            meridian_render->flags = (u16) (meridian_render->flags | 0xC);
            meridian_origin = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_08;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_00 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_00;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_04 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_04;
            ((R12_801749EC_S_801749EC_9 *)meridian_origin)->unk_08 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_08;
            meridian_render = ((R12_801749EC_S_801749EC_7 *)meridian_object)->unk_0C;
            meridian_render->scale_y = ONE;
            meridian_render->scale_x = ONE;
            meridian_render->color.c.r = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0C;
            meridian_render->color.c.g = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0D;
            meridian_render->color.c.b = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0E;
            segment_index = sector << 0x10;
            segment_index >>= 0x10;
            sector_offset = meridian * 6;
            segment_end = (s8 *)vertices + (sector_offset + ((segment_index + 1) * 0x24));
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_00;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_02;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_12 *)segment_end)->unk_04;
            segment_start = (s8 *)vertices + (sector_offset + (segment_index * 0x24));
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6A = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_00;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6C = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_02;
            ((R12_801749EC_S_801749EC_6 *)meridian_line)->unk_6E = (u16) ((R12_801749EC_S_801749EC_13 *)segment_start)->unk_04;
        }
        }
    }
    for (sector = 1; sector < 9; sector++) {
        meridian = 0;
        {
            s32 signed_outer;
            s32 scaled_outer;
            signed_outer = sector;
            scaled_outer = (signed_outer << 3) + signed_outer;
            vertex_base_or_offset = scaled_outer << 2;
        }
        for (; meridian < 6; meridian++) {
            ring_object = func_8003FC64(0x212);
            if (ring_object != NULL) {
                meridian_line = ring_object + 0x20;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_1A = 1;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_1C = 1;
                ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_10 = ((u8 *)update_turning_fade_effect_and_model);
                register_node(ring_object, &queue_line_packets_for_node_chain);
                ring_render = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_0C;
                {
                    u16 object_flags;
                    s32 object_width;
                    object_flags = ring_render->flags;
                    object_width = 0x20;
                    ring_render->tpage_abr = object_width;
                    object_flags |= 0xC;
                    ring_render->flags = object_flags;
                }
                ring_origin = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_08;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_00 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_00;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_04 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_04;
                ((R12_801749EC_S_801749EC_17 *)ring_origin)->unk_08 = (s32) ((R12_801749EC_S_801749EC_10 *)object_origin)->unk_08;
                ring_render = ((R12_801749EC_S_801749EC_15 *)ring_object)->unk_0C;
                ring_render->scale_y = ONE;
                ring_render->scale_x = ONE;
                ring_render->color.c.r = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0C;
                ring_render->color.c.g = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0D;
                ring_render->color.c.b = (u8) ((R12_801749EC_S_801749EC_11 *)tint)->unk_0E;
                if (meridian != 5) {
                    next_vertex = (s8 *)vertices + (((meridian + 1) * 6) + vertex_base_or_offset);
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_00;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_02;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_19 *)next_vertex)->unk_04;
                } else {
                    sector_or_ring_start = (s8 *)vertices + vertex_base_or_offset;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_64 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_00;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_66 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_02;
                    ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_68 = (u16) ((R12_801749EC_S_801749EC_20 *)sector_or_ring_start)->unk_04;
                }
                current_vertex = (s8 *)vertices + ((meridian * 6) + vertex_base_or_offset);
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6A = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_00;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6C = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_02;
                ((R12_801749EC_S_801749EC_14 *)meridian_line)->unk_6E = (u16) ((R12_801749EC_S_801749EC_21 *)current_vertex)->unk_04;
            }
        }
    }
    {
        remaining_ticks = (u16) ((R12_801749EC_S_801749EC_1 *)effect)->unk_08 - 1;
        ((R12_801749EC_S_801749EC_1 *)effect)->unk_08 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((R12_801749EC_S_801749EC_1_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
        return;
    }
}

void create_offset_effect(void *source_arg, void *spawn_pos_arg, void *unused_context)
{
    void *spawn_pos = spawn_pos_arg;
    u16 render_flags;
    void *effect;
    SpriteFrameState *render_part;
    R12_80175180_S_80175180_4 *position;
    u8 *state;

    effect = func_8003FC64(0x12);
    state = (u8 *)effect + 0x20;
    if (effect != 0) {
        ((R12_80175180_S_80175180_0 *)state)->unk_08 = 0x4A;
        ((R12_80175180_S_80175180_0 *)state)->unk_0A = ((R12_80175180_S_80175180_1 *)source_arg)->unk_96;
        ((R12_80175180_S_80175180_0 *)state)->unk_0C = 0;
        ((R12_80175180_S_80175180_2 *)effect)->unk_10 = ((u8 *)build_animated_spherical_wireframe);
        source_arg = project_sprite_chain;
        register_node(effect, source_arg);
        render_part = ((R12_80175180_S_80175180_2 *)effect)->unk_0C;
        render_flags = render_part->flags;
        render_flags |= 0xC;
        render_part->flags = render_flags;
        render_part->tpage_abr = 0x20;
        render_flags |= 0x80;
        render_part->flags = render_flags;
        position = ((R12_80175180_S_80175180_2 *)effect)->unk_08;
        position->unk_00 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_00;
        position->unk_04 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_04;
        position->unk_08 = ((R12_80175180_S_80175180_5 *)spawn_pos)->unk_08 + 0xFFE80000;
        render_part = ((R12_80175180_S_80175180_2 *)effect)->unk_0C;
        render_part->scale_y = 0x1000;
        render_part->scale_x = 0x1000;
        render_part->color.c.b = 0x80;
        render_part->color.c.r = 0x80;
        render_part->color.c.g = 0x80;
    }
}

void func_8017526C(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)func_8017526C);
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

void fade_effect_to_neutral(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    GameWork *colors = &g_game_work;
    u16 elapsed_ticks;
    u16 fade_ticks;

    if (entity[0x9A] == 0) {
        ((s32 *)D_80175B28)[0] = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            unlink_node(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        elapsed_ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = elapsed_ticks + 1;
        if ((elapsed_ticks & 7) == 0) {
            ((u16 *)D_80175B20)[0]++;
            return;
        }
    } else {
        colors->view.tint.parts.tint_r += (0x80 - colors->view.tint.parts.tint_r) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_g += (0x80 - colors->view.tint.parts.tint_g) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_b += (0x80 - colors->view.tint.parts.tint_b) / *(s16 *)(entity + 0x96);

        fade_ticks = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_ticks;
        if ((fade_ticks << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            *(s32 *)((u8 *)(&object_flag_block)) |= 0x8000;
        }
    }
}

void advance_effect_sequence_and_restore_actor(void *sequence, void *position, SpriteFrameState *record, void *actor) {
    GameWork *scene_color = &g_game_work;
    R12_80175470_S_80175470_2 *node;
    SpriteFrameState *model;
    void *child;
    u8 *target_color;
    s32 direction;
    s32 color_index;
    s32 effect_choice;
    u32 model_color;
    u32 state;
    u8 cd_ready;
    u16 timer;
    u16 next_timer;
    s32 next_state;
    s16 effect_index;

    state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n;
    switch (state) {

    case 0:
        next_state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.v + 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n = next_state;
        return;

    case 1:
        run_cd_image_commands(((u8 *)arachne_image_commands), ((u8 *)D_80175B24), 0);
        ((R12_80175470_S_80175470_0 *)sequence)->unk_AC = 0;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        ((R12_80175470_S_80175470_1 *)actor)->unk_8A = ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u;
        return;

    case 2:
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_80175470_S_80175470_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        if ((*(u8 *)D_80175B24) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u += 0x200;
            return;
        }

        run_cd_image_commands(((u8 *)arachne_image_commands), ((u8 *)D_80175B24), 1);
        sound_set_cd_cue_parameters(0, ((s32 *)cd_cue_base)[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), 0);
        (*(u8 *)D_80175B25) = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((u8 *)D_80175B25));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        create_offset_effect(sequence, position, record);

    case 3:
        timer = ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u;
        next_timer = timer - 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = next_timer;
        if ((s16)next_timer <= 0) {
            cd_ready = (*(u8 *)D_80175B25);
            ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = timer;
            if (cd_ready == 0) {
                return;
            }
            ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
            play_sound_if_enabled(0x300);
            return;
        }
        color_index = lookup_masked_byte_table(actor);
        target_color = ((u8 * *)actor_effect_color_targets)[color_index];
        scene_color->view.tint.parts.tint_r += ((s32)target_color[0]
            - scene_color->view.tint.parts.tint_r) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        scene_color->view.tint.parts.tint_g += ((s32)target_color[1]
            - scene_color->view.tint.parts.tint_g) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        scene_color->view.tint.parts.tint_b += ((s32)target_color[2]
            - scene_color->view.tint.parts.tint_b) / ((R12_80175470_S_80175470_0 *)sequence)->unk_96.s;
        return;

    case 4:
        node = func_8003FC64(0x12);
        if (node == 0) {
            return;
        }
        node->unk_10.p = ((u8 *)fade_effect_to_neutral);
        register_node(node, ((u8 *)func_8017458C));
        ((R12_80175470_S_80175470_0 *)sequence)->unk_A8 = node;
        model_color = 0x00808080;
        *(s32 *)node->unk_08 = ((s32 *)position)[0];
        ((s32 *)node->unk_08)[1] = ((s32 *)position)[1];
        ((s32 *)node->unk_08)[2] = ((s32 *)position)[2];
        (*(s16 *)D_80175B20) = -12;
        model = node->unk_0C;
        model->scale_y = 0x1000;
        model->scale_x = 0x1000;
        model->color.word = model_color;
        effect_choice = lookup_masked_byte_table(actor) - 1;
        effect_index = effect_choice;
        if ((s16)effect_choice < 0) {
            effect_index = func_80069EF8() % 3;
        }
        func_8003DB94(model, ((u8 *)D_8014A000) + ((s32 *)D_80175B14)[(s16)effect_index], 0);
        record->flags |= 0x80;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0;
        next_state = ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n + 1;
store_next_state:
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n = next_state;
        return;

    case 5:
        node = ((R12_80175470_S_80175470_0 *)sequence)->unk_A8;
        model = node->unk_0C;
        if (model->flags & 0xE000) {
            ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
            ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
            decrement_monster_entry_count(((R12_80175470_S_80175470_1 *)actor)->unk_13, 3);
            update_map_cell_flags_with_item_limit(record->unk_24, record->unk_25, 0x300);
            unlink_entity_node(actor);
            node = (u8 *)actor - 0x20;
            node->unk_10.i |= 0x80000000;
        }

    case 6:
        if (((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n != 6) {
            return;
        }
        if (!create_status_linked_render_effect(position, (*(void * *)D_80175B28), (*(s16 *)D_80175B20), ((s32 *)D_800DCF5C))) {
            return;
        }
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        decrement_monster_entry_count(((R12_80175470_S_80175470_1 *)actor)->unk_13, 3);
        update_map_cell_flags_with_item_limit(record->unk_24, record->unk_25, 0x300);
        unlink_entity_node(actor);
        node = (u8 *)actor - 0x20;
        node->unk_10.i |= 0x80000000;
        return;

    case 7:
        ((R12_80175470_S_80175470_1 *)actor)->unk_60 = advance_staged_entity_load(record, actor);
        if (((R12_80175470_S_80175470_1 *)actor)->unk_60 == 0) {
            return;
        }
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = 0x10;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_9B.n++;
        ((R12_80175470_S_80175470_5 *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))->unk_2A = ((R12_80175470_S_80175470_1 *)actor)->unk_2A.u;
        model = ((R12_80175470_S_80175470_5_pre *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))[-1].unk_00;
        node = ((R12_80175470_S_80175470_1 *)actor)->unk_60;
        select_indirect_table_entry(model, ((u8 *)model->frameTable)[
                      ((g_game_work.view.camera_rotation.parts.viewAngle + node->unk_2A + 0x100) >> 9) & 7],
                      model->unk_04);
        model->flags &= 0xFFFE;

    case 8:
        next_timer = ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u - 1;
        ((R12_80175470_S_80175470_0 *)sequence)->unk_96.u = next_timer;
        if ((s16)next_timer > 0) {
            return;
        }
        ((R12_80175470_S_80175470_5 *)(((R12_80175470_S_80175470_1 *)actor)->unk_60))->unk_2A = ((R12_80175470_S_80175470_1 *)actor)->unk_8A;
        ((R12_80175470_S_80175470_0_pre *)sequence)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((R12_80175470_S_80175470_1 *)actor)->unk_6D = 0;
    default:
        return;
    }
}

void finish_actor_floor_trap_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_select_target;
    }
}

void finish_actor_action_flag_propagation_then_select_target(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_select_target;
    }
}
