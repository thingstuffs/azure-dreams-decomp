#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800CE04C();     /* extern */

typedef struct S_800CDC2C_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800CDC2C_0;   /* arg0 in func_800CDC2C */

typedef struct S_800CDC2C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CDC2C_1;   /* arg1 in func_800CDC2C */

/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void func_800CDC2C(S_800CDC2C_0 *object, S_800CDC2C_1 *motion, M2C_UNK context) {
    object->unk_72 = (u16) (object->unk_72 + 0x400);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    func_80095388(motion);
    if (motion->unk_14 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
