#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026CD8_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
    s32 * unk_10;
} S_80026CD8_0;   /* arg0 in func_80026CD8 */

void func_80026CD8(S_80026CD8_0 *arg0) {
    *arg0->unk_0C = 0;
    *arg0->unk_10 = 0;
}
