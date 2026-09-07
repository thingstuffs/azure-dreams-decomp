#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();  /* extern */
M2C_UNK func_800C8A68();                     /* extern */
extern M2C_UNK D_800C84B8;
extern M2C_UNK D_800D62AC;

typedef struct S_800C8524_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C8524_0;   /* arg0 in func_800C8524 */

/* Decrement the object's countdown and advance its state when it expires. */
void func_800C8524(S_800C8524_0 *object, M2C_UNK update_context, M2C_UNK state_context) {
    u16 ticks_left;

    ticks_left = object->unk_6C - 1;
    object->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800C8A68(update_context);
        func_800C2E84(object, state_context, &D_800D62AC);
        object->unk_54 = &D_800C84B8;
        object->unk_6C = 0x15U;
    }
}
