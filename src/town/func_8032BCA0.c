#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK contains_record_value_in_byte_0();                     /* extern */

/* Calls contains_record_value_in_byte_0 with selector 0x10. */
void query_state_with_selector_10(void) {
    contains_record_value_in_byte_0(0x10);
}
