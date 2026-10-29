#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_801257C8_0 {
    u8 pad_00[0xA];
    s8 unk_0A;
} S_801257C8_0;   /* arg0 in enter_catalog_grid */

/* Update the controller and set its state to one. */
void enter_catalog_grid(S_801257C8_0 *controller) {
    refresh_catalog_entry_grid(controller);
    controller->unk_0A = 1;
}
