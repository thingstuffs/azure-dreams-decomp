#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80091920_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80091920_0;   /* arg0 in func_80091920 */

void func_80091920(S_80091920_0 *arg0) {
    arg0->unk_9A = 0x29;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
}
