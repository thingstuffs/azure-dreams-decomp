#include "common.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"


typedef struct S_8003719C_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8003719C_4;   /* node in init_cursor_sprite_object */

typedef struct S_8003719C_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_8003719C_5;   /* ((S_8003719C_4 *)node)->unk_20 in init_cursor_sprite_object */


typedef struct S_8003719C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    void (*unk_10)(void *, s32, void *);
    u8 pad_14[0xC];
    void * unk_20;
} S_8003719C_0;   /* node in init_cursor_sprite_object */

typedef struct S_8003719C_1 {
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
} S_8003719C_1;   /* state in init_cursor_sprite_object */


typedef struct S_8003719C_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    u8 *unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_8003719C_3;   /* sprite in init_cursor_sprite_object */

void copy_texture_descriptor_with_page_offsets(); /* extern */
extern u8 cursor_texture_template_0[];
extern u8 cursor_texture_template_1[];
extern u8 cursor_texture_template_2[];
extern u8 cursor_texture_template_3[];
extern u8 cursor_texture_template_4[];
extern u8 cursor_texture_template_5[];
extern u8 cursor_texture_descriptor_4[];
extern u8 cursor_texture_descriptor_5[];
extern u8 cursor_texture_descriptor_0[];
extern u8 cursor_texture_descriptor_1[];
extern u8 cursor_texture_descriptor_2[];
extern u8 cursor_texture_descriptor_3[];
extern u8 window_node_list_storage[];

/* Initializes a sprite node, links it to its owner, and applies its initial display state. */
void init_cursor_sprite_object(void *node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base,
    void *owner) {
    s32 render_data;
    S_8003719C_1 *state;
    S_8003719C_3 *sprite;
    void *node;

    node = initialize_runtime_node_storage(0x11, node_addr, 0x49, &window_node_list_storage);
    ((S_8003719C_0 *)node)->unk_10 = update_cursor_blink_colors;
    register_node(node, &draw_linked_sprite_nodes);
    state = node + 0x20;
    render_data = ((S_8003719C_0 *)node)->unk_08;
    sprite = ((S_8003719C_0 *)node)->unk_0C;
    state->unk_44 = script_data;
    state->unk_48 = 1;
    state->unk_4A = cursor_offset;
    runtime_initialize_state_value(transform, *script_data);
    ((S_8003719C_0 *)node)->unk_20 = transform;
    transform->unk_60 = 6;
    ((S_8003719C_5 *)(((S_8003719C_4 *)node)->unk_20))->unk_10 = 0x47;
    ((S_8003719C_5 *)(((S_8003719C_4 *)node)->unk_20))->unk_14 = 2;
    state->unk_04 = 0;
    state->unk_08 = 0;
    prepend_embedded_object_node(owner, state);
    sprite->unk_0C = 0xC0C0C0;
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_0, &cursor_texture_descriptor_0);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_1, &cursor_texture_descriptor_1);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_2, &cursor_texture_descriptor_2);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_3, &cursor_texture_descriptor_3);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_4, &cursor_texture_descriptor_4);
    copy_texture_descriptor_with_page_offsets(state->unk_44 + 3, &cursor_texture_template_5, &cursor_texture_descriptor_5);
    sprite->unk_08 = cursor_texture_descriptor_1;
    sprite->unk_00 = 0;
    sprite->unk_04 = 0;
    sprite->unk_05 = 0;
    sprite->unk_14 = (u16) (sprite->unk_14 | 0x1C);
    state->unk_66 = (s16) sprite_base;
    update_cursor_blink_colors(state, render_data, sprite);
}
