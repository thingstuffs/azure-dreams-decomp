#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_801257C8_0 {
    u8 pad_00[0xA];
    s8 unk_0A;
} S_801257C8_0;   /* arg0 in townEnterCatalogGrid */


extern void townRefreshCatalogEntryGrid(S_801257C8_0 *);
/* Update the controller and set its state to one. */
void townEnterCatalogGrid(S_801257C8_0 *controller) {
    townRefreshCatalogEntryGrid(controller);
    controller->unk_0A = 1;
}
