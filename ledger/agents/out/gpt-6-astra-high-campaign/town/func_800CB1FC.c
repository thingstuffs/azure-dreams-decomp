#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D6220;
extern M2C_UNK D_800D62D8;
extern M2C_UNK D_800D62E0;
extern M2C_UNK D_800D6308;
extern M2C_UNK D_800D630C;

typedef struct S_800C895C_0 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C895C_0;   /* arg0 in func_800C895C */

typedef struct S_800C895C_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C895C_1;   /* &D_800D62E0 in func_800C895C */

/* Assign the object data pointers and link the shared data entry. */
void func_800C895C(S_800C895C_0 *object) {
    object->unk_58 = &D_800D6308;
    object->unk_5C = &D_800D630C;
    object->unk_7C = &D_800D62D8;
    object->unk_80 = &D_800D62E0;
    ((S_800C895C_1 *)(&D_800D62E0))->unk_04 = &D_800D6220;
}
