#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */

typedef struct S_800AB030_0 {
    u8 pad_00[0x6A];
    u16 unk_6A;
} S_800AB030_0;   /* arg0 in func_800AB030 */

s16 func_800AB030(S_800AB030_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6A + 0xCC;
    arg0->unk_6A = temp_v0;
    return (s16) (func_800644B8((s16) temp_v0) / 384);
}
