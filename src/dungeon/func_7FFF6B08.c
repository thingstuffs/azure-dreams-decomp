#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80091F64;
extern M2C_UNK D_800D00A0;

typedef struct S_80094268_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_80094268_0;   /* arg0 in func_80094268 */

void func_80094268(S_80094268_0 *arg0) {
    func_80094984(&D_800D00A0, arg0);
    arg0->unk_00 = &D_80091F64;
    arg0->unk_0A = 3;
}
