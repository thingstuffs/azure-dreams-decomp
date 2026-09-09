#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_806DB17C_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_806DB17C_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_806DB17C */




u32 func_80016134(s32, s32);                                /* extern */
extern Rec_D_80016000 *D_80016000;


/* Check whether the stored value meets the queried threshold. */
s32 func_806DB17C(s32 query_input, s32 query_param) {
    return (u32) ((S_806DB17C_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= func_80016134(query_input, query_param);
}
