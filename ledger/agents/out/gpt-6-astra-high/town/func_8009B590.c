#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098180;
extern M2C_UNK D_800D0090;

typedef struct S_80098CF0_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_80098CF0_0;   /* arg0 in func_80098CF0 */

/* Initializes an object with default state and clears the shared flag. */
void func_80098CF0(S_80098CF0_0 *object, M2C_UNK setupParameter, M2C_UNK initializationParameter) {
    func_80099754(setupParameter);
    func_80094984(&D_800D0090, object, initializationParameter);
    D_80082668 = 0;
    object->unk_04 = &D_80098180;
    object->unk_0A = 0x10;
    object->unk_10 = 0x400;
}
