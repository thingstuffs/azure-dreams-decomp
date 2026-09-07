#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80034F88_0 {
    u8 pad_00[0x34];
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0xCC];
    s32 unk_108;
} S_80034F88_0;   /* arg0 in func_80034F88 */


void func_80034F88(void *arg0, s32 arg1) {
    ((S_80034F88_0 *)arg0)->unk_34 = arg1;
    ((S_80034F88_0 *)arg0)->unk_38 = arg1;
    ((S_80034F88_0 *)arg0)->unk_108 = (s32) (arg0 + 0xC8);
}
