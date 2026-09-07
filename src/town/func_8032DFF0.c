#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_800187F0_1 {
    u8 pad_00[0x1E8];
    M2C_UNK (*unk_1E8)(M2C_UNK);
} S_800187F0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_800187F0 */




extern Rec_D_80016000 *D_80016000;


void func_800187F0(void) {
    ((S_800187F0_1 *)(D_80016000->unk_20))->unk_1E8(7);
}
