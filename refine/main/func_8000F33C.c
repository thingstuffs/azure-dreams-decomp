#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E264();                /* extern */
M2C_UNK func_8004E884();                     /* extern */

/* Processes consecutive 12-byte entries starting at the requested index. */
void func_8002233C(s32 entry_base, s32 start_index, s32 entry_count) {
    s32 entry_index;
    s32 entry_addr;

    func_8004E884(entry_base, 1);
    entry_addr = entry_base + (start_index * 0xC);
    entry_index = 0;
    if (entry_count > 0) {
        do {
            func_8004E264(entry_addr, 0);
            entry_index += 1;
            entry_addr += 0xC;
        } while (entry_index < entry_count);
    }
}
