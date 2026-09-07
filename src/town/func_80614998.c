#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80614998_1 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_80614998_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_80614998 */




extern Rec_D_80016000 *D_80016000;


s32 func_80614998(void) {
    return ((S_80614998_1 *)(D_80016000->unk_1C.as_pv))->unk_38 != 1;
}
