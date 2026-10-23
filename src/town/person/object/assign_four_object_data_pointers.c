#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D6330;
extern M2C_UNK D_800D6338;
extern M2C_UNK D_800D6360;
extern M2C_UNK D_800D6364;

typedef struct S_800C8928_0 {
    u8 pad_00[0x58];
    s32 * unk_58;
    s32 * unk_5C;
    u8 pad_60[0x1C];
    s32 * unk_7C;
    s32 * unk_80;
} S_800C8928_0;   /* arg0 in assign_four_object_data_pointers */

/*
 * Binds object fields 0x58/0x5C to D_800D6360/D_800D6364 and fields 0x7C/0x80 to
 * D_800D6330/D_800D6338.
 */
void assign_four_object_data_pointers(S_800C8928_0 *object) {
    object->unk_58 = &D_800D6360;
    object->unk_5C = &D_800D6364;
    object->unk_7C = &D_800D6330;
    object->unk_80 = &D_800D6338;
}
