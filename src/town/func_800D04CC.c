#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800CE04C();     /* extern */

typedef struct S_800CDC2C_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800CDC2C_0;   /* arg0 in func_800CDC2C */


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void func_800CDC2C(S_800CDC2C_0 *object, Rec_D_800E3D7C *motion, M2C_UNK context) {
    object->unk_72 = (u16) (object->unk_72 + 0x400);
    motion->unk_08.at00_s32.v = (s32) (motion->unk_08.at00_s32.v + motion->unk_14.as_s32);
    func_80095388(motion);
    if (motion->unk_14.as_s32 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
