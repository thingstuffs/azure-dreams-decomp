#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8059E6D8_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8059E6D8_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8059E6D8 */




extern Rec_D_80016000 *D_80016000;


/* Check whether the stored value meets the minimum. */
s32 func_8059E6D8(u32 minimum) {
    return (u32) ((S_8059E6D8_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= minimum;
}
