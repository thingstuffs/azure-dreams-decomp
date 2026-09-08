#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80051FBC();                         /* extern */

typedef struct S_8001C3EC_0 {
    u8 pad_00[0x68C];
    s32 * unk_68C;
} S_8001C3EC_0;   /* var_s0 in func_8001C3EC */

/* Pass each of four referenced values to func_80051FBC. */
void func_8001C3EC(void *object) {
    s32 *value_ptr;
    s32 slot_index;
    void *slot_cursor;

    slot_index = 0;
    slot_cursor = object;
    do {
        value_ptr = ((S_8001C3EC_0 *)slot_cursor)->unk_68C;
        slot_cursor += 4;
        slot_index += 1;
        func_80051FBC(*value_ptr);
    } while (slot_index < 4);
}
