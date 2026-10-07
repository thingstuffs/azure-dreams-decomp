#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"


typedef struct S_8001890C_2 {
    u8 pad_00[0x110];
    u32 unk_110;
} S_8001890C_2;   /* ((S_8001890C_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_40 in func_8001890C */

typedef struct S_8001890C_3 {
    u8 pad_00[0x50];
    u32 (*unk_50)(s8 *);
} S_8001890C_3;   /* ((S_8001890C_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20 in func_8001890C */


/* Checks whether the stored value is at least the callback result for query {5, 0x17}. */
s32 func_8001890C(void) {
    s8 queryArgs[2];

    queryArgs[1] = 0x17;
    queryArgs[0] = 5;
    return (s32) ((S_8001890C_2 *)(D_80016000->unk_40))->unk_110
    >= ((S_8001890C_3 *)(D_80016000->unk_20))->unk_50(queryArgs);
}
