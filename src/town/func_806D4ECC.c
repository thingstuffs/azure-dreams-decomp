#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"


typedef struct S_806D4ECC_2 {
    u8 pad_00[0x50];
    s32 (*unk_50)(s8 *);
} S_806D4ECC_2;   /* ((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_806D4ECC */

typedef struct S_806D4ECC_3 {
    u8 pad_00[0x110];
    s32 unk_110;
} S_806D4ECC_3;   /* ((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_40 in func_806D4ECC */


/* Return the callback result for the pair (5, 0x17) minus the stored value. */
s32 func_806D4ECC(void) {
    s8 queryPair[2];

    queryPair[1] = 0x17;
    queryPair[0] = 5;
    return ((S_806D4ECC_2 *)(D_80016000->unk_20))->unk_50(queryPair)
    - ((S_806D4ECC_3 *)(D_80016000->unk_40))->unk_110;
}
