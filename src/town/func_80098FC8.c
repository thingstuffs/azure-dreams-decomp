#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954DC();                            /* extern */
extern s8 D_800CFCED;

typedef struct S_80096728_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_80096728_0;   /* arg0 in func_80096728 */

void func_80096728(S_80096728_0 *arg0, s32 arg1) {
    D_800CFCED = 1;
    arg0->unk_04 = arg1;
    arg0->unk_10 = 0;
    func_800954DC();
}
