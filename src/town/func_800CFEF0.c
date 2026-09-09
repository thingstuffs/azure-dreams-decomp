#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
s32 *func_8008FAC0();              /* extern */
s32 func_800C30E0(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_800CDDFC();    /* extern */
M2C_UNK func_800CDE4C();    /* extern */
extern M2C_UNK D_800CFCB4;



void func_800CD650(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s32 *temp_v0;
    u16 temp_v0_2;

    if ((func_800C30E0(arg0, arg1, arg2, arg3) == 0) && ((temp_v0 = func_8008FAC0(arg0, &D_800CFCB4), (temp_v0 == NULL)) || (*temp_v0 == 2)) && (temp_v0_2 = arg0->unk_6C.as_u16 - 1, arg0->unk_6C.as_u16 = temp_v0_2, ((temp_v0_2 << 0x10) <= 0))) {
        if (func_800374F4(2) & 0xFFFF) {
            func_800CDDFC(arg0, arg1, arg2);
            return;
        }
        func_800CDE4C(arg0, arg1, arg2);
    }
}
