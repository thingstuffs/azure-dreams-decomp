#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_80096788(Rec_D_800E3D7C *);                                /* extern */
M2C_UNK func_800967E0();                 /* extern */
extern s32 D_800FE5D4;


void func_80096810(Rec_D_800E3D7C *arg0) {
    s32 temp_a1;

    if (D_800FE5D4 < 0) {
        temp_a1 = (func_80096788(arg0) << 0x10) - 1;
        if (temp_a1 >= arg0->unk_08.at00_s32.v) {
            func_800967E0(arg0, temp_a1);
        }
    }
}
