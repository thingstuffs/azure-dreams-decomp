#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D4ECC_0 {
    void * unk_00;
} S_806D4ECC_0;   /* &D_80016000 in func_806D4ECC */

typedef struct S_806D4ECC_1 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    void * unk_40;
} S_806D4ECC_1;   /* ((S_806D4ECC_0 *)(&D_80016000))->unk_00 in func_806D4ECC */

typedef struct S_806D4ECC_2 {
    u8 pad_00[0x50];
    s32 (*unk_50)(s8 *);
} S_806D4ECC_2;   /* ((S_806D4ECC_1 *)(((S_806D4ECC_0 *)(&D_80016000))->unk_00))->unk_20 in func_806D4ECC */

typedef struct S_806D4ECC_3 {
    u8 pad_00[0x110];
    s32 unk_110;
} S_806D4ECC_3;   /* ((S_806D4ECC_1 *)(((S_806D4ECC_0 *)(&D_80016000))->unk_00))->unk_40 in func_806D4ECC */




extern M2C_UNK D_80016000;


/* Return the callback result for the pair (5, 0x17) minus the stored value. */
s32 func_806D4ECC(void) {
    s8 queryPair[2];

    queryPair[1] = 0x17;
    queryPair[0] = 5;
    return ((S_806D4ECC_2 *)(((S_806D4ECC_1 *)(((S_806D4ECC_0 *)(&D_80016000))->unk_00))->unk_20))->unk_50(queryPair) - ((S_806D4ECC_3 *)(((S_806D4ECC_1 *)(((S_806D4ECC_0 *)(&D_80016000))->unk_00))->unk_40))->unk_110;
}
