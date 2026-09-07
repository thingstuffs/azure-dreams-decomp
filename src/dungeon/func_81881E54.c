#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800255DC;
extern M2C_UNK D_800CEEFC;

typedef struct S_80025654_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80025654_0;   /* temp_v0 in func_80025654 */

typedef struct S_80025654_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80025654_1;   /* temp_a0 in func_80025654 */

typedef struct S_80025654_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80025654_2;   /* arg0 in func_80025654 */

typedef struct S_80025654_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80025654_3;   /* temp_v1 in func_80025654 */

typedef struct S_80025654_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80025654_4;   /* arg1 in func_80025654 */

void *func_80025654(S_80025654_2 *arg0, S_80025654_4 *arg1) {
    S_80025654_1 *temp_a0;
    S_80025654_0 *temp_v0;
    S_80025654_3 *temp_v1;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800255DC;
        func_8004491C(temp_v0, &D_800CEEFC);
        temp_a0 = temp_v0->unk_08;
        temp_a0->unk_02 = (u16) arg0->unk_02;
        temp_a0->unk_06 = (u16) arg0->unk_06;
        temp_a0->unk_0A = (u16) arg0->unk_0A;
        temp_a0->unk_0E = (s16) (arg0->unk_02 - arg0->unk_0E);
        temp_a0->unk_12 = (s16) (arg0->unk_06 - arg0->unk_12);
        temp_a0->unk_16 = (s16) (arg0->unk_0A - arg0->unk_16);
        temp_v1 = temp_v0->unk_0C;
        temp_v1->unk_1C = (u16) arg1->unk_1C;
        temp_v1->unk_1E = (u16) arg1->unk_1E;
        temp_v1->unk_0C = (s32) arg1->unk_0C;
        temp_v1->unk_08 = (s32) arg1->unk_08;
        temp_v1->unk_14 = (u16) arg1->unk_14;
    }
    return temp_v0;
}
