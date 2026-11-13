#include "common.h"

#include "engine/graphics.h"
#include "engine/town.h"
void town_seq_reserve(s16 sequence_effect, s16 sequence_id);            /* extern */

/* Run the runtime sequence ending in town_seq_reserve(0x2B, 0x200). */
void init_town_runtime_with_sequence(void) {
    load_town_sprite_bundle_and_clear_alternates();
    init_town_runtime_objects();
    town_seq_reserve(0x2B, 0x200);
}
