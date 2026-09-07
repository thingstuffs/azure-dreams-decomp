#include "common.h"
#include "m2c_compat.h"

s16 func_80095464();    /* extern */
u16 func_800BCB04();                   /* extern */

typedef struct S_80094ED4_0 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80094ED4_0;   /* arg3 in func_80094ED4 */

typedef struct S_80094ED4_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80094ED4_1;   /* arg2 in func_80094ED4 */

s16 func_80094ED4(s32 arg0, M2C_UNK arg1, S_80094ED4_1 *arg2, S_80094ED4_0 *arg3) {
    s16 temp_v0;
    u16 temp_s2;

    temp_s2 = arg3->unk_88;
    arg3->unk_88 = func_800BCB04((arg2->unk_24 << 6) | 0x20, (arg2->unk_25 << 6) | 0x20, (s16) (temp_s2 - 0x20));
    temp_v0 = func_80095464(arg0, arg1, arg2, arg3);
    arg3->unk_88 = temp_s2;
    return temp_v0;
}
