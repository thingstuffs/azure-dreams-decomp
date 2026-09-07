#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();    /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;

typedef struct S_800BDB20_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDB20_0;   /* temp_v0 in func_800BDB20 */

typedef struct S_800BDB20_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDB20_1;   /* temp_v1 in func_800BDB20 */

typedef struct S_800BDB20_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDB20_2;   /* arg0 in func_800BDB20 */

typedef struct S_800BDB20_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BDB20_3;   /* temp_a0 in func_800BDB20 */

void *func_800BDB20(S_800BDB20_2 *arg0, s32 arg1, M2C_UNK arg2) {
    S_800BDB20_3 *temp_a0;
    S_800BDB20_0 *temp_v0;
    S_800BDB20_1 *temp_v1;

    temp_v0 = func_8003FC64(0x132);
    if (temp_v0 != NULL) {
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = temp_v0->unk_0C;
        temp_v1 = temp_v0->unk_08;
        temp_v0->unk_10 = arg1;
        temp_v1->unk_00 = (s32) arg0->unk_00;
        temp_v1->unk_04 = (s32) arg0->unk_04;
        temp_v1->unk_08 = (s32) arg0->unk_08;
        temp_a0->unk_0C = 0x808080;
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        func_8003DB94(temp_a0, arg2, 0);
    }
    return temp_v0;
}
