#include "common.h"

extern u32 D_800188C8;   /* saved entry count (set by store_calling_zero / func_8001679C) */

/* Return the saved entry count. */
u32 get_saved_entry_count(void) {
    return D_800188C8;
}
