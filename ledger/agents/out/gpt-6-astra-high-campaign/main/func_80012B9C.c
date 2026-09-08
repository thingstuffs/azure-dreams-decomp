#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025D34();                         /* extern */
M2C_UNK func_80027AFC();                /* extern */

typedef struct S_80025B9C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B9C_0;   /* arg0 in func_80025B9C */

/* Processes the object header and passes its stored value to func_80027AFC. */
void func_80025B9C(void *object_data) {
    func_80025D34(object_data - 0x20);
    func_80027AFC(((S_80025B9C_0 *)object_data)->unk_20, 0);
}
