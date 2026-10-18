#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"
#include "m2c_compat.h"

M2C_UNK zero_words();          /* extern */
void update_packed_map_levels();                            /* extern */

/* Process the 0x200-byte global buffer and run the follow-up routine. */
void process_global_buffer_and_submit(void) {
    zero_words(D_800E50A8, 0x200);
    update_packed_map_levels();
}
