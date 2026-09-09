#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8072A244_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8072A244_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_8072A244 */




M2C_UNK func_80016100(s32, s32);                            /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80017A7C;
extern M2C_UNK *D_80017B90;
extern M2C_UNK D_80017F64;


void func_8072A244(s32 arg0, s32 arg1) {
    func_80016100(arg0, arg1);
    D_80017B90 = &D_80017A7C;
    ((S_8072A244_1 *)(D_80016000->unk_1C.as_pv))->unk_40 = &D_80017F64;
}
