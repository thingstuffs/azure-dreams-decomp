#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A0C30;

typedef struct S_800A0CC0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A0CC0_0;   /* arg0 in func_800A0CC0 */


s32 func_800352FC(S_800A0CC0_0 *, s32, s32, s32);
/* Set the object handler when func_800352FC returns zero. */
void func_800A0CC0(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (func_800352FC(object, value_1, value_2, value_3) == 0) {
        object->unk_50 = &D_800A0C30;
    }
}
