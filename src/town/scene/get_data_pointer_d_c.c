#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001D0C0;

/* Return the address of D_8001D0C0. */
s32 *get_data_pointer_1_d_0_c_0(void) {
    return &D_8001D0C0;
}
