#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK func_800C2E84();
extern M2C_UNK D_800CB474;
extern M2C_UNK D_800D6938;


void func_800CB4B0(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C2E84(arg0, arg2, &D_800D6938);
        arg0->unk_54 = &D_800CB474;
        arg0->unk_6C.as_u16 = 0xAU;
    }
}
