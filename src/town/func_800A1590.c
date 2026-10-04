#include "common.h"
#include "m2c_compat.h"

void func_8008F294();            /* extern */
void func_8008F664();            /* extern */
void func_8009EC70(); /* extern */

typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;   /* arg0 in func_8009ECF0 */

/* Run both updates, decrement the countdown, and check for completion. */
void func_8009ECF0(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx) {
    u16 countdown;

    func_8008F294(update_ctx, update_data);
    func_8008F664(update_ctx, update_data);
    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        func_8009EC70(state, update_ctx, update_data, finish_ctx);
    }
}
