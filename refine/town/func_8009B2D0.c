#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80097EC0;
extern M2C_UNK D_800D0178;

typedef struct S_80098A30_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098A30_0;   /* arg0 in func_80098A30 */

/* Initializes the object with default data and resets its state. */
void func_80098A30(S_80098A30_0 *object, M2C_UNK preparationValue, M2C_UNK initializationValue) {
    func_80099754(preparationValue);
    func_80094984(&D_800D0178, object, initializationValue);
    object->unk_04 = &D_80097EC0;
    D_80082668 = 0;
    object->unk_0A = 0x18;
}
