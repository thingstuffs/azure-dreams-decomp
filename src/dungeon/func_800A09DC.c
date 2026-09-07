#include "common.h"
#include "m2c_compat.h"

s32 func_8003FC64();                         /* extern */
M2C_UNK func_8004491C();              /* extern */
extern M2C_UNK D_800A5FC0;

typedef struct S_800A613C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A613C_0;   /* temp_v1 in func_800A613C */

s32 func_800A613C(void) {
    s32 temp_v0;
    S_800A613C_0 *temp_v1;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != 0) {
        func_8004491C(temp_v0, &D_800A5FC0);
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_08 = 6;
        temp_v1->unk_0C = 0x10;
    }
    return temp_v0;
}
