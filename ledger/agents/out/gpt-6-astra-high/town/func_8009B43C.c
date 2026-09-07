#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_800980B4;
extern M2C_UNK D_800D0180;

typedef struct S_80098B9C_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_80098B9C_0;   /* arg0 in func_80098B9C */

/* Initialize the object's data and state, then run the setup callback. */
void func_80098B9C(S_80098B9C_0 *object, M2C_UNK setupArgument) {
    func_80094984(&D_800D0180, object);
    object->unk_04 = &D_800980B4;
    D_80082668 = 0;
    object->unk_0A = 0x15;
    func_80099754(setupArgument);
    object->unk_10 = 0;
}
