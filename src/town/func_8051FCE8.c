#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8051FCE8_1 {
    u8 pad_00[0x280];
    M2C_UNK (*unk_280)(s32);
} S_8051FCE8_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_8051FCE8 */




extern Rec_D_80016000 *D_80016000;


void func_8051FCE8(s32 arg0) {
    ((S_8051FCE8_1 *)(D_80016000->unk_20))->unk_280(arg0 | 0x8000);
}
