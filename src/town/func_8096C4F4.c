#include "common.h"
#include "m2c_compat.h"

typedef struct S_8012498C_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_8012498C_0;   /* arg0 in func_8012498C */

/* Initialize state with its byte field set to one and both 16-bit fields cleared. */
void func_8012498C(S_8012498C_0 *state) {
    state->unk_0A = 1;
    state->unk_04 = 0;
    state->unk_06 = 0;
}
