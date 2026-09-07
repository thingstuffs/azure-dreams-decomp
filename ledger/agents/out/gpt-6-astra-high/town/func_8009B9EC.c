#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D0120;

typedef struct S_8009914C_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_8009914C_0;   /* arg0 in func_8009914C */

/* Clears the object's indexed flag and resets its state before processing the context. */
void func_8009914C(S_8009914C_0 *object, M2C_UNK context) {
    func_80094984(&D_800D0120, object);
    *((object->unk_40 * 8) + &D_80082660) = 0;
    object->unk_04 = &D_80098078;
    object->unk_0A = 6;
    func_80099754(context);
}
