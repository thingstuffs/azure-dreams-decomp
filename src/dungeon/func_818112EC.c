#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025C4C();                         /* extern */

typedef struct S_800262EC_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x40];
    s32 unk_54;
} S_800262EC_0;   /* temp_v0 in func_800262EC */

/* Clears an object data field and passes its stored value to func_80025C4C. */
void func_800262EC(s32 object_addr) {
    S_800262EC_0 *object_data;

    object_data = object_addr + 0x20;
    object_data->unk_10 = 0;
    func_80025C4C(object_data->unk_54);
}
