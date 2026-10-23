#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 encounter_object_slots[3];

/* Tests the first or second encounter_object_slots entry for zero according to the selector. */
s32 is_encounter_overlay_absent(s32 use_second_word) {
    if (use_second_word != 0) {
        return encounter_object_slots[1] == 0;
    }
    return encounter_object_slots[0] == 0;
}
