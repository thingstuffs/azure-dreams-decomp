#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016F1C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80016F1C_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_80016F1C */




extern Rec_D_80016000 *D_80016000;


/* Initialize both linked record values to 0x4E0. */
void func_80016F1C(void) {
    ((S_80016F1C_1 *)(D_80016000->unk_1C.as_pv))->unk_04 = 0x4E0;
    ((S_80016F1C_1 *)(D_80016000->unk_1C.as_pv))->unk_08 = 0x4E0;
}
