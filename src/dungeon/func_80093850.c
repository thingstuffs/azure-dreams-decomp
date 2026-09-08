#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern M2C_UNK D_8001004C;

typedef struct S_80098FB0_0 {
    u8 pad_00[0x249];
    u8 unk_249;
} S_80098FB0_0;   /* var_a0 in func_80098FB0 */

/* Find the start of the last contiguous run of zero entries. */
s32 func_80098FB0(void) {
    s8 *entry_address;
    s32 run_start;
    s32 shifted_index;
    s32 entry_index;

    run_start = -1;
    entry_index = 0x13;
    entry_address = (s8 *)0x8001004C;
for (;;) {
loop_1:
    if (((S_80098FB0_0 *)entry_address)->unk_249 == 0) {
        run_start = entry_index;
    } else if (run_start >= 0) {
        break;
    }
    entry_index -= 1;
    entry_address -= 4;
    if (entry_index < 0) {
        break;
    }
    goto loop_1;
}
done:
    shifted_index = run_start << 0x10;
    return shifted_index >> 0x10;
}
