#include "common.h"
#include "m2c_compat.h"

s32 func_800B3C04(s32);                                /* extern */
M2C_UNK func_800B3D04();                    /* extern */

/* Processes the entry when its lookup returns a valid index. */
void func_800B3D84(s32 entry_id) {
    s32 entry_index;

    entry_index = func_800B3C04(entry_id);
    if (entry_index != -1) {
        func_800B3D04(entry_id, entry_index);
    }
}
