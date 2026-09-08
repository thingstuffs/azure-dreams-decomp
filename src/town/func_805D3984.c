#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_805D3984_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_805D3984_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_805D3984 */




extern Rec_D_80016000 *D_80016000;
extern u32 D_80019B00;


/* Check whether the stored value meets the D_80019B00 threshold. */
s32 func_805D3984(void) {
    return (u32) ((S_805D3984_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= (u32) D_80019B00;
}
