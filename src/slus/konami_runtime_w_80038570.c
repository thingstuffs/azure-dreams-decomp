#include "common.h"

#include "common.h"

typedef struct S_80038570_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x13];
    s8 unk_27;
    u8 pad_28[0x5C];
    s8 unk_84;
} S_80038570_0;   /* arg0 in clear_two_state_fields */


extern s32 func_80038588;

/* Clear two state fields and set the next handler. */
void clear_two_state_fields(S_80038570_0 *state) {
    state->unk_27 = 0;
    state->unk_84 = 0;
    state->unk_10 = &func_80038588;
}
