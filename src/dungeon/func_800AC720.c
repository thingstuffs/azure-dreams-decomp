#include "common.h"
#include "m2c_compat.h"

void upload_vram_row_and_cache(); /* extern */
extern u8 D_800DF068[];

typedef struct S_800B1E80_0 {
    u16 unk_00;
    u16 unk_02;
} S_800B1E80_0;   /* arg0 in advance_cyclic_panel_entry */

/* Advance the cyclic table index every four ticks and apply the selected entry. */
void advance_cyclic_panel_entry(S_800B1E80_0 *state) {
    u16 ticks_left;
    u16 entry_index;

    ticks_left = state->unk_00 - 1;
    state->unk_00 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        state->unk_00 = 4U;
        entry_index = state->unk_02 + 8;
        state->unk_02 = entry_index;
        if ((s16) entry_index >= 0x60) {
            state->unk_02 = 0U;
        }
        upload_vram_row_and_cache(((s16) state->unk_02 * 4) + D_800DF068, 0x7340, 1, 2);
    }
}
