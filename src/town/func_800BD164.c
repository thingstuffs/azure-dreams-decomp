#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

typedef struct S_800BA8C4_0_pre {
    u16 unk_00;
} S_800BA8C4_0_pre;   /* the 0x2 bytes before arg0 in func_800BA8C4, addressed as arg0[-1] */



M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                            /* extern */
extern volatile struct { s32 v; s32 pad[2]; } D_800814A0;

void func_800BA8C4(void *arg0) {
    if (*((Rec_D_80082D58 *)arg0)->unk_98.as_pu8 == 0) {
        func_8008F134();
        func_80033D08(arg0);
        ((S_800BA8C4_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800BA8C4_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0.v |= 0x8000;
    }
}
