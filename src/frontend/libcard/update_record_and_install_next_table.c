#include "main.h"
#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800265B8[];

/* Update the record, run the shared follow-up, and install its next table. */
void update_record_and_install_next_table(void *record_data) {
    card_boot_highlight_selected_load_slot(record_data);
    card_boot_recheck_selected_channel();
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = D_800265B8;
}
