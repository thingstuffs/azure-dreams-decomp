#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660;
extern M2C_UNK D_800C5ADC;
extern M2C_UNK D_800D54BC;

typedef struct S_800C5944_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C5944_0;   /* arg0 in func_800C5944 */

void func_800C5944(S_800C5944_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D54BC);
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    arg0->unk_54 = &D_800C5ADC;
}
