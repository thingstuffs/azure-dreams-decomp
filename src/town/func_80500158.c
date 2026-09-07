#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80500158_1 {
    u8 pad_00[0x35BC];
    s16 unk_35BC;
} S_80500158_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_80500158 */




extern Rec_D_80016000 *D_80016000;


s16 func_80500158(void) {
    return ((S_80500158_1 *)(D_80016000->unk_38.as_pv))->unk_35BC;
}
