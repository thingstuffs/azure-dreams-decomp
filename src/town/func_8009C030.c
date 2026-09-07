#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80098928();     /* extern */
M2C_UNK func_80099858();                            /* extern */
s16 func_800C2AE8();                          


/* extern */

void func_80099790(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    arg1->unk_08.at02_s16.v = func_800C2AE8(arg1);
    temp_v0 = arg0->unk_0A.as_u16 - 1;
    arg0->unk_0A.as_u16 = temp_v0;
    if ((s16) temp_v0 <= 0) {
        arg1->unk_00.at02_u16.v = (u16) arg0->unk_30;
        arg1->unk_04.at02_u16.v = (u16) arg0->unk_32;
        arg0->unk_10.as_u16 = (u16) arg0->unk_0E;
        func_80098928(arg0, arg1, arg2);
        func_80099858();
        return;
    }
    arg1->unk_00.at02_u16.v = (u16) (arg1->unk_00.at02_u16.v + ((s32) ((s16) arg0->unk_30 - (s16) arg1->unk_00.at02_u16.v) / (s16) temp_v0));
    arg1->unk_04.at02_u16.v = (u16) (arg1->unk_04.at02_u16.v + ((s32) ((s16) arg0->unk_32 - (s16) arg1->unk_04.at02_u16.v) / (s16) arg0->unk_0A.as_u16));
}
