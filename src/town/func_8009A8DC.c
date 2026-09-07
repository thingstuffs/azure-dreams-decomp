#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80098928();                            /* extern */

typedef struct S_8009803C_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8009803C_0;   /* arg0 in func_8009803C */

void func_8009803C(S_8009803C_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80098928();
    }
}
