#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B09EC();                 /* extern */

typedef struct S_800B17E4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17E4_0;   /* temp_a0 in func_800B17E4 */

/* Pass the object's data at offset 0x20 and its unk_08 value to func_800B09EC. */
void func_800B17E4(s32 object_addr) {
    S_800B17E4_0 *data;

    data = object_addr + 0x20;
    func_800B09EC(data, data->unk_08);
}
