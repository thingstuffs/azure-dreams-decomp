#include "engine/object/render_words.h"

#include "common.h"

/* Retail bytes at assets/3E018.bin + 0x161A0; current ownership reconstruction only. */
s32 attached_node_initial_word_14 = 0x01DE03E0;
s32 attached_node_initial_word_18 = 0x00100030;

#include "engine/object/render_words.h"

/* Registers an attached message-window node with fade, drawing and update callbacks and variant data. */
void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner)
{
    void *node;
    void *object;
    void *aux_state;
    void *render_state;

    node = initialize_runtime_node_storage(0x11, node_storage, 0x49, window_node_list_storage);
    ((S_80035888_0 *)node)->unk_10 = dispatch_window_fade_and_update_extents;
    register_node(node, draw_linked_sprite_nodes);

    object = (u8 *)node + 0x20;
    aux_state = ((S_80035888_0 *)node)->unk_08;
    render_state = ((S_80035888_0 *)node)->unk_0C;
    ((S_80035888_1 *)object)->unk_44 = init_data;
    ((S_80035888_1 *)object)->unk_48 = 1;
    ((S_80035888_1 *)object)->unk_4A = object_id;

    runtime_initialize_state_value(attached_object, *init_data);

    ((S_80035888_0 *)node)->unk_20 = attached_object;
    ((S_80035888_1 *)object)->unk_04 = 0;
    ((S_80035888_1 *)object)->unk_08 = draw_window_rects;
    copy_window_params(object, attached_node_default_parameters);
    prepend_embedded_object_node(owner, object);

    {
        s32 color;
        s32 initial_state_14;
        s32 initial_state_18;

        color = 0x800000;
        initial_state_14 = attached_node_initial_word_14;
        (*(void * *)((u8 *)object + 0x68)) = set_window_handler;
        (*(s32 *)((u8 *)object + 0x14)) = initial_state_14;
        initial_state_18 = attached_node_initial_word_18;
        color |= 0x8080;
        ((S_80035888_1 *)object)->unk_18 = initial_state_18;
        ((S_80035888_2 *)aux_state)->unk_02 = 0;
        ((S_80035888_3 *)render_state)->unk_0C = color;
        ((S_80035888_3 *)render_state)->unk_08 = attached_node_default_render_data;
        ((S_80035888_3 *)render_state)->unk_00 = 0;
        ((S_80035888_3 *)render_state)->unk_04 = 0;
        ((S_80035888_3 *)render_state)->unk_05 = 0;
        ((S_80035888_1 *)object)->unk_74 = owner;
        ((S_80035888_1 *)object)->unk_78 = ((Rec_func_80034F58_arg0 *)owner)->unk_01;
        ((S_80035888_5 *)(((S_80035888_0 *)node)->unk_20))->unk_34 =
            attached_node_variant_data[((S_80035888_6 *)(((S_80035888_1 *)object)->unk_74))->unk_02];
    }
}
