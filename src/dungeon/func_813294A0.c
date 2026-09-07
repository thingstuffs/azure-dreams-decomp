#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80174CE0[];
typedef struct S_80170CA0_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_80170CA0_0;   /* temp_v0 in func_80170CA0 */

void func_80170CA0(void) {
    S_80170CA0_0 *temp_v0;

    temp_v0 = *D_80174CE0 + 0x20;
    temp_v0->unk_9A = 0;
    temp_v0->unk_96 = 0;
}
