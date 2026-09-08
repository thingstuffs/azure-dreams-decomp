#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80697764_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_80697764_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_80697764 */




extern Rec_D_80016000 *D_80016000;
extern u32 D_80018AE0;


/* Checks whether the stored value meets the D_80018AE0 threshold. */
s32 func_80697764(void) {
    return (u32) ((S_80697764_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= (u32) D_80018AE0;
}
