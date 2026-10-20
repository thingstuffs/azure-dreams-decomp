#include "modules/dungeon_resource17_slot0.h"
void * (*const resource17_slot0_entry0)(s32 kind, s32 tile_x, s32 tile_y, s32 copy_value) = func_8017089C;
void (*const resource17_slot0_entry1)(void *actor, void *motion, void *object) = create_anchored_directional_object;
#include "modules/dungeon_resource17_slot0.h"
#include "shared/sprite_frame_state.h"

void *func_8017089C(s32 kind, s32 tile_x, s32 tile_y, s32 copy_value)
{
    void *root;
    void *copy;
    s32 outer_index;
    s32 saved_kind;
    s32 saved_copy_value;
    s16 saved_tile_y;
    u16 saved_tile_x;
    void *object;
    void *outer;
    void *stable_object;
    s32 kind_copy;
    SpriteFrameState *part;
    void *allocated;
    s32 allocation_size;
    ObjectNodeHeader *allocation_pool;

    saved_kind = kind;
    object = 0;
    allocation_size = 0x112;
    saved_tile_x = tile_x;
    allocation_pool = &D_80083498;

    saved_copy_value = copy_value;
    saved_tile_y = tile_y;
    allocated = allocate_list_node(allocation_size, allocation_pool);
    kind_copy = saved_kind;
    root = allocated;
    if (allocated != 0) {
        {
            void *init_root;
            void *setup;

            object = (u8 *)allocated + 0x20;
            init_root = allocated;
            setup = project_sprite_chain;
            ((R17_8017089C_S_8017089C_0 *)init_root)->unk_10 = ((u8 *)create_anchored_directional_object);
            ((R17_8017089C_S_8017089C_1 *)object)->unk_13 = 17;
            register_node(init_root, setup);
        }

        {
            void *part_callback;

            part_callback = ((u8 *)D_80174494);
            copy = ((R17_8017089C_S_8017089C_2 *)root)->unk_08.at00.v;
            ((R17_8017089C_S_8017089C_2 *)copy)->unk_08.at02.v = saved_copy_value;
            stable_object = object;
            part = ((R17_8017089C_S_8017089C_2 *)root)->unk_0C;
            part->frameTable = part_callback;
        }
        part->unk_24 = saved_tile_x;
        part->unk_25 = saved_tile_y;

        {
            s32 object_flags;
            s32 state_flags;

            if ((saved_kind & 3) == 1) {
                object_flags = ((R17_8017089C_S_8017089C_1 *)object)->unk_14 | 0x6000;
                state_flags = ((R17_8017089C_S_8017089C_1 *)object)->unk_1C | 0x6000;
                ((R17_8017089C_S_8017089C_1 *)object)->unk_14 = object_flags;
                ((R17_8017089C_S_8017089C_1 *)object)->unk_1C = state_flags;
            } else if ((saved_kind & 3) >= 2) {
                object_flags = ((R17_8017089C_S_8017089C_1 *)object)->unk_14 | 0x2000;
                state_flags = ((R17_8017089C_S_8017089C_1 *)object)->unk_1C | 0x2000;
                ((R17_8017089C_S_8017089C_1 *)object)->unk_14 = object_flags;
                ((R17_8017089C_S_8017089C_1 *)object)->unk_1C = state_flags;
            } else {
                object_flags = saved_kind & ~3;
                if ((s16)object_flags == 0) {
                    if ((((R17_8017089C_S_8017089C_1 *)object)->unk_14 & 0x200) == 0) {
                        if (generate_random_value() & 1) {
                            ((R17_8017089C_S_8017089C_1 *)object)->unk_1C |= 0x200;
                            set_or_clear_actor_status_slot(object, 1,
                                (generate_random_value() & 0x3F) | 0x20);
                            part->frameTable = ((u8 *)D_801744FC);
                        }
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(root, copy, part,(s16)((s16)kind_copy));

        outer = stable_object;
        outer_index = 0;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_9A = 0xFF;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_9C = -1;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        ((R17_8017089C_S_8017089C_1 *)object)->unk_1C |= 0x40000;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_92 = -48;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_A8 = 0;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_9E = 1;
        ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_98 |= 0x4000;

        do {

            saved_copy_value = (s32)allocate_list_node(0x112, ((u8 *)(&D_80083498)));
            allocated = (void *)saved_copy_value;
            ((R17_8017089C_S_8017089C_5 *)outer)->unk_A4 = allocated;
            if (allocated != 0) {
                s32 item_offset;
                s32 item_index;
                register void *outer_base;
                u8 *table;
                s32 more_items;

                saved_kind = (s32)((u8 *)allocated + 0x20);
                ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_02 = 1;
                item_index = 0;
                outer_base = outer;
                table = ((u8 *)D_801744E4);
                item_offset = 8;
                do {
                    void *item;
                    s32 direction_index;
                    s32 part_value;
                    s32 call_zero;
                    void *outer_child;

                    item = (u8 *)(void *)saved_kind + item_offset;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_04 |= 0x8000;
                    part_value = part->unk_28;
                    ((R17_8017089C_S_8017089C_7 *)item)->unk_10 = 0x20;
                    ((R17_8017089C_S_8017089C_7 *)item)->unk_0C = 0x00808080;
                    ((R17_8017089C_S_8017089C_7 *)item)->unk_28 = part_value;
                    outer_child = ((R17_8017089C_S_8017089C_8 *)outer_base)->unk_A4;
                    call_zero = 0;
                    ((R17_8017089C_S_8017089C_9 *)outer_child)->unk_10 = ((u8 *)D_800D78C0);
                    (*(void * *)((u8 *)item + 0x2C)) = table;
                    direction_index = (((*(s16 *)D_80083228) +
                        ((R17_8017089C_S_8017089C_1 *)object)->unk_2A + 0x100) >> 9) & 7;
                    select_sprite_entry(item,
                        *(u8 *)((R17_8017089C_uptr)direction_index + (R17_8017089C_uptr)table), call_zero);
                    item_offset += 0x30;
                    item_index++;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_06 = 1;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part, ((u8 *)D_800D71A8), 1);
                    more_items = item_index < ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_02;
                    ((R17_8017089C_S_8017089C_6 *)(void *)saved_kind)->unk_98 = (u8 *)root + 0x1E;
                } while (more_items);
            }
            outer = (u8 *)outer + 4;
            {
                s32 child_count;

                child_count = ((R17_8017089C_S_8017089C_4 *)stable_object)->unk_9E;
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
#include "modules/dungeon_resource17_slot0.h"

void create_anchored_directional_object(void *actor, void *motion, void *object)
{
    u16 initial_flags = g_dungeon_status.flags;
    s32 bob = 0;
    void *actor_state = actor;
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
    status_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14;

    if (!(status_flags & 0x8000)) {
        {
            ground_offset = (g_game_work.view.camera_rotation.parts.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100) >> 9;
            direction = ground_offset & 7;
        }
        if ((*(s16 *)((u8 *)actor + (0x94))) != direction) {
            select_indirect_table_entry(object, ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C[direction],
                          ((R17_80170BB8_S_80170BB8_1 *)object)->unk_04);
            (*(s16 *)((u8 *)actor + (0x94))) = direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[direction] != 0) {
                flip_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 | 1;
            } else {
                flip_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0xFFFE;
            }
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = flip_flags;
        }
        if ((*(u8 *)((u8 *)actor + (0x9A))) != 8) {
            apply_monster_koyaw_data(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.s, (u8 *)object + 0xC);
        }

        if (!(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0x20)) {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                func_800478B8(object);
            }
        } else {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 |= 0x7000;
            ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF));
        if (((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF)) & 0x40000) {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C;
                    if (animation_table == ((u8 *)D_8017449C)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_80174494);
                        select_sprite_entry(object,
                            ((u8 *)D_80174494)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_80170BB8_S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                    else if (animation_table == ((u8 *)D_80174494)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_8017449C);
                        select_sprite_entry(object,
                            ((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_80170BB8_S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                }
                if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C == ((u8 *)D_80174494)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u);
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
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
                }
            }
        }
    } else {
        if (!(status_flags & 0x800)) {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = status_flags | 0x7000;
        } else {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = status_flags & 0x8FFF;
        }
        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF));

        if (!(((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF)) & 0x40000)) {
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(s16 *)((u8 *)actor + (0x92))) -= bob;
            bob = 0;
            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground_offset = ((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C;
                    if (animation_table == ((u8 *)D_8017449C)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_80174494);
                        select_sprite_entry(object,
                            ((u8 *)D_80174494)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    } else if (animation_table == ((u8 *)D_80174494)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_8017449C);
                        select_sprite_entry(object,
                            ((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    }
                }
                if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C == ((u8 *)D_80174494)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u);
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

    if (((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0x40000000) {
        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xBFFFFFFF;
        ground = ((s16)sample_terrain_surface_height((((R17_80170BB8_S_80170BB8_1 *)object)->unk_24 << 6) | 0x20,
            (((R17_80170BB8_S_80170BB8_1 *)object)->unk_25 << 6) | 0x20,
            (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)actor + (0x92))) += ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - ground;
            ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u = ground;
        }
    }
    height = ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u +
        (u16)(*(s16 *)((u8 *)actor + (0x92)));
    height += bob;
    *(s16 *)((u8 *)motion + 0xA) = height;
    ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 |= 0x40;
}
#include "modules/dungeon_resource17_slot0.h"

void update_entity_movement_and_ground_height(void *actor, void *context, void *sprite, EntityRec *status)
{
    s32 distance;
    u32 flags;
    s32 action_index;
    s8 tile_index;
    u16 action_flags;
    void *resume_handler;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        advance_entity_along_path_2(actor, context, sprite, status);
        return;
    }

    if (status->tileY == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C == ((u8 *)D_801744FC)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744EC)[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7]),
            0);
        return;
    }

    if (((u32)status->flags1C) & 0x200) {
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C == ((u8 *)D_801744FC)) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 2;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            status->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, ((u8 *)D_801744EC)) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((u32)status->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 14) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        }

        if ((((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C != ((u8 *)D_80174494)) &&
            (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C != ((u8 *)D_8017449C))) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017449C);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + status->facing + 0x100) >> 9) & 7]),
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A8);
        }

        status->flags1C |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF7;

        if (status->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, ((u8 *)D_801744A4)) != 0) {
                return;
            }
        }

        if (((u32)status->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80174250(actor, context, sprite, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }

    tile_index = ((s8)find_active_rect_containing_point((u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v)));
    ((R17_801713A8_S_801713A8_2 *)sprite)->unk_26 = tile_index;

    if (status->unk_6D > 0) {
        if (((u32)status->flags1C) & 0x20) {
            update_actor_status_and_food(status);
            return;
        }
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_80171A98(actor, context, sprite, status);
            return;
        }
        action_flags = status->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        status, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801724C4(actor, context, sprite, 0) == 0) {
                return;
            }
            action_flags = status->unk_46 | 0x4000;
            status->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_80171A98(actor, context, sprite, status);
                return;
            }
        }

        action_index = (status->unk_46 & 0x3FFF) - 1;
        switch (action_index) {

        case 7:
        case 8:
            if ((s16)func_801721E0(actor, context, sprite, status) != 0) {
                return;
            }
            func_801723A4(actor, context, sprite, status);
            return;

        case 4:
        case 5:
        case 6:
        {
            s16 target_angle;
            EntityRec *active_actor;

            target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y), &distance));
            active_actor = D_800814A8;
            status->facing = target_angle;
            if (active_actor->unk_9A != 0x11) {
                update_actor_status_and_food(status);
                return;
            }
        }
            resume_handler = (void *)update_entity_movement_and_ground_height;
            begin_actor_spell_action(actor, context, sprite, ((u8 *)D_801744D4), resume_handler);
            return;

        case 11:
            update_actor_status_and_food(status);
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
            func_80171A98(actor, context, sprite, status);
            return;
        }
    }

    flags = ((u32)status->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    if ((s16)compare_monster_neighbor_values((u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(u8)(D_80082E80.tile_position.parts.tile_x),(u8)(D_80082E80.tile_position.parts.tile_y)) == 0) {
        return;
    }
    status->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y), &distance));
}
#include "modules/dungeon_resource17_slot0.h"

void advance_entity_along_path_2(void *motion, s32 unused, void *entity, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;

    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.u <= ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = ((SpriteTableView *)entity)->unk_2C;
    if (direction_table != ((u8 *)D_80174494) && direction_table != ((u8 *)D_8017449C)) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = ((u8 *)D_8017449C);
        select_sprite_entry(
            entity,
            ((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)motion)->unk_A8 = 0;
    }

    old_x = ((SpriteTableView *)entity)->unk_24;
    old_y = ((SpriteTableView *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

    ((SpriteTableView *)entity)->unk_24 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s))->unk_74;
    ((SpriteTableView *)entity)->unk_25 =
        ((ActorStatusBytesView *)((u8 *)path_state + ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.s))->unk_7C;
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_8A.u++;

    new_x = ((SpriteTableView *)entity)->unk_24;
    new_y = ((SpriteTableView *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, occupancy_mask);

    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag(
        old_x, old_y, ((SpriteTableView *)entity)->unk_24, ((SpriteTableView *)entity)->unk_25,
        (u8 *)motion + 0x98));
    ((R17_801718D0_S_801718D0_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 0;
        return;
    }

    ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 8;
    {
        s32 step_count = ((R17_801718D0_S_801718D0_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_800A9E70_arg0 *)motion)->unk_96.as_u16 = 8 / step_count;
        }
    }
}
#include "modules/dungeon_resource17_slot0.h"

void func_80171A98(void *move_data, void *context, void *position_data, void *actor_data)
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

    if ((dungeon_flags & 0x4000) || ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)func_801721E0(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_food(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_valid_monster_neighbor(actor_data,(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v));
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R17_80171A98_S_80171C34_7 *)(((R17_80171A98_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R17_80171A98_S_80171C34_7 *)(((R17_80171A98_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (place_actor_at_directional_neighbor(actor_data,(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &D_80082E80;
                    s32 target_facing = ((u16)D_800814A8->facing);
                    s32 offset_index =
                        ((((R17_80171A98_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v == (u16)target_x &&
                    ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v == (u16)target_y) {
                    ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_directional_move_and_terrain((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)compare_monster_neighbor_values(
                        ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                rebuild_monster_reachable_tiles(position_data, ((R17_80171A98_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((R17_80171A98_S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((R17_80171A98_DungeonRecord *)D_800E2970)[((R17_80171A98_S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        rebuild_monster_reachable_tiles(position_data, ((R17_80171A98_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)place_actor_at_directional_neighbor(actor_data,(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R17_80171A98_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)compare_monster_neighbor_values(
                    ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(D_800814A8, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            rebuild_monster_reachable_tiles(position_data, ((R17_80171A98_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)D_8006CD00);

    do {
        turn_flags = ((R17_80171A98_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_directional_move_and_terrain((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_data + (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v;
            ((ActorStatusBytesView *)((u8 *)actor_data + (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v;
            ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v += *x_step;
                ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v),(u16)((((R17_80171A98_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tile_position.parts.tile_x) != ((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00u.v) {
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
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_food(actor_data);
        return;
    }

    {
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R17_80171A98_S_80171C34_5 *)move_data)->unk_9C.u = ((R17_80171A98_S_80171C34_2 *)position_data)->unk_26.u;
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R17_80171A98_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at00.v << 6) | 0x20,
        (((R17_80171A98_S_80171C34_2 *)position_data)->unk_24.at01.v << 6) | 0x20,(s16)((s16)(((R17_80171A98_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R17_80171A98_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}
#include "modules/dungeon_resource17_slot0.h"

s32 func_801721E0(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->unk_71;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = place_actor_at_directional_neighbor(actor, ((SpriteTableView *)sprite_arg)->unk_24,
                           ((SpriteTableView *)sprite_arg)->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        ((SpriteTableView *)sprite_arg)->unk_2C = ((u8 *)D_80174494);
        select_sprite_entry(sprite_arg, (((u8 *)D_80174494))[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D--;
        prepare_directional_attack(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
#include "modules/dungeon_resource17_slot0.h"

void func_801723A4(Rec_func_800A9E70_arg0 *action_state, void *context, Rec_D_80082E80 *animation,
    EntityRec *entity) {
    entity->unk_71 = (s8) (entity->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            select_sprite_entry(animation, *(animation->unk_2C.as_pu8 + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            prepare_directional_attack(entity, animation, entity->facing, 1, 0);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
#include "modules/dungeon_resource17_slot0.h"

s32 func_801724C4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        func_80171A98(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R17_801724C4_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        func_80171A98(entity, primary_context_arg, secondary_context_arg, entity);
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
#include "modules/dungeon_resource17_slot0.h"

void finish_actor_tile_move_then_resume_ground_movement(void *state, s32 unused, s32 source, s32 target) {
    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(target, 4);
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
#include "modules/dungeon_resource17_slot0.h"

void finish_linked_actor_motion_and_floor_trap_then_resume_ground_movement(Resource17CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_entity_movement_and_ground_height;
        }
    }
}
#include "modules/dungeon_resource17_slot0.h"

void update_staged_movement_and_direction(void *action, void *motion, void *sprite, void *actor)
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
        flags = F16(sprite, 0x14);
        turn_actor = actor;
        if (flags & 0x8000) {
            F8(action, 0x9B) = 0xFF;
            F16(sprite, 0x14) |= 0x6000;
            resolve_attack_damage_and_effects(turn_actor, sprite,(s16)(FS16(turn_actor, 0x2A)),(s16)(1));
            return;
        }
        if (!(flags & 0xE000))
            return;
        FPTR(sprite, 0x2C) = ((u8 *)D_801744B4);
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
            FPTR(sprite, 0x2C) = ((u8 *)D_801744BC);
            select_sprite_entry(sprite, ((u8 *)D_801744BC)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        if (FS16(action, 0x96) > 0)
            return;
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        F16(action, 0x96) = phase_ticks;
        F32(motion, 0xC) = (step_x << 18) + (step_x << 17);
        F32(motion, 0x10) = (step_y << 18) + (step_y << 17);
        FPTR(sprite, 0x2C) = ((u8 *)D_801744C4);
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
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        FPTR(sprite, 0x2C) = ((u8 *)D_801744CC);
        select_sprite_entry(sprite, ((u8 *)D_801744CC)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F32(motion, 0x14) = 0;
        F32(action, 0x90) = 0;
        F16(action, 0x98) &= 0xFFF7;
        F32(actor, 0x1C) |= 0x08000000;
        F8(action, 0x9B) = 0xFF;
        return;

    case 0xFF:
        target = F8(sprite, 0x24) << 6;
        current = FS16(motion, 2);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0xC) = target;
        target = F8(sprite, 0x25) << 6;
        current = FS16(motion, 6);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0x10) = target;
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        F32(motion, 0x10) = 0;
        F32(motion, 0xC) = 0;
        F32(actor, 0x1C) |= 0x40000;
        set_record_integer_tile_center(motion, F8(sprite, 0x24), F8(sprite, 0x25));
        reduce_actor_food_meter(actor, 0x100);
        FPTR(action, 0x8C) = ((u8 *)update_entity_movement_and_ground_height);
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        FPTR(sprite, 0x2C) = ((u8 *)D_8017449C);
        select_sprite_entry(sprite, ((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        if (FS8(actor, 0x6D) == 0) {
            F16(actor, 0x46) &= 0x7FFF;
            return;
        }
        (*(void * *)D_800E3DE8) = (u8 *)actor - 0x20;

        return;
    default:
        return;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void update_entity_item_action_and_idle_return(R17_80172C18_State *state, R17_80172C18_Position *pos, R17_80172C18_Actor *actor, R17_80172C18_Entity *ent)
{
    u8 *item_slot;
    s32 state_index;
    s16 use_main_link;
    u8 *actor_parts;
    R17_80172C18_SubActor *sub_actor;
    R17_80172C18_ActorBase *actor_base;

    use_main_link = 0;
    state_index = state->state9B;
    actor_parts = state->fA4;
    sub_actor = (R17_80172C18_SubActor *)(actor_parts + 0x20);
    actor_base = (R17_80172C18_ActorBase *)(actor_parts + 0x28);

    switch (state_index) {
    case 0:
        if (ent->flags1C & 0x2000) {
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
                link_base = (u8 *)((R17_80172C18_MainObj *)D_800814A8);
                ent->f60 = link_base;
                linked_actor = *(u8 **)(link_base - 0x14);
                ent->f72 = linked_actor[0x24];
                ent->f73 = linked_actor[0x25];
            } else if (D_8006DE24[*item_slot].kind == 2) {
                link_base = ent->f60;
                if (link_base != 0) {
                    linked_actor = *(u8 **)(link_base - 0x14);
                    ent->f72 = linked_actor[0x24];
                    ent->f73 = linked_actor[0x25];
                }
            } else {
                s32 offset_y;
                s32 offset_x;

                ent->f60 = scan_monster_along_heading(
                    ent,(u8)(actor->f24),(u8)(actor->f25),(s16)(ent->f2A), 0x10);
                offset_x = __builtin_abs(ent->f72);
                offset_y = __builtin_abs(ent->f73);
                ent->f72 = offset_x;
                ent->f73 = offset_y;
            }

            sub_actor->flags4 &= 0x7FFF;
            actor_base->f2C = (void (*)(void))((u8 *)D_801744E4);
            select_sprite_entry(
                actor_base,
                ((u8 *)D_801744E4)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                0);
            if (!create_actor_spell_effect(ent, item_slot, use_main_link, &state->flags98)) {
                return;
            }
            actor->flags14 &= 0xF7FF;
            create_source_positioned_object(pos, 5);
            play_sound_if_enabled(0x703);
            state->state9B++;
            state->flags98 |= 8;
            ent->flags1C &= 0xF7FFFFFF;
            ent->flags1C &= 0xFFFBFFFF;
            return;
        }

        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->f24),(u8)(actor->f25));
        {
            R17_80172C18_MainObj *main_obj;

            main_obj = ((R17_80172C18_MainObj *)D_800814A8);
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
        if (actor->flags14 & 0xE000) {
            actor->f2C = (void (*)(void))((u8 *)D_801744DC);
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
            actor->flags14 |= 0x800;
            return;
        }
        actor->flags14 &= 0xF7FF;
        state->state9B++;


    case 3:
        state->u90.h.half92 +=
            (-0x30 - (s16)state->u90.h.half92) >> 3;
        state->f96--;
        if ((s16)state->f96 <= 0 || (actor->flags14 & 0xE000)) {
            state->flags98 |= 0x80;
        }
        if ((!(state->flags98 & 0x4000) && state->fA8 == 2) || (actor->flags14 & 0x8000)) {
            state->flags98 |= 0x4000;
        }
        if (!(actor->flags14 & 0xE000)) {
            return;
        }

        sub_actor->flags4 |= 0x8000;
        pos->f14 = 0;
        pos->f10 = 0;
        pos->fC = 0;
        set_record_integer_tile_center(pos,(u8)(actor->f24),(u8)(actor->f25));
        state->flags98 &= 0xFFF7;
        ent->flags1C |= 0x08000000;
        ent->flags1C |= 0x00040000;

        if (actor->f2C != (void (*)(void))((u8 *)D_80174494) &&
            actor->f2C != (void (*)(void))((u8 *)D_8017449C)) {
            state->fA8 = 0;
            state->flags98 &= 0xBFFF;
            actor->f2C = (void (*)(void))((u8 *)D_80174494);
            select_sprite_entry(
                actor,
                ((u8 *)D_80174494)[((g_game_work.view.camera_rotation.parts.viewAngle + ent->f2A + 0x100) >> 9) & 7],
                state->fA8);
        }
        {

            if (((u32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            if (!(state->flags98 & 0x4000)) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags14 &= 0xF7FF;
        state->f8C = (void (*)(void))((u8 *)update_entity_movement_and_ground_height);
        advance_status_timers(ent);
        if (ent->f6D > 0) {
            ent->f6D--;
        }
        ent->f73 = 0;
        ent->f72 = 0;
        ent->f46 &= 0x7FFF;
        play_sound_if_enabled(0xB4);

        return;
    default:
        return;
    }
}
#include "modules/dungeon_resource17_slot0.h"
#include "shared/sprite_frame_state.h"

void func_80173244(void *action, void *motion, void *sprite, void *actor)
{
    s16 flight_timer;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;

    direction = (((EntityRec *)actor)->unk_6A >> 9) & 7;

    switch (((R17_80173244_S_80173354_1 *)action)->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_801744AC));
            return;
        }

        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R17_80173244_S_80173354_1 *)action)->unk_96.s = 0;
            ((R17_80173244_S_80173354_1 *)action)->unk_9B = 2;
            return;
        }

        ((EntityRec *)motion)->unk_0C = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        ((EntityRec *)motion)->unk_10 = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((EntityRec *)motion)->flags14 = 0x40000;
        ((R17_80173244_S_80173354_1 *)action)->unk_98 |= 8;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((EntityRec *)actor)->flags1C &= 0xFFFBFFFF;
        ((R17_80173244_S_80173354_1 *)action)->unk_9B++;

        flight_timer = -1;
        if (((u32)((EntityRec *)actor)->flags1C) & 0x228) {
            flight_timer = 8;
        }
        ((R17_80173244_S_80173354_1 *)action)->unk_96.s = flight_timer;

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

        if (((R17_80173244_S_80173354_1 *)action)->unk_96.s > 0) {
            ((R17_80173244_S_80173354_1 *)action)->unk_96.u--;
        } else if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((R17_80173244_S_80173354_1 *)action)->unk_96.s = 0;
        }
        if (((R17_80173244_S_80173354_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((R17_80173244_S_80173354_1 *)action)->unk_9B = 0;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            begin_actor_display_action(action, motion, sprite, ((u8 *)D_801744AC));
            return;
        }
        ((R17_80173244_S_80173354_1 *)action)->unk_96.s = 8;
        ((R17_80173244_S_80173354_1 *)action)->unk_9B++;
        return;

    case 2:
        ((EntityRec *)motion)->flags14 = 0xFFFE0000;
        if (((R17_80173244_S_80173354_1 *)action)->unk_96.s != 0) {
            s32 tile_delta;
            s32 position;

            tile_delta = ((SpriteFrameState *)sprite)->unk_24 << 6;
            position = ((EntityRec *)motion)->x.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_0C = tile_delta >> 1;
            tile_delta = ((SpriteFrameState *)sprite)->unk_25 << 6;
            position = ((EntityRec *)motion)->y.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_10 = tile_delta >> 1;
            ((EntityRec *)motion)->unk_0C += ((EntityRec *)motion)->unk_0C >> 1;
            ((EntityRec *)motion)->unk_10 += ((EntityRec *)motion)->unk_10 >> 1;
        }

        {
            s16 landing_timer = (u16)((R17_80173244_S_80173354_1 *)action)->unk_96.s - 1;

            ((R17_80173244_S_80173354_1 *)action)->unk_96.s = landing_timer;
            if (landing_timer > 0) {
                return;
            }
        }

        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25);

        ((R17_80173244_S_80173354_1 *)action)->unk_90 = 0;
        ((R17_80173244_S_80173354_1 *)action)->unk_98 &= 0xFFF7;
        ((EntityRec *)actor)->flags1C |= 0x08000000;
        ((EntityRec *)actor)->flags1C |= 0x00040000;
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_8017449C);
        select_sprite_entry(sprite,(u8)(((u8 *)D_8017449C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7]),
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
#include "modules/dungeon_resource17_slot0.h"

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
        *(s32 *)((u8 *)motion + 0xC) = offset_x << 16;
        *(s32 *)((u8 *)motion + 0x10) = offset_y << 16;
        *(s32 *)((u8 *)motion + 0x14) = 0x8000;
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

        if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)entity - 0x20)) {
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
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
        break;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void func_80173868(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}
#include "modules/dungeon_resource17_slot0.h"

void func_80173888(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}
#include "modules/dungeon_resource17_slot0.h"

void finish_actor_hop_and_grow_then_resume_ground_movement(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void func_801738E0(void *actor_arg, void *motion_arg, void *sprite_arg, void *entity_arg)
{
    void *actor = actor_arg;
    void *motion = motion_arg;
    SpriteStatusIndexView *sprite = sprite_arg;
    void *entity = entity_arg;
    DungeonGlobalStatus *global_state;
    u8 *anim_table;
    u32 clear_mask;
    u32 entity_flags;
    u8 state;

    state = ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (sprite->unk_14 & 0x8000) {
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_90 = 0;
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744FC);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_801744FC)[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 2;
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xFFFBFFFF;
        if (!(sprite->unk_14 & 0x6000)) {
            return;
        }
        {
            s32 initial_speed = 0xFFF80000;
            anim_table = ((u8 *)D_801744F4);
            ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = initial_speed;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        select_sprite_entry(
            sprite,(u8)(*(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7)
                    + (u32)anim_table)),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
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
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744FC);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744FC)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        update_actor_status_and_food(entity);

        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 2;
        return;

    case 2:
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        if ((get_entity_effect_value(entity, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
            select_sprite_entry(
                sprite,(u8)(((u8 *)D_801744F4)[
                    ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
                0);
            entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
            ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
            if (sprite->unk_14 & 0x8000) {
                clear_mask = ~0x200U;
                break;
            }
            {
                register struct R17_801738E0_GlobalStruct *globals;
                globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
                entity_flags = globals->counter + 1;
                globals->counter = entity_flags;
            }
            ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
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
            func_80174250(actor, motion, sprite, entity);
            return;
        }
        if (((R17_801738E0_S_801738E0_2 *)entity)->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(
                     entity, (u8 *)D_800814A8->unk_58 + 0x20)
                 << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            TileObject *origin = &D_80082E80;
            s8 coordinate = sprite->unk_26;

            if ((((coordinate == origin->room_index) && (coordinate >= 0)) ||
                 (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                ((generate_random_value() & 7) == 0)) {
                clear_slots_of_type(entity, 1);
            }
        }
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744F4)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        entity_flags = ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C | 0x40000;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = entity_flags;
        if (sprite->unk_14 & 0x8000) {
            clear_mask = ~0x200U;
            break;
        }
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter++;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 3:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        } else {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        }

        select_sprite_entry(
            sprite,(u8)(((u8 *)D_801744EC)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);

advance_state:
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B++;
        return;

    case 4:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0xFFF80000;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_A8 = 8;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xBFFF;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017449C);
        select_sprite_entry(
            sprite,(u8)(((u8 *)D_8017449C)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + ((R17_801738E0_S_801738E0_2 *)entity)->unk_2A + 0x100) >> 9) & 7]),
            0);
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 8;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= 0xF7FFFFFF;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_9B = 0x10;
        return;

    case 16:
        if (!(sprite->unk_14 & 0xE000)) {
            return;
        }
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 &= 0xFFF7;
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C |= 0x08000000;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_98 |= 0x4000;
        ((R17_801738E0_S_801738E0_3 *)motion)->unk_14 = 0;
        {
            struct R17_801738E0_GlobalStruct *globals = ((struct R17_801738E0_GlobalStruct *)&g_dungeon_status);
            globals->counter--;
        }
        ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C &= ~0x200;
        ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    default:
        return;
    }

    ((R17_801738E0_S_801738E0_2 *)entity)->unk_1C = clear_mask & entity_flags;
    ((R17_801738E0_S_801738E0_0 *)actor)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);

    return;
}
#include "modules/dungeon_resource17_slot0.h"

void func_80173F10(void *action, void *context, void *sprite, void *entity)
{
    void *saved_context;
    register void *dungeon_state;
    void *saved_entity;
    u8 state;
    s32 direction;

    saved_context = context;
#define action action
#define context saved_context
#define sprite sprite

    state = ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B;
    saved_entity = entity;
#define entity saved_entity
    switch (state) {
    case 0:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.turn_scale;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744F4);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)D_801744F4)[direction & 7]), 0);
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;
    }

    case 1:
        if (((EntityRec *)entity)->tileY != 0) {
            register u8 *counter_state;

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
            select_sprite_entry(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
            (*(u32 *)((u8 *)entity + 0x1C)) |= 0x40000;
            counter_state = (u8 *)&g_dungeon_status.turn_scale;
            ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A++;
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
            return;
        }

        dungeon_state = &g_dungeon_status.turn_scale;
        if (((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_02 & 0x1000) {
            return;
        }

        if ((((EntityRec *)entity)->unk_64 != 0) &&
            begin_ready_actor_directional_action(action, context, sprite, 0)) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            ((R17_80173F10_S_80173ED8_0 *)action)->unk_A8 = 0;
            func_80174250(action, context, sprite, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            void *owner = D_800814A8;

            if ((check_entity_relation(entity,
                    (u8 *)((R17_80173F10_S_80173ED8_5 *)owner)->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_food(entity);
        on_actor_status_updated(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9;
        select_sprite_entry(sprite,(u8)(((u8 *)D_801744EC)[direction & 7]), 0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        ((R17_80173F10_S_80173ED8_4 *)dungeon_state)->unk_0A++;

        ((R17_80173F10_S_80173ED8_0 *)action)->unk_9B++;
        return;

    case 2:
    {
        u8 *counter_state;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        counter_state = (u8 *)&g_dungeon_status.turn_scale;
        ((R17_80173F10_S_80173ED8_2 *)counter_state)->unk_0A--;
        ((EntityRec *)entity)->flags1C &= ~0x208;
        ((R17_80173F10_S_80173ED8_0 *)action)->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
        return;
    }

    default:
        return;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void func_80174250(R17_80174250_Actor *actor, s32 action, R17_80174250_Entity *entity, R17_80174250_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_entity_movement_and_ground_height);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)D_801744FC) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)D_80174494);
        select_sprite_entry(entity,(s16)(((u8 *)D_80174494)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}
#include "modules/dungeon_resource17_slot0.h"

void update_timed_effect_and_expire(Resource17CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_entity_movement_and_ground_height;
        }
    }
}
#include "modules/dungeon_resource17_slot0.h"

void finish_actor_terrain_interpolation_then_resume_ground_movement(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void finish_spinning_actor_fall_then_resume_ground_movement(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void update_effect_trajectory_and_sprite(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void blend_animation_palette_and_complete(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
#include "modules/dungeon_resource17_slot0.h"

void finish_actor_action_flag_propagation_then_resume_ground_movement(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_entity_movement_and_ground_height;
    }
}
