#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"

extern void zero_words(int *dst, int count);          /* extern */
void update_packed_map_levels();                            /* extern */

/* Process the 0x200-byte global buffer and run the follow-up routine. */
void process_global_buffer_and_submit(void) {
    zero_words(D_800E50A8, 0x200);
    update_packed_map_levels();
}
