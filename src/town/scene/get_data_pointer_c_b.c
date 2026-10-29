#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80016A0C;

/* Returns the address of D_80016A0C. */
s32 *get_data_pointer_16_a_0_c(void) {
    return &D_80016A0C;
}
