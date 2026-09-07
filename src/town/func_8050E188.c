#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8050E188_1 {
    u8 pad_00[0x35BE];
    s16 unk_35BE;
} S_8050E188_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8050E188 */




extern Rec_D_80016000 *D_80016000;


s32 func_8050E188(void) {
    return ((S_8050E188_1 *)(D_80016000->unk_38.as_pv))->unk_35BE >= 0x33;
}
