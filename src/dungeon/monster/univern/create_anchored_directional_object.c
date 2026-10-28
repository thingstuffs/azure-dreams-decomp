#include "shared/entity.h"
#include "shared/audio_commands.h"
#include "dungeon/actor/motion.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Univern actor spawning, linked displays, movement, attacks, and spell effects. */
#include "dungeon/actor.h"
#include "engine/cd.h"
#include "dungeon/monster/univern.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/object_flags.h"
void * (*const resource17_slot0_entry0)(s32 kind, s32 tile_x, s32 tile_y, s32 copy_value) = spawn_univern_actor;
void (*const resource17_slot0_entry1)(void *actor, void *motion, void *object) = create_anchored_directional_object;
#include "dungeon/monster/univern.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/level/room_flags.h"

/* Creates a Univern actor and its linked directional display, then initializes status and tile placement. */
void *spawn_univern_actor(s32 kind, s32 tile_x, s32 tile_y, s32 copy_value)
{
    ObjectNodeHeader *root;
    void *copy;
    s32 outer_index;
    s32 saved_kind;
    s32 saved_copy_value;
    s16 saved_tile_y;
    u16 saved_tile_x;
    ActorRecord *object;
    void *outer;
    R17_8017089C_S_8017089C_4 *stable_object;
    s32 kind_copy;
    SpriteFrameState *part;
    ObjectNodeHeader *allocated;
    s32 allocation_size;
    ObjectNodeHeader *allocation_pool;

    saved_kind = kind;
    object = 0;
    allocation_size = 0x112;
    saved_tile_x = tile_x;
    allocation_pool = &scene_object_list_anchor;

    saved_copy_value = copy_value;
    saved_tile_y = tile_y;
    allocated = allocate_list_node(allocation_size, allocation_pool);
    kind_copy = saved_kind;
    root = allocated;
    if (allocated != 0) {
        {
            ObjectNodeHeader *init_root;
            void *setup;

            object = (ActorRecord *)(allocated + 1);
            init_root = allocated;
            setup = project_sprite_chain;
            init_root->update_callback = ((u8 *)create_anchored_directional_object);
            object->species = MONSTER_UNIVERN;
            register_node(init_root, setup);
        }

        {
            void *part_callback;

            part_callback = ((u8 *)univern_direction_frames);
            copy = root->position;
            ((R17_8017089C_S_8017089C_2 *)copy)->unk_08.at02.v = saved_copy_value;
            stable_object = (R17_8017089C_S_8017089C_4 *)object;
            part = root->sprite;
            part->frameTable = part_callback;
        }
        part->tile_x = saved_tile_x;
        part->tile_y = saved_tile_y;

        {
            s32 object_flags;
            s32 state_flags;

            if ((saved_kind & 3) == 1) {
                object_flags = object->flags14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                state_flags = object->flags1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                object->flags14 = object_flags;
                object->flags1C = state_flags;
            } else if ((saved_kind & 3) >= 2) {
                object_flags = object->flags14 | ACTOR_CLASS_ENABLED;
                state_flags = object->flags1C | ACTOR_PLAYER_SIDE;
                object->flags14 = object_flags;
                object->flags1C = state_flags;
            } else {
                object_flags = saved_kind & ~3;
                if ((s16)object_flags == 0) {
                    if ((object->flags14 & ACTOR_RESIST_SLEEP) == 0) {
                        if (generate_random_value() & 1) {
                            object->flags1C |= ACTOR_ASLEEP;
                            set_or_clear_actor_status_slot(object, STATUS_SLEEP,
                                (generate_random_value() & 0x3F) | 0x20);
                            part->frameTable = ((u8 *)univern_alt_spawn_direction_frames);
                        }
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(root, copy, part,(s16)((s16)kind_copy));

        outer = stable_object;
        outer_index = 0;
        stable_object->unk_9A = 0xFF;
        stable_object->unk_9C = -1;
        stable_object->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        object->flags1C |= 0x40000;
        stable_object->unk_92 = -48;
        stable_object->unk_A8 = 0;
        stable_object->unk_9E = 1;
        stable_object->unk_98 |= 0x4000;

        do {

            saved_copy_value = (s32)allocate_list_node(0x112, &scene_object_list_anchor.next);
            allocated = (void *)saved_copy_value;
            ((R17_8017089C_S_8017089C_5 *)outer)->unk_A4 = allocated;
            if (allocated != 0) {
                s32 item_offset;
                s32 item_index;
                register R17_8017089C_S_8017089C_8 *outer_base;
                u8 *table;
                s32 more_items;

                saved_kind = (s32)((u8 *)allocated + 0x20);
                ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_02 = 1;
                item_index = 0;
                outer_base = outer;
                table = ((u8 *)univern_frame_set);
                item_offset = 8;
                do {
                    SpriteFrameState *item;
                    s32 direction_index;
                    s32 part_value;
                    s32 call_zero;
                    ObjectNodeHeader *outer_child;

                    item = (u8 *)(void *)saved_kind + item_offset;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_04 |= 0x8000;
                    part_value = part->animation_resource;
                    item->tpage_abr = 0x20;
                    item->color.word = 0x00808080;
                    item->animation_resource = part_value;
                    outer_child = outer_base->unk_A4;
                    call_zero = 0;
                    outer_child->update_callback = ((u8 *)child_object_update_address);
                    (*(void **)((u8 *)item + 0x2C)) = table;
                    direction_index = (((*(s16 *)view_facing_angle_alias) +
                        object->facing + 0x100) >> 9) & 7;
                    select_sprite_entry(item,
                        *(u8 *)((R17_8017089C_uptr)direction_index + (R17_8017089C_uptr)table), call_zero);
                    item_offset += 0x30;
                    item_index++;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_06 = 1;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part, ((u8 *)child_texture_entries), 1);
                    more_items = item_index < ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_02;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_98 = (u8 *)root + 0x1E;
                } while (more_items);
            }
            outer = (u8 *)outer + 4;
            {
                s32 child_count;

                child_count = stable_object->unk_9E;
                outer_index++;
                if (outer_index >= child_count) {
                    break;
                }
            }
        } while (1);

        try_move_actor_to_valid_position(stable_object, copy, part, object);
    }
    return object;
}
#include "dungeon/monster/univern.h"

/* Runs actor callbacks and updates facing, animation, bobbing height, movement, and terrain contact. */
void create_anchored_directional_object(void *actor, void *motion, SpriteFrameState *object)
{
    u16 initial_flags = g_dungeon_status.flags;
    s32 bob = 0;
    R17_80170BB8_S_80170BB8_2 *actor_state = actor;
    s16 previous_index;
    s16 direction;
    s16 ground;
    s32 ground_offset;
    s32 bob_wave;
    s32 height;
    R17_80170BB8_EntityCallback callback;
    u8 *animation_table;
    u16 status_flags;
    u16 movement_flags;

    if (initial_flags & 0x2000) {
        R17_80170BB8_EntityCallback early_callback = (*(R17_80170BB8_EntityCallback *)((u8 *)actor + (0x8C)));
        if ((void *)early_callback == (void *)((u8 *)update_entity_movement_and_ground_height)) {
            early_callback(actor, motion, object, actor);
            return;
        } else {
            (*(u8 *)((u8 *)actor + (0x71))) &= 0x7F;
            return;
        }
    }

    previous_index = (s8)(*(u8 *)((u8 *)actor + (0x6D)));
    if (refresh_actor_facing_and_lifecycle(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(R17_80170BB8_EntityCallback *)((u8 *)actor + (0x8C)));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    ((R17_80170BB8_EntityCallback *)D_80174504)[(*(u8 *)((u8 *)actor + (0x9A)))](actor, motion, object, actor);
    if ((s16)previous_index != (s8)(*(u8 *)((u8 *)actor + (0x6D)))) {
        try_move_actor_to_valid_position(actor, motion, object, actor);
    }

    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at00.v += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_0C;
    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at00.v += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)actor + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
        ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 += (s8)(*(u8 *)((u8 *)actor + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)actor + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)actor + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)actor + (0x90))) += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14;
    status_flags = object->flags;

    if (!(status_flags & 0x8000)) {
        {
            ground_offset = (g_game_work.view.camera_rotation.parts.viewAngle + actor_state->unk_2A + 0x100) >> 9;
            direction = ground_offset & 7;
        }
        if ((*(s16 *)((u8 *)actor + (0x94))) != direction) {
            select_indirect_table_entry(object, (*(u8 **)&object->frameTable)[direction],
                          object->unk_04);
            (*(s16 *)((u8 *)actor + (0x94))) = direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[direction] != 0) {
                flip_flags = object->flags | 1;
            } else {
                flip_flags = object->flags & 0xFFFE;
            }
            object->flags = flip_flags;
        }
        if ((*(u8 *)((u8 *)actor + (0x9A))) != 8) {
            apply_monster_koyaw_data(actor_state->unk_1C.s, (u8 *)object + 0xC);
        }

        if (!(actor_state->unk_1C.u & 0x20)) {
            if (!(object->flags & 0x40)) {
                advance_sprite_animation_and_textures(object);
            }
        } else {
            object->flags |= 0x7000;
            actor_state->unk_1C.u &= 0xFFFBFFFF;
        }

        actor_state->unk_1C.u = ((u32)(actor_state->unk_1C.u & 0xF7FFFFFF));
        if (((u32)(actor_state->unk_1C.u & 0xF7FFFFFF)) & 0x40000) {
            if (!(object->flags & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = object->frameTable;
                    if (animation_table == ((u8 *)univern_alt_direction_frames)) {
                        (object->frameTable) = ((u8 *)univern_direction_frames);
                        select_sprite_entry(object,
                            ((u8 *)univern_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                    else if (animation_table == ((u8 *)univern_direction_frames)) {
                        (object->frameTable) = ((u8 *)univern_alt_direction_frames);
                        select_sprite_entry(object,
                            ((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                }
                if (object->flags & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (*(u8 **)&object->frameTable == ((u8 *)univern_direction_frames)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = rsin(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(actor_state->unk_88.u - 0x20))) -
                    actor_state->unk_88.u);
                if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
                } else if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
                }
            }
        } else {
            movement_flags = (*(u16 *)((u8 *)actor + (0x98)));
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(u16 *)((u8 *)actor + (0x98))) = movement_flags & 0x7FFF;
            if (!(movement_flags & 8)) {
                ground_offset = ((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(actor_state->unk_88.u - 0x20))) -
                    actor_state->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    actor_state->unk_1C.u |= 0x08000000;
                }
            }
        }
    } else {
        if (!(status_flags & 0x800)) {
            object->flags = status_flags | 0x7000;
        } else {
            object->flags = status_flags & 0x8FFF;
        }
        actor_state->unk_1C.u = ((u32)(actor_state->unk_1C.u & 0xF7FFFFFF));

        if (!(((u32)(actor_state->unk_1C.u & 0xF7FFFFFF)) & 0x40000)) {
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(s16 *)((u8 *)actor + (0x92))) -= bob;
            bob = 0;
            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground_offset = ((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(actor_state->unk_88.u - 0x20))) -
                    actor_state->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    actor_state->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(object->flags & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = object->frameTable;
                    if (animation_table == ((u8 *)univern_alt_direction_frames)) {
                        (object->frameTable) = ((u8 *)univern_direction_frames);
                        select_sprite_entry(object,
                            ((u8 *)univern_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    } else if (animation_table == ((u8 *)univern_direction_frames)) {
                        (object->frameTable) = ((u8 *)univern_alt_direction_frames);
                        select_sprite_entry(object,
                            ((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    }
                }
                if (object->flags & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (*(u8 **)&object->frameTable == ((u8 *)univern_direction_frames)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = rsin(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(actor_state->unk_88.u - 0x20))) -
                    actor_state->unk_88.u);
                if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
                } else if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
                }
            }
        }

        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
        (*(u16 *)((u8 *)actor + (0x98))) &= 0x7FFF;
    }

    if (actor_state->unk_1C.u & 0x40000000) {
        actor_state->unk_1C.u = actor_state->unk_1C.u & 0xBFFFFFFF;
        ground = ((s16)sample_terrain_surface_height((object->tile_x << 6) | 0x20,
            (object->tile_y << 6) | 0x20,
            (s16)(actor_state->unk_88.u - 0x20)));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)actor + (0x92))) += actor_state->unk_88.u - ground;
            actor_state->unk_88.u = ground;
        }
    }
    height = actor_state->unk_88.u +
        (u16)(*(s16 *)((u8 *)actor + (0x92)));
    height += bob;
    *(s16 *)((u8 *)motion + 0xA) = height;
    object->flags |= 0x40;
}
#include "dungeon/monster/univern.h"

/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void update_entity_movement_and_ground_height(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status) {
    u16 distance;
    u32 flags;
    s32 action_index;
    s8 tile_index;
    u16 action_flags;
    void *resume_handler;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 14;
        advance_entity_along_path_2(actor, context, sprite, status);
        return;
    }

    if (status->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (*(u8 **)&sprite->frameTable == ((u8 *)univern_alt_spawn_direction_frames)) {
            return;
        }
        (sprite->frameTable) = ((u8 *)univern_frame_set_1);
        select_sprite_entry(
            sprite,(u8)(((u8 *)univern_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7]),
            0);
        return;
    }

    if (((u32)status->flags1C) & ACTOR_ASLEEP) {
        if (*(u8 **)&sprite->frameTable == ((u8 *)univern_alt_spawn_direction_frames)) {
            actor->action_id.u = 13;
            actor->action_phase.u = 2;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            status->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, ((u8 *)univern_frame_set_1)) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((u32)status->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }

        if (actor->action_id.u != 14) {
            actor->action_id.u = 14;
        }

        if ((*(u8 **)&sprite->frameTable != ((u8 *)univern_direction_frames)) &&
            (*(u8 **)&sprite->frameTable != ((u8 *)univern_alt_direction_frames))) {
            actor->unk_A8.s = 0;
            (sprite->frameTable) = ((u8 *)univern_alt_direction_frames);
            select_sprite_entry(
                sprite,(u8)(((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7]),
                actor->unk_A8.s);
        }

        status->flags1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (status->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, ((u8 *)D_801744A4)) != 0) {
                return;
            }
        }

        if (((u32)status->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            actor->unk_A8.s = 0;
            update_univern_parent_motion(actor, context, sprite, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }

    tile_index = ((s8)find_active_rect_containing_point((u8)(sprite->tile_x),(u8)(sprite->tile_y)));
    sprite->room_index = tile_index;

    if (status->pending_turn_updates > 0) {
        if (((u32)status->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(status);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            choose_univern_move(actor, context, sprite, status);
            return;
        }
        action_flags = status->action_flags;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        status, (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)relink_univern_path(actor, context, sprite, 0) == 0) {
                return;
            }
            action_flags = status->action_flags | 0x4000;
            status->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                choose_univern_move(actor, context, sprite, status);
                return;
            }
        }

        action_index = (status->action_flags & ACTOR_ACTION_CODE_MASK) - 1;
        switch (action_index) {

        case 7:
        case 8:
            if ((s16)try_univern_attack(actor, context, sprite, status) != 0) {
                return;
            }
            begin_univern_attack(actor, context, sprite, status);
            return;

        case 4:
        case 5:
        case 6:
        {
            s16 target_angle;
            ActorRecord *active_actor;

            target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(sprite->tile_x),(s16)(sprite->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), &distance));
            active_actor = primary_actor_record;
            status->facing = target_angle;
            if (active_actor->action_id.u != 0x11) {
                update_actor_status_and_mp(status);
                return;
            }
        }
            resume_handler = (void *)update_entity_movement_and_ground_height;
            begin_actor_spell_action(actor, context, sprite, ((u8 *)D_801744D4), resume_handler);
            return;

        case 11:
            update_actor_status_and_mp(status);
            return;

        case 0:
        case 1:
        case 2:
            resume_handler = (void *)update_entity_movement_and_ground_height;

            begin_actor_spell_action(actor, context, sprite, ((u8 *)D_801744D4), resume_handler);
            return;

        case 3:
        case 9:
        case 10:
        default:
            choose_univern_move(actor, context, sprite, status);
            return;
        }
    }

    flags = ((u32)status->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (dungeon_rooms[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    if ((s16)test_neighbor_position_relation((u8)(sprite->tile_x),(u8)(sprite->tile_y),(u8)(reference_tile_object.tile_position.parts.tile_x),(u8)(reference_tile_object.tile_position.parts.tile_y)) == 0) {
        return;
    }
    status->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(sprite->tile_x),(s16)(sprite->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), &distance));
}
#include "dungeon/monster/univern.h"

/* Advances one stored path step, updates occupied tiles and facing, and sets the movement delay. */
void advance_entity_along_path_2(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *entity, ActorRecord *path_state) {
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;

    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (path_state->movement_queue_state <= path_state->unk_8A) {
        return;
    }

    direction_table = entity->frameTable;
    if (direction_table != ((u8 *)univern_direction_frames) && direction_table != ((u8 *)univern_alt_direction_frames)) {
        (entity->frameTable) = ((u8 *)univern_alt_direction_frames);
        select_sprite_entry(
            entity,
            ((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + path_state->facing + 0x100) >> 9) & 7],
            0);
        motion->unk_A8.s = 0;
    }

    old_x = entity->tile_x;
    old_y = entity->tile_y;
    occupancy_mask = 0x3000;
    if (path_state->flags1C & 0x2000) {
        occupancy_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

    entity->tile_x =
        ((ActorStatusBytesView *)((u8 *)path_state + path_state->unk_8A))->path_x;
    entity->tile_y =
        ((ActorStatusBytesView *)((u8 *)path_state + path_state->unk_8A))->path_y;
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.u++;

    new_x = entity->tile_x;
    new_y = entity->tile_y;
    occupancy_mask = 0x3000;
    if (path_state->flags1C & 0x2000) {
        occupancy_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, occupancy_mask);

    path_state->facing = ((s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, entity->tile_x, entity->tile_y,
        (u8 *)motion + 0x98));
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.u |= 0x40000000;
    motion->action_id.u = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        motion->action_timer.u = 0;
        return;
    }

    motion->action_timer.u = 8;
    {
        s32 step_count = path_state->movement_queue_state;
        if (step_count > 0) {
            motion->action_timer.u = 8 / step_count;
        }
    }
}
#include "dungeon/monster/univern.h"

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_univern_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data) {
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (actor_data->unk_12 >= 2 ||
            (s16)try_univern_attack(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y));
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(blocker_sprite->tile_x),(s16)(blocker_sprite->tile_y),
                    &move_data->action_state_flags));
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y),(s16)(actor_data->facing)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_x == (u16)target_x &&
                    position_data->tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = &move_data->action_state_flags;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                actor_data->facing = target_angle;
                if (((s16)check_directional_move_and_terrain((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                              &move_data->action_state_flags);
            }
        }
    } else if ((s8)position_data->room_index >= 0 &&
               dungeon_rooms[(s8)position_data->room_index].flags & ROOM_HOLY_BEAM) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                      &move_data->action_state_flags);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)(position_data->tile_x),(u8)(position_data->tile_y),(s16)(actor_data->facing));
        blocker = (ActorRecord *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)((s16)get_actor_height_difference(blocker, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    (actor_data->facing >> 9) & 0xFFFF,(s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), &move_data->action_state_flags));
            if (((s16)test_neighbor_position_relation(
                    position_data->tile_x, position_data->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            (actor_data->facing >> 9) & 0xFFFF,(s16)(position_data->tile_x),(s16)(position_data->tile_y),(s16)((s16)(actor_data->ground_height - 0x20)))) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C, (u8 *)actor_data,
                          &move_data->action_state_flags);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = move_data->action_state_flags;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_directional_move_and_terrain((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_x =
                position_data->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))->path_y =
                position_data->tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_x, position_data->tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = ((u16)actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_x += *x_step;
                position_data->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)(position_data->tile_x),(s16)(position_data->tile_y),(u16)((actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object.tile_position.word != *(u16 *)&position_data->tile_x) {
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
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (position_data->tile_x << 6) | 0x20,
        (position_data->tile_y << 6) | 0x20,(s16)((s16)(actor_data->ground_height - 0x20))));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}
#include "dungeon/monster/univern.h"

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 try_univern_attack(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor) {
    ActorRecord *neighbor;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    neighbor = probe_directional_neighbor(actor, sprite_arg->tile_x,
                           sprite_arg->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, neighbor) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(neighbor, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->action_id.s = 0x11;
        action_state->action_phase.s = 0;
        action_state->unk_8C.run = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite_arg->frameTable = ((u8 *)univern_direction_frames);
        select_sprite_entry(sprite_arg, (((u8 *)univern_direction_frames))[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
#include "dungeon/monster/univern.h"

/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void begin_univern_attack(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity) {
    entity->movement_queue_state = (s8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->action_id.u = 0x11;
            action_state->unk_8C.handler = 0;
            action_state->action_phase.u = 0;
            select_sprite_entry(animation, *(*(u8 **)&animation->frameTable + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
            prepare_directional_attack(entity, animation, entity->facing, 1, 0);
            action_state->action_state_flags = (u16) (action_state->action_state_flags | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
#include "dungeon/monster/univern.h"

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 relink_univern_path(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_univern_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R17_801724C4_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_univern_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R17_801724C4_S_80172628_0 *)entity)->unk_71 = (u8) (((R17_801724C4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R17_801724C4_S_80172628_0 *)entity)->unk_71 = (u8) (((R17_801724C4_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R17_801724C4_S_80172628_0 *)entity)->unk_46 = (u16) (((R17_801724C4_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
#include "dungeon/monster/univern.h"

/*
 * Spends MP and advances status timers when movement completes, resuming the actor handler only
 * after a positive signed floor-trap check. Sets the secondary timer to -0x20 under dungeon flag
 * 0x80 during movement or after an accepted trap check. /
 */
void finish_actor_tile_move_then_resume_ground_movement(void *state, void *motion, void *source, void *target) {
    if (update_actor_movement_to_tile(state, motion, source, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)update_entity_movement_and_ground_height);
            if (g_dungeon_status.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs update_linked_actor_motion and installs update_entity_movement_and_ground_height only when
 * it succeeds and the signed floor-trap check returns positive.
 */
void finish_linked_actor_motion_and_floor_trap_then_resume_ground_movement(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = update_entity_movement_and_ground_height;
        }
    }
}
#include "dungeon/monster/univern.h"

/* Animates a backward hop and forward attack, applies damage, then recenters the actor and spends MP. */
void update_staged_movement_and_direction(void *action, void *motion, SpriteFrameState *sprite, void *actor)
{
    s32 step_x;
    s32 step_y;
    s32 phase_ticks;
    s32 state;
    s32 dir_offset;
    s32 rise;
    s32 target;
    s32 current;
    void *turn_actor;
    u16 flags;
    u8 *dir_x;
    u8 *dir_y;

    dir_x = ((u8 *)dir_step_x);
    dir_offset = (F16(actor, 0x2A) >> 8) & 0xE;
    step_x = *(s16 *)(dir_x + dir_offset);
    dir_y = ((u8 *)dir_step_y);
    step_y = *(s16 *)(dir_y + dir_offset);
    state = F8(action, 0x9B);
    F16(action, 0x96)--;

    switch (state) {
    case 0:
        flags = sprite->flags;
        turn_actor = actor;
        if (flags & 0x8000) {
            F8(action, 0x9B) = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(turn_actor, sprite,(s16)(FS16(turn_actor, 0x2A)),(s16)(1));
            return;
        }
        if (!(flags & 0xE000))
            return;
        sprite->frameTable = ((u8 *)D_801744B4);
        select_sprite_entry(sprite, ((u8 *)D_801744B4)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F32(motion, 0xC) = (-step_x) << 18;
        F32(motion, 0x10) = (-step_y) << 18;
        F16(action, 0x98) |= 8;
        F32(actor, 0x1C) &= 0xF7FFFFFF;
        F32(actor, 0x1C) &= 0xFFFBFFFF;
        F16(action, 0x96) = 4;
        F32(motion, 0x14) = 0xFFFE8000;
        F8(action, 0x9B)++;
        return;

    case 1:
        rise = F32(motion, 0x14);
        F32(motion, 0x14) = rise + (rise >> 2);
        if (FS16(action, 0x96) > 0)
            return;
        F16(action, 0x96) = 8;
        F8(action, 0x9B)++;
        return;

    case 2:
        F32(motion, 0xC) -= F32(motion, 0xC) >> 3;
        F32(motion, 0x10) -= F32(motion, 0x10) >> 3;
        F32(motion, 0x14) -= F32(motion, 0x14) >> 3;
        phase_ticks = 4;
        if (FS16(action, 0x96) == phase_ticks) {
            F32(motion, 0xC) = 0;
            F32(motion, 0x10) = 0;
            F32(motion, 0x14) = 0;
            sprite->frameTable = ((u8 *)D_801744BC);
            select_sprite_entry(sprite, ((u8 *)D_801744BC)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        if (FS16(action, 0x96) > 0)
            return;
        if (!(sprite->flags & 0xE000))
            return;
        F16(action, 0x96) = phase_ticks;
        F32(motion, 0xC) = (step_x << 18) + (step_x << 17);
        F32(motion, 0x10) = (step_y << 18) + (step_y << 17);
        sprite->frameTable = ((u8 *)D_801744C4);
        select_sprite_entry(sprite, ((u8 *)D_801744C4)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F8(action, 0x9B)++;
        return;

    case 3:
        F32(action, 0x90) += 0x80000;
        F32(motion, 0xC) += step_x << 18;
        F32(motion, 0x10) += step_y << 18;
        if (FS16(action, 0x96) == 2) {
            play_sound_if_enabled(0x809);
        }
        turn_actor = actor;
        if (FS16(action, 0x96) > 0)
            return;
        resolve_attack_damage_and_effects(turn_actor, sprite,(s16)(FS16(turn_actor, 0x2A)),(s16)(1));

        F8(action, 0x9B)++;
        return;

    case 4:
        F32(action, 0x90) += 0x80000;
        if (!(sprite->flags & 0xE000))
            return;
        sprite->frameTable = ((u8 *)D_801744CC);
        select_sprite_entry(sprite, ((u8 *)D_801744CC)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F32(motion, 0x14) = 0;
        F32(action, 0x90) = 0;
        F16(action, 0x98) &= 0xFFF7;
        F32(actor, 0x1C) |= 0x08000000;
        F8(action, 0x9B) = 0xFF;
        return;

    case 0xFF:
        target = sprite->tile_x << 6;
        current = FS16(motion, 2);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0xC) = target;
        target = sprite->tile_y << 6;
        current = FS16(motion, 6);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0x10) = target;
        if (!(sprite->flags & 0xE000))
            return;
        F32(motion, 0x10) = 0;
        F32(motion, 0xC) = 0;
        F32(actor, 0x1C) |= 0x40000;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        FPTR(action, 0x8C) = ((u8 *)update_entity_movement_and_ground_height);
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        sprite->frameTable = ((u8 *)univern_alt_direction_frames);
        select_sprite_entry(sprite, ((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        if (FS8(actor, 0x6D) == 0) {
            F16(actor, 0x46) &= 0x7FFF;
            return;
        }
        (*(void **)actor_update_node_cursor) = (u8 *)actor - 0x20;

        return;
    default:
        return;
    }
}
#include "dungeon/monster/univern.h"

/* Targets and starts a spell effect, waits for loading and animation, then restores movement and status. */
void update_entity_item_action_and_idle_return(R17_80172C18_State *state, R17_80172C18_Position *pos, SpriteFrameState *actor, R17_80172C18_Entity *ent)
{
    u8 *item_slot;
    s32 state_index;
    s16 use_main_link;
    u8 *actor_parts;
    R17_80172C18_SubActor *sub_actor;
    SpriteFrameState *actor_base;

    use_main_link = 0;
    state_index = state->state9B;
    actor_parts = state->fA4;
    sub_actor = (R17_80172C18_SubActor *)(actor_parts + 0x20);
    actor_base = (R17_80172C18_ActorBase *)(actor_parts + 0x28);

    switch (state_index) {
    case 0:
        if (ent->flags1C & ACTOR_PLAYER_SIDE) {
            s32 slot_index;

            slot_index = (ent->f46 & 0x3FFF) - 1;
            switch (slot_index) {
            case 6:
                use_main_link = 1;
                /* fall through */
            case 2:
                item_slot = &ent->slots[6];
                break;
            case 5:
                use_main_link = 1;
                /* fall through */
            case 1:
                item_slot = &ent->slots[3];
                break;
            case 4:
                use_main_link = 1;
                /* fall through */
            case 0:
                item_slot = &ent->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 slot_type;

            slot_type = ent->f46 & 0x3FFF;
            switch (slot_type) {
            case 3:
                item_slot = &ent->slots[6];
                break;
            case 2:
                item_slot = &ent->slots[3];
                break;
            case 1:
                item_slot = &ent->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            s32 main_link_test;
            u16 state_flags;
            u8 *link_base;
            u8 *linked_actor;

            state_flags = state->flags98;
            state_flags &= 0xFF7F;
            state->flags98 = state_flags;
            main_link_test = use_main_link;
            if (main_link_test) {
                link_base = (u8 *)((R17_80172C18_MainObj *)primary_actor_record);
                ent->f60 = link_base;
                linked_actor = *(u8 * *)&((ObjectNodeHeader *)((u8 *)link_base - 0x20))->sprite;
                ent->f72 = linked_actor[0x24];
                ent->f73 = linked_actor[0x25];
            } else if (item_action_definitions[*item_slot].kind == 2) {
                link_base = ent->f60;
                if (link_base != 0) {
                    linked_actor = *(u8 * *)&((ObjectNodeHeader *)((u8 *)link_base - 0x20))->sprite;
                    ent->f72 = linked_actor[0x24];
                    ent->f73 = linked_actor[0x25];
                }
            } else {
                s32 offset_y;
                s32 offset_x;

                ent->f60 = scan_actor_along_heading(
                    ent,(u8)(actor->tile_x),(u8)(actor->tile_y),(s16)(ent->f2A), 0x10);
                offset_x = __builtin_abs(ent->f72);
                offset_y = __builtin_abs(ent->f73);
                ent->f72 = offset_x;
                ent->f73 = offset_y;
            }

            sub_actor->flags4 &= 0x7FFF;
            actor_base->frameTable = (void (*)(void))((u8 *)univern_frame_set);
            select_sprite_entry(
                actor_base,
                ((u8 *)univern_frame_set)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                0);
            if (!create_actor_spell_effect(ent, item_slot, use_main_link, &state->flags98)) {
                return;
            }
            actor->flags &= 0xF7FF;
            create_source_positioned_object(pos, 5);
            play_sound_if_enabled(0x703);
            state->state9B++;
            state->flags98 |= 8;
            ent->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
            ent->flags1C &= 0xFFFBFFFF;
            return;
        }

        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->tile_x),(u8)(actor->tile_y));
        {
            R17_80172C18_MainObj *main_obj;

            main_obj = ((R17_80172C18_MainObj *)primary_actor_record);
            g_dungeon_status.active_actor = 0;
            main_obj->fA6--;
        }
        advance_status_timers(ent);
        ent->f6D--;
        state->f8C = (void (*)(void))((u8 *)update_entity_movement_and_ground_height);
        ent->f73 = 0;
        ent->f72 = 0;
        ent->f46 &= 0x7FFF;
        return;

    case 1:
        state->u90.h.half92 += (-0x60 - (s16)state->u90.h.half92) >> 3;
        if (actor->flags & 0xE000) {
            actor->frameTable = (void (*)(void))((u8 *)D_801744DC);
            select_sprite_entry(
                actor,
                ((u8 *)D_801744DC)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                0);
            state->f96 = state_index;
            state->state9B++;
        }
        return;

    case 2:
        if (get_cd_command_queue_depth()) {
            actor->flags |= 0x800;
            return;
        }
        actor->flags &= 0xF7FF;
        state->state9B++;

    case 3:
        state->u90.h.half92 +=
            (-0x30 - (s16)state->u90.h.half92) >> 3;
        state->f96--;
        if ((s16)state->f96 <= 0 || (actor->flags & 0xE000)) {
            state->flags98 |= 0x80;
        }
        if ((!(state->flags98 & 0x4000) && state->fA8 == 2) || (actor->flags & 0x8000)) {
            state->flags98 |= 0x4000;
        }
        if (!(actor->flags & 0xE000)) {
            return;
        }

        sub_actor->flags4 |= 0x8000;
        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->tile_x),(u8)(actor->tile_y));
        state->flags98 &= 0xFFF7;
        ent->flags1C |= ACTOR_GROUNDED;
        ent->flags1C |= 0x00040000;

        if (*(void (**)(void))&actor->frameTable != (void (*)(void))((u8 *)univern_direction_frames) &&
            *(void (**)(void))&actor->frameTable != (void (*)(void))((u8 *)univern_alt_direction_frames)) {
            state->fA8 = 0;
            state->flags98 &= 0xBFFF;
            actor->frameTable = (void (*)(void))((u8 *)univern_direction_frames);
            select_sprite_entry(
                actor,
                ((u8 *)univern_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                state->fA8);
        }
        {

            if ((g_dungeon_status.active_actor) != 0) {
                return;
            }
            if (!(state->flags98 & 0x4000)) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags &= 0xF7FF;
        state->f8C = (void (*)(void))((u8 *)update_entity_movement_and_ground_height);
        advance_status_timers(ent);
        if (ent->f6D > 0) {
            ent->f6D--;
        }
        ent->f73 = 0;
        ent->f72 = 0;
        ent->f46 &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);

        return;
    default:
        return;
    }
}
#include "dungeon/monster/univern.h"
#include "shared/sprite_frame_state.h"

/* Applies a value change and knockback, then returns the actor to its tile and restores movement. */
void advance_univern_flight(void *action, void *motion, SpriteFrameState *sprite, void *actor)
{
    s16 flight_timer;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;

    direction = (((EntityRec *)actor)->unk_6A >> 9) & 7;

    switch (((R17_80173244_S_80173354_1 *)action)->phase) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_801744AC));
            return;
        }

        if (sprite->flags & 0x8000) {
            ((R17_80173244_S_80173354_1 *)action)->timer.s = 0;
            ((R17_80173244_S_80173354_1 *)action)->phase = 2;
            return;
        }

        ((EntityRec *)motion)->unk_0C = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        ((EntityRec *)motion)->unk_10 = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((EntityRec *)motion)->flags14 = 0x40000;
        ((R17_80173244_S_80173354_1 *)action)->unk_98 |= 8;
        ((EntityRec *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((EntityRec *)actor)->flags1C &= 0xFFFBFFFF;
        ((R17_80173244_S_80173354_1 *)action)->phase++;

        flight_timer = -1;
        if (((u32)((EntityRec *)actor)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            flight_timer = 8;
        }
        ((R17_80173244_S_80173354_1 *)action)->timer.s = flight_timer;

        velocity_x = ((EntityRec *)motion)->unk_0C;
        rounded_velocity_x = velocity_x;
        if (velocity_x < 0) {
            rounded_velocity_x = velocity_x + 3;
        }
        velocity_y = ((EntityRec *)motion)->unk_10;
        ((EntityRec *)motion)->unk_0C = velocity_x - (rounded_velocity_x >> 2);
        rounded_velocity_y = velocity_y;
        ((EntityRec *)motion)->unk_10 = velocity_y - (rounded_velocity_y / 4);
        return;

    case 1:
        ((EntityRec *)motion)->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        ((EntityRec *)motion)->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (((R17_80173244_S_80173354_1 *)action)->timer.s > 0) {
            ((R17_80173244_S_80173354_1 *)action)->timer.u--;
        } else if (sprite->flags & 0x6000) {
            ((R17_80173244_S_80173354_1 *)action)->timer.s = 0;
        }
        if (((R17_80173244_S_80173354_1 *)action)->timer.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((R17_80173244_S_80173354_1 *)action)->phase = 0;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_801744AC));
            return;
        }
        ((R17_80173244_S_80173354_1 *)action)->timer.s = 8;
        ((R17_80173244_S_80173354_1 *)action)->phase++;
        return;

    case 2:
        ((EntityRec *)motion)->flags14 = 0xFFFE0000;
        if (((R17_80173244_S_80173354_1 *)action)->timer.s != 0) {
            s32 tile_delta;
            s32 position;

            tile_delta = sprite->tile_x << 6;
            position = ((EntityRec *)motion)->x.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_0C = tile_delta >> 1;
            tile_delta = sprite->tile_y << 6;
            position = ((EntityRec *)motion)->y.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_10 = tile_delta >> 1;
            ((EntityRec *)motion)->unk_0C += ((EntityRec *)motion)->unk_0C >> 1;
            ((EntityRec *)motion)->unk_10 += ((EntityRec *)motion)->unk_10 >> 1;
        }

        {
            s16 landing_timer = (u16)((R17_80173244_S_80173354_1 *)action)->timer.s - 1;

            ((R17_80173244_S_80173354_1 *)action)->timer.s = landing_timer;
            if (landing_timer > 0) {
                return;
            }
        }

        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)sprite->tile_x,(u8)sprite->tile_y);

        ((R17_80173244_S_80173354_1 *)action)->unk_90 = 0;
        ((R17_80173244_S_80173354_1 *)action)->unk_98 &= 0xFFF7;
        ((EntityRec *)actor)->flags1C |= ACTOR_GROUNDED;
        ((EntityRec *)actor)->flags1C |= 0x00040000;
        sprite->frameTable = ((u8 *)univern_alt_direction_frames);
        select_sprite_entry(sprite,(u8)(((u8 *)univern_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7]),
            0);

        {
            DungeonGlobalStatus *global_state = &g_dungeon_status;

            if (((s32)global_state->pending_display_owner) == (u8 *)actor - 0x20) {
                (*(u32 *)&global_state->pending_display_owner) &= 0x7FFFFFFF;
            }
        }
        ((R17_80173244_S_80173354_1 *)action)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;

    default:
        return;
    }
}
#include "dungeon/monster/univern.h"

/* Moves and fades the defeated actor, awards experience, clears tile occupancy, and unlinks the actor. */
void advance_familiar_defeat_sequence(R17_80173614_S_func_80C17E14_0 *action, MotionDeltaView *motion, R17_80173614_S_func_80C17E14_2 *sprite,
    R17_80173614_S_func_80C17E14_3 *entity) {
    s32 direction_offset;
    s32 offset_x;
    s32 offset_y;
    s32 state;

    direction_offset = (entity->unk_6A >> 8) & 0xE;
    offset_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    offset_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    state = action->unk_9B;

    switch (state) {
    case 0:
        motion->velocity_x = offset_x << 16;
        motion->velocity_y = offset_y << 16;
        motion->velocity_z = 0x8000;
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        action->unk_9B = action->unk_9B + 1;
    case 1:
    {
        s32 entity_status;
        u32 entity_flags;
        u32 clear_bit_27;
        u32 clear_bit_18;
        u16 action_flags;

        entity_status = entity->unk_14;
        if (entity_status & 0x4000) {
            if (!(entity_status & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        play_sound_if_enabled(0x805);

        clear_bit_27 = 0xF7FFFFFF;
        action_flags = action->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        action_flags |= 8;
        action->unk_98 = action_flags;
        entity_flags = entity->unk_1C;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        entity->unk_1C = entity_flags;
        sprite->unk_10 = 0x60;
        sprite->unk_12 = 0xFF80;
        sprite->unk_14 |= 0xC;
        action->unk_9B = action->unk_9B + 1;
        return;
    }
    case 2:
        if (!(sprite->unk_14 & 0x6000)) {
            return;
        }
        action->unk_96.unk_00_u16 = 0x80;
        action->unk_9B = action->unk_9B + 1;
        return;
    case 3:
    {
        s32 sound_kind;
        u32 entity_flags;
        u32 sound_x;
        u32 sound_y;
        u16 next_brightness;
        u8 brightness;

        entity->unk_1C |= 0x10000000;
        brightness = action->unk_96.unk_00_u8;
        sprite->unk_0E = brightness;
        sprite->unk_0D = brightness;
        sprite->unk_0C = brightness;
        next_brightness = action->unk_96.unk_00_u16 - 0x10;
        action->unk_96.unk_00_u16 = next_brightness;
        if ((s16)next_brightness >= 0x10) {
            return;
        }

        if ((g_dungeon_status.pending_display_owner) == (u8 *)entity - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);

        entity_flags = entity->unk_1C;
        sound_x = sprite->unk_24;
        sound_y = sprite->unk_25;
        sound_kind = 0x3000;
        if (entity_flags & 0x2000) {
            sound_kind = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_kind);
        unlink_entity_node(entity);
        *(u16 *)((u8 *)entity - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
        break;
    }
}
#include "dungeon/monster/univern.h"

/* Runs the shared hop and shrink sequence for the actor with the supplied callback arguments. */
void shrink_hopping_univern(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}
#include "dungeon/monster/univern.h"

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_univern_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}
#include "dungeon/monster/univern.h"

/*
 * Runs update_actor_hop_and_grow and installs update_entity_movement_and_ground_height when it
 * returns nonzero.
 */
void finish_actor_hop_and_grow_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
#include "dungeon/monster/univern.h"

/* Animates status entry and recovery, updates status timers and activity counts, then restores movement. */
void update_sleeping_univern(ActorRecord *actor_arg, ObjectPosition *motion_arg, SpriteFrameState *sprite_arg, ActorRecord *entity_arg) {
    void *actor = actor_arg;
    void *motion = motion_arg;
    SpriteFrameState *sprite= sprite_arg;
    void *entity = entity_arg;
    DungeonGlobalStatus *global_state;
    u8 *anim_table;
    u32 clear_mask;
    u32 entity_flags;
    u8 state;

    state = ((R17_801738E0_S_801738E0_0 *)actor)->phase;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_90 = 0;
            (sprite->frameTable) = ((u8 *)univern_alt_spawn_direction_frames);
            select_sprite_entry(
                sprite,(u8)(((u8 *)univern_alt_spawn_direction_frames)[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((R17_801738E0_S_801738E0_0 *)actor)->phase = 2;
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xFFFBFFFF;
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        {
            s32 initial_speed = 0xFFF80000;
            anim_table = ((u8 *)univern_frame_set_2);
            ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = initial_speed;
        }
        (sprite->frameTable) = anim_table;
        select_sprite_entry(
            sprite,(u8)(*(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7)
                    + (u32)anim_table)),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->phase++;
        return;

    case 1:
        if (((R17_801738E0_S_801738E0_3 *)motion)->unk_14 <= 0xFFFFF) {
            ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 += 0x20000;
        }
        if (((R17_801738E0_S_801738E0_0 *)actor)->unk_90 < 0) {
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_90 = 0;
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0;
        (sprite->frameTable) = ((u8 *)univern_alt_spawn_direction_frames);
        select_sprite_entry(
            sprite,(u8)(((u8 *)univern_alt_spawn_direction_frames)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        update_actor_status_and_mp(entity);

        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->phase = 2;
        return;

    case 2:
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= ACTOR_GROUNDED;
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) == 0) {
            (sprite->frameTable) = ((u8 *)univern_frame_set_2);
            select_sprite_entry(
                sprite,(u8)(((u8 *)univern_frame_set_2)[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
            ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
            if (sprite->flags & 0x8000) {
                clear_mask = ~0x200U;
                break;
            }
            {
                register struct R17_801738E0_GlobalStruct *globals;
                globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
                entity_flags = globals->counter + 1;
                globals->counter = entity_flags;
            }
            ((R17_801738E0_S_801738E0_0 *)actor)->phase++;
            return;
        } else {
            global_state = &g_dungeon_status;
        }

        if (global_state->flags & 0x1000) {
            return;
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, motion, sprite, 0) != 0) {
                return;
            }
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(actor, motion, sprite, entity);
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, motion, sprite, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor, motion, sprite, entity);
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_A8 = 0;
            update_univern_parent_motion(actor, motion, sprite, entity);
            return;
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(
                     entity, (u8 *)primary_actor_record->previous_actor_header + 0x20)
                 << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) != 0) {
            TileObject *origin = &reference_tile_object;
            s8 coordinate = *(s8 *)&sprite->room_index;

            if ((((coordinate == origin->room_index) && (coordinate >= 0)) ||
                 (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                ((generate_random_value() & 7) == 0)) {
                clear_slots_of_type(entity, STATUS_SLEEP);
            }
        }
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) != 0) {
            return;
        }

        (sprite->frameTable) = ((u8 *)univern_frame_set_2);
        select_sprite_entry(
            sprite,(u8)(((u8 *)univern_frame_set_2)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
        if (sprite->flags & 0x8000) {
            clear_mask = ~0x200U;
            break;
        }
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter++;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->phase++;
        return;

    case 3:
        if (!(sprite->flags & 0xE000)) {
            return;
        } else {
            (sprite->frameTable) = ((u8 *)univern_frame_set_1);
        }

        select_sprite_entry(
            sprite,(u8)(((u8 *)univern_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);

advance_state:
        ((R17_801738E0_S_801738E0_0 *)actor)->phase++;
        return;

    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0xFFF80000;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_A8 = 8;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xBFFF;
        (sprite->frameTable) = ((u8 *)univern_alt_direction_frames);
        select_sprite_entry(
            sprite,(u8)(((u8 *)univern_alt_direction_frames)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((R17_801738E0_S_801738E0_0 *)actor)->phase = 0x10;
        return;

    case 16:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= ACTOR_GROUNDED;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 0x4000;
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0;
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= ~ACTOR_ASLEEP;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    default:
        return;
    }

    ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = clear_mask & entity_flags;
    ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);

    return;
}
#include "dungeon/monster/univern.h"

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void advance_univern_status_action(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    ObjectPosition *saved_context;
    register DungeonGlobalStatus *dungeon_state;
    ActorRecord *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = action->action_phase.u;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        R17_80173F10_S_80173ED8_2 *counter_state;

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (R17_80173F10_S_80173ED8_2 *)&g_dungeon_status.turn_scale;
        counter_state->unk_0A--;
        (sprite->frameTable) = ((u8 *)univern_frame_set_2);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)univern_frame_set_2)[direction & 7]), 0);
        action->action_phase.u++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            (sprite->frameTable) = ((u8 *)univern_frame_set_1);
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite,(u8)(((u8 *)univern_frame_set_1)[direction & 7]), 0);
            (*(u32 *)&entity->flags1C) |= 0x40000;
            counter_state = (u8 *)&g_dungeon_status.turn_scale;
            ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A++;
            action->action_phase.u++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (dungeon_state->flags & 0x1000) {
            return;
        }

        if ((entity->hp_delta != 0) &&
            begin_ready_actor_directional_action(action, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_A8 = 0;
            update_univern_parent_motion(action, context, sprite, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            void *owner = primary_actor_record;

            if ((check_entity_relation(entity,
                    (u8 *)((R17_80173F10_S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (sprite->frameTable) = ((u8 *)univern_frame_set_1);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)univern_frame_set_1)[direction & 7]), 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_0A++;

        action->action_phase.u++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.turn_scale;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~(ACTOR_MP_EMPTY | ACTOR_ASLEEP);
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    }

    default:
        return;
    }
}
#include "dungeon/monster/univern.h"

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_univern_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object) {
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C.handler = ((u8 *)update_entity_movement_and_ground_height);
            return;
        }
    } else if (*(u8 **)&entity->frameTable == ((u8 *)univern_alt_spawn_direction_frames) &&
               !(map_object->flags1C & 0x208)) {
        entity->frameTable = ((u8 *)univern_direction_frames);
        select_sprite_entry(entity,(s16)(((u8 *)univern_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->facing + 0x100) >> 9) & 7]),(s16)(0));
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs update_thrown_actor_travel and installs update_entity_movement_and_ground_height only when
 * it succeeds and the signed floor-trap check returns positive.
 */
void update_timed_effect_and_expire(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic) {
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->unk_8C.handler = update_entity_movement_and_ground_height;
        }
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs interpolate_actor_to_terrain_tile and installs update_entity_movement_and_ground_height
 * when it returns nonzero.
 */
void finish_actor_terrain_interpolation_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs update_spinning_actor_fall and installs update_entity_movement_and_ground_height when it
 * returns nonzero.
 */
void finish_spinning_actor_fall_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs update_actor_fade_in and installs update_entity_movement_and_ground_height when it returns
 * nonzero.
 */
void update_effect_trajectory_and_sprite(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
#include "dungeon/monster/univern.h"

/*
 * Runs resolve_actor_floor_trap_once and installs update_entity_movement_and_ground_height when it
 * returns positive.
 */
void blend_animation_palette_and_complete(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
#include "dungeon/monster/univern.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/tile_object.h"

/*
 * Runs propagate_actor_action_flag and installs update_entity_movement_and_ground_height when it
 * returns positive.
 */
void finish_actor_action_flag_propagation_then_resume_ground_movement(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor) {
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->unk_8C.handler = update_entity_movement_and_ground_height;
    }
}
