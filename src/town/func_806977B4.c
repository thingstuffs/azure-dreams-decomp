#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_806977B4_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_806977B4_1;   /* temp_a0 in func_806977B4 */


extern s32 D_80018AE0;

/* Add D_80018AE0 to the current state's accumulator. */
void func_806977B4(void) {
    S_806977B4_1 *state;

    state = D_80016000->unk_38;
    state->unk_2D5C = (s32) (state->unk_2D5C + D_80018AE0);
}
