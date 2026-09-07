#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK bzero();             /* extern */
s32 func_800AE500();                     /* extern */
s32 func_800AEFD8(); /* extern */
M2C_UNK func_800B06C4();                      /* extern */
extern M2C_UNK D_800B0490;

typedef struct S_800B05DC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
} S_800B05DC_0;   /* temp_s0 in func_800B05DC */

typedef struct S_800B05DC_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B05DC_1;   /* var_s1 in func_800B05DC */

/* Create a display controller and its child display object. */
void *func_800B05DC(s32 owner, s32 display_config, M2C_UNK x, M2C_UNK y, s32 init_config) {
    s32 init_result;
    s32 display_object;
    S_800B05DC_0 *state;
    void *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_08 = owner;
        state->unk_0C = init_config;
        state->unk_14 = display_config;
        bzero(state, 4);
        init_result = func_800AE500(state, init_config);
        state->unk_18 = init_result;
        if (init_result != 0) {
            ((S_800B05DC_1 *)object)->unk_10 = &D_800B0490;
            display_object = func_800AEFD8(object, x, y, display_config, state->unk_18, state);
            state->unk_04 = display_object;
            if (display_object == 0) {
                func_800B06C4(state);
                object = NULL;
            }
        }
    }
    return object;
}
