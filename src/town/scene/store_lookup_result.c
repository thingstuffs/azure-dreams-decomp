#include "common.h"
#include "shared/town_dispatch_data.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016B1C(void *entry, s32 callback_mode);              /* extern */
extern s32 town_stored_amount;

/* Store the result of calling func_80016B1C on D_80018AE8. */
void store_lookup_result(void) {
    town_stored_amount = func_80016B1C(&D_80018AE8, 0);
}
