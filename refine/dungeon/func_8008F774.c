#include "common.h"
#include "m2c_compat.h"

s16 func_80095464();    /* extern */
u16 func_800BCB04();                   /* extern */

typedef struct S_80094ED4_0 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80094ED4_0;   /* arg3 in func_80094ED4 */

typedef struct S_80094ED4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80094ED4_1;   /* arg2 in func_80094ED4 */

/* Call func_80095464 with a temporary tile-based value in unk_88. */
s16 func_80094ED4(s32 context, M2C_UNK data, S_80094ED4_1 *tile, S_80094ED4_0 *state) {
    s16 result;
    u16 saved_value;

    saved_value = state->unk_88;
    state->unk_88 = func_800BCB04((tile->unk_24 << 6) | 0x20, (tile->unk_25 << 6) | 0x20, (s16) (saved_value - 0x20));
    result = func_80095464(context, data, tile, state);
    state->unk_88 = saved_value;
    return result;
}
