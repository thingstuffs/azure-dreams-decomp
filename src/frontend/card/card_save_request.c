/* Set and initialize the memory card save menu request. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"


/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80026720_0 {
    u8 pad_00[0x20];
    void *request;
} S_80026720_0;   /* arg0 in card_boot_set_save_menu_request */

/* Stores the supplied value in the object's field at offset 0x20. */

void card_boot_set_save_menu_request(S_80026720_0 *object, void *value) {
    object->request = value;
}

/* Set the object's field at offset 0x20 to the supplied value. */
void card_boot_initialize_save_menu_request(void *object, void *value) {
    card_boot_set_save_menu_request(object, value);
}
