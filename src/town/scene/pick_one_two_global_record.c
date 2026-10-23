#include "common.h"

/* TOWN file 0x3EAB90 (rowbase sweep_3EA000, delta 0x7FC31000; the local `j` lands inside this
 * function only at that base).  Same shape as the matched selector select_record_by_mode
 * (src/town/func_8032BAA4.c): reads only the third argument.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 scene_mode_event_data[];
extern u8 scene_event_data[];

/* Returns scene_event_data for selector four or scene_mode_event_data for all other selectors. */
u8 *pick_one_two_global_records(s32 unused_a, s32 unused_b, s32 selector) {
    if (selector == 4) {
        return scene_event_data;
    }
    return scene_mode_event_data;
}
