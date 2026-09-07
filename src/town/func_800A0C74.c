#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009E3D4_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8009E3D4_0;   /* D_80100AF0 in func_8009E3D4 */


extern S_8009E3D4_0 *D_80100AF0;

s32 func_8009E3D4(void) {
    return D_80100AF0->unk_1E & 0x8000;
}
