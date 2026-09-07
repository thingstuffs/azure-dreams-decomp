#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_805D352C_2 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_805D352C_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_805D352C */




M2C_UNK func_800174CC();                            /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80019814;
extern M2C_UNK D_80019884;
extern s32 D_80019AF8;
extern M2C_UNK *D_80019B90;

void func_805D352C(void) {
    func_800174CC();
    D_80019B90 = &D_80019814;
    D_80019AF8 = D_80016000->unk_40.as_s32 + (D_80016000->unk_08.at00_s32.v * 8);
    ((S_805D352C_2 *)(((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv))->unk_40 = &D_80019884;
}
