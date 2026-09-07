#include "common.h"
#include "m2c_compat.h"

s16 func_800C8DB0();               /* extern */

typedef struct S_800C8788_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_800C8788_0;   /* arg0 in func_800C8788 */

u32 func_800C8788(S_800C8788_0 *arg0, M2C_UNK arg1) {
    u8 temp_v0;

    temp_v0 = arg0->unk_11;
    return (u32) ~func_800C8DB0(arg1, temp_v0 * 4, (temp_v0 >> 2) + 0x10) >> 0x1F;
}
