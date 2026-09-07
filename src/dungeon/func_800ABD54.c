#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B14B4_0 {
    u8 pad_00[0x104];
    s32 unk_104;
} S_800B14B4_0;   /* D_800E3D7C in func_800B14B4 */


extern S_800B14B4_0 *D_800E3D7C;

s32 func_800B14B4(void) {
    return D_800E3D7C->unk_104 == 0;
}
