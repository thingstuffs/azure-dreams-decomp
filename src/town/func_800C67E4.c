#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800C3F44_3 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800C3F44_3;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C3F44 */




M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800C2E84();        /* extern */
extern M2C_UNK D_800C3EAC;



void func_800C3F44(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    arg1->unk_08.at00_s32.v = (s32) (arg1->unk_08.at00_s32.v + arg1->unk_14.as_s32);
    func_80095388(arg1);
    if (arg1->unk_14.as_s32 >= 0) {
        func_800C2E84(arg0, arg2, ((S_800C3F44_3 *)(((Rec_func_80094268_arg0 *)arg0)->unk_80))->unk_20);
        arg0->unk_54 = &D_800C3EAC;
    }
}
