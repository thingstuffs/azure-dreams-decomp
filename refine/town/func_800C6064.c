#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C2E84();                /* extern */
extern M2C_UNK D_800C34EC;

typedef struct S_800C37C4_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0xE];
    s32 * unk_7C;
} S_800C37C4_0;   /* arg0 in func_800C37C4 */

/* Initializes the object, assigns its state data, and sets a value in multiples of 21. */
void func_800C37C4(S_800C37C4_0 *object, M2C_UNK unusedArg, M2C_UNK initializationArg) {
    func_800C2E84(object, initializationArg, *object->unk_7C);
    object->unk_50 = &D_800C34EC;
    object->unk_6C = (s16) (((func_800374F4(4) & 0xFFFF) * 0x15) + 0x15);
}
