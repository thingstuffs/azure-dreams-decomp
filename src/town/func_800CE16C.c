#include "common.h"
#include "m2c_compat.h"

M2C_UNK D_800CB9B8();               /* extern (function symbol used as callback) */
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();              /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern s32 D_800D68B0[];


typedef struct S_800CB8CC_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
} S_800CB8CC_0;   /* temp_v0 in func_800CB8CC */

typedef struct S_800CB8CC_1 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x38];
    s32 unk_9C;
} S_800CB8CC_1;   /* temp_s1 in func_800CB8CC */

typedef struct S_800CB8CC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CB8CC_2;   /* temp_s0 in func_800CB8CC */

/* Creates an object, initializes its render data, and invokes its callback. */
s32 func_800CB8CC(s32 initial_value, s32 resource_index) {
    s32 callback_arg;
    S_800CB8CC_2 *render_data;
    S_800CB8CC_1 *state;
    void *object;

    object = func_8003FD64(0x136, &D_80083498);
    if (object == NULL) {
        return 0;
    }
    state = object + 0x20;
    callback_arg = ((S_800CB8CC_0 *)object)->unk_08;
    render_data = ((S_800CB8CC_0 *)object)->unk_0C;
    state->unk_9C = initial_value;
    ((S_800CB8CC_0 *)object)->unk_10 = D_800CB9B8;
    render_data->unk_1E = 0x1000;
    render_data->unk_1C = 0x1000;
    render_data->unk_0C = 0x808080;
    state->unk_60 = resource_index;
    render_data->unk_08 = D_800D68B0[resource_index];
    func_8004491C(object, &D_80045340);
    ((S_800CB8CC_0 *)object)->unk_10(state, callback_arg, render_data);
    return (s32)object;
}
