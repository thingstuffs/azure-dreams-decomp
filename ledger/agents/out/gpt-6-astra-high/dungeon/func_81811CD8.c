#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026CD8_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
    s32 * unk_10;
} S_80026CD8_0;   /* arg0 in func_80026CD8 */

/* Clear both values referenced by the state. */
void func_80026CD8(S_80026CD8_0 *state) {
    *state->unk_0C = 0;
    *state->unk_10 = 0;
}
