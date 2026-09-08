#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038368_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x4];
    u16 unk_18;
} S_80038368_0;   /* arg0 in func_80038368 */


extern M2C_UNK func_80038A10;

/* Decrements the countdown and switches the handler when the signed count reaches zero or below. */
void func_80038368(S_80038368_0 *state) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_18 - 1;
    state->unk_18 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        state->unk_10 = &func_80038A10;
    }
}
