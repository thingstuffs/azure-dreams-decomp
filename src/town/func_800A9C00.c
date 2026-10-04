#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                 /* extern */
extern M2C_UNK D_800A73E0;


typedef struct S_800A7360_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A7360_1;   /* arg0 in func_800A7360 */

/* Accumulate motion offsets and switch the object handler when the final offset is nonnegative. */
void func_800A7360(S_800A7360_1 *object, EntityRec *motion) {
    motion->x.v = (s32) (motion->x.v + motion->unk_0C);
    motion->y.v = (s32) (motion->y.v + motion->unk_10);
    motion->z.v = (s32) (motion->z.v + (motion->flags14));
    func_80095388(motion, (motion->flags14));
    if (motion->flags14 >= 0) {
        object->unk_50 = &D_800A73E0;
    }
}
