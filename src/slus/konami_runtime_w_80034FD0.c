#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80034FD0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80034FD0_0;   /* arg0 in func_80034FD0 */


s32 func_80034FD0(void *arg0) {
    return ((S_80034FD0_0 *)arg0)->unk_10 != (s32) (arg0 + 8);
}
