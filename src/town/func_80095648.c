#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8009451C();        /* extern */
M2C_UNK func_80094714();        /* extern */
M2C_UNK func_80094910();                            /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800ABD74();                      /* extern */
extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern M2C_UNK D_800FE488;

typedef struct S_80092DA8_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092DA8_0;   /* town_state in func_80092DA8 */


void func_80092DA8(s32 arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    u8 *town_state;

    town_state = D_80083160;
    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    if (((S_80092DA8_0 *)town_state)->unk_10 & 0x40) {
        func_80094714(arg0, arg1, arg2);
    }
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if (arg1->unk_08.at02_s16.v >= temp_v0) {
        func_80094910();
        func_80095A94(arg1, temp_v0, &D_800FE488);
        func_800ABD74(arg1);
        goto shared_update;
    }

    if (D_800CFCEF == 0) {
        goto no_update;
    }
    func_80094910();
    arg1->unk_14.as_s32 = 0;
    func_800954F4(arg1);

shared_update:
    func_8009451C(arg0, arg1, arg2);
    return;

no_update:
    func_80095388(arg1);
}
