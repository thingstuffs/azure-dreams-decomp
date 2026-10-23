#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/univern/create_actor_child_display.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/univern/create_actor_child_display.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/monster/death.h"

/* Allocates and initializes an object and its child display items. */
/* Creates Univern with frames at D_80150494 and a directional child display linked to the actor's sprite
 * resources. */
void *create_actor_child_display(s32 kind, s32 part_byte_24, s32 part_byte_25, s32 copy_halfword)
{
    ObjectNodeHeader *root;
    void *copy;
    s32 outer_index;
    s32 saved_kind;
    s32 saved_halfword;
    s16 saved_byte_25;
    u16 saved_part_byte_24;
    void *object;
    void *child_slot;
    void *stable_object;
    s32 kind_copy;
    SpriteFrameState *part;
    void *allocated;
    s32 allocation_size;
    ObjectNodeHeader *allocation_pool;

    saved_kind = kind;
    object = 0;
    allocation_size = 0x112;
    saved_part_byte_24 = part_byte_24;
    allocation_pool = &scene_object_list_anchor;
    saved_halfword = copy_halfword;
    saved_byte_25 = part_byte_25;
    allocated = allocate_list_node(allocation_size, allocation_pool);
    kind_copy = saved_kind;
    root = allocated;
    if (allocated != 0) {
        {
            ObjectNodeHeader *init_root;
            void *setup;

            object = (u8 *)allocated + 0x20;
            init_root = allocated;
            setup = project_sprite_chain;
            init_root->unk_10 = func_8014CBB8;
            ((S_8014C89C_1 *)object)->unk_13 = MONSTER_UNIVERN;
            register_node(init_root, setup);
        }

        {
            void *part_callback;

            part_callback = D_80150494;
            copy = root->position;
            ((S_8014C89C_2 *)copy)->unk_08.at02.v = saved_halfword;
            stable_object = object;
            part = root->sprite;
            part->frameTable = part_callback;
        }
        part->unk_24 = saved_part_byte_24;
        part->unk_25 = saved_byte_25;

        {
            s32 flags_14;
            s32 flags_1c;

            if ((saved_kind & 3) == 1) {
                flags_14 = ((S_8014C89C_1 *)object)->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                flags_1c = ((S_8014C89C_1 *)object)->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                ((S_8014C89C_1 *)object)->unk_14 = flags_14;
                ((S_8014C89C_1 *)object)->unk_1C = flags_1c;
            } else if ((saved_kind & 3) >= 2) {
                flags_14 = ((S_8014C89C_1 *)object)->unk_14 | ACTOR_CLASS_ENABLED;
                flags_1c = ((S_8014C89C_1 *)object)->unk_1C | ACTOR_PLAYER_SIDE;
                ((S_8014C89C_1 *)object)->unk_14 = flags_14;
                ((S_8014C89C_1 *)object)->unk_1C = flags_1c;
            } else {
                flags_14 = saved_kind & ~3;
                if ((s16)flags_14 == 0) {
                    if ((((S_8014C89C_1 *)object)->unk_14 & ACTOR_RESIST_SLEEP) == 0) {
                        if (generate_random_value() & 1) {
                            ((S_8014C89C_1 *)object)->unk_1C |= ACTOR_ASLEEP;
                            set_or_clear_actor_status_slot(object, STATUS_SLEEP,
                                (generate_random_value() & 0x3F) | 0x20);
                            part->frameTable = D_801504FC;
                        }
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(root, copy, part, (s16)kind_copy);

        child_slot = stable_object;
        outer_index = 0;
        ((S_8014C89C_4 *)stable_object)->unk_9A = 0xFF;
        ((S_8014C89C_4 *)stable_object)->unk_9C = -1;
        ((S_8014C89C_4 *)stable_object)->unk_8C = update_entity_movement_animation_and_ground;
        ((S_8014C89C_1 *)object)->unk_1C |= 0x40000;
        ((S_8014C89C_4 *)stable_object)->unk_92 = -48;
        ((S_8014C89C_4 *)stable_object)->unk_A8 = 0;
        ((S_8014C89C_4 *)stable_object)->unk_9E = 1;
        ((S_8014C89C_4 *)stable_object)->unk_98 |= 0x4000;

        do {

            saved_halfword = (s32)allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
            allocated = (void *)saved_halfword;
            ((S_8014C89C_5 *)child_slot)->unk_A4 = allocated;
            if (allocated != 0) {
                s32 item_offset;
                s32 item_index;
                register void *slot_base;
                u8 *direction_table;
                s32 more_items;

                saved_kind = (s32)((u8 *)allocated + 0x20);
                ((S_8014C89C_6 *)(void *)saved_kind)->unk_02 = 1;
                item_index = 0;
                slot_base = child_slot;
                direction_table = D_80150494 + 0x50;
                item_offset = 8;
                do {
                    SpriteFrameState *item;
                    s32 direction_index;
                    s32 part_value;
                    s32 call_zero;
                    ObjectNodeHeader *child_root;

                    item = (u8 *)(void *)saved_kind + item_offset;
                    ((S_8014C89C_6 *)(void *)saved_kind)->unk_04 |= 0x8000;
                    part_value = part->unk_28;
                    item->tpage_abr = 0x20;
                    item->color.word = 0x00808080;
                    item->unk_28 = part_value;
                    child_root = ((S_8014C89C_8 *)slot_base)->unk_A4;
                    call_zero = 0;
                    child_root->unk_10 = process_effect_block_entries;
                    (*(void **)((u8 *)item + 0x2C)) = direction_table;
                    direction_index = ((view_facing_angle_alias +
                        ((S_8014C89C_1 *)object)->unk_2A + 0x100) >> 9) & 7;
                    select_sprite_entry(item,
                        *(u8 *)((uptr)direction_index + (uptr)direction_table), call_zero);
                    item_offset += 0x30;
                    item_index++;
                    ((S_8014C89C_6 *)(void *)saved_kind)->unk_06 = 1;
                    texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(part, draw_sprite_effect_quads, 1);
                    more_items = item_index < ((S_8014C89C_6 *)(void *)saved_kind)->unk_02;
                    ((S_8014C89C_6 *)(void *)saved_kind)->unk_98 = (u8 *)root + 0x1E;
                } while (more_items);
            }
            child_slot = (u8 *)child_slot + 4;
            {
                s32 child_count;

                child_count = ((S_8014C89C_4 *)stable_object)->unk_9E;
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
