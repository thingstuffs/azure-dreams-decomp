#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8054FAEC_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8054FAEC_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8054FAEC */




extern Rec_D_80016000 *D_80016000;


/* Returns whether the current record's value at offset 0x2D5C is at least 100. */
s32 func_8054FAEC(void) {
    return (u32) ((S_8054FAEC_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= 0x64U;
}
