#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
void *func_8009C390();       /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A7C0C;

typedef struct S_800A7B98_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800A7B98_0;   /* temp_v0 in func_800A7B98 */

typedef struct S_800A7B98_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_1;   /* temp_v1 in func_800A7B98 */

typedef struct S_800A7B98_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_2;   /* arg2 in func_800A7B98 */

typedef struct S_800A7B98_3 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800A7B98_3;   /* temp_s0 in func_800A7B98 */

void func_800A7B98(s32 arg0, M2C_UNK arg1, S_800A7B98_2 *arg2) {
    S_800A7B98_3 *temp_s0;
    void *temp_v0;
    S_800A7B98_1 *temp_v1;

    temp_v0 = func_8009C390(arg0 - 0x20, arg1, &D_800A7C0C, 0);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        temp_v1 = ((S_800A7B98_0 *)temp_v0)->unk_0C;
        temp_v1->unk_08 = (s32) arg2->unk_08;
        temp_v1->unk_14 = (u16) arg2->unk_14;
        func_80033CD8(temp_s0, &D_80045340);
        temp_s0->unk_6C = 5;
    }
}
