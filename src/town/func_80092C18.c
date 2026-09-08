#include "common.h"
#include "m2c_compat.h"

typedef struct S_80090378_0 {
    s32 unk_00;
} S_80090378_0;   /* temp_a1 in func_80090378; pointer addresses record offset 0x14 */


M2C_UNK func_80094984();   /* extern */
extern M2C_UNK D_800834B8;
extern M2C_UNK D_800D0178;

/* Initialize the global record using its preceding value and D_800D0178. */
void func_80090378(void) {
    M2C_UNK *record = &D_800834B8;
    func_80094984(&D_800D0178, record, ((S_80090378_0 *)((u8 *)record - 0x14))->unk_00);
}
