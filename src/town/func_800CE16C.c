#include "common.h"
#include "m2c_compat.h"

M2C_UNK D_800CB9B8();               /* extern (function symbol used as callback) */
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();              /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern s32 D_800D68B0[];


typedef struct S_800CB8CC_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    M2C_UNK (*unk_10)(void *, s32, void *);
} S_800CB8CC_0;   /* temp_v0 in func_800CB8CC */

typedef struct S_800CB8CC_1 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x38];
    s32 unk_9C;
} S_800CB8CC_1;   /* temp_s1 in func_800CB8CC */

typedef struct S_800CB8CC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800CB8CC_2;   /* temp_s0 in func_800CB8CC */

s32 func_800CB8CC(s32 arg0, s32 arg1) {
    s32 temp_s2;
    S_800CB8CC_2 *temp_s0;
    S_800CB8CC_1 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_s1 = temp_v0 + 0x20;
    temp_s2 = ((S_800CB8CC_0 *)temp_v0)->unk_08;
    temp_s0 = ((S_800CB8CC_0 *)temp_v0)->unk_0C;
    temp_s1->unk_9C = arg0;
    ((S_800CB8CC_0 *)temp_v0)->unk_10 = D_800CB9B8;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    temp_s0->unk_0C = 0x808080;
    temp_s1->unk_60 = arg1;
    temp_s0->unk_08 = D_800D68B0[arg1];
    func_8004491C(temp_v0, &D_80045340);
    ((S_800CB8CC_0 *)temp_v0)->unk_10(temp_s1, temp_s2, temp_s0);
    return (s32)temp_v0;
}
