#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_800ADFE8();                      /* extern */
M2C_UNK func_800AE0F4();                      /* extern */
M2C_UNK func_800AE2A4();                      /* extern */
s32 func_800B14B0(); /* extern */
s32 func_800B1BEC();        /* extern */
extern M2C_UNK D_800AE090;

typedef struct S_800AE1AC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    s32 unk_2C;
} S_800AE1AC_0;   /* temp_s0 in func_800AE1AC */

typedef struct S_800AE1AC_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800AE1AC_1;   /* var_s1 in func_800AE1AC */

/* Allocate and initialize an object with two resources, cleaning up if either fails. */
void *func_800AE1AC(M2C_UNK unused, s32 primary_param, s32 secondary_param, s32 shared_param) {
    s32 second_resource;
    S_800AE1AC_0 *state;
    void *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_20 = shared_param;
        state->unk_18 = primary_param;
        state->unk_1C = secondary_param;
        state->unk_14 = 6;
        func_800ADFE8(state);
        ((S_800AE1AC_1 *)object)->unk_10 = &D_800AE090;
        state->unk_28 = func_800B14B0(object, state->unk_04, state->unk_08, state->unk_0C, state->unk_10, state->unk_20, primary_param);
        second_resource = func_800B1BEC(object, 0x48, -0xC);
        state->unk_2C = second_resource;
        if ((state->unk_28 == 0) || (second_resource == 0)) {
            func_800AE2A4(state);
            object = NULL;
        }
        func_800AE0F4(state);
    }
    return object;
}
