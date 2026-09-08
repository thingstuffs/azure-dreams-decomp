#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                 /* extern */
extern M2C_UNK D_800A73E0;


typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A7360_1;   /* arg0 in func_800A7360 */

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void func_800A7360(S_800A7360_1 *object, Rec_D_800E3D7C *motion) {
    motion->unk_00.at00_s32.v = (s32) (motion->unk_00.at00_s32.v + motion->unk_0C.as_s32);
    motion->unk_04.at00_s32.v = (s32) (motion->unk_04.at00_s32.v + motion->unk_10.at00_s32.v);
    motion->unk_08.at00_s32.v = (s32) (motion->unk_08.at00_s32.v + (motion->unk_14.as_s32));
    func_80095388(motion, (motion->unk_14.as_s32));
    if (motion->unk_14.as_s32 >= 0) {
        object->unk_50 = &D_800A73E0;
    }
}
