#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B25D8_0 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B25D8_0;   /* (((*(s32 *)((u8 *)arg0 + 0x14)) * 4) + arg0) in func_800B25D8 */


M2C_UNK func_8004B08C();                         /* extern */

void func_800B25D8(void *arg0) {
    func_8004B08C(((S_800B25D8_0 *)((((*(s32 *)((u8 *)arg0 + 0x14)) * 4) + arg0)))->unk_3C);
}
