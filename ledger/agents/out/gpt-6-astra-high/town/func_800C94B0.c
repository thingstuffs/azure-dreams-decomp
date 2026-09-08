#include "common.h"
#include "m2c_compat.h"

M2C_UNK D_800C6CE4();            /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_8004A658();                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;


typedef struct S_800C6C10_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
} S_800C6C10_0;   /* temp_v0 in func_800C6C10 */

typedef struct S_800C6C10_1 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_800C6C10_1;   /* temp_s1 in func_800C6C10 */

typedef struct S_800C6C10_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800C6C10_2;   /* temp_s0 in func_800C6C10 */

/* Creates an object, initializes its render data, and runs its callback. */
s32 func_800C6C10(s32 state_value) {
    s32 callback_arg;
    S_800C6C10_2 *render_data;
    S_800C6C10_1 *state;
    void *object;

    object = func_8003FD64(0x136, &D_80083498);
    if (object == NULL) {
        return 0;
    }
    state = object + 0x20;
    callback_arg = ((S_800C6C10_0 *)object)->unk_08;
    render_data = ((S_800C6C10_0 *)object)->unk_0C;
    state->unk_9C = state_value;
    ((S_800C6C10_0 *)object)->unk_10 = D_800C6CE4;
    render_data->unk_1E = 0x1000;
    render_data->unk_1C = 0x1000;
    render_data->unk_0C = 0x808080;
    render_data->unk_08 = func_8004A658(0xD, 3);
    func_8004491C(object, &D_80045340);
    ((S_800C6C10_0 *)object)->unk_10(state, callback_arg, render_data);
    return (s32)object;
}
