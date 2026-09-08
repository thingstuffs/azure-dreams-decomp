#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016334_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_80016334_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_80016334 */

typedef struct S_80016334_2 {
    u8 pad_00[0x248];
    M2C_UNK (*unk_248)(M2C_UNK);
} S_80016334_2;   /* ((S_80016334_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20 in func_80016334 */

typedef struct S_80016334_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016334_3;   /* ((S_80016334_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_1C in func_80016334 */




extern s8 D_80016000[];


/* Invoke the context callback and check whether the stored value is below 0x3E0. */
s32 func_80016334(void) {
    ((S_80016334_2 *)(((S_80016334_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20))->unk_248(0);
    return ((S_80016334_3 *)(((S_80016334_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_1C))->unk_04 < 0x3E0;
}
