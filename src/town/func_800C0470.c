#include "common.h"
#include "m2c_compat.h"

extern void *func_8003FC64(s32 a0);
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;

typedef struct S_800BDBD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDBD0_0;   /* temp_v0 in func_800BDBD0 */

typedef struct S_800BDBD0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BDBD0_1;   /* temp_v1 in func_800BDBD0 */

typedef struct S_800BDBD0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDBD0_2;   /* temp_v1_2 in func_800BDBD0 */

typedef struct S_800BDBD0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDBD0_3;   /* arg0 in func_800BDBD0 */

void *func_800BDBD0(S_800BDBD0_3 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    S_800BDBD0_0 *temp_v0;
    S_800BDBD0_1 *temp_v1;
    S_800BDBD0_2 *temp_v1_2;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        func_8004491C(temp_v0, &D_80046398);
        temp_v1 = temp_v0->unk_0C;
        temp_v0->unk_10 = arg1;
        temp_v1->unk_1A = (s16) arg2;
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_20 = 0x1000;
        temp_v1->unk_0C = 0x808080;
        temp_v1->unk_08 = arg3;
        temp_v1_2 = temp_v0->unk_08;
        temp_v1_2->unk_00 = arg0->unk_00;
        temp_v1_2->unk_04 = arg0->unk_04;
        temp_v1_2->unk_08 = arg0->unk_08;
    }
    return temp_v0;
}
