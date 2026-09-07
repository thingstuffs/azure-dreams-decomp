#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80090F00;
extern M2C_UNK D_800D00C0;

typedef struct S_80094330_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_80094330_0;   /* arg0 in func_80094330 */

void func_80094330(S_80094330_0 *arg0) {
    func_80094984(&D_800D00C0, arg0);
    arg0->unk_00 = &D_80090F00;
    arg0->unk_0A = 6;
}
