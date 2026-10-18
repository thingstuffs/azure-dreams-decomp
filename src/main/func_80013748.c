#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026748_0 {
    s32 * unk_00;
} S_80026748_0;   /* arg0 in update_record_and_install_next_table; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800265B8[];
void card_boot_highlight_selected_load_slot(void *);                            /* extern */

/* Update the record, run the shared follow-up, and install its next table. */
void update_record_and_install_next_table(void *record_data) {
    card_boot_highlight_selected_load_slot(record_data);
    card_boot_recheck_selected_channel();
    ((S_80026748_0 *)((u8 *)record_data - 0x10))->unk_00 = D_800265B8;
}
