#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B1B04_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B1B04_0;   /* arg0 in func_800B1B04 */

void func_800B1B04(S_800B1B04_0 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = arg2;
}
