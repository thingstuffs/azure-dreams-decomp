#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025C58();                         /* extern */

typedef struct S_80026314_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x40];
    s32 unk_54;
} S_80026314_0;   /* temp_v1 in func_80026314 */

void func_80026314(s32 arg0) {
    S_80026314_0 *temp_v1;

    temp_v1 = arg0 + 0x20;
    temp_v1->unk_10 = 1;
    func_80025C58(temp_v1->unk_54);
}
