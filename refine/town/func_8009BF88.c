#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D01E0;

typedef struct S_800996E8_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800996E8_0;   /* arg0 in func_800996E8 */

/* Initialize the object's state and run the follow-up setup. */
void func_800996E8(S_800996E8_0 *object, M2C_UNK setupContext) {
    func_80094984(&D_800D01E0, object);
    D_80082668 = 0;
    object->unk_10 = 0x800;
    object->unk_04 = &D_80098078;
    object->unk_0A = 4;
    func_80099754(setupContext);
}
