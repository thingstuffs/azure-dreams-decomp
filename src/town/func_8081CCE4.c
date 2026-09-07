#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80026D28;

typedef struct S_80026CE4_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x5E];
    s16 unk_72;
} S_80026CE4_0;   /* temp_v0 in func_80026CE4 */

void func_80026CE4(s16 arg0) {
    S_80026CE4_0 *temp_v0;

    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_80026D28;
        temp_v0->unk_72 = arg0;
    }
}
