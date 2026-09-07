#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8040343C();                     /* extern */

typedef struct S_8001B93C_0 {
    u8 pad_00[0x20];
    s32 * unk_20;
} S_8001B93C_0;   /* arg0 in func_8001B93C */

void func_8001B93C(S_8001B93C_0 *arg0) {
    if (*arg0->unk_20 == 0) {
        func_8040343C(0);
    }
}
