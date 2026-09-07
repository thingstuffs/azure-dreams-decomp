#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800AB538(arg0);                            /* extern */

typedef struct S_80173D50_0 {
    u8 pad_00[0xA6];
    s16 unk_A6;
} S_80173D50_0;   /* arg0 in func_80173D50 */

void func_80173D50(S_80173D50_0 *arg0) {
    func_800AB538(arg0);
    arg0->unk_A6 = 0;
}
