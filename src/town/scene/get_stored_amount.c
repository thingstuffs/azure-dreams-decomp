#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 town_stored_amount;

/* Returns the value of D_80018AE0. */
s32 get_stored_amount(void) {
    return town_stored_amount;
}
