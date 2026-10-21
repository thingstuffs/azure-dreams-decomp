#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "main/data.h"

typedef struct S_8001F590_0 {
    s32 * unk_00;
} S_8001F590_0;   /* arg0 in card_dev_update_save_slot_selection; pointer addresses record offset 0x10 */

s32 func_80400908(void);

/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_save_slot_selection(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    func_80400908();
    ((S_8001F590_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406368;
}
