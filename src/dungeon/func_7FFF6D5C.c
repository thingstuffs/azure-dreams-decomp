#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_80092698;
extern M2C_UNK D_800D0120;

typedef struct S_800944BC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800944BC_0;   /* arg0 in func_800944BC */

void func_800944BC(S_800944BC_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80053DA8(0x511);
    func_80094984(&D_800D0120, arg0, arg2);
    arg0->unk_00 = &D_80092698;
    arg0->unk_0A = 6;
}
