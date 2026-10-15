/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

void func_80093D48();      

typedef struct S_80090DF0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80090DF0_0;   

void func_80090A74(s32 *, S_80090DF0_0 *, s32);

void func_80090E78(s32 *value, S_80090DF0_0 *state, s32 context) {
    s32 old_value;

    old_value = *value;
    func_80090A74(value, state, context);
    if ((old_value == *value) && (state->unk_0C == 0) && (state->unk_10 == 0)) {
        func_80093D48(value, state, context);
    }
}
