#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_805D39D4_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_805D39D4_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_805D39D4 */




extern Rec_D_80016000 *D_80016000;


/* Returns whether the stored value is below the threshold. */
s32 func_805D39D4(u32 threshold) {
    return (u32) ((S_805D39D4_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C < threshold;
}
