#include "modules/dungeon_resource16_slot0.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"

void * (*const resource16_slot0_entry0)(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c) = func_80170878;

void *func_80170878(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    void *result = 0;
    void *created;
    void *position;
    SpriteFrameState *part_b;
    R16_80170878_S_80170878_4 *actor;
    s16 held_a;
    s32 held_c;
    s16 held_b;
    s16 flags_copy;
    void *call_a0;
    void *call_a1;
    s32 kind;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    created = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    flags_copy = spawn_flags;
    if (created != 0) {

        result = (u8 *)created + 0x20;
        ((R16_80170878_S_80170878_0 *)created)->unk_10 = update_entity_facing_and_ground;
        ((R16_80170878_S_80170878_1 *)result)->unk_13 = 0x10;
        register_node(created, project_sprite_chain);

        position = ((R16_80170878_S_80170878_0 *)created)->unk_08;
        ((R16_80170878_S_80170878_2 *)position)->unk_0A = held_c;
        part_b = ((R16_80170878_S_80170878_0 *)created)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = result;
        part_b->frameTable = ((u8 *)D_8017420C);
        part_b->unk_24 = held_a;

        if (kind == 1) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= 0x6000;
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= 0x2000;
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x2000;
        } else {
            call_a0 = created;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((R16_80170878_S_80170878_1 *)result)->unk_14 & 0x200)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        set_or_clear_actor_status_slot(result, 1,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = ((u8 *)D_8017425C);
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, part_b, (s16)flags_copy);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        try_move_actor_to_valid_position(actor, position, part_b, result);
    }
    return result;
}

void update_entity_facing_and_ground(void *entity, EntityRec *motion, void *sprite)
{
    R16_80170A58_S_80170A58_2 *state = entity;
    s16 previous_state;
    s32 view_dir;
    u8 dir_index;
    s16 height_offset;
    u16 height_bits;
    s32 hover_limit;
    s16 ground_delta;
    s16 ground_height;
    u16 part_flags;
    s32 entity_flags;
    R16_80170A58_Callback gated_callback;
    R16_80170A58_Callback update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        gated_callback = (*(R16_80170A58_Callback *)((u8 *)entity + 0x8C));
        if (gated_callback == (R16_80170A58_Callback)((u8 *)update_actor_state_and_dispatch_transition)) {
            gated_callback(entity, motion, sprite, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    previous_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(R16_80170A58_Callback *)((u8 *)entity + 0x8C));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    ((R16_80170A58_Callback *)D_8017426C)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    if (previous_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, sprite, entity);
    }

    motion->x.v += motion->unk_0C;
    motion->y.v += motion->unk_10;

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) && !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->flags14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D)) = (*(u8 *)((u8 *)entity + 0x9D)) + 1;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->flags14;

    part_flags = ((SpriteFrameState *)sprite)->flags;
    if (!(part_flags & 0x8000)) {
        view_dir = ((g_game_work.view.camera_rotation.parts.viewAngle + state->unk_2A + 0x100) >> 9) & 7;
        dir_index = view_dir;
        if ((*(s16 *)((u8 *)entity + 0x94)) != dir_index) {
            select_indirect_table_entry(sprite,(u8)((*(u8 * *)&((SpriteFrameState *)sprite)->frameTable)[dir_index]),(s8)((SpriteFrameState *)sprite)->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = view_dir;
        }
        if (dir_sprite_flag[dir_index] != 0) {
            ((SpriteFrameState *)sprite)->flags |= 1;
        } else {
            ((SpriteFrameState *)sprite)->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(state->unk_1C, (u8 *)sprite + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((SpriteFrameState *)sprite)->flags |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags != 0) {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_8017420C)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20)));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        } else {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20))) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            ((SpriteFrameState *)sprite)->flags = part_flags | 0x7000;
        } else {
            ((SpriteFrameState *)sprite)->flags = part_flags & 0x8FFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags == 0) {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20))) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        } else {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable == ((u8 *)D_8017420C)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20)));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        }
    }

    entity_flags = state->unk_1C;
    if (entity_flags & 0x40000000) {
        state->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((((SpriteFrameState *)sprite)->unk_24 << 6) | 0x20,
                               (((SpriteFrameState *)sprite)->unk_25 << 6) | 0x20,(s16)((s16)(state->unk_88 - 0x20)));
        if ((s16)ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (*(u16 *)((u8 *)entity + 0x92)) + (state->unk_88 - ground_height);
            state->unk_88 = ground_height;
        }
    }

    motion->z.w.i = state->unk_88 + (*(u16 *)((u8 *)entity + 0x92)) -
                            (*(u16 *)((u8 *)entity + 0xA2));
    ((SpriteFrameState *)sprite)->flags |= 0x40;
}

void update_actor_state_and_dispatch_transition(void *actor, void *actor_context, void *map_object, EntityRec *creature)
{
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((R16_80171014_S_80171014_0 *)actor)->unk_9A = 0xE;
        advance_actor_path_step_and_update_counters(actor, actor_context, map_object, creature);
        return;
    }
    if (creature->tileY == 0) {
        void *animation_table;

        advance_actor_pending_action(actor, actor_context, map_object, creature);
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_2C == ((u8 *)D_8017425C)) {
            return;
        }
        animation_table = ((u8 *)D_80174254);
        (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
        select_sprite_entry(map_object,
            ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_2C == ((u8 *)D_8017425C)) {
            ((R16_80171014_S_80171014_0 *)actor)->unk_9A = 0xD;
            ((R16_80171014_S_80171014_0 *)actor)->unk_9B = 1;
            ((R16_80171014_S_80171014_0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, actor_context, map_object, ((u8 *)D_80174254)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, actor_context, map_object, creature);
            return;
        }

        {
            u8 current_state = ((R16_80171014_S_80171014_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_animation;
            void *animation_table;

            if (current_state != next_state) {
                ((R16_80171014_S_80171014_0 *)actor)->unk_9A = next_state;
            }
            current_animation = ((R16_80171014_S_80171014_2 *)map_object)->unk_2C;
            animation_table = ((u8 *)D_8017420C);
            if (current_animation != animation_table) {
                (*(void * *)((u8 *)map_object + (0x2C))) = animation_table;
                select_sprite_entry(map_object,
                    ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                    0);
                ((R16_80171014_S_80171014_2 *)map_object)->unk_05 = 1;
                ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
                ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            }
        }

        creature->flags1C |= 0x40000;
        ((R16_80171014_S_80171014_0 *)actor)->unk_98 &= 0xFFF7;

        if (creature->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, map_object, ((u8 *)D_8017421C)) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            s16 offset_delta;

            begin_actor_move_to_target_facing(actor, actor_context, map_object, creature);
            offset_delta = ((R16_80171014_S_80171014_0 *)actor)->unk_92.u - ((R16_80171014_S_80171014_0 *)actor)->unk_A2.u;
            ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_92.s = offset_delta;
            func_80173468(actor, actor_context, map_object, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, map_object, creature) << 16) != 0) {
                func_80173AE8(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v, ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v));
    ((R16_80171014_S_80171014_2 *)map_object)->unk_26 = room_id;

    if (creature->unk_6D > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if (((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            if (!(creature->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801721B4(actor, actor_context, map_object, 0) << 16) == 0) {
                    return;
                }
                action_state = creature->unk_46 | 0x4000;
                creature->unk_46 = action_state;
            }

            if (creature->unk_46 & 0x8000) {
                action_state = creature->unk_46 & 0x3FFF;
                switch (action_state - 1) {

                case 7:
                case 8:
                    if ((initialize_transition_action(actor, actor_context, map_object, creature) << 16) != 0) {
                        return;
                    }
                    begin_eligible_actor_action(actor, actor_context, map_object, creature);
                    return;

                case 4:
                case 5:
                case 6:
                    {
                        EntityRec *player;
                        s16 facing_angle;

                        facing_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v),(s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                            &distance));
                        player = D_800814A8;
                        creature->facing = facing_angle;
                        if (player->unk_9A == 0x11) {
                            begin_actor_spell_action(actor, actor_context, map_object, ((u8 *)D_8017424C), ((u8 *)update_actor_state_and_dispatch_transition));
                            return;
                        }
                    }

                case 11:
                    update_actor_status_and_food(creature);
                    return;

                case 0:
                case 1:
                case 2:
                    begin_actor_spell_action(actor, actor_context, map_object, ((u8 *)D_8017424C), ((u8 *)update_actor_state_and_dispatch_transition));
                    return;

                case 3:
                case 9:
                case 10:
                default:
                    break;
                }
            }
        }
        func_80171784(actor, actor_context, map_object, creature);
        return;
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                    ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v, ((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at00.v),(s16)(((R16_80171014_S_80171014_2 *)map_object)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }
}

void advance_actor_path_step_and_update_counters(void *motion_state, s32 unused, void *entity, void *path_state)
{
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    u16 hp;
    u16 energy;
    u16 step_index;
    void *path_entry;

    if (((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if ((s32)((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.u <= ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s) {
        return;
    }

    if (((R16_80171574_S_80171FC8_1 *)entity)->unk_2C != ((u8 *)D_8017420C)) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = ((u8 *)D_8017420C);
        select_sprite_entry(entity,
                      ((u8 *)D_8017420C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
                      0);
    }

    path_entry = (u8 *)path_state + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s;
    if (((R16_80171574_S_80171FC8_1 *)entity)->unk_24 == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_74 &&
        ((R16_80171574_S_80171FC8_1 *)entity)->unk_25 == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_7C) {
        hp = ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92;
        energy = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88;
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92 = hp + 0x20;
        step_index = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88 = energy - 0x20;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u = step_index + 1;
    } else {
        flags = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C;
        old_x = ((R16_80171574_S_80171FC8_1 *)entity)->unk_24;
        old_y = ((R16_80171574_S_80171FC8_1 *)entity)->unk_25;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        ((R16_80171574_S_80171FC8_1 *)entity)->unk_24 = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_74;
        ((R16_80171574_S_80171FC8_1 *)entity)->unk_25 = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_7C;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u += 1;

        cycle_map_cell_flags(((R16_80171574_S_80171FC8_1 *)entity)->unk_24, ((R16_80171574_S_80171FC8_1 *)entity)->unk_25,
                      (((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A =
            ((s16)get_rounded_facing_and_rounding_flag(old_x, old_y, ((R16_80171574_S_80171FC8_1 *)entity)->unk_24,
                          ((R16_80171574_S_80171FC8_1 *)entity)->unk_25, (u8 *)motion_state + 0x98));
    }

    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_9A = 0xF;
    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_8C = 0;
    (*(s32 *)((u8 *)path_state + 0x1C)) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 0;
        return;
    }

    ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 8;
    step_count = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_71.u;
    if (step_count > 0) {
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_96 = 8 / step_count;
    }

    return;
}

void func_80171784(void *move_data, void *context, void *position_data, void *actor_data)
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

    if ((dungeon_flags & 0x4000) || ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R16_80171784_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)initialize_transition_action(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R16_80171784_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v));
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R16_80171784_S_80171C34_7 *)(((R16_80171784_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R16_80171784_S_80171C34_7 *)(((R16_80171784_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R16_80171784_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &D_80082E80;
                    s32 target_facing = ((u16)D_800814A8->facing);
                    s32 offset_index =
                        ((((R16_80171784_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v == (u16)target_x &&
                    ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v == (u16)target_y) {
                    ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_directional_move_and_terrain((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)compare_monster_neighbor_values(
                        ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((R16_80171784_S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((R16_80171784_DungeonRecord *)D_800E2970)[((R16_80171784_S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R16_80171784_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R16_80171784_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)compare_monster_neighbor_values(
                    ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(D_800814A8, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)D_8006CD00);

    do {
        turn_flags = ((R16_80171784_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_directional_move_and_terrain((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R16_80171784_S_80171C34_8 *)((u8 *)actor_data + (((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v;
            ((R16_80171784_S_80171C34_8 *)((u8 *)actor_data + (((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v;
            ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((R16_80171784_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v += *x_step;
                ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(u16)((((R16_80171784_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tile_position.parts.tile_x) != ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00u.v) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)D_800814A8->unk_58 + 0x20)) != 0) {
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
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.u = ((R16_80171784_S_80171C34_2 *)position_data)->unk_26.u;
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R16_80171784_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v << 6) | 0x20,
        (((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v << 6) | 0x20,(s16)((s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}

s32 initialize_transition_action(void *action_state, s32 action_id, void *source_obj, EntityRec *actor)
{
    s32 target_angle;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    target_angle = place_actor_at_directional_neighbor(actor, ((R16_80171ECC_S_80171ECC_1 *)source_obj)->unk_24,
                                 ((R16_80171ECC_S_80171ECC_1 *)source_obj)->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        (*(u8 * *)((u8 *)source_obj + 0x2C)) = ((u8 *)D_80174214);
        select_sprite_entry(
            source_obj,
            ((u8 *)D_80174214)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        prepare_directional_attack(actor, source_obj, actor->facing, 1, 0);
        actor->unk_6D--;
        return 1;
    }
    return -1;
}

/* MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0.
   An unused 8-byte local (unused[2]) raises the otherwise exact 0x38 frame to retail's 0x40
   without emitting body code; source-based byte indexing preserves the final call operands. */

void begin_eligible_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 context, Rec_D_80082E80 *animation, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, context, 8, 0x300);
        if ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            animation->unk_2C.as_pu8 = ((u8 *)D_8017423C);
            select_sprite_entry(animation, ((u8 *)D_8017423C)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            prepare_directional_attack(actor, animation, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

s32 func_801721B4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_80171784(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R16_801721B4_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        func_80171784(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R16_801721B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R16_801721B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R16_801721B4_S_80172628_0 *)entity)->unk_71 = (u8) (((R16_801721B4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R16_801721B4_S_80172628_0 *)entity)->unk_46 = (u16) (((R16_801721B4_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

void func_801722F8(void *state, s32 unused, s32 source, s32 target) {
    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)update_actor_state_and_dispatch_transition);
            if (g_dungeon_status.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}

void func_8017238C(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}

void finish_actor_action_animation(void *action, void *motion, void *anim, void *actor) {
    s32 state;
    u16 ticks;

    state = ((R16_801723F0_S_801723F0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 1;
    case 1:
        if (((SpriteFrameState *)anim)->flags & 0x8000) {
            ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 3;
            ((SpriteFrameState *)anim)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, anim,(s16)(((EntityRec *)actor)->facing),(s16)(1));
            return;
        }
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_14 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_10 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_0C = 0;
        ((SpriteFrameState *)anim)->frameTable = ((u8 *)D_8017423C);
        select_sprite_entry(anim,(u8)(((u8 *)D_8017423C)[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7]),
            0);
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = 0;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x804);
        return;
    case 2:
        ticks = ((R16_801723F0_S_801723F0_0 *)action)->unk_96 + 1;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = ticks;
        if (((s16)ticks == 8) || (((SpriteFrameState *)anim)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim,(s16)(((EntityRec *)actor)->facing),(s16)(1));
        }
    case 3:
        if (((SpriteFrameState *)anim)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((R16_801723F0_S_801723F0_0 *)action)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
            advance_status_timers(actor);
        }
    default:
        break;
    }
}

void update_overlay_object_action(void *owner, void *motion, void *actor, void *object_in)
{
    void *object = object_in;
    register s32 is_special;
    u8 *action_data;
    s16 x;
    s32 absolute_x;
    s32 y;
    s32 kind;
    u32 kind_index;
    void *spawn;
    u8 *action_entry;
    u8 *record;
    u8 *action_table;
    u32 action_id;
    s32 state;
    state = ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B;
    is_special = 0;
    switch (state) {
    case 0:
        if (((R16_801725A4_S_801725A4_1 *)object)->unk_1C & 0x2000) {
            kind_index = (((R16_801725A4_S_801725A4_1 *)object)->unk_46 & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                is_special = 1;
            case 2:
                action_data = (u8 *)object + 0xE;
                break;
            case 5:
                is_special = 1;
            case 1:
                action_data = (u8 *)object + 0xB;
                break;
            case 4:
                is_special = 1;
            case 0:
                action_data = (u8 *)object + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            kind = ((R16_801725A4_S_801725A4_1 *)object)->unk_46 & 0x3FFF;
            switch (kind) {
            case 3:
                action_data = (u8 *)object + 0xE;
                break;
            case 2:
                action_data = (u8 *)object + 0xB;
                break;
            case 1:
                action_data = (u8 *)object + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {
            x = ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 & 0xFF7F;
            ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 = x;
            x = is_special;
            if (x) {
                spawn = D_800814A8;
                ((R16_801725A4_S_801725A4_1 *)object)->unk_60 = spawn;
                record = *(u8 **)((u8 *)spawn - 0x14);
                x = record[0x24];
                ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                x = record[0x25];
                ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
            } else {
                action_table = D_8006DE24;
                action_id = *action_data;
                action_entry = action_table + (action_id * 20);
                if (action_entry[0x12] == 2) {
                    spawn = ((R16_801725A4_S_801725A4_1 *)object)->unk_60;
                    if (spawn != 0) {
                        record = *(u8 **)((u8 *)spawn - 0x14);
                        x = record[0x24];
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                        x = record[0x25];
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
                    }
                } else {
                    spawn = scan_monster_along_heading(
                        object,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25),(s16)(((R16_801725A4_S_801725A4_1 *)object)->unk_2A),
                        0x10);
                    ((R16_801725A4_S_801725A4_1 *)object)->unk_60 = spawn;

                    absolute_x = abs(((R16_801725A4_S_801725A4_1 *)object)->unk_72.u);
                    y = abs(((R16_801725A4_S_801725A4_1 *)object)->unk_73.u);

                    ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = absolute_x;
                    ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = y;

                }
            }

            if (create_actor_spell_effect(object, action_data, is_special,
                              (u16 *)((u8 *)owner + 0x98)) == 0) {
                return;
            }
            create_actor_linked_effect(object);
            ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B++;
            return;
        }

        ((R16_801725A4_S_801725A4_3 *)motion)->unk_14 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_10 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25));
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        advance_status_timers(object);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_6D--;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((SpriteAnimationTableView *)actor)->unk_14 |= 0x0800;
            return;
        }
        ((SpriteAnimationTableView *)actor)->unk_14 &= 0xF7FF;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B++;

    case 2:
        if (((SpriteAnimationTableView *)actor)->unk_04 != 4 || !(((SpriteAnimationTableView *)actor)->unk_14 & 0x1000)) {
            if ((((SpriteAnimationTableView *)actor)->unk_14 & 0xE000) == 0) {
                return;
            }
        }
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 |= 0x80;
        if ((((SpriteAnimationTableView *)actor)->unk_14 & 0xE000) == 0) {
            return;
        }

        ((R16_801725A4_S_801725A4_3 *)motion)->unk_14 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_10 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)(((SpriteAnimationTableView *)actor)->unk_24),(u8)(((SpriteAnimationTableView *)actor)->unk_25));

        {
            u8 *direction_table = ((u8 *)D_8017420C);
            if (((SpriteAnimationTableView *)actor)->unk_2C != direction_table) {
                (*(u8 * *)((u8 *)actor + 0x2C)) = direction_table;
                select_sprite_entry(
                    actor,(u8)(direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((R16_801725A4_S_801725A4_1 *)object)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
        }

        {
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        advance_status_timers(object);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_6D--;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;
    default:
        return;
    }
}

void func_801729D8(R16_801729D8_S_80173294_0 *motion_state, EntityRec *motion, SpriteFrameState *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    switch (motion_state->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->unk_0C =
            -*(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion->unk_10 =
            -*(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion_state->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, tile_state, ((u8 *)D_80174244));
            return;
        }
        if (tile_state->flags & 0x8000) {
            motion_state->unk_96.s = 0;
            motion_state->unk_9B = 2;
            return;
        }
        timer = -1;
        if (((EntityRec *)entity)->flags1C & 0x228) {
            timer = 8;
        }
        motion_state->unk_96.s = timer;
                        /* fall through */

    case 1:
        x_speed_or_entity = motion->unk_0C;
        rounded_velocity = x_speed_or_entity;
        if (x_speed_or_entity < 0) {
            rounded_velocity = x_speed_or_entity + 3;
        }
        velocity_z = motion->unk_10;
        motion->unk_0C = x_speed_or_entity - (rounded_velocity >> 2);

        rounded_velocity = velocity_z;
        motion->unk_10 = velocity_z - (rounded_velocity / 4);

        if (motion_state->unk_96.s > 0) {
            motion_state->unk_96.u = motion_state->unk_96.u - 1;
        } else if (tile_state->flags & 0x6000) {
            motion_state->unk_96.s = 0;
        }

        if (motion_state->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, tile_state, ((u8 *)D_80174244));
            return;
        }
        motion_state->unk_96.s = 8;
        motion_state->unk_9B++;
        return;

    case 2:
        timer = motion_state->unk_96.s;
        if (timer != 0) {
            s32 tile_coord;
            s32 offset_coord;

            tile_coord = tile_state->unk_24 << 6;
            offset_coord = motion->x.w.i;
            offset_coord -= 0x20;
            motion->unk_0C = ((tile_coord - offset_coord) << 15) / timer;

            offset_coord = motion->y.w.i;
            offset_coord -= 0x20;
            tile_coord = tile_state->unk_25 << 6;
            motion->unk_10 =
                ((tile_coord - offset_coord) << 15) / motion_state->unk_96.s;
        }

        countdown = motion_state->unk_96.u - 1;
        motion_state->unk_96.p = countdown;
        if ((countdown << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)tile_state->unk_24,(u8)tile_state->unk_25);
        {

            x_speed_or_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (x_speed_or_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = x_speed_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C = ((void *)update_actor_state_and_dispatch_transition);
        return;

    default:
        return;
    }
}

void func_80172CAC(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

void func_80172CCC(R16_80172CCC_S_80173588_0 *state, void *context, void *data) {
    update_actor_hop_and_shrink(state, context, data);
    state->unk_A2 = 0;
}

void func_80172CF8(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

void func_80172D18(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

void func_80172D50(void *actor, void *context, void *render_record, EntityRec *actor_state)
{
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = ((u8 *)D_8017425C);
        select_sprite_entry(render_record,(u8)(((u8 *)D_8017425C)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        do {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
        } while (0);
        return;

    case 1:
        if ((get_entity_effect_value(actor_state, 1) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (actor_state->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor, context, render_record, 0) != 0) {
                    return;
                }
            }
            if (actor_state->tileY == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(actor, context, render_record, actor_state);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                return;
            }
            actor_flags = actor_state->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(actor, context, render_record, actor_state);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(actor, context, render_record, actor_state);
                value = ((R16_80172D50_S_80173E50_0 *)actor)->unk_92;
                value_offset = ((R16_80172D50_S_80173E50_0 *)actor)->unk_A2;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_A2 = 0;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_9E = 0;
                ((R16_80172D50_S_80173E50_0 *)actor)->unk_92 = value - value_offset;
                func_80173468(actor, context, render_record, actor_state);
                return;
            }
            if (actor_state->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((check_entity_relation(actor_state,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_food(actor_state);
            on_actor_status_updated(actor_state);
            if ((get_entity_effect_value(actor_state, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((Rec_D_80082E80 *)render_record)->unk_26.as_s8;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, render_record) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor_state, 1);
                    }
                }
            }
            if ((get_entity_effect_value(actor_state, 1) << 16) != 0) {
                return;
            }
        }
        ((Rec_D_80082E80 *)render_record)->unk_2C.as_pv = ((u8 *)D_80174264);
        select_sprite_entry(render_record,(u8)(((u8 *)D_80174264)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        (*(u32 *)&actor_state->flags1C) |= 0x40000;
        if (((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0x8000) {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
        ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        return;

    case 2:
        if (!(((Rec_D_80082E80 *)render_record)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        return;
    }
}

void func_80173114(void *actor, void *context, void *animation, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)D_8017425C);
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        select_sprite_entry(animation,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = ((u8 *)D_80174264);
            select_sprite_entry(animation,
                ((u8 *)D_80174264)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            func_80173468(actor, context, animation, entity);
            return;
        }

        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = ((u8 *)D_80174264);
        select_sprite_entry(animation,
            ((u8 *)D_80174264)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~8;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = ((void *)update_actor_state_and_dispatch_transition);
        }

        return;
    }
}

void func_80173468(R16_80173468_Actor *actor, s32 action, R16_80173468_Entity *entity, R16_80173468_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_8017425C) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_8017420C);
        select_sprite_entry(entity,(s16)(((u8 *)D_8017420C)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

void func_80173530(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}

void func_80173594(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

void func_801735CC(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

void func_80173604(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

void func_8017363C(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

void func_80173674(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

s32 func_801736AC(void *initial_payload, s32 entry_data, R16_801736AC_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R16_801736AC_Scratchpad *scratch = (R16_801736AC_Scratchpad *)0x1F800000;
    R16_801736AC_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_801742E0)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R16_801736AC_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */

void update_expanding_spiral_effect(void *effect, R16_80173738_FuncArg1 *position, Rec_D_80082E80 *primitive) {
    s16 life;
    s16 next_life;
    s32 y_offset;
    s32 base_y;
    s32 z_step;
    void *primitive_dst;

    ((R16_80173738_S_80173738_0 *)effect)->unk_1E = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_1E - 0x12C);
    ((R16_80173738_S_80173738_0 *)effect)->unk_20 = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_20 + 2);
    position->unk00 = (s32) (((R16_80173738_S_80173738_0 *)effect)->unk_40
        + ((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * func_80064584((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E) * 0x10));
    y_offset = (s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * func_800644B8((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E);
    primitive_dst = primitive;
    z_step = 0xFFF40000U;
    base_y = ((R16_80173738_S_80173738_0 *)effect)->unk_44;
    position->unk08 = (s32) (position->unk08 + z_step);
    position->unk04 = (s32) (base_y + (y_offset * 0x10));
    func_800478B8(primitive_dst);
    if (((SpriteFrameState *)primitive)->flags & 0x4000) {
        func_8003DB94(primitive, ((s32 *)D_800DEC70), 0);
    }
    life = ((R16_80173738_S_80173738_0 *)effect)->unk_1A;
    if (life < 0xA) {
        ((SpriteFrameState *)primitive)->color.c.r = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_00 * life) / 9);
        ((SpriteFrameState *)primitive)->color.c.g = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_01 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
        ((SpriteFrameState *)primitive)->color.c.b = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_02 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((R16_80173738_S_80173738_0 *)effect)->unk_1A - 1;
    ((R16_80173738_S_80173738_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 = (u16) (((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 =
            (s32) (((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 | 0x8000);
    }
}

void create_angled_source_effect(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset)
{
    void *object;
    R16_80173904_S_80173904_0 *state;
    SpriteFrameState *display;
    R16_80173904_S_80173904_4 *transform;
    s16 wrapped_angle;

    object = func_8003FC64(0x212);
    wrapped_angle = angle;
    if (object != NULL) {
        state = (R16_80173904_S_80173904_0 *)((u8 *)object + 0x20);
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = angle;
        ((R16_80173904_S_80173904_1 *)object)->unk_10 = ((void *)update_expanding_spiral_effect);
        register_node(object, project_sprite_chain);

        display = ((R16_80173904_S_80173904_1 *)object)->unk_0C;
        display->tpage_abr = 0x60;
        display->flags |= 0xC;
        if (rand() & 1) {
            display->flags |= 1;
        }

        transform = ((R16_80173904_S_80173904_1 *)object)->unk_08;
        state->unk_40 = origin->unk_00;
        state->unk_44 = origin->unk_04;
        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        transform->unk_00 = state->unk_40 + ((state->unk_20 * func_80064584(wrapped_angle)) << 4);
        transform->unk_04 = state->unk_44 + ((state->unk_20 * func_800644B8(wrapped_angle)) << 4);
        transform->unk_0A = origin->unk_0A + depth_offset;

        display = ((R16_80173904_S_80173904_1 *)object)->unk_0C;
        display->scale_y = 0x1000;
        display->scale_x = 0x1000;
        display->color.c.r = 0x40;
        display->color.c.b = 0x40;
        display->color.c.g = 0xC0;
        state->unk_00 = display->color.c.r;
        state->unk_01 = display->color.c.g;
        state->unk_02 = display->color.c.b;
        func_8003DB94(display, ((u8 *)D_800DEC70), 0);
        display->clut = 0x7DCF;
        display->flags |= 0x100;
    }
}

void func_80173AE8(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)func_80173AE8);
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

void fade_entity_colors_to_neutral(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    GameWork *colors = &g_game_work;
    u16 ticks;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        (*(s32 *)D_801742E8) = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            unlink_node(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = ticks + 1;
        if ((ticks & 3) == 0) {
            (*(u16 *)D_801742E0)--;
            return;
        }
    } else {
        colors->view.tint.parts.tint_r += (0x80 - colors->view.tint.parts.tint_r) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_g += (0x80 - colors->view.tint.parts.tint_g) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_b += (0x80 - colors->view.tint.parts.tint_b) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}

void advance_actor_effect_sequence(Rec_func_801732A4_arg0 *state, EntityRec *position, Rec_D_80082E80 *actor, void *model) {
    s16 next_spawn;
    s16 next_trail;
    s16 spawn_count;
    s16 trail_count;
    s32 direction;
    s32 color;
    s32 variant_index;
    s16 effect_value;
    s32 effect_value_2;
    u16 fade_left;
    u16 elapsed;
    u16 fade_timer;
    s32 event_done;
    u8 phase;
    void *effect_model;
    R16_80173CEC_S_80173CEC_4 *target_color;
    R16_80173CEC_S_80173CEC_8 *effect_position;
    R16_80173CEC_S_80173CEC_9 *effect_sprite;
    GameWork *scene_color;
    R16_80173CEC_S_80173CEC_5 *effect;

    scene_color = &g_game_work;
    phase = state->unk_9B;
    switch (phase) {
    case 0:
        state->unk_9B = (u8) (state->unk_9B + 1);
        return;
    case 1:
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)D_801742E4), 0);
        state->unk_A6 = 0;
        state->unk_9B = (u8) (state->unk_9B + 1);
        ((Rec_D_80082E80 *)model)->unk_8A = (u16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v;
        ((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v =
            (s32) (((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v & 0xFFFBFFFF);
    case 2:
        direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)((s32 *)D_801742E4)) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x200);
            return;
        }
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)D_801742E4), 1);
        sound_set_cd_cue_parameters(0, (*(s32 *)D_8006CD58), 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, func_800445E0(), NULL);
        (*(s8 *)((s32 *)D_801742E5)) = 0;
        Control_CD(0xFF, ((s32 *)D_8003E140), ((s32 *)D_801742E5));
        select_nearby_target_and_initialize_slot(model - 0x20, position, 8, 0x300);
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 3:
        fade_timer = state->unk_96;
        fade_left = fade_timer - 1;
        state->unk_96 = fade_left;
        if ((fade_left << 0x10) <= 0) {
            event_done = ((R16_80173CEC_S_80173CEC_2 *)(((s32 *)D_801742E5)))->unk_00;
            state->unk_96 = fade_timer;
            if (event_done == 0) {
                return;
            }
            state->unk_9B = (u8) (state->unk_9B + 1);
            play_sound_if_enabled(0x300);
            return;
        }
        target_color = (*(void **)((u8 *)(((s32 *)D_800DCEEC)) + lookup_masked_byte_table(model) * 4));
        scene_color->view.tint.parts.tint_r = (u8) (scene_color->view.tint.parts.tint_r + ((s32) (target_color->unk_00
            - scene_color->view.tint.parts.tint_r) / (s16) state->unk_96));
        scene_color->view.tint.parts.tint_g = (u8) (scene_color->view.tint.parts.tint_g + ((s32) (target_color->unk_01
            - scene_color->view.tint.parts.tint_g) / (s16) state->unk_96));
        scene_color->view.tint.parts.tint_b = (u8) (scene_color->view.tint.parts.tint_b + ((s32) (target_color->unk_02
            - scene_color->view.tint.parts.tint_b) / (s16) state->unk_96));
        return;
    case 4:
        effect = func_8003FC64(0x12);
        if (effect == NULL) {
            return;
        }
        effect->unk_10 = ((void *)fade_entity_colors_to_neutral);
        register_node(effect, ((void *)func_801736AC));
        color = 0x808080;
        state->unk_AC = effect;
        effect_model = model;
        ((R16_80173CEC_S_80173CEC_12 *)(((R16_80173CEC_S_80173CEC_11 *)effect)->unk_08))->unk_00 = (s32) position->x.v;
        ((R16_80173CEC_S_80173CEC_12 *)(((R16_80173CEC_S_80173CEC_11 *)effect)->unk_08))->unk_04 = (s32) position->y.v;
        effect_position = effect->unk_08;
        effect_value_2 = position->z.v;
        (*(s16 *)D_801742E0) = -8;
        effect_position->unk_08 = effect_value_2;
        effect_sprite = effect->unk_0C;
        effect_sprite->unk_1E = 0x1000;
        effect_sprite->unk_1C = 0x1000;
        effect_sprite->unk_0C.s = color;
        variant_index = lookup_masked_byte_table(effect_model) - 1;
        effect_value = variant_index;
        if ((variant_index << 0x10) < 0) {
            effect_value = func_80069EF8() % 3;
        }
        func_8003DB94(effect_sprite, ((s32 *)D_801742D4)[(s16) effect_value] + (s8 *) ((s32 *)D_8014A000), 0);
        ((SpriteFrameState *)actor)->flags = (u16) (((SpriteFrameState *)actor)->flags | 0x80);
        spawn_count = 0;
        state->unk_96 = 0U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        do {
            create_angled_source_effect(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
            next_spawn = spawn_count + 1;
            spawn_count = next_spawn;
            if (next_spawn >= 8) {
                return;
            }
        } while (1);
    case 5:
        elapsed = state->unk_96;
        state->unk_96 = (u16) (elapsed + 1);
        if ((s16) elapsed < 0x1E) {
            trail_count = 0;
            do {
                create_angled_source_effect(state, position, actor, model, func_80069EF8() & 0xFFF, 0);
                next_trail = trail_count + 1;
                trail_count = next_trail;
            } while (next_trail < 8);
        }
        effect_sprite = state->unk_AC;
        effect_sprite = effect_sprite->unk_0C.u;
        if (effect_sprite->unk_14 & 0xE000) {
            state->unk_9B = (u8) (state->unk_9B + 1);
        }
    case 6:
        if (state->unk_9B != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, (*(s32 *)D_801742E8), (*(s16 *)D_801742E0), ((s32 *)D_800DCF5C)) == 0) {
            return;
        }
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)model)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25, 0x300);
        unlink_entity_node(model);
        effect_sprite = model - 0x20;
        effect_sprite->unk_10 = (s32) (effect_sprite->unk_10 | 0x80000000);
        return;
    case 7:
        ((Rec_D_80082E80 *)model)->unk_60.as_s32 = advance_staged_entity_load(actor, model);
        return;
    }
}
