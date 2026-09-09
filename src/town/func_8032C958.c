#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017158_0 {
    s32 unk_00;
} S_80017158_0;   /* arg0 in func_80017158; pointer addresses record offset 0x1C */


s32 func_80019C68(void *, s32);                                /* extern */

s32 func_80017158(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80019C68(arg0, arg1);
    if (temp_v0 == 0) {
        ((S_80017158_0 *)((u8 *)arg0 - 0x1C))->unk_00 = (s32) (((S_80017158_0 *)((u8 *)arg0 - 0x1C))->unk_00 | 0x8000);
    }
    return temp_v0;
}
