#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3_32;
void compute_offset_position_linked_object(void *object, Vec3_32 *out_pos);            /* extern */
void *func_8003FD64();            /* extern */
s32 func_8004491C();           /* extern */
s32 lookup_item_category_mapped_value();                /* extern */


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

typedef struct S_800C6C10_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C6C10_2;

/* Creates an object, initializes its render data, and runs its callback. */
s32 func_800C6C10(s32 state_value) {
    s32 callback_arg;
    S_800C6C10_2 *render_data;
    S_800C6C10_1 *state;
    void *object;

    object = func_8003FD64(0x136, ((s32 *)&D_80083498.next));
    if (object == 0) {
        return 0;
    }
    state = object + 0x20;
    callback_arg = ((S_800C6C10_0 *)object)->unk_08;
    render_data = ((S_800C6C10_0 *)object)->unk_0C;
    state->unk_9C = state_value;
    ((S_800C6C10_0 *)object)->unk_10 = compute_offset_position_linked_object;
    render_data->unk_1E = 0x1000;
    render_data->unk_1C = 0x1000;
    render_data->unk_0C = 0x808080;
    render_data->unk_08 = lookup_item_category_mapped_value(0xD, 3);
    func_8004491C(object, func_80045340);
    ((S_800C6C10_0 *)object)->unk_10(state, callback_arg, render_data);
    return (s32)object;
}
