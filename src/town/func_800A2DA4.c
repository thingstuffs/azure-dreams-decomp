#include "common.h"
#include "m2c_compat.h"

s32 func_800A027C();                     /* extern */
void *func_800A04A8();                              /* extern */
M2C_UNK func_800A04B4();                            /* extern */

typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;   /* temp_v0 in func_800A0504 */

void func_800A0504(s32 arg0) {
    u8 temp_v1;
    S_800A0504_0 *temp_v0;

    temp_v0 = func_800A04A8();
    temp_v1 = temp_v0->unk_01;
    if ((temp_v1 != 0) && (temp_v1 != 0x13) && (func_800A027C(temp_v0, arg0) != 0)) {
        func_800A04B4();
    }
}
