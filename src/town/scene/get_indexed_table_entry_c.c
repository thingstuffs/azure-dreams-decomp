#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_choice_index[];
extern s32 scene_choice_values[];

/* Returns the table entry indexed by the first value in D_80019BB4. */
s32 get_indexed_table_entry(void) {
    return scene_choice_values[*scene_choice_index];
}
