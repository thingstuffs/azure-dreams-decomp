#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_80023194_0 {
    u8 pad_00[0x8CC];
    s32 * unk_8CC;
} S_80023194_0;   /* var_s0 in func_80023194 */

/* Processes the values referenced by five consecutive record entries. */
void func_80023194(void *record) {
    s32 *value_ptr;
    s32 entry_index;
    void *entry_cursor;

    entry_index = 0;
    entry_cursor = record;
    do {
        value_ptr = ((S_80023194_0 *)entry_cursor)->unk_8CC;
        entry_cursor += 4;
        entry_index += 1;
        func_8004E994(*value_ptr);
    } while (entry_index < 5);
}
