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
