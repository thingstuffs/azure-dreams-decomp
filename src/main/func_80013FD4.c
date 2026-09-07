#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80026FD4_0 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_80026FD4_0;   /* temp_a0 in func_80026FD4 */

void func_80026FD4(s32 arg0, s32 arg1) {
    S_80026FD4_0 *temp_a0;

    temp_a0 = arg0 + 0x20;
    temp_a0->unk_24 = arg1;
    func_800269B4(temp_a0);
}
