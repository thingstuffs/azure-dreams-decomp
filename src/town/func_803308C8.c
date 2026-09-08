#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8001B0C8_1 {
    u8 pad_00[0x2D60];
    s32 unk_2D60;
} S_8001B0C8_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8001B0C8 */




extern Rec_D_80016000 *D_80016000;


/* Returns the field at offset 0x2D60 in the record linked through D_80016000. */
s32 func_8001B0C8(void) {
    return ((S_8001B0C8_1 *)(D_80016000->unk_38.as_pv))->unk_2D60;
}
