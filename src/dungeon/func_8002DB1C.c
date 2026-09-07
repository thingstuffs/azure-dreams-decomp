#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660[];
extern M2C_UNK D_800CB21C;
extern M2C_UNK D_800D6910;

typedef struct S_800CB27C_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800CB27C_0;   /* arg0 in func_800CB27C */

void func_800CB27C(S_800CB27C_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D6910);
    D_80082660[arg0->unk_60 * 8] = 0;
    arg0->unk_54 = &D_800CB21C;
    arg0->unk_6C = 7;
}
