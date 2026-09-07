#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_800B7B8C;

typedef struct S_800B8170_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
    s16 unk_22;
} S_800B8170_0;   /* temp_v0 in func_800B8170 */

void func_800B8170(void) {
    S_800B8170_0 *temp_v0;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800B7B8C;
        temp_v0->unk_20 = 0;
        temp_v0->unk_22 = 0;
    }
}
