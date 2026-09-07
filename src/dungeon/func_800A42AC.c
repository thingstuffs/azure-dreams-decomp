#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800AA53C();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
extern u16 D_80013714;
extern u16 D_80083462;

typedef struct S_800A9A0C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x26];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800A9A0C_0;   /* arg0 in func_800A9A0C */

void func_800A9A0C(S_800A9A0C_0 *arg0) {
    s8 temp_v0;
    u8 temp_v1;

    arg0->unk_71 = (u8) (arg0->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2800)) {
        if (arg0->unk_6D != 0) {
            do {
                if (!(D_80013714 & 8)) {
                    if (!(arg0->unk_1C & 8) && ((temp_v1 = arg0->unk_13, ((temp_v1 < 0x2FU) != 0)) || (temp_v1 == 0x39))) {
                        func_800AD594(arg0, 4);
                    }
                    func_800A4ACC(arg0);
                }
                temp_v0 = (u8) arg0->unk_6D - 1;
                arg0->unk_6D = temp_v0;
            } while ((temp_v0 << 0x18) != 0);
        }
        arg0->unk_46 = (u16) (arg0->unk_46 & 0x7FFF);
        func_800AA53C(arg0);
    }
}
