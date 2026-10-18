#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void release_lshop_entry(s32);
/* Pass the value to release_lshop_entry, then call compact_lshop_entry_list. */
void refresh_lshop_entry_list(s32 value) {
    release_lshop_entry(value);
    compact_lshop_entry_list();
}
