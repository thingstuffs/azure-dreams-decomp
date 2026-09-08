#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800942B0();        /* extern */
M2C_UNK func_80094378();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_800CFCEF;
extern M2C_UNK D_800FE488;



typedef struct S_80091000_1 {
    u8 unk_00;
} S_80091000_1;   /* &D_800CFCEF in func_80091000 */

typedef struct S_80091000_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091000_2;   /* state in func_80091000 */

void func_80091000(s32 arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    u8 *state = D_80083160;

    func_80095C80(arg1);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - arg1->unk_08.at02_s16.v) >= 4) {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(arg0, arg1, arg2);
            return;
        }
        goto block_6;
    }
    if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (((S_80091000_2 *)state)->unk_10 & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        return;
    }
    if (((S_80091000_2 *)state)->unk_08 & 0xF000) {
        func_80094C1C(arg0);
    }
}

/* MECHANISM: Holding D_80083160 in a local base creates retail's s3 lifetime and moves arg2 to s4,
   completing the six-register 0x28-byte prologue contract. Both control-flow arms read the same
   D_800CFCEF byte, allowing one shared lui in the branch delay slot and removing the +1-word cascade. */
