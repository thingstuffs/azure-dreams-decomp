#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
typedef struct S_800CB9B8_2 S_800CB9B8_2;
#include "records/Rec_D_80082D58.h"
void update_entity_relative_position(Rec_D_80082D58 *entity, S_800CB9B8_2 *out_pos);               /* extern (function symbol used as callback) */
void *allocate_list_node();               /* extern */
s32 register_node();              /* extern */
extern s32 D_800D68B0[];

typedef struct S_800CB8CC_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    s32 (*unk_10)(void *, s32, void *);
} S_800CB8CC_0;

typedef struct S_800CB8CC_1 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x38];
    s32 unk_9C;
} S_800CB8CC_1;

/* Creates an object, initializes its render data, and invokes its callback. */
s32 create_and_invoke_render_object(s32 initial_value, s32 resource_index) {
    s32 callback_arg;
    SpriteFrameState *render_data;
    S_800CB8CC_1 *state;
    void *object;

    object = allocate_list_node(0x136, ((s32 *)&D_80083498.next));
    if (object == 0) {
        return 0;
    }
    state = object + 0x20;
    callback_arg = ((S_800CB8CC_0 *)object)->unk_08;
    render_data = ((S_800CB8CC_0 *)object)->unk_0C;
    state->unk_9C = initial_value;
    ((S_800CB8CC_0 *)object)->unk_10 = update_entity_relative_position;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = 0x808080;
    state->unk_60 = resource_index;
    render_data->source = D_800D68B0[resource_index];
    register_node(object, project_sprite_chain);
    ((S_800CB8CC_0 *)object)->unk_10(state, callback_arg, render_data);
    return (s32)object;
}
