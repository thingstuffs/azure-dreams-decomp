#include "engine/window/attached_message_window.h"
#include "engine/object/render_words.h"

#include "common.h"
#include "engine/object.h"

/* Retail bytes at assets/3E018.bin + 0x161A0; current ownership reconstruction only. */
s32 attached_node_initial_word_14 = 0x01DE03E0;
s32 attached_node_initial_word_18 = 0x00100030;

#include "engine/object/render_words.h"

/* Registers an attached message-window node with fade, drawing and update callbacks and variant data. */
void initialize_attached_message_window_node(void *node_storage, void *attached_object, s32 *init_data, s16 object_id, void *owner)
{
    ObjectNodeHeader *node;
    AttachedMessageWindowBody *object;
    ObjectPosition *aux_state;
    SpriteFrameState *render_state;

    node = initialize_runtime_node_storage(0x11, node_storage, 0x49, window_node_list_storage);
    node->update_callback = dispatch_window_fade_and_update_extents;
    register_node(node, draw_linked_sprite_nodes);

    object = NODE_BODY(node);
    aux_state = node->position;
    render_state = node->sprite;
    object->unk_44 = init_data;
    object->active = 1;
    object->object_id = object_id;

    runtime_initialize_state_value(attached_object, *init_data);

    object->attached_object = attached_object;
    object->unk_04 = 0;
    object->draw_callback = draw_window_rects;
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
        object->initial_state_18 = initial_state_18;
        aux_state->x.w.i = 0;
        render_state->color.word = color;
        render_state->source = attached_node_default_render_data;
        render_state->unk_00 = 0;
        render_state->unk_04 = 0;
        render_state->frame_ticks = 0;
        object->owner = owner;
        object->unk_78 = ((Rec_func_80034F58_arg0 *)owner)->unk_01;
        ((S_80035888_5 *)(object->attached_object))->unk_34 =
            attached_node_variant_data[((S_80035888_6 *)(object->owner))->unk_02];
    }
}
