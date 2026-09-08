#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039A88_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A88_0;   /* arg0 in func_80039A88 */


s32 func_80053EF0();                         /* extern */

/* Clear the script state and rewind one byte while the runtime status is nonzero. */
void func_80039A88(S_80039A88_0 *state) {
    if (func_80053EF0(4) != 0) {
        state->unk_10 = 0;
        state->unk_1C = (s32) (state->unk_1C - 1);
    }
}
