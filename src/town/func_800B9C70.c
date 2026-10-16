#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeBuildingRegionResources();                            /* extern */

/* Updates the active entries through townInitializeBuildingRegionResources. */
void townUpdateActiveBuildingEntries(void) {
    townInitializeBuildingRegionResources();
}
