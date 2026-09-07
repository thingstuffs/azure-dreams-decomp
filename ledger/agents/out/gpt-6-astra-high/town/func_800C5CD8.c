#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();                   /* extern */
M2C_UNK func_8008F074();  /* extern */
M2C_UNK func_800C2CB0(); /* extern */
M2C_UNK func_800C337C();    /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800D5028;

typedef struct S_800C3438_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
    u8 pad_80[0xC];
    s16 unk_8C;
    s16 unk_8E;
} S_800C3438_0;   /* arg0 in func_800C3438 */

/* Initialize the object and its animation, then dispatch its current state. */
void func_800C3438(S_800C3438_0 *object, M2C_UNK context, M2C_UNK animation) {
    func_80033CD8(object, &D_80045340);
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    func_800C2CB0(object, animation, **object->unk_7C, 0);
    func_8008F074(object, context, &D_800D5028);
    func_800C337C(object, context, animation);
}
