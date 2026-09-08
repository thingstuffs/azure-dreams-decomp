#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80019514_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_80019514_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80019514 */




extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_800186A8;


/* Return the table value selected by the callback at offset 0x2D4. */
s32 func_80019514(void) {
    return *(s32 *)((s8 *) &D_800186A8 + (((S_80019514_1 *)(D_80016000->unk_20))->unk_2D4(0) * 4));
}
