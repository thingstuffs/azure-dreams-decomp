#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C9A98_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C9A98_0;   /* arg0 in func_800C9A98 */


M2C_UNK func_800C9CDC(S_800C9A98_0 *, void *, s32);
void func_800C9A98(S_800C9A98_0 *arg0, void *arg1, s32 arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C9CDC(arg0, arg1, arg2);
    }
}
