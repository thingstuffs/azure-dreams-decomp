#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B14DC_0 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_800B14DC_0;   /* D_800E3D7C in func_800B14DC */


extern S_800B14DC_0 *D_800E3D7C;

s32 func_800B14DC(void) {
    return D_800E3D7C->unk_9A != 0x29;
}
