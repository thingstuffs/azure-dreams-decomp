#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_80093D48();      /* extern */

typedef struct S_80090DF0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80090DF0_0;   /* arg1 in func_80090DF0 */


M2C_UNK func_80090A74(s32 *, S_80090DF0_0 *, M2C_UNK);
/* Runs the fallback if the value is unchanged and both state fields are zero. */
void func_80090DF0(s32 *value, S_80090DF0_0 *state, M2C_UNK context) {
    s32 old_value;

    old_value = *value;
    func_80090A74(value, state, context);
    if ((old_value == *value) && (state->unk_0C == 0) && (state->unk_10 == 0)) {
        func_80093D48(value, state, context);
    }
}
