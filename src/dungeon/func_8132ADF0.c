#include "common.h"
#include "m2c_compat.h"

typedef struct S_801725F0_0 {
    u8 pad_00[0xBA];
    u8 unk_BA;
} S_801725F0_0;   /* D_80174CE0 in func_801725F0 */


extern S_801725F0_0 *D_80174CE0;

s32 func_801725F0(s32 arg0) {
    return (s32) D_80174CE0->unk_BA >= arg0;
}
