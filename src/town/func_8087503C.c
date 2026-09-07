#include "common.h"
#include "m2c_compat.h"

typedef struct S_8087503C_0 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_8087503C_0;   /* temp_a1 in func_8087503C */

s32 func_8087503C(s32 arg0) {
    S_8087503C_0 *temp_a1;

    temp_a1 = *(void **)0x80701968;
    temp_a1->unk_30 = (s32) (temp_a1->unk_30 & 0xBFFFFFFF);
    return arg0;
}
