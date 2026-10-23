/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 scene_captured_value;
extern s32 scene_captured_flags;
extern s32 D_00003FBC[];
extern s32 D_000045F8;
extern s32 D_00001598[];

extern s32 set_flag_entry_has_bit(s32 index, s32 mode);

/* Picks the selected table value (or a fixed table's address) and returns it plus the global offset after a mode-one call. */
s32 get_table_value_plus_offset(void) {
    s32 held;

    if (scene_captured_flags == 0) {
        held = D_00003FBC[scene_captured_value * 8];
    } else {
        held = (s32)&D_00001598[0];
    }
    set_flag_entry_has_bit(scene_captured_value, 1);
    return held + D_000045F8;
}
