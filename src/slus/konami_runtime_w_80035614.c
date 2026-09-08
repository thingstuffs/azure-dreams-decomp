#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035614_0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    u8 pad_4D[0x1B];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    s32 unk_74;
} S_80035614_0;   /* arg0 in func_80035614 */


M2C_UNK func_80035888(); /* extern */
extern M2C_UNK D_80081F14;
extern M2C_UNK D_800821CC;
extern M2C_UNK func_8003566C;

/* Initialize the object, clear its state byte, and set its next handler. */
void func_80035614(S_80035614_0 *object) {
    func_80035888(&D_800821CC, &D_80081F14, object, 0, object->unk_74);
    object->unk_4C = 0;
    object->unk_68 = &func_8003566C;
}
