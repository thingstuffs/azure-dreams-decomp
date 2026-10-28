#include "common.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"


typedef struct S_80036D4C_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80036D4C_4;   /* temp_v0 in create_blinking_cursor_object */

typedef struct S_80036D4C_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80036D4C_5;   /* ((S_80036D4C_4 *)temp_v0)->unk_20 in create_blinking_cursor_object */


typedef struct S_80036D4C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void (*unk_10)();
    u8 pad_14[0xC];
    void * unk_20;
} S_80036D4C_0;   /* temp_v0 in create_blinking_cursor_object */

typedef struct S_80036D4C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 * unk_44;
    s8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x1A];
    s16 unk_66;
} S_80036D4C_1;   /* temp_s1 in create_blinking_cursor_object */


typedef struct S_80036D4C_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    u8 *unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80036D4C_3;   /* temp_s2 in create_blinking_cursor_object */

void copy_texture_descriptor_with_page_offsets(); /* extern */
extern u8 blinking_cursor_texture_template_0[];
extern u8 blinking_cursor_texture_template_1[];
extern u8 blinking_cursor_texture_template_2[];
extern u8 blinking_cursor_texture_descriptor_0[];
extern u8 blinking_cursor_texture_descriptor_1[];
extern u8 blinking_cursor_texture_descriptor_2[];
extern u8 window_node_list_storage[];
void update_blinking_cursor_with_bright_idle();

/* Initializes and links a runtime node, then sets its record, state, and display data. */
void create_blinking_cursor_object(void *node_addr, Rec_D_80081FDC *record, s32 *config, s16 initial_mode, s32 initial_value,
    void *setup_id) {
    S_80036D4C_1 *state;
    S_80036D4C_3 *display;
    void *node;

    node = initialize_runtime_node_storage(0x11, node_addr, 0x49, &window_node_list_storage);
    ((S_80036D4C_0 *)node)->unk_10 = &update_blinking_cursor_with_bright_idle;
    register_node(node, &runtime_handle_transform_submit_textured_sprite_quads_each_node_invoke_callback);
    state = node + 0x20;
    display = ((S_80036D4C_0 *)node)->unk_0C;
    state->unk_44 = config;
    state->unk_48 = 1;
    state->unk_4A = initial_mode;
    runtime_initialize_state_value(record, *config);
    ((S_80036D4C_0 *)node)->unk_20 = record;
    record->unk_60 = 6;
    ((S_80036D4C_5 *)(((S_80036D4C_4 *)node)->unk_20))->unk_10 = 0x47;
    ((S_80036D4C_5 *)(((S_80036D4C_4 *)node)->unk_20))->unk_14 = 2;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(setup_id, state);
    display->unk_0C = 0xC0C0C0;
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &blinking_cursor_texture_template_0, &blinking_cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &blinking_cursor_texture_template_1, &blinking_cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &blinking_cursor_texture_template_2, &blinking_cursor_texture_descriptor_2);
    display->unk_08 = blinking_cursor_texture_descriptor_1;
    display->unk_00 = 0;
    display->unk_04 = 0;
    display->unk_05 = 0;
    display->unk_14 = (u16) (display->unk_14 | 0x1C);
    state->unk_66 = (s16) initial_value;
}
