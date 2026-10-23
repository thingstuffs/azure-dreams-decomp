#include "common.h"
#include "records/Rec_func_80036210_arg0.h"

#include "common.h"
#include "engine/window/message.h"
#include "slus/data.h"

typedef struct S_80035ABC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035ABC_0;   /* arg1 in shrink_window_extent_to_two */

/* Decreases the entry value by 16, clamping it to 2 and switching handlers below 2. */
void shrink_window_extent_to_two(Rec_func_80036210_arg0 *state, S_80035ABC_0 *entry) {
    u16 reduced_value;

    reduced_value = entry->unk_02 - 0x10;
    entry->unk_02 = reduced_value;
    if ((s16) reduced_value < 2) {
        entry->unk_02 = 2U;
        state->unk_68 = &display_sound_selection_and_prepare_playback;
    }
}
