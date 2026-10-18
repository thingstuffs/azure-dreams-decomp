#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001C374;
/* Sets the value stored in D_8001C374. */
void set_global_entry_value(s32 value) {
    D_8001C374 = value;
}
