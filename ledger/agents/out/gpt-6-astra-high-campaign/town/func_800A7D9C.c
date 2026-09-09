#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A5340;

typedef struct S_800A54FC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x16];
    M2C_UNK * unk_1C;
} S_800A54FC_0;   /* arg0 in func_800A54FC */


s32 func_800352FC(S_800A54FC_0 *, s32, s32, s32);
/* Initialize the object value and handler when func_800352FC returns zero. */
void func_800A54FC(S_800A54FC_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (func_800352FC(object, value_1, value_2, value_3) == 0) {
        object->unk_04 = 0x400;
        object->unk_1C = &D_800A5340;
    }
}
