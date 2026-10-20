#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035C44_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035C44_0;   /* arg1 in grow_window_extent_to_sixty_four */

typedef struct S_80035C44_1 {
    u8 pad_00[0x68];
    s32 * unk_68;
} S_80035C44_1;   /* arg0 in grow_window_extent_to_sixty_four */


extern M2C_UNK fade_and_shrink_window_on_value_change;

/* Advance progress by 16, clamp it to 64, and switch handlers when it exceeds 64. */
void grow_window_extent_to_sixty_four(S_80035C44_1 *state, S_80035C44_0 *progress) {
    u16 next_value;

    next_value = progress->unk_02 + 0x10;
    progress->unk_02 = next_value;
    if ((s16) next_value >= 0x41) {
        progress->unk_02 = 0x40U;
        state->unk_68 = &fade_and_shrink_window_on_value_change;
    }
}
