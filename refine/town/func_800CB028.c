#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800C2E84();  /* extern */
extern M2C_UNK D_800C86EC;
extern M2C_UNK D_800D6290;

typedef struct S_800C8788_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C8788_0;   /* arg1 in func_800C8788 */

typedef struct S_800C8788_1 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
} S_800C8788_1;   /* arg0 in func_800C8788 */

/* Advance the motion state and update the object when its step is nonnegative. */
void func_800C8788(S_800C8788_1 *object, S_800C8788_0 *motion, M2C_UNK context) {
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    func_80095388(motion);
    if (motion->unk_14 >= 0) {
        func_800C2E84(object, context, &D_800D6290);
        object->unk_54 = &D_800C86EC;
    }
}
