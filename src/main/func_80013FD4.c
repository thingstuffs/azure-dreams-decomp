#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80026FD4_0 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_80026FD4_0;

/* Stores a value in the object's embedded state and processes that state. */
void cardBootSetPairedChoiceSelection(s32 object_addr, s32 value) {
    S_80026FD4_0 *state;

    state = object_addr + 0x20;
    state->unk_24 = value;
    cardBootRefreshPairedChoiceLabels(state);
}
