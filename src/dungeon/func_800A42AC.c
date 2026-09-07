#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800AA53C();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
extern u16 D_80013714;
extern u16 D_80083462;


void func_800A9A0C(Rec_D_800E3D7C *arg0) {
    s8 temp_v0;
    u8 temp_v1;

    arg0->unk_71.as_u8 = (u8) (arg0->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2800)) {
        if (arg0->unk_6D.as_s8 != 0) {
            do {
                if (!(D_80013714 & 8)) {
                    if (!(arg0->unk_1C.as_s32 & 8) && ((temp_v1 = arg0->unk_10.at03_u8.v, ((temp_v1 < 0x2FU) != 0)) || (temp_v1 == 0x39))) {
                        func_800AD594(arg0, 4);
                    }
                    func_800A4ACC(arg0);
                }
                temp_v0 = (u8) arg0->unk_6D.as_s8 - 1;
                arg0->unk_6D.as_s8 = temp_v0;
            } while ((temp_v0 << 0x18) != 0);
        }
        arg0->unk_44.at02_u16.v = (u16) (arg0->unk_44.at02_u16.v & 0x7FFF);
        func_800AA53C(arg0);
    }
}
