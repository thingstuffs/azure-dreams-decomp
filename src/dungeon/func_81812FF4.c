#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80028774();                            /* extern */

typedef struct S_80027FF4_0 {
    u8 pad_00[0x2];
    s8 unk_02;
    u8 pad_03[0x7];
    s8 unk_0A;
    u8 pad_0B[0x3];
    s8 unk_0E;
    u8 pad_0F[0x7];
    s8 unk_16;
} S_80027FF4_0;   /* arg0 in func_80027FF4 */

void *func_80027FF4(S_80027FF4_0 *arg0, s32 arg1) {
    func_80028774();
    if (arg1 == 1) {
        arg0->unk_02 = -0x31;
        arg0->unk_0E = -0x31;
        arg0->unk_0A = 0x63;
        arg0->unk_16 = 0x63;
    }
    return arg0;
}
