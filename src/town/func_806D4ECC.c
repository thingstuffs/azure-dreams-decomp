#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_806D4ECC_1 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    void * unk_40;
} S_806D4ECC_1;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_806D4ECC */

typedef struct S_806D4ECC_2 {
    u8 pad_00[0x50];
    s32 (*unk_50)(s8 *);
} S_806D4ECC_2;   /* ((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_806D4ECC */

typedef struct S_806D4ECC_3 {
    u8 pad_00[0x110];
    s32 unk_110;
} S_806D4ECC_3;   /* ((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_40 in func_806D4ECC */




extern M2C_UNK D_80016000;


s32 func_806D4ECC(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 5;
    return ((S_806D4ECC_2 *)(((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_50(sp10) - ((S_806D4ECC_3 *)(((S_806D4ECC_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_40))->unk_110;
}
