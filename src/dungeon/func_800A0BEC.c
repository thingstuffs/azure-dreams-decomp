#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800A6194;
extern M2C_UNK D_800A624C;

typedef struct S_800A634C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800A634C_0;   /* temp_v0 in func_800A634C */

typedef struct S_800A634C_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A634C_1;   /* temp_v1 in func_800A634C */

void *func_800A634C(s16 arg0) {
    void *temp_v0;
    S_800A634C_1 *temp_v1;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        ((S_800A634C_0 *)temp_v0)->unk_10 = &D_800A6194;
        func_8004491C(temp_v0, &D_800A624C);
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_08 = 8;
        temp_v1->unk_0C = arg0;
    }
    return temp_v0;
}
