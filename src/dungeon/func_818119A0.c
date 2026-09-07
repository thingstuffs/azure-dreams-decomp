#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800267D8();       /* extern */
M2C_UNK func_80026878();                 /* extern */
M2C_UNK func_8002692C();                            /* extern */

typedef struct S_800269A0_0 {
    u8 pad_00[0x70];
    s32 unk_70;
} S_800269A0_0;   /* arg0 in func_800269A0 */

void func_800269A0(void *arg0) {
    func_8002692C();
    func_800267D8(arg0, arg0 + 0x60, arg0 + 0x38, arg0 + 0x48);
    func_80026878(arg0, ((S_800269A0_0 *)arg0)->unk_70);
}
