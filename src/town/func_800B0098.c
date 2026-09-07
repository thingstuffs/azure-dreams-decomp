#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AD7F8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x18];
    s32 unk_20;
} S_800AD7F8_0;   /* arg0 in func_800AD7F8 */

typedef struct S_800AD7F8_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AD7F8_1;   /* temp_a0 in func_800AD7F8 */

void func_800AD7F8(S_800AD7F8_0 *arg0) {
    u8 temp_v1;
    S_800AD7F8_1 *temp_a0;

    temp_a0 = (arg0->unk_04 * 4) + arg0->unk_20;
    temp_v1 = temp_a0->unk_03;
    if (!(temp_v1 & 0x80)) {
        temp_a0->unk_03 = (u8) (temp_v1 ^ 0x20);
    }
}
