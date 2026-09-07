#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                 /* extern */
extern M2C_UNK D_800A73E0;

typedef struct S_800A7360_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A7360_0;   /* arg1 in func_800A7360 */

typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A7360_1;   /* arg0 in func_800A7360 */

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void func_800A7360(S_800A7360_1 *object, S_800A7360_0 *motion) {
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + (motion->unk_14));
    func_80095388(motion, (motion->unk_14));
    if (motion->unk_14 >= 0) {
        object->unk_50 = &D_800A73E0;
    }
}
