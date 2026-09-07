#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80026FB0;
extern u8 D_80028808;
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;

typedef struct S_80027070_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80027070_0;   /* temp_v0 in func_80027070 */

typedef struct S_80027070_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80027070_1;   /* temp_v0_2 in func_80027070 */

typedef struct S_80027070_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80027070_2;   /* temp_a0 in func_80027070 */

typedef struct S_80027070_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027070_3;   /* temp_v1 in func_80027070 */

void *func_80027070(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    S_80027070_2 *temp_a0;
    void *temp_v0;
    S_80027070_1 *temp_v0_2;
    S_80027070_3 *temp_v1;

    temp_v0 = func_8003FD64(0x12, &D_80083498);
    if (temp_v0 != NULL) {
        ((S_80027070_0 *)temp_v0)->unk_10 = &D_80026FB0;
        func_8004491C(temp_v0, &D_80045340);
        temp_v0_2 = ((S_80027070_0 *)temp_v0)->unk_08;
        temp_v0_2->unk_02 = arg0;
        temp_v0_2->unk_06 = arg1;
        temp_v0_2->unk_0A = arg2;
        temp_a0 = ((S_80027070_0 *)temp_v0)->unk_0C;
        temp_a0->unk_08 = (void *) ((arg3 * 0xC) + &D_80028808);
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        temp_a0->unk_10 = 0x20;
        temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0xC);
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_04 = arg4;
        temp_v1->unk_66 = 0x1C;
    }
    return temp_v0;
}
