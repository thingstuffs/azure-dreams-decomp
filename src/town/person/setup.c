#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3_32;
void compute_offset_position_linked_object(void *object, Vec3_32 *out_pos);            /* extern */
struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);            /* extern */
s32 register_node();           /* extern */
s32 lookup_item_category_mapped_value(s32, s32);                /* extern */

typedef struct S_800C6C10_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    s32 (*unk_10)(void *, s32, void *);
} S_800C6C10_0;

typedef struct S_800C6C10_1 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_800C6C10_1;

/* Creates an object, initializes its render data, and runs its callback. */
s32 func_800C6C10(s32 state_value) {
    s32 callback_arg;
    SpriteFrameState *render_data;
    S_800C6C10_1 *state;
    void *object;

    object = allocate_list_node(0x136, (struct ObjectNodeHeader * *)(((s32 *)&D_80083498.next)));
    if (object == 0) {
        return 0;
    }
    state = object + 0x20;
    callback_arg = ((S_800C6C10_0 *)object)->unk_08;
    render_data = ((S_800C6C10_0 *)object)->unk_0C;
    state->unk_9C = state_value;
    ((S_800C6C10_0 *)object)->unk_10 = compute_offset_position_linked_object;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = 0x808080;
    render_data->source = lookup_item_category_mapped_value(0xD, 3);
    register_node(object, project_sprite_chain);
    ((S_800C6C10_0 *)object)->unk_10(state, callback_arg, render_data);
    return (s32)object;
}
