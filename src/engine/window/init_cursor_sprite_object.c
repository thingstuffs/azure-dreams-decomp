#include "engine/window/cursor_body.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

#include "records/Rec_D_80081FDC.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"
#include "shared/entity.h"
#include "slus/data.h"
#include "slus/window_node_list_data.h"






void copy_texture_descriptor_with_page_offsets(); /* extern */

/* Initializes a sprite node, links it to its owner, and applies its initial display state. */
void init_cursor_sprite_object(void *node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base,
    void *owner) {
    ObjectPosition *render_data;
    WindowCursorBody *state;
    SpriteFrameState *sprite;
    ObjectNodeHeader *node;

    node = initialize_runtime_node_storage(0x11, node_addr, 0x49, &window_node_list_storage);
    node->update_callback = update_cursor_blink_colors;
    register_node(node, &draw_linked_sprite_nodes);
    state = NODE_BODY(node);
    render_data = node->position;
    sprite = node->sprite;
    state->script = script_data;
    state->enabled = 1;
    state->cursor_offset = cursor_offset;
    runtime_initialize_state_value(transform, *script_data);
    state->model = transform;
    transform->unk_60 = 6;
    state->model->unk_10 = 0x47;
    state->model->unk_14 = 2;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(owner, state);
    sprite->color.word = 0xC0C0C0;
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_0, &cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_1, &cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_2, &cursor_texture_descriptor_2);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_3, &cursor_texture_descriptor_3);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_4, &cursor_texture_descriptor_4);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &cursor_texture_template_5, &cursor_texture_descriptor_5);
    sprite->source = cursor_texture_descriptor_1;
    sprite->unk_00 = 0;
    sprite->unk_04 = 0;
    sprite->frame_ticks = 0;
    sprite->flags = (u16) (sprite->flags | 0x1C);
    state->variant_offset = (s16) sprite_base;
    update_cursor_blink_colors(state, render_data, sprite);
}
