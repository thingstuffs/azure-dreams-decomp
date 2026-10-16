#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"
#include "m2c_compat.h"

M2C_UNK zeroWords();          /* extern */
void dungeonUpdatePackedMapLevels();                            /* extern */

/* Process the 0x200-byte global buffer and run the follow-up routine. */
void dungeonProcessGlobalBufferAndSubmit(void) {
    zeroWords(D_800E50A8, 0x200);
    dungeonUpdatePackedMapLevels();
}
