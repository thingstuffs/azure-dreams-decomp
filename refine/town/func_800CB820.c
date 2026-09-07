#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C8FF0;
extern M2C_UNK D_800D6268;

typedef struct S_800C8F80_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
    u8 pad_74[0x22];
    u8 unk_96;
} S_800C8F80_0;   /* arg0 in func_800C8F80 */

/* Decrement the object's countdown and advance its state when the countdown expires. */
void func_800C8F80(S_800C8F80_0 *object, M2C_UNK unused, M2C_UNK updateContext) {
    u16 remainingTicks;

    remainingTicks = object->unk_6C - 1;
    object->unk_6C = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        func_800C2E84(object, updateContext, &D_800D6268);
        object->unk_50 = &D_800C8FF0;
        object->unk_72 = 0xC00;
        object->unk_6C = (u16) (object->unk_96 * 3);
    }
}
