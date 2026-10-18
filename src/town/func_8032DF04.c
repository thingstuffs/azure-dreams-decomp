#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001BE60;
/* Passes the address of D_8001BE60 to append_shop_entry. */
void pass_global_record_to_handler(void) {
    append_shop_entry(&D_8001BE60);
}
