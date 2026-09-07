#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800478B8();                      /* extern */


void func_80DE6A54(u16 *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = *arg0 + 1;
    *arg0 = temp_v0;
    if ((s16) temp_v0 < 9) {
        temp_v0_2 = arg2->unk_1C.at02_u16.v + 0x100;
        arg2->unk_1C.at02_u16.v = temp_v0_2;
        arg2->unk_1C.at00_u16.v = temp_v0_2;
    }
    func_800478B8(arg2);
}
