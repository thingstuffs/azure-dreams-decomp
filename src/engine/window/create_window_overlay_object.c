#include "common.h"

#include "engine/node.h"
#include "engine/window/message.h"
#include "sdk/libgpu.h"
#include "slus/data.h"
#include "engine/object.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *);

typedef struct S_func_80035E58_1 {
    void *unk_00;
    void *unk_04;
    Callback unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x1A];
    u16 unk_2E;
    u8 pad_30[0x6];
    u16 unk_36;
    u8 pad_38[0xC];
    s32 *unk_44;
    u8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x1C];
    Callback unk_68;
    u8 pad_6C[0x8];
    void *unk_74;
} S_func_80035E58_1;

typedef struct S_func_80035E58_3 {
    u8 pad_00[0x80];
    u8 *unk_80;
} S_func_80035E58_3;

typedef struct S_func_80035E58_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_func_80035E58_4;

typedef struct S_func_80035E58_5 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_func_80035E58_5;

extern void copy_window_params(struct Container *container, struct Source *source);

extern void update_window_state(struct RuntimeObject *object, s32 handler_arg1, s32 handler_arg2, s32 state);
extern void scroll_window_y(void *);
extern void draw_window_rects(void *);

extern u8 window_node_list_storage[];

/* Initializes an actor-linked display node, clears its image region, and sets callbacks and rendering data. */
void create_window_overlay_object(void *node_addr, void *display, u8 *image, s32 *state_ref,
                   s32 option, u8 *owner) {
    ObjectNodeHeader *node;
    S_func_80035E58_1 *node_data;
    SpriteFrameState *render_data;
    S_func_80035E58_3 *actor;

    node = initialize_runtime_node_storage(0x11, node_addr, 0x49, window_node_list_storage);
    node->update_callback = update_window_state;
    register_node(node, draw_linked_sprite_nodes);

    node_data = NODE_BODY(node);
    render_data = node->sprite;
    node_data->unk_44 = state_ref;
    node_data->unk_48 = 1;
    node_data->unk_4A = (s16)option;
    ClearImage(image + 4, 0, 0, 0);

    runtime_initialize_state_value(display, *state_ref);
    node_data->unk_00 = display;
    node_data->unk_04 = image;
    node_data->unk_08 = draw_window_rects;
    copy_window_params(node_data, window_overlay_parameter_template);
    prepend_embedded_object_node(owner, node_data);

    node_data->unk_68 = scroll_window_y;
    actor = (S_func_80035E58_3 *)(owner + 0x8C);
    render_data->color.word = 0x808080;
    render_data->source = window_overlay_default_render_data;
    render_data->unk_00 = 0;
    render_data->unk_04 = 0;
    render_data->frame_ticks = 0;
    node_data->unk_74 = actor;

    node_data->unk_12 = window_overlay_field_12_values[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    node_data->unk_2E = window_overlay_field_2e_values[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    node_data->unk_36 = window_overlay_field_36_values[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    copy_window_offset_rectangle((u8 *)node + 0x2C, node_data->unk_74);
    render_data->source = window_overlay_render_variants[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
    ((S_func_80035E58_5 *)node_data->unk_00)->unk_34 =
        window_overlay_model_values[((S_func_80035E58_4 *)actor->unk_80)->unk_02];
}
