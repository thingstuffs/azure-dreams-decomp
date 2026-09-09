#include "common.h"
#include "m2c_compat.h"

/* extern */

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


M2C_UNK func_80028774(S_80027FF4_0 *, s32, s32, s32);
/* Initialize the object and set paired byte fields when mode is one. */
void *func_80027FF4(S_80027FF4_0 *object, s32 mode, s32 init_value, s32 init_value_2) {
    func_80028774(object, mode, init_value, init_value_2);
    if (mode == 1) {
        object->unk_02 = -0x31;
        object->unk_0E = -0x31;
        object->unk_0A = 0x63;
        object->unk_16 = 0x63;
    }
    return object;
}
