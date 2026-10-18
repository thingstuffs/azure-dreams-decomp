#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001EAB4_0 {
    s32 * unk_00;
} S_8001EAB4_0;   /* arg0 in invoke_callback_with_zero; pointer addresses record offset 0x10 */


void card_devkit_refresh_save_slot_selection();                            /* extern */
extern M2C_UNK D_80406368;

/* Process the record data and set its preceding header pointer. */
void invoke_callback_with_zero(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    ((S_8001EAB4_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406368;
}
