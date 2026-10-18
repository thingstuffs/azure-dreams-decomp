#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void card_boot_set_slot_menu_request();                            /* extern */

/* Set the object's field at offset 0x20 to the supplied value. */
void card_boot_initialize_slot_menu_request(void *object, s32 value) {
    card_boot_set_slot_menu_request(object, value);
}
