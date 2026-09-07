#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_800188D4_1 {
    u8 pad_00[0x114];
    s8 unk_114;
} S_800188D4_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_40.as_pv in func_800188D4 */




extern Rec_D_80016000 *D_80016000;


void func_800188D4(void) {
    ((S_800188D4_1 *)(D_80016000->unk_40.as_pv))->unk_114 = 0;
}
