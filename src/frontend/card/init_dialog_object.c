#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void position_linked_dialog_and_bind_object_data();                         /* extern */
void *initialize_four_paired_drawing_records();                    /* extern */

/* Process the embedded data at offset 0x24, then the containing object. */
void init_dialog_object(s32 object_addr) {
    initialize_four_paired_drawing_records(object_addr + 0x24, object_addr);
    position_linked_dialog_and_bind_object_data(object_addr);
}
