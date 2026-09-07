#include "common.h"

typedef struct S_800A5894_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800A5894_0;   /* arg0 in func_800A5894 */



s32 func_800A5894(S_800A5894_0 *arg0) {
    if (arg0->unk_08.at00.v > -0x400000) {
        goto calculate;
    }
    {
        register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        result = 0;
        goto out;
    calculate:
        result = (arg0->unk_08.at02.v * 0xC00) + 0x30000;
    out:
        return result;
    }
}
