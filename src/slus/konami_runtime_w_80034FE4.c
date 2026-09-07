#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80034FE4_0 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_80034FE4_0;   /* arg0 in func_80034FE4 */


extern M2C_UNK func_80038A00;

s32 func_80034FE4(S_80034FE4_0 *arg0) {
    return arg0->unk_9C != (s32) &func_80038A00;
}
