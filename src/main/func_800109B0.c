#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_800239B0_0 {
    u8 pad_00[0x1D8];
    s32 * unk_1D8;
} S_800239B0_0;   /* var_s0 in func_800239B0 */

/* Processes the values referenced by three consecutive record entries. */
void func_800239B0(void *record) {
    s32 *value_ptr;
    s32 entry_index;
    void *entry_cursor;

    entry_index = 0;
    entry_cursor = record;
    do {
        value_ptr = ((S_800239B0_0 *)entry_cursor)->unk_1D8;
        entry_cursor += 4;
        entry_index += 1;
        func_8004E994(*value_ptr);
    } while (entry_index < 3);
}
