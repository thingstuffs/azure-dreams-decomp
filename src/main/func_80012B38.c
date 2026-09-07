#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80025B38_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025B38_0;   /* arg0 in func_80025B38 */

void func_80025B38(S_80025B38_0 *arg0, s32 arg1) {
    arg0->unk_20 = arg1;
}
