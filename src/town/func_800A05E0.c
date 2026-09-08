#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

typedef struct S_8009DD40_0_pre {
    u16 unk_00;
} S_8009DD40_0_pre;   /* the 0x2 bytes before arg0 in func_8009DD40, addressed as arg0[-1] */



M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_800478B8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
s32 func_80096FF4();                         /* extern */
M2C_UNK func_800970AC();                 /* extern */
s32 func_8009D20C(void *, M2C_UNK);                                /* extern */
extern s32 D_800814A0[];

void func_8009DD40(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s8 *temp_v0;

    if (func_8009D20C(arg0, arg1) != 0) {
        func_8008F134(arg0);
        temp_v0 = ((Rec_D_80082D58 *)arg0)->unk_98.as_ps8;
        if (temp_v0 != NULL) {
            *temp_v0 = 0;
        }
        func_80033D08(arg0);
        ((S_8009DD40_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8009DD40_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)arg0)->unk_50.as_x151a23(arg0, arg0, arg1, arg2);
    if (!(((S_8009DD40_0_pre *)arg0)[-1].unk_00 & 0x8000)) {
        func_800970AC(func_80096FF4(arg1), arg0);
        if (((Rec_D_80082D58 *)arg0)->unk_4D == 0x13) {
            func_800478B8(arg2);
        }
    }
}
