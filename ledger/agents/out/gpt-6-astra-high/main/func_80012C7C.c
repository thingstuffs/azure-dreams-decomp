#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800220DC();                            /* extern */
M2C_UNK func_8002223C();                            /* extern */
s32 func_800238D4();                          /* extern */
s32 func_80024D58();            /* extern */
M2C_UNK func_80025B40();                 /* extern */
void *func_8003FE78();   /* extern */
s32 func_8004F418();                  /* extern */
extern M2C_UNK D_80025BD4;
extern M2C_UNK D_8002B7E0;

typedef struct S_80025C7C_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x1C];
    s32 unk_48;
} S_80025C7C_0;   /* temp_s1 in func_80025C7C */

typedef struct S_80025C7C_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025C7C_1;   /* temp_v0 in func_80025C7C */

/* Creates an object and initializes its state. */
void *func_80025C7C(s32 init_value) {
    S_80025C7C_0 *state;
    void *object;

    object = func_8003FE78(0, &D_8002B7E0, 0x1C);
    state = object + 0x20;
    func_80025B40(state, init_value);
    func_8002223C();
    func_800220DC();
    state->unk_48 = 1;
    ((S_80025C7C_1 *)object)->unk_20 = func_8004F418(object, object + 0x68);
    state->unk_18 = func_800238D4(object);
    state->unk_1C = func_80024D58(object, state->unk_28, 0);
    state->unk_24 = 0;
    ((S_80025C7C_1 *)object)->unk_10 = &D_80025BD4;
    return object;
}
