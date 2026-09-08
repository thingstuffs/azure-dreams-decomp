#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_8009204C;
extern M2C_UNK D_800D00B0;

typedef struct S_800942B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800942B0_0;   /* arg1 in func_800942B0 */


/* Initializes an object and its associated state. */
void func_800942B0(Rec_func_80094268_arg0 *object, S_800942B0_0 *state, M2C_UNK initData) {
    func_800948DC();
    state->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D00B0, object, initData);
    object->unk_00.as_pm = &D_8009204C;
    object->unk_0A.as_s16 = 0;
}
