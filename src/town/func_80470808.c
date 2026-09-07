#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80017808_1 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80017808_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_40.as_pv in func_80017808 */




extern Rec_D_80016000 *D_80016000;


void func_80017808(void) {
    ((S_80017808_1 *)(D_80016000->unk_40.as_pv))->unk_B0 = 1;
}
