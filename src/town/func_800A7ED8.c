#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8008F664();           /* extern */
M2C_UNK func_8009065C();     /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800953D0();                      /* extern */
M2C_UNK func_80095460();                      /* extern */
M2C_UNK func_80095910();                   /* extern */
M2C_UNK func_80096FF4();                      /* extern */
M2C_UNK func_800A573C();     /* extern */
extern M2C_UNK D_800903FC;
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800FE490;


typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;   /* the 0x10 bytes before arg0 in func_800A5638, addressed as arg0[-1] */

typedef struct S_800A5638_0 {
    M2C_UNK (*unk_00)(void *, void *, M2C_UNK);
} S_800A5638_0;   /* arg0 in func_800A5638 */


void func_800A5638(void *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    func_800953D0(arg1);
    func_80095910(&D_800FE490);
    func_8009539C(arg1);
    func_80096FF4(arg1);
    func_80095460(arg1);
    func_8008F664(&D_800CFCB4, arg1);
    ((S_800A5638_0 *)arg0)->unk_00(arg0, arg1, arg2);
    if (!(((S_800A5638_0_pre *)arg0)[-1].unk_0E & 0x8000)) {
        if (arg1->unk_04.at00_s32.v <= 0x06500000) {
            arg1->unk_04.at00_s32.v = 0x06500000;
            arg1->unk_10.at00_s32.v = 0x180000;
            if (arg1->unk_08.at00_s32.v > 0) {
                arg1->unk_08.at00_s32.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)arg0)[-1].unk_00 == &D_800903FC) {
            func_8009065C(arg0, arg1, arg2);
            return;
        }
        func_800A573C(arg0, arg1, arg2);
    }
}
