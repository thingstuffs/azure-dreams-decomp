#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800DBD5C(); /* extern */
extern M2C_UNK D_800814A8;

typedef struct S_800DC5B4_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_800DC5B4_0;   /* *state in func_800DC5B4 */

typedef struct S_800DC5B4_1 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_800DC5B4_1;   /* arg0 in func_800DC5B4 */

void func_800DC5B4(S_800DC5B4_1 *arg0) {
    u8 temp_a0;
    void **state;

    state = (void **)&D_800814A8;
    temp_a0 = ((S_800DC5B4_0 *)(*state))->unk_11;
    if (temp_a0 != arg0->unk_30) {
        func_800DBD5C(temp_a0, arg0->unk_30, 2, 0x18A, 0x190, 0);
        arg0->unk_30 = ((S_800DC5B4_0 *)(*state))->unk_11;
    }
}

/* MECHANISM: The state address stays held in s1 across the call while arg0 stays in s0,
   yielding the retail 0x28 frame and s1/s0/ra save contract; the six-argument call
   supplies the two stack slots. 2.7.2-cdk-G0 closes the residual code motion exactly. */
