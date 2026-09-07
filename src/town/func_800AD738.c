#include "common.h"
#include "m2c_compat.h"

s32 func_8008C180();                        /* extern */

typedef struct S_800AAE98_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800AAE98_0;   /* arg0 in func_800AAE98 */

s32 func_800AAE98(S_800AAE98_0 *arg0) {
    s32 temp_v1;

    temp_v1 = func_8008C180(arg0->unk_02, arg0->unk_06) & 0xFFFF;
    if ((u32) (temp_v1 - 0xC0) < 3U) {
        return 0x18;
    }
    if ((u32) (temp_v1 - 0xC7) < 3U) {
        return 0x18;
    }
    if ((u32) (temp_v1 - 0xCE) < 3U) {
        return 0x18;
    }
    ASM_KEEP(temp_v1);   /* MATCH pin: load-bearing for the whole function shape */
    return 0x60;
}

/* MECHANISM: Three explicit range-check returns materialize 0x18 in each taken-branch delay slot.
   ASM_KEEP extends temp_v1 through the final fallthrough, preserving $v1 so the last test uses $v0.
   The natural 0x18-byte frame saves only $ra; 2.7.2-cdk-G0 then emits all 25 retail words. */
