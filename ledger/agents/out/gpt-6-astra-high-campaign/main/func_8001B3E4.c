#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001B3E4_0 {
    u16 unk_00;
} S_8001B3E4_0;   /* arg0 in func_8001B3E4; pointer addresses record offset 0x2 */


M2C_UNK func_80047938(void *, s32, s32);                            /* extern */
M2C_UNK func_804024A4();                      /* extern */

/* Run the object update and invoke its follow-up when flag 0x2000 is set. */
void func_8001B3E4(void *object_data, s32 first_value, s32 second_value) {
    u16 object_flags;
    func_80047938(object_data, first_value, second_value);
    object_flags = ((S_8001B3E4_0 *)((u8 *)object_data - 0x2))->unk_00;
    object_data = (s8 *) object_data - 0x20;
    if (object_flags & 0x2000) {
        func_804024A4(object_data);
    }
}
