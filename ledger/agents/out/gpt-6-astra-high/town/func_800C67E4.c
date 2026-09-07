#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C3F44_2 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C3F44_2;   /* arg0 in func_800C3F44 */

typedef struct S_800C3F44_3 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800C3F44_3;   /* ((S_800C3F44_2 *)arg0)->unk_80 in func_800C3F44 */




M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800C2E84();        /* extern */
extern M2C_UNK D_800C3EAC;

typedef struct S_800C3F44_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C3F44_0;   /* arg1 in func_800C3F44 */

typedef struct S_800C3F44_1 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
} S_800C3F44_1;   /* arg0 in func_800C3F44 */

/* Advances motion and changes the object handler when the motion step is nonnegative. */
void func_800C3F44(S_800C3F44_1 *object, S_800C3F44_0 *motion, M2C_UNK context) {
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    func_80095388(motion);
    if (motion->unk_14 >= 0) {
        func_800C2E84(object, context, ((S_800C3F44_3 *)(((S_800C3F44_2 *)object)->unk_80))->unk_20);
        object->unk_54 = &D_800C3EAC;
    }
}
