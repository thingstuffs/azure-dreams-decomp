#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025514();                         /* extern */
M2C_UNK func_800255FC();               /* extern */
s32 func_80026CCC();                             /* extern */
s32 strcmp();                     /* extern */

typedef struct S_8002573C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_8002573C_0;   /* arg0 in func_8002573C */

typedef struct S_8002573C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
} S_8002573C_1;   /* temp_s2 in func_8002573C */

s32 func_8002573C(void *arg0) {
    s32 temp_v0;
    S_8002573C_1 *temp_s2;

    temp_s2 = ((S_8002573C_0 *)arg0)->unk_14 + 0x20;
    temp_v0 = func_80026CCC(temp_s2->unk_28);
    if (strcmp(temp_v0, arg0 + 0x78) != 0) {
        func_800255FC(temp_v0, ((S_8002573C_0 *)arg0)->unk_0C, temp_s2->unk_1C);
    }
    func_80025514(((S_8002573C_0 *)arg0)->unk_14);
    return 1;
}
