#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800197D8();                 /* extern */

typedef struct S_80477B24_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80477B24_0;   /* arg0 in func_80477B24 */

typedef struct S_80477B24_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80477B24_1;   /* temp_a1 in func_80477B24 */

void func_80477B24(S_80477B24_0 *arg0, s32 arg1) {
    S_80477B24_1 *temp_a1;

    temp_a1 = (arg1 * 0x10) + arg0->unk_10;
    func_800197D8(temp_a1->unk_0C, temp_a1);
}
