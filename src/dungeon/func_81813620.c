#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80026CD8();                         /* extern */

typedef struct S_80028620_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x64];
    s32 unk_88;
} S_80028620_0;   /* temp_v0 in func_80028620 */

void func_80028620(s32 arg0) {
    S_80028620_0 *temp_v0;

    temp_v0 = arg0 + 0x20;
    temp_v0->unk_20 = 0;
    func_80026CD8(temp_v0->unk_88);
}
