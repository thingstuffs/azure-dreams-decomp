#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003571C_0 {
    void * unk_00;
    u8 pad_04[0x64];
    M2C_UNK * unk_68;
} S_8003571C_0;   /* arg0 in func_8003571C */

typedef struct S_8003571C_1 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003571C_1;   /* temp_v0 in func_8003571C */

typedef struct S_8003571C_2 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003571C_2;   /* temp_v1 in func_8003571C */


extern M2C_UNK func_80035760;

/* Decreases the state field at offset 0x08 by 0xA0, clamping below zero and advancing the handler. */
void func_8003571C(S_8003571C_0 *object) {
    S_8003571C_1 *state;
    S_8003571C_2 *updated_state;

    state = object->unk_00;
    state->unk_08 = (u16) (state->unk_08 - 0xA0);
    updated_state = object->unk_00;
    if ((s16) updated_state->unk_08 < 0) {
        updated_state->unk_08 = 0U;
        object->unk_68 = &func_80035760;
    }
}
