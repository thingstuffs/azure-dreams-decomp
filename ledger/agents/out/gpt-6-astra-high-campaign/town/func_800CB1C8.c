#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D6330;
extern M2C_UNK D_800D6338;
extern M2C_UNK D_800D6360;
extern M2C_UNK D_800D6364;

typedef struct S_800C8928_0 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C8928_0;   /* arg0 in func_800C8928 */

/* Assign the four object data pointers. */
void func_800C8928(S_800C8928_0 *object) {
    object->unk_58 = &D_800D6360;
    object->unk_5C = &D_800D6364;
    object->unk_7C = &D_800D6330;
    object->unk_80 = &D_800D6338;
}
