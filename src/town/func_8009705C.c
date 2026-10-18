#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800933FC;
/* Stores the address of D_800933FC in the output pointer. */
void set_item_selection_data_pointer(s32 **out_ptr) {
    *out_ptr = &D_800933FC;
}
