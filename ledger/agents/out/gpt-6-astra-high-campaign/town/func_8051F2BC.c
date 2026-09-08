#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800160D4(s32);                            /* extern */
M2C_UNK func_80016104();     /* extern */
extern M2C_UNK D_80018E80;

/* Initializes the requested entry, then processes it with the shared data and supplied value. */
void func_80016ABC(s32 entry_id, M2C_UNK unused, M2C_UNK value) {
    func_800160D4(entry_id);
    func_80016104(&D_80018E80, entry_id, value);
}
