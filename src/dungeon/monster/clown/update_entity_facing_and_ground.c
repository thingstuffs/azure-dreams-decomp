#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Clown actor spawning, action updates, movement, and transition effects. */
#include "dungeon/actor/motion.h"
#include "dungeon/monster/clown.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/clown.h"
#include "engine/cd.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"

void * (*const resource16_slot0_entry0)(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c) = spawn_clown_actor;

/* Creates a Clown actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_clown_actor(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    void *result = 0;
    ObjectNodeHeader *created;
    ObjectPosition *position;
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
    created = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    flags_copy = spawn_flags;
    if (created != 0) {

        result = (u8 *)created + 0x20;
        created->update_callback = update_entity_facing_and_ground;
        ((R16_80170878_S_80170878_1 *)result)->unk_13 = MONSTER_CLOWN;
        register_node(created, project_sprite_chain);

        position = created->position;
        position->z.w.i = held_c;
        part_b = created->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = held_b;
        actor = result;
        part_b->frameTable = ((u8 *)clown_direction_frames);
        part_b->tile_x = held_a;

        if (kind == 1) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
        } else if (kind >= 2) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= ACTOR_CLASS_ENABLED;
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= ACTOR_PLAYER_SIDE;
        } else {
            call_a0 = created;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((R16_80170878_S_80170878_1 *)result)->unk_14 & ACTOR_RESIST_SLEEP)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        set_or_clear_actor_status_slot(result, STATUS_SLEEP,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = ((u8 *)clown_alt_direction_frames);
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

/* Runs actor callbacks and updates facing, animation, bobbing height, movement, and terrain contact. */
void update_entity_facing_and_ground(void *entity, ObjectPosition *motion, SpriteFrameState *sprite)
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

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) && !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->velocity_z += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D)) = (*(u8 *)((u8 *)entity + 0x9D)) + 1;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->velocity_z;

    part_flags = sprite->flags;
    if (!(part_flags & 0x8000)) {
        view_dir = ((g_game_work.view.camera_rotation.parts.viewAngle + state->unk_2A + 0x100) >> 9) & 7;
        dir_index = view_dir;
        if ((*(s16 *)((u8 *)entity + 0x94)) != dir_index) {
            select_indirect_table_entry(sprite,(u8)((*(u8 * *)&sprite->frameTable)[dir_index]),(s8)sprite->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = view_dir;
        }
        if (dir_sprite_flag[dir_index] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(state->unk_1C, (u8 *)sprite + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags != 0) {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 * *)&sprite->frameTable == ((u8 *)clown_direction_frames)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += rsin((s16)bob_tick * 0xAA) << 5;
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
                    motion->velocity_z = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            sprite->flags = part_flags | 0x7000;
        } else {
            sprite->flags = part_flags & 0x8FFF;
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
                    motion->velocity_z = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 * *)&sprite->frameTable == ((u8 *)clown_direction_frames)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += rsin((s16)bob_tick * 0xAA) << 5;
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
        ground_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                               (sprite->tile_y << 6) | 0x20,(s16)((s16)(state->unk_88 - 0x20)));
        if ((s16)ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (*(u16 *)((u8 *)entity + 0x92)) + (state->unk_88 - ground_height);
            state->unk_88 = ground_height;
        }
    }

    motion->z.w.i = state->unk_88 + (*(u16 *)((u8 *)entity + 0x92)) -
                            (*(u16 *)((u8 *)entity + 0xA2));
    sprite->flags |= 0x40;
}

/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void update_actor_state_and_dispatch_transition(void *actor, void *actor_context, SpriteFrameState *map_object, ActorRecord *creature)
{
    s32 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((R16_80171014_S_80171014_0 *)actor)->unk_9A = 0xE;
        advance_actor_path_step_and_update_counters(actor, actor_context, map_object, creature);
        return;
    }
    if (creature->mp == 0) {
        void *animation_table;

        advance_actor_pending_action(actor, actor_context, map_object, creature);
        if (map_object->frameTable == ((u8 *)clown_alt_direction_frames)) {
            return;
        }
        animation_table = ((u8 *)D_80174254);
        (map_object->frameTable) = animation_table;
        select_sprite_entry(map_object,
            ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & ACTOR_ASLEEP) {
        if (map_object->frameTable == ((u8 *)clown_alt_direction_frames)) {
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
        if (((u32)creature->flags1C) & ACTOR_PUSH_PENDING) {
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
            current_animation = map_object->frameTable;
            animation_table = ((u8 *)clown_direction_frames);
            if (current_animation != animation_table) {
                (map_object->frameTable) = animation_table;
                select_sprite_entry(map_object,
                    ((u8 *)animation_table)[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                    0);
                map_object->frame_ticks = 1;
                ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
                ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            }
        }

        creature->flags1C |= 0x40000;
        ((R16_80171014_S_80171014_0 *)actor)->unk_98 &= 0xFFF7;

        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, map_object, ((u8 *)D_8017421C)) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & ACTOR_LIFTED) {
            s16 offset_delta;

            begin_actor_move_to_target_facing(actor, actor_context, map_object, creature);
            offset_delta = ((R16_80171014_S_80171014_0 *)actor)->unk_92.u - ((R16_80171014_S_80171014_0 *)actor)->unk_A2.u;
            ((R16_80171014_S_80171014_0 *)actor)->unk_A2.s = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_9E = 0;
            ((R16_80171014_S_80171014_0 *)actor)->unk_92.s = offset_delta;
            update_clown_parent_motion(actor, actor_context, map_object, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, map_object, creature) << 16) != 0) {
                wait_for_clown_action_slot(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = ((s8)find_active_rect_containing_point(map_object->tile_x, map_object->tile_y));
    map_object->room_index = room_id;

    if (creature->pending_turn_updates > 0) {
        if (((u32)creature->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(creature);
            return;
        }
        if (*(u16 *)&map_object->tile_x != reference_tile_object.tile_position.word) {
            if (!(creature->action_flags & ACTOR_ACTION_PENDING)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(creature,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((relink_clown_path(actor, actor_context, map_object, 0) << 16) == 0) {
                    return;
                }
                action_state = creature->action_flags | 0x4000;
                creature->action_flags = action_state;
            }

            if (creature->action_flags & ACTOR_ACTION_PENDING) {
                action_state = creature->action_flags & ACTOR_ACTION_CODE_MASK;
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
                        ActorRecord *player;
                        s16 facing_angle;

                        facing_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(map_object->tile_x),(s16)(map_object->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                            &distance));
                        player = primary_actor_record;
                        creature->facing = facing_angle;
                        if (player->action_id == 0x11) {
                            begin_actor_spell_action(actor, actor_context, map_object, ((u8 *)D_8017424C), ((u8 *)update_actor_state_and_dispatch_transition));
                            return;
                        }
                    }

                case 11:
                    update_actor_status_and_mp(creature);
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
        choose_clown_move(actor, actor_context, map_object, creature);
        return;
    }

    if (!(((u32)creature->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                    map_object->tile_x, map_object->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(map_object->tile_x),(s16)(map_object->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &distance));
                }
            }
        }
    }
}

/* Advances a stored path step or adjusts height in place, then updates occupied tiles, facing, and
 * movement delay. */
void advance_actor_path_step_and_update_counters(void *motion_state, s32 unused, SpriteFrameState *entity, void *path_state)
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

    if (*(u8 **)&entity->frameTable != ((u8 *)clown_direction_frames)) {
        (entity->frameTable) = ((u8 *)clown_direction_frames);
        select_sprite_entry(entity,
                      ((u8 *)clown_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
                      0);
    }

    path_entry = (u8 *)path_state + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s;
    if (entity->tile_x == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_74 &&
        entity->tile_y == ((R16_80171574_S_80171FC8_2 *)path_entry)->unk_7C) {
        hp = ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92;
        energy = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88;
        ((R16_80171574_S_80171FC8_3 *)motion_state)->unk_92 = hp + 0x20;
        step_index = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_88 = energy - 0x20;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u = step_index + 1;
    } else {
        flags = ((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C;
        old_x = entity->tile_x;
        old_y = entity->tile_y;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        entity->tile_x = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_74;
        entity->tile_y = ((R16_80171574_S_80171FC8_4 *)((u8 *)path_state
            + ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.s))->unk_7C;
        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_8A.u += 1;

        cycle_map_cell_flags(entity->tile_x, entity->tile_y,
                      (((R16_80171574_S_80171FC8_0 *)path_state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        ((R16_80171574_S_80171FC8_0 *)path_state)->unk_2A =
            ((s16)get_rounded_facing_and_rounding_flag(old_x, old_y, entity->tile_x,
                          entity->tile_y, (u8 *)motion_state + 0x98));
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

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_clown_move(void *move_data, void *context, void *position_data, void *actor_data)
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
            update_actor_status_and_mp(actor_data);
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
            current_angle = (s32)find_adjacent_actor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v));
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
            if (probe_directional_neighbor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
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
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
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
                    ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((R16_80171784_S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((R16_80171784_DungeonRecord *)dungeon_rooms)[((R16_80171784_S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        select_actor_route_target(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s));
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
            TileObject *target_position = &reference_tile_object;
            ((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)test_neighbor_position_relation(
                    ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R16_80171784_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R16_80171784_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target(position_data, ((R16_80171784_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

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
            reference_tile_object.tile_position.word != ((R16_80171784_S_80171C34_2 *)position_data)->unk_24.at00u.v) {
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
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R16_80171784_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(actor_data);
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

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 initialize_transition_action(void *action_state, s32 action_id, void *source_obj, ActorRecord *actor)
{
    s32 target_angle;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    target_angle = probe_directional_neighbor(actor, ((SpriteFrameState *)source_obj)->tile_x,
                                 ((SpriteFrameState *)source_obj)->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (g_dungeon_status.flags & 8)) {
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
        (((SpriteFrameState *)source_obj)->frameTable) = ((u8 *)D_80174214);
        select_sprite_entry(
            source_obj,
            ((u8 *)D_80174214)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        prepare_directional_attack(actor, source_obj, actor->facing, 1, 0);
        actor->pending_turn_updates--;
        return 1;
    }
    return -1;
}

/*
 * Claims an action slot, starts the directional attack animation, and prepares its target and
 * damage state.
 *
 * MECHANISM: The true-rowbase CFG holds arg2 in $s3 and the status base in $s2 at cdk-G0. An
 * unused 8-byte local (unused[2]) raises the otherwise exact 0x38 frame to retail's 0x40 without
 * emitting body code; source-based byte indexing preserves the final call operands.
 */
void begin_eligible_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 context, SpriteFrameState *animation, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, context, 8, 0x300);
        if ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            animation->frameTable = ((u8 *)clown_frame_set);
            select_sprite_entry(animation, ((u8 *)clown_frame_set)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            prepare_directional_attack(actor, animation, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 relink_clown_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_clown_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R16_801721B4_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_clown_move(entity, primary_context_arg, secondary_context_arg, entity);
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

/*
 * Spends MP and advances status timers when movement completes, resuming the actor handler only
 * after a positive signed floor-trap check. Sets the secondary timer to -0x20 under dungeon flag
 * 0x80 during movement or after an accepted trap check. /
 */
void finish_actor_tile_move_then_dispatch_transition(void *state, void *motion, void *source, void *target) {
    if (update_actor_movement_to_tile(state, motion, source, target) != 0) {
        spend_actor_mp(target, 4);
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

/*
 * Runs update_linked_actor_motion and installs update_actor_state_and_dispatch_transition only
 * when it succeeds and the signed floor-trap check returns positive.
 */
void finish_linked_actor_motion_and_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}

/* Times the attack animation and damage, spends MP, and restores normal actor movement and status. */
void finish_actor_action_animation(void *action, void *motion, SpriteFrameState *anim, ActorRecord *actor) {
    s32 state;
    u16 ticks;

    state = ((R16_801723F0_S_801723F0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 1;
    case 1:
        if (anim->flags & 0x8000) {
            ((R16_801723F0_S_801723F0_0 *)action)->unk_9B = 3;
            anim->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, anim,(s16)(actor->facing),(s16)(1));
            return;
        }
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_14 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_10 = 0;
        ((R16_801723F0_S_801723F0_3 *)motion)->unk_0C = 0;
        anim->frameTable = ((u8 *)clown_frame_set);
        select_sprite_entry(anim,(u8)(((u8 *)clown_frame_set)[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7]),
            0);
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = 0;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x804);
        return;
    case 2:
        ticks = ((R16_801723F0_S_801723F0_0 *)action)->unk_96 + 1;
        ((R16_801723F0_S_801723F0_0 *)action)->unk_96 = ticks;
        if (((s16)ticks == 8) || (anim->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim,(s16)(actor->facing),(s16)(1));
        }
    case 3:
        if (anim->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((R16_801723F0_S_801723F0_0 *)action)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            g_dungeon_status.active_actor = 0;
            (actor->action_flags) &= 0x7FFF;
            advance_status_timers(actor);
        }
    default:
        break;
    }
}

/* Starts a targeted spell and linked effect, waits for its animation, and restores actor movement and
 * status. */
void update_overlay_object_action(void *owner, void *motion, SpriteFrameState *actor, void *object_in)
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
    SpriteFrameState *record;
    u8 *action_table;
    u32 action_id;
    s32 state;
    state = ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B;
    is_special = 0;
    switch (state) {
    case 0:
        if (((R16_801725A4_S_801725A4_1 *)object)->unk_1C & ACTOR_PLAYER_SIDE) {
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
                spawn = primary_actor_record;
                ((R16_801725A4_S_801725A4_1 *)object)->unk_60 = spawn;
                record = ((ObjectNodeHeader *)((u8 *)spawn - 0x20))->sprite;
                x = record->tile_x;
                ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                x = record->tile_y;
                ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
            } else {
                action_table = item_action_definitions;
                action_id = *action_data;
                action_entry = action_table + (action_id * 20);
                if (action_entry[0x12] == 2) {
                    spawn = ((R16_801725A4_S_801725A4_1 *)object)->unk_60;
                    if (spawn != 0) {
                        record = ((ObjectNodeHeader *)((u8 *)spawn - 0x20))->sprite;
                        x = record->tile_x;
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = x;
                        x = record->tile_y;
                        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = x;
                    }
                } else {
                    spawn = scan_actor_along_heading(
                        object,(u8)(actor->tile_x),(u8)(actor->tile_y),(s16)(((R16_801725A4_S_801725A4_1 *)object)->unk_2A),
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
        set_record_integer_tile_center(motion,(u8)(actor->tile_x),(u8)(actor->tile_y));
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(object);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_6D--;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        ((R16_801725A4_S_801725A4_1 *)object)->unk_73.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_72.s = 0;
        ((R16_801725A4_S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            actor->flags |= 0x0800;
            return;
        }
        actor->flags &= 0xF7FF;
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_9B++;

    case 2:
        if (actor->unk_04 != 4 || !(actor->flags & 0x1000)) {
            if ((actor->flags & 0xE000) == 0) {
                return;
            }
        }
        ((R16_801725A4_S_801725A4_0 *)owner)->unk_98 |= 0x80;
        if ((actor->flags & 0xE000) == 0) {
            return;
        }

        ((R16_801725A4_S_801725A4_3 *)motion)->unk_14 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_10 = 0;
        ((R16_801725A4_S_801725A4_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)(actor->tile_x),(u8)(actor->tile_y));

        {
            u8 *direction_table = ((u8 *)clown_direction_frames);
            if (*(unsigned char **)&actor->frameTable != direction_table) {
                (actor->frameTable) = direction_table;
                select_sprite_entry(
                    actor,(u8)(direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((R16_801725A4_S_801725A4_1 *)object)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
        }

        {
            if ((g_dungeon_status.active_actor) != 0) {
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
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}

/* Applies a value change and damped motion, then returns the actor to its tile and restores movement. */
void damp_actor_motion_then_recenter(R16_801729D8_S_80173294_0 *motion_state, ObjectPosition *motion, SpriteFrameState *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    switch (motion_state->phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -*(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion->velocity_y =
            -*(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 15;
        motion_state->phase++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, ((u8 *)D_80174244));
            return;
        }
        if (tile_state->flags & 0x8000) {
            motion_state->timer.s = 0;
            motion_state->phase = 2;
            return;
        }
        timer = -1;
        if (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        }
        motion_state->timer.s = timer;
                        /* fall through */

    case 1:
        x_speed_or_entity = motion->velocity_x;
        rounded_velocity = x_speed_or_entity;
        if (x_speed_or_entity < 0) {
            rounded_velocity = x_speed_or_entity + 3;
        }
        velocity_z = motion->velocity_y;
        motion->velocity_x = x_speed_or_entity - (rounded_velocity >> 2);

        rounded_velocity = velocity_z;
        motion->velocity_y = velocity_z - (rounded_velocity / 4);

        if (motion_state->timer.s > 0) {
            motion_state->timer.u = motion_state->timer.u - 1;
        } else if (tile_state->flags & 0x6000) {
            motion_state->timer.s = 0;
        }

        if (motion_state->timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, ((u8 *)D_80174244));
            return;
        }
        motion_state->timer.s = 8;
        motion_state->phase++;
        return;

    case 2:
        timer = motion_state->timer.s;
        if (timer != 0) {
            s32 tile_coord;
            s32 offset_coord;

            tile_coord = tile_state->tile_x << 6;
            offset_coord = motion->x.w.i;
            offset_coord -= 0x20;
            motion->velocity_x = ((tile_coord - offset_coord) << 15) / timer;

            offset_coord = motion->y.w.i;
            offset_coord -= 0x20;
            tile_coord = tile_state->tile_y << 6;
            motion->velocity_y =
                ((tile_coord - offset_coord) << 15) / motion_state->timer.s;
        }

        countdown = motion_state->timer.u - 1;
        motion_state->timer.p = countdown;
        if ((countdown << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion,(u8)tile_state->tile_x,(u8)tile_state->tile_y);
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

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void remove_defeated_clown(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

/* Runs the shared hop and shrink update, then clears the halfword at offset 0xA2. */
void shrink_hopping_clown(R16_80172CCC_S_80173588_0 *state, void *context, SpriteFrameState *data, void *render) {
    update_actor_hop_and_shrink(state, context, data, render);
    state->unk_A2 = 0;
}

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_clown_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

/*
 * Runs update_actor_hop_and_grow and installs update_actor_state_and_dispatch_transition when it
 * returns nonzero.
 */
void finish_actor_hop_and_grow_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void advance_clown_status_action(void *actor, void *context, SpriteFrameState *render_record, ActorRecord *actor_state)
{
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(render_record->flags & 0xE000)) {
            return;
        }
        render_record->frameTable = ((u8 *)clown_alt_direction_frames);
        select_sprite_entry(render_record,(u8)(((u8 *)clown_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        do {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
        } while (0);
        return;

    case 1:
        if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (actor_state->hp_delta != 0) {
                if (begin_ready_actor_directional_action(actor, context, render_record, 0) != 0) {
                    return;
                }
            }
            if (actor_state->mp == 0) {
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
                update_clown_parent_motion(actor, context, render_record, actor_state);
                return;
            }
            if (actor_state->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(actor_state,
                        (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor_state);
            on_actor_status_updated(actor_state);
            if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&render_record->room_index;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, render_record) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor_state, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }
        render_record->frameTable = ((u8 *)clown_frame_set_1);
        select_sprite_entry(render_record,(u8)(((u8 *)clown_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7]),
            0);
        (*(u32 *)&actor_state->flags1C) |= 0x40000;
        if (render_record->flags & 0x8000) {
            ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
        ((R16_80172D50_S_80173E50_0 *)actor)->unk_9B++;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        return;

    case 2:
        if (!(render_record->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        ((R16_80172D50_S_80173E50_0 *)actor)->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        return;
    }
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void advance_clown_mp_action(void *actor, void *context, SpriteFrameState *animation, ActorRecord *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(animation->flags & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)clown_alt_direction_frames);
        (animation->frameTable) = direction_anims;
        select_sprite_entry(animation,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp != 0) {

            (animation->frameTable) = ((u8 *)clown_frame_set_1);
            select_sprite_entry(animation,
                ((u8 *)clown_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->hp_delta != 0) {
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
            update_clown_parent_motion(actor, context, animation, entity);
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

        (animation->frameTable) = ((u8 *)clown_frame_set_1);
        select_sprite_entry(animation,
            ((u8 *)clown_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (animation->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~ACTOR_MP_EMPTY;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = ((void *)update_actor_state_and_dispatch_transition);
        }

        return;
    }
}

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_clown_parent_motion(R16_80173468_Actor *actor, s32 action, SpriteFrameState *entity, R16_80173468_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
            return;
        }
    } else if (*(u8 **)&entity->frameTable == ((u8 *)clown_alt_direction_frames) &&
               !(map_object->unk_1C & 0x208)) {
        entity->frameTable = ((u8 *)clown_direction_frames);
        select_sprite_entry(entity,(s16)(((u8 *)clown_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

/*
 * Runs update_thrown_actor_travel and installs update_actor_state_and_dispatch_transition only
 * when it succeeds and the signed floor-trap check returns positive.
 */
void finish_thrown_actor_travel_and_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_actor_state_and_dispatch_transition;
        }
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs update_actor_state_and_dispatch_transition
 * when it returns nonzero.
 */
void finish_actor_terrain_interpolation_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/*
 * Runs update_spinning_actor_fall and installs update_actor_state_and_dispatch_transition when it
 * returns nonzero.
 */
void finish_spinning_actor_fall_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/*
 * Runs propagate_actor_action_flag and installs update_actor_state_and_dispatch_transition when it
 * returns nonzero.
 */
void finish_actor_action_flag_propagation_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/*
 * Runs update_actor_fade_in and installs update_actor_state_and_dispatch_transition when it
 * returns nonzero.
 */
void finish_actor_fade_in_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/*
 * Runs resolve_actor_floor_trap_once and installs update_actor_state_and_dispatch_transition when
 * it returns positive.
 */
void finish_actor_floor_trap_then_dispatch_transition(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_actor_state_and_dispatch_transition;
    }
}

/* Projects visible sprites in the linked effect chain using the shared depth adjustment. */
s32 project_clown_sprite_chain(void *initial_payload, s32 entry_data, R16_801736AC_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R16_801736AC_Scratchpad *scratch = (R16_801736AC_Scratchpad *)0x1F800000;
    R16_801736AC_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)clown_fade_count)[0];

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

/*
 * Moves the effect in an expanding spiral, advances its sprite, fades its color, and expires it on
 * timeout.
 *
 * MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
 */
void update_expanding_spiral_effect(void *effect, R16_80173738_FuncArg1 *position, SpriteFrameState *primitive) {
    s16 life;
    s16 next_life;
    s32 y_offset;
    s32 base_y;
    s32 z_step;
    void *primitive_dst;

    ((R16_80173738_S_80173738_0 *)effect)->unk_1E = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_1E - 0x12C);
    ((R16_80173738_S_80173738_0 *)effect)->unk_20 = (u16) (((R16_80173738_S_80173738_0 *)effect)->unk_20 + 2);
    position->unk00 = (s32) (((R16_80173738_S_80173738_0 *)effect)->unk_40
        + ((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * rcos((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E) * 0x10));
    y_offset = (s16) ((R16_80173738_S_80173738_0 *)effect)->unk_20 * rsin((s16) ((R16_80173738_S_80173738_0 *)effect)->unk_1E);
    primitive_dst = primitive;
    z_step = 0xFFF40000U;
    base_y = ((R16_80173738_S_80173738_0 *)effect)->unk_44;
    position->unk08 = (s32) (position->unk08 + z_step);
    position->unk04 = (s32) (base_y + (y_offset * 0x10));
    advance_sprite_animation_and_textures(primitive_dst);
    if (primitive->flags & 0x4000) {
        select_record_entry_and_value(primitive, ((s32 *)shared_sprite_entries), 0);
    }
    life = ((R16_80173738_S_80173738_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->color.c.r = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_00 * life) / 9);
        primitive->color.c.g = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_01 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
        primitive->color.c.b = (s8) ((((R16_80173738_S_80173738_0 *)effect)->unk_02 * ((R16_80173738_S_80173738_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((R16_80173738_S_80173738_0 *)effect)->unk_1A - 1;
    ((R16_80173738_S_80173738_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 = (u16) (((R16_80173738_S_80173738_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 =
            (s32) (((R16_80173738_S_80173738_2 *)((s32 *)(&object_flag_block)))->unk_00 | 0x8000);
    }
}

/* Creates a green sprite at an angular offset from the source and installs its expanding spiral animation. */
void create_angled_source_effect(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset)
{
    ObjectNodeHeader *object;
    R16_80173904_S_80173904_0 *state;
    SpriteFrameState *display;
    ObjectPosition *transform;
    s16 wrapped_angle;

    object = allocate_flagged_object_node(0x212);
    wrapped_angle = angle;
    if (object != NULL) {
        state = (R16_80173904_S_80173904_0 *)((u8 *)object + 0x20);
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = angle;
        object->update_callback = ((void *)update_expanding_spiral_effect);
        register_node(object, project_sprite_chain);

        display = object->sprite;
        display->tpage_abr = 0x60;
        display->flags |= 0xC;
        if (rand() & 1) {
            display->flags |= 1;
        }

        transform = object->position;
        state->unk_40 = origin->unk_00;
        state->unk_44 = origin->unk_04;
        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        transform->x.v = state->unk_40 + ((state->unk_20 * rcos(wrapped_angle)) << 4);
        transform->y.v = state->unk_44 + ((state->unk_20 * rsin(wrapped_angle)) << 4);
        transform->z.w.i = origin->unk_0A + depth_offset;

        display = object->sprite;
        display->scale_y = 0x1000;
        display->scale_x = 0x1000;
        display->color.c.r = 0x40;
        display->color.c.b = 0x40;
        display->color.c.g = 0xC0;
        state->unk_00 = display->color.c.r;
        state->unk_01 = display->color.c.g;
        state->unk_02 = display->color.c.b;
        select_record_entry_and_value(display, ((u8 *)shared_sprite_entries), 0);
        display->clut = 0x7DCF;
        display->flags |= 0x100;
    }
}

/* Stops movement and waits for dungeon activity to finish, then clears the callback and counts the new
 * action. */
void wait_for_clown_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)wait_for_clown_action_slot);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)actor_action_reset_value) = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}

/* Advances the transition sprite, then restores the view tint to neutral and removes the effect. */
void fade_entity_colors_to_neutral(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    SpriteFrameState *source= source_data;
    GameWork *colors = &g_game_work;
    u16 ticks;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        (*(s32 *)D_801742E8) = *(s32 *)&source->source;
        advance_sprite_animation_and_textures(source);

        if (source->flags & 0xE000) {
            unlink_node(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = ticks + 1;
        if ((ticks & 3) == 0) {
            (*(u16 *)clown_fade_count)--;
            return;
        }
    } else {
        colors->view.tint.parts.tint_r += (0x80 - colors->view.tint.parts.tint_r) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_g += (0x80 - colors->view.tint.parts.tint_g) / *(s16 *)(entity + 0x96);
        colors->view.tint.parts.tint_b += (0x80 - colors->view.tint.parts.tint_b) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}

/* Loads transition effects, fades the view tint, emits particles, and starts loading the replacement
 * actor. */
void advance_actor_effect_sequence(Rec_func_801732A4_arg0 *state, EntityRec *position, SpriteFrameState *actor, void *model) {
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
    ObjectPosition *effect_position;
    R16_80173CEC_S_80173CEC_9 *effect_sprite;
    GameWork *scene_color;
    ObjectNodeHeader *effect;

    scene_color = &g_game_work;
    phase = state->unk_9B;
    switch (phase) {
    case 0:
        state->unk_9B = (u8) (state->unk_9B + 1);
        return;
    case 1:
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)clown_image_load_done), 0);
        state->unk_A6 = 0;
        state->unk_9B = (u8) (state->unk_9B + 1);
        ((Rec_D_80082E80 *)model)->unk_8A = (u16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v;
        ((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v =
            (s32) (((Rec_D_80082E80 *)model)->unk_1C.at00_s32.v & 0xFFFBFFFF);
    case 2:
        direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)((s32 *)clown_image_load_done)) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)model)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)model)->unk_28.at02_u16.v + 0x200);
            return;
        }
        run_cd_image_commands(((s32 *)D_801742CC), ((s32 *)clown_image_load_done), 1);
        sound_set_cd_cue_parameters(0, (*(s32 *)cd_cue_base), 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), NULL);
        (*(s8 *)((s32 *)clown_effect_load_done)) = 0;
        Control_CD(0xFF, ((s32 *)resource_completion_callback_address), ((s32 *)clown_effect_load_done));
        select_nearby_target_and_initialize_slot(model - 0x20, position, 8, 0x300);
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
    case 3:
        fade_timer = state->unk_96;
        fade_left = fade_timer - 1;
        state->unk_96 = fade_left;
        if ((fade_left << 0x10) <= 0) {
            event_done = ((R16_80173CEC_S_80173CEC_2 *)(((s32 *)clown_effect_load_done)))->unk_00;
            state->unk_96 = fade_timer;
            if (event_done == 0) {
                return;
            }
            state->unk_9B = (u8) (state->unk_9B + 1);
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }
        target_color = (*(void **)((u8 *)(((s32 *)actor_effect_color_targets)) + lookup_masked_byte_table(model) * 4));
        scene_color->view.tint.parts.tint_r = (u8) (scene_color->view.tint.parts.tint_r + ((s32) (target_color->unk_00
            - scene_color->view.tint.parts.tint_r) / (s16) state->unk_96));
        scene_color->view.tint.parts.tint_g = (u8) (scene_color->view.tint.parts.tint_g + ((s32) (target_color->unk_01
            - scene_color->view.tint.parts.tint_g) / (s16) state->unk_96));
        scene_color->view.tint.parts.tint_b = (u8) (scene_color->view.tint.parts.tint_b + ((s32) (target_color->unk_02
            - scene_color->view.tint.parts.tint_b) / (s16) state->unk_96));
        return;
    case 4:
        effect = allocate_flagged_object_node(0x12);
        if (effect == NULL) {
            return;
        }
        effect->update_callback = ((void *)fade_entity_colors_to_neutral);
        register_node(effect, ((void *)project_clown_sprite_chain));
        color = 0x808080;
        state->unk_AC = effect;
        effect_model = model;
        effect->position->x.v = (s32) position->x.v;
        effect->position->y.v = (s32) position->y.v;
        effect_position = effect->position;
        effect_value_2 = position->z.v;
        (*(s16 *)clown_fade_count) = -8;
        effect_position->z.v = effect_value_2;
        effect_sprite = effect->sprite;
        effect_sprite->unk_1E = 0x1000;
        effect_sprite->unk_1C = 0x1000;
        effect_sprite->unk_0C.s = color;
        variant_index = lookup_masked_byte_table(effect_model) - 1;
        effect_value = variant_index;
        if ((variant_index << 0x10) < 0) {
            effect_value = rand() % 3;
        }
        select_record_entry_and_value(effect_sprite, ((s32 *)D_801742D4)[(s16) effect_value] + (s8 *) ((s32 *)dungeon_resource_buffer), 0);
        actor->flags = (u16) (actor->flags | 0x80);
        spawn_count = 0;
        state->unk_96 = 0U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        do {
            create_angled_source_effect(state, position, actor, model, rand() & 0xFFF, 0);
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
                create_angled_source_effect(state, position, actor, model, rand() & 0xFFF, 0);
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
        if (create_status_linked_render_effect(position, (*(s32 *)D_801742E8), (*(s16 *)clown_fade_count), ((s32 *)staged_spawn_count)) == 0) {
            return;
        }
        state->unk_96 = 0x10U;
        state->unk_9B = (u8) (state->unk_9B + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)model)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(actor->tile_x, actor->tile_y, 0x300);
        unlink_entity_node(model);
        effect_sprite = model - 0x20;
        effect_sprite->unk_10 = (s32) (effect_sprite->unk_10 | 0x80000000);
        return;
    case 7:
        ((Rec_D_80082E80 *)model)->unk_60.as_s32 = advance_staged_entity_load(actor, model);
        return;
    }
}
