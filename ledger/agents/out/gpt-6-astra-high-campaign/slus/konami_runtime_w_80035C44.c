#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035C44_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035C44_0;   /* arg1 in func_80035C44 */

typedef struct S_80035C44_1 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_80035C44_1;   /* arg0 in func_80035C44 */


extern M2C_UNK func_80035C80;

/* Advance progress by 16, clamp it to 64, and switch handlers when it exceeds 64. */
void func_80035C44(S_80035C44_1 *state, S_80035C44_0 *progress) {
    u16 next_value;

    next_value = progress->unk_02 + 0x10;
    progress->unk_02 = next_value;
    if ((s16) next_value >= 0x41) {
        progress->unk_02 = 0x40U;
        state->unk_68 = &func_80035C80;
    }
}
