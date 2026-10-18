#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


s32 record_check_returned();                   /* extern */
s32 func_80018824(void *, s32);
extern M2C_UNK D_8001B218;
extern s32 D_8001B318;

/* Prepares D_8001B218, passes it to the active object's callback, and saves the result. */
void prepare_passes_active_object_callback(void) {
    func_80018824(&D_8001B218, 0x100);
    record_check_returned(&D_8001B218);
    D_8001B318 = D_80016000->unk_20->callback_068(0, 0, 1, &D_8001B218);
}
