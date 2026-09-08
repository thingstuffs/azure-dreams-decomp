#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024A50();                      /* extern */
M2C_UNK func_80024E44();                      /* extern */

typedef struct S_80024F3C_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
} S_80024F3C_0;   /* temp_s0 in func_80024F3C */

/* Stores two object values and runs the associated update routines. */
void func_80024F3C(s32 object_addr, s32 value_7c, s32 value_80) {
    S_80024F3C_0 *object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        object_data->unk_7C = value_7c;
        object_data->unk_80 = value_80;
        func_80024E44(object_data);
        func_80024A50(object_data);
    }
}
