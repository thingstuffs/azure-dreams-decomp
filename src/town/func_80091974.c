#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8008F01C();                            /* extern */

typedef struct S_8008F0D4_0 {
    u8 pad_00[0x14];
    s8 unk_14;
} S_8008F0D4_0;   /* arg0 in func_8008F0D4 */

void func_8008F0D4(S_8008F0D4_0 *arg0) {
    func_8008F01C();
    arg0->unk_14 = 4;
}
