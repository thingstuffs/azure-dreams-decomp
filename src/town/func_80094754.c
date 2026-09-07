#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80091F48();
extern M2C_UNK func_80093D48();
extern M2C_UNK func_80095C80();




void func_80091EB4(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s32 temp_v1;
    u16 temp_v0;

    func_80095C80(arg1);
    temp_v0 = arg0->unk_0A.as_u16 - 1;
    temp_v1 = arg0->unk_34.as_s16 << 0x10;
    arg0->unk_0A.as_u16 = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg1->unk_0C.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_14.as_s32 = 0;
        arg1->unk_08.at00_s32.v = (s32) (arg0->unk_34.as_s16 << 0x10);
        func_80093D48(arg0, arg1, arg2);
        func_80091F48();
        return;
    }
    arg1->unk_14.as_s32 =
        (s32) ((s32) (temp_v1 - arg1->unk_08.at00_s32.v) /
               (s16) temp_v0);
}
