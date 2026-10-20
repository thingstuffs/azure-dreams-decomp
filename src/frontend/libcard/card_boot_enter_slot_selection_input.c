#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025B60_0 {
    s32 * unk_00;
} S_80025B60_0;   /* arg0 in card_boot_enter_slot_selection_input; pointer addresses record offset 0x10 */


void card_boot_recheck_selected_channel(void);                            /* extern */
void card_boot_refresh_five_slot_selection(void *);                            /* extern */
extern M2C_UNK D_8002593C;

/* Update the record, run the shared follow-up, and install its next table. */
void card_boot_enter_slot_selection_input(void *record_data) {
    card_boot_refresh_five_slot_selection(record_data);
    card_boot_recheck_selected_channel();
    ((S_80025B60_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_8002593C;
}
