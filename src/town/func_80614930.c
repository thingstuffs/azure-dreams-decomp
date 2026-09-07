#include "common.h"
#include "m2c_compat.h"

typedef struct S_80614930_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80614930_0;   /* D_80016000 in func_80614930 */

typedef struct S_80614930_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80614930_1;   /* temp_v1 in func_80614930 */

typedef struct S_80614930_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80614930_2;   /* temp_v1_2 in func_80614930 */


extern S_80614930_0 *D_80016000;

void func_80614930(void) {
    S_80614930_1 *temp_v1;
    S_80614930_2 *temp_v1_2;

    temp_v1 = D_80016000->unk_1C;
    temp_v1->unk_04 = (s32) (temp_v1->unk_04 + temp_v1->unk_10);
    temp_v1_2 = D_80016000->unk_1C;
    temp_v1_2->unk_08 = (s32) (temp_v1_2->unk_08 + temp_v1_2->unk_14);
}
