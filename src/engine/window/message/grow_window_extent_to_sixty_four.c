#include "common.h"
#include "records/Rec_func_80036210_arg0.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/window/message.h"
#include "slus/data.h"
#include "engine/window.h"

typedef struct S_80035C44_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035C44_0;   /* arg1 in grow_window_extent_to_sixty_four */

/* Advance progress by 16, clamp it to 64, and switch handlers when it exceeds 64. */
void grow_window_extent_to_sixty_four(Rec_func_80036210_arg0 *state, S_80035C44_0 *progress) {
    u16 next_value;

    next_value = progress->unk_02 + 0x10;
    progress->unk_02 = next_value;
    if ((s16) next_value >= 0x41) {
        progress->unk_02 = 0x40U;
        state->unk_68 = &fade_and_shrink_window_on_value_change;
    }
}
