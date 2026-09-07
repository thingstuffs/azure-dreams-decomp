#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E5910;

typedef struct S_800DBF38_0 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800DBF38_0;   /* temp_v1 in func_800DBF38 */

void func_800DBF38(void) {
    S_800DBF38_0 *temp_v1;

    temp_v1 = D_800E5910 + 0x20;
    temp_v1->unk_54 = (s32) (temp_v1->unk_54 & ~1);
}
