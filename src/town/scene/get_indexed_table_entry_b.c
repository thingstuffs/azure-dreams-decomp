#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_choice_index[];
extern M2C_UNK D_80016550;

/* Returns the table entry selected by the current index. */
s32 get_indexed_table_entry(void) {
    return *(s32 *)((u8 *)&D_80016550 + ((*scene_choice_index) * 4));
}
