#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954F4();                            /* extern */
extern s8 D_800CFCE8;

typedef struct S_800967E0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800967E0_0;   /* arg0 in func_800967E0 */

void func_800967E0(S_800967E0_0 *arg0, s32 arg1) {
    D_800CFCE8 = 1;
    arg0->unk_08 = arg1;
    arg0->unk_14 = 0;
    func_800954F4();
}
