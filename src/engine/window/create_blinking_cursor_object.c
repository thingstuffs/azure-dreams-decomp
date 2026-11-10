#include "engine/window/cursor_body.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

#include "records/Rec_D_80081FDC.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"
#include "engine/graphics.h"








void copy_texture_descriptor_with_page_offsets(); /* extern */
extern u8 blinking_cursor_texture_template_0[];
extern u8 blinking_cursor_texture_template_1[];
extern u8 blinking_cursor_texture_template_2[];
extern u8 blinking_cursor_texture_descriptor_0[];
extern u8 blinking_cursor_texture_descriptor_1[];
extern u8 blinking_cursor_texture_descriptor_2[];
extern u8 window_node_list_storage[];

/* Initializes and links a runtime node, then sets its record, state, and display data. */
void create_blinking_cursor_object(void *node_addr, Rec_D_80081FDC *record, s32 *config, s16 initial_mode, s32 initial_value,
    void *setup_id) {
    WindowCursorBody *state;
    SpriteFrameState *display;
    ObjectNodeHeader *node;

    node = initialize_runtime_node_storage(0x11, node_addr, 0x49, &window_node_list_storage);
    node->update_callback = &update_blinking_cursor_with_bright_idle;
    register_node(node, &draw_linked_sprite_nodes);
    state = NODE_BODY(node);
    display = node->sprite;
    state->script = config;
    state->enabled = 1;
    state->cursor_offset = initial_mode;
    runtime_initialize_state_value(record, *config);
    state->model = record;
    record->unk_60 = 6;
    state->model->unk_10 = 0x47;
    state->model->unk_14 = 2;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(setup_id, state);
    display->color.word = 0xC0C0C0;
    copy_texture_descriptor_with_page_offsets(state->script + 3, &blinking_cursor_texture_template_0, &blinking_cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &blinking_cursor_texture_template_1, &blinking_cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->script + 3, &blinking_cursor_texture_template_2, &blinking_cursor_texture_descriptor_2);
    display->source = blinking_cursor_texture_descriptor_1;
    display->unk_00 = 0;
    display->unk_04 = 0;
    display->frame_ticks = 0;
    display->flags = (u16) (display->flags | 0x1C);
    state->variant_offset = (s16) initial_value;
}
