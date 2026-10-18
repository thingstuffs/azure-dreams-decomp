#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001F590_0 {
    s32 * unk_00;
} S_8001F590_0;   /* arg0 in func_8001F590; pointer addresses record offset 0x10 */


void card_devkit_refresh_save_slot_selection();                            /* extern */
s32 func_80400908(void);
extern M2C_UNK D_80406368;

/* Process the record data, run the follow-up routine, and set its header pointer. */
void func_8001F590(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    func_80400908();
    ((S_8001F590_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406368;
}
