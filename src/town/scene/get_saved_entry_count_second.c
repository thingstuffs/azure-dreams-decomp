#include "common.h"

extern u32 scene_money_adjustment;   /* saved entry count (set by store_calling_zero / store_run_operation_result) */

/* Returns the current value of scene_money_adjustment. */
u32 get_saved_entry_count(void) {
    return scene_money_adjustment;
}
