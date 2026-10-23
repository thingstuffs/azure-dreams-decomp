#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 encounter_object_slots[3];

/* Returns whether the selected word in D_80175D58 is zero. */
s32 is_encounter_overlay_absent(s32 use_second_word) {
    if (use_second_word != 0) {
        return encounter_object_slots[1] == 0;
    }
    return encounter_object_slots[0] == 0;
}
