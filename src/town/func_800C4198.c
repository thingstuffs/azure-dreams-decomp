#include "common.h"
#include "m2c_compat.h"

M2C_UNK reserve_twch_load();                     /* extern */

/* Calls reserve_twch_load for IDs 6 and 3. */
void reserve_movie_resources_for_ids_6_and_3(void) {
    reserve_twch_load(6);
    reserve_twch_load(3);
}
