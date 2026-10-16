#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void townReleaseLshopEntry(s32);
/* Pass the value to townReleaseLshopEntry, then call townCompactLshopEntryList. */
void townRefreshLshopEntryList(s32 value) {
    townReleaseLshopEntry(value);
    townCompactLshopEntryList();
}
