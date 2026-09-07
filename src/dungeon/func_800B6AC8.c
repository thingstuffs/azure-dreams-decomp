#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_800BC1B4;

typedef struct S_800BC228_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800BC228_0;   /* temp_v0 in func_800BC228 */

void func_800BC228(s16 arg0) {
    S_800BC228_0 *temp_v0;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800BC1B4;
        temp_v0->unk_2C = arg0;
    }
}
