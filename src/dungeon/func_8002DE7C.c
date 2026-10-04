#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

void func_800C2E84(void *state, s8 *output, s32 *entries);
extern M2C_UNK D_800CB570;
extern M2C_UNK D_800D694C;

typedef struct S_800CB5DC_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    M2C_UNK16 unk_6C;
} S_800CB5DC_0;   /* arg0 in func_800CB5DC */

/* Initialize the object's state, clear its slot flag, and set its counter to ten. */
void func_800CB5DC(void *object, M2C_UNK unused, s8 *context) {
    func_800C2E84(object, context, &D_800D694C);
    D_80082660[((S_800CB5DC_0 *)object)->unk_60].unk_00 = 0;
    ((S_800CB5DC_0 *)object)->unk_54 = &D_800CB570;
    ((S_800CB5DC_0 *)object)->unk_6C = 0xA;
}
