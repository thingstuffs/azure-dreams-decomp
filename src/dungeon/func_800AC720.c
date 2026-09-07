#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003F80C(); /* extern */
extern u8 D_800DF068[];

typedef struct S_800B1E80_0 {
    u16 unk_00;
    u16 unk_02;
} S_800B1E80_0;   /* arg0 in func_800B1E80 */

void func_800B1E80(S_800B1E80_0 *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = arg0->unk_00 - 1;
    arg0->unk_00 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_00 = 4U;
        temp_v0_2 = arg0->unk_02 + 8;
        arg0->unk_02 = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x60) {
            arg0->unk_02 = 0U;
        }
        func_8003F80C(((s16) arg0->unk_02 * 4) + D_800DF068, 0x7340, 1, 2);
    }
}
