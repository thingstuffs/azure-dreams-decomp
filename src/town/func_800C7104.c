#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C4864_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C4864_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C4864 */




s16 func_800C2BE8();                 /* extern */
M2C_UNK func_800C2E84();                /* extern */
extern u8 D_80082660;
extern M2C_UNK D_800C3C5C;


/* Update the object's state, clear its indexed flag, and store the lookup result. */
void func_800C4864(Rec_func_80094268_arg0 *object, M2C_UNK lookup_key, M2C_UNK state_value) {
    func_800C2E84(object, state_value, ((S_800C4864_2 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_14);
    *((object->unk_60 * 8) + &D_80082660) = 0;
    object->unk_54 = &D_800C3C5C;
    object->unk_72.as_s16 = func_800C2BE8(object, lookup_key);
}
