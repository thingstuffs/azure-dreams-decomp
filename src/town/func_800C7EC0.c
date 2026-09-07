#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C4174();                            /* extern */

typedef struct S_800C5620_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C5620_0;   /* arg0 in func_800C5620 */

void func_800C5620(S_800C5620_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C4174();
    }
}
