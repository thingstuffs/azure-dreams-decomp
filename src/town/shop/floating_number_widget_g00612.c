/* Floating number widget (G00612). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B41D8, CL:town/func_800B4200, CL:town/func_800B4298, CL:town/func_800B43B0, CL:town/func_800B4410. */
#include "town/shop/floating_number_widget_g00612.h"

/* Initialize panel content and element positions. */
void initialize_panel_content_and_positions(S_800B19F8_0 *panel)
{
    ((S_800B19F8_2 *)(((S_800B19F8_1 *)panel)->unk_48))->unk_00 = (s32) D_80078D6C;
    ((S_800B19F8_6 *)(((S_800B19F8_2 *)(((S_800B19F8_1 *)panel)->unk_48))->unk_04))->unk_08 = 0;
    ((S_800B19F8_6 *)(((S_800B19F8_2 *)(((S_800B19F8_1 *)panel)->unk_48))->unk_04))->unk_0A = 0;

    ((S_800B19F8_3 *)(((S_800B19F8_1 *)panel)->unk_4C))->unk_00 = panel->unk_08;
    ((S_800B19F8_7 *)(((S_800B19F8_3 *)(((S_800B19F8_1 *)panel)->unk_4C))->unk_04))->unk_08 = 0;
    ((S_800B19F8_7 *)(((S_800B19F8_3 *)(((S_800B19F8_1 *)panel)->unk_4C))->unk_04))->unk_0A = 0xF;

    ((S_800B19F8_4 *)(((S_800B19F8_1 *)panel)->unk_54))->unk_00 =
        (s32) decode_fullwidth_text(panel->unk_0C, D_800D1560, 0);
    ((S_800B19F8_8 *)(((S_800B19F8_4 *)(((S_800B19F8_1 *)panel)->unk_54))->unk_04))->unk_08 = 0x43;
    ((S_800B19F8_8 *)(((S_800B19F8_4 *)(((S_800B19F8_1 *)panel)->unk_54))->unk_04))->unk_0A = 0x88;

    ((S_800B19F8_9 *)(((S_800B19F8_5 *)(((S_800B19F8_1 *)panel)->unk_50))->unk_04))->unk_08 = 0x67;
    ((S_800B19F8_9 *)(((S_800B19F8_5 *)(((S_800B19F8_1 *)panel)->unk_50))->unk_04))->unk_0A = 0x88;

    refresh_formatted_global_display(panel);
    func_800B18F8(panel->unk_08);
}

/* Store two values in the pair. */
void store_pair_values(S_800B1B04_0 *pair, s32 first, s32 second) {
    pair->unk_00 = first;
    pair->unk_04 = second;
}

/* Set up the object, update its embedded records, and finalize it. */
void build_owned_floating_number_widget(s32 object_addr, s32 setup_value, s32 update_value_1, s32 update_value_2) {
    store_pair_values((S_800B1B04_0 *)object_addr, setup_value, update_value_1);
    initialize_templated_state_and_position(object_addr + 0x38, object_addr + 0x10, object_addr + 0x20, update_value_1, update_value_2);
    initialize_panel_content_and_positions((S_800B19F8_0 *)object_addr);
}

/* Initializes four nodes with a shared anchor and default data. */
void initialize_four_anchored_nodes(void *state)
{
    s32 node_index;
    s32 data_offset;
    s32 node_offset;
    s32 first_word;
    void *anchor;
    s32 *default_data;
    s32 *data_row;
    Node **node_slot;
    Node *node;

    node_index = 0;
    anchor = (u8 *)state + 0x20;
    do {
        default_data = display_block_defaults;
        node_slot = (Node **)((u8 *)state + node_index * 4);
        node_offset = 0x58 + node_index * 0x10;
        data_offset = 0x98 + node_index * 0x10;
        data_row = (s32 *)((u8 *)state + node_index * 0x10);
        node = (Node *)((u8 *)state + node_offset);
        node_slot[0x12] = node;
        node->data = (u8 *)state + data_offset;
        node_slot[0x12]->anchor = (first_word = display_block_defaults[0], anchor);
        data_row[0x26] = first_word;
        data_row[0x27] = default_data[1];
        data_row[0x28] = default_data[2];
        data_row[0x29] = default_data[3];
        node_index++;
    } while (node_index < 4);
}

/* Create an object with two buffers and initialize its state and position. */
void *create_dual_buffer_object(s32 setup_value, s32 x, s32 y)
{
    void *object;
    S_800B1BEC_0 *part;
    void *second_buffer;
    u16 object_flags;
    u32 global_flags;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        part = (u8 *)object + 0x20;
        part->unk_08 = create_callback_pair_default(0xCC);
        second_buffer = create_callback_pair_default(0xCC);
        part->unk_0C = second_buffer;

        if (part->unk_08 != 0 && second_buffer != 0) {
            ((S_800B1BEC_1 *)object)->unk_0C = (u8 *)object + 0x58;
            initialize_four_anchored_nodes(part);
            part->unk_44 = process_context_with_selector_4((u8 *)object + 0x68);
            build_owned_floating_number_widget((s32)part, setup_value, x, y);
            register_node(object, dungeon_menu_tag);
            ((S_800B1BEC_1 *)object)->unk_10 = lower_value_toward_target;
        } else {
            flag_object_for_removal(part->unk_08);
            flag_object_for_removal(part->unk_0C);
            object_flags = ((S_800B1BEC_1 *)object)->unk_1E | 0x8000;
            global_flags = ((u32)object_flag_block.flags) | 0x8000;
            ((S_800B1BEC_1 *)object)->unk_1E = object_flags;
            object_flag_block.flags = global_flags;
        }
    }
    return object;
}
