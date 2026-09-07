#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800C2E84();  /* extern */
extern M2C_UNK D_800C86EC;
extern M2C_UNK D_800D6290;



void func_800C8788(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    arg1->unk_08.at00_s32.v = (s32) (arg1->unk_08.at00_s32.v + arg1->unk_14.as_s32);
    func_80095388(arg1);
    if (arg1->unk_14.as_s32 >= 0) {
        func_800C2E84(arg0, arg2, &D_800D6290);
        arg0->unk_54 = &D_800C86EC;
    }
}
