#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A48B0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A48B0_0;   /* arg0 in func_800A48B0 */

typedef struct S_800A48B0_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A48B0_1;   /* arg1 in func_800A48B0 */

void func_800A48B0(S_800A48B0_0 *arg0, S_800A48B0_1 *arg1) {
    arg0->unk_00 = (s32) arg1->unk_00;
    arg0->unk_04 = (s32) arg1->unk_04;
    arg0->unk_08 = (s32) arg1->unk_08;
    arg0->unk_0C = (s32) arg1->unk_0C;
    arg0->unk_10 = (s32) arg1->unk_10;
    arg0->unk_14 = (s32) arg1->unk_14;
}
