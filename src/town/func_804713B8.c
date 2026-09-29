#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_804713B8_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_804713B8_1;   /* state in func_804713B8 */


extern s32 D_8001B210;

/* Adds the global increment to the current state's accumulator. */
void func_804713B8(void) {
    S_804713B8_1 *state;

    state = D_80016000->unk_38;
    state->unk_2D5C = (s32) (state->unk_2D5C + D_8001B210);
}
