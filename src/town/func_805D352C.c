#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D352C_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_805D352C_1;   /* D_80016000 in func_805D352C */

typedef struct S_805D352C_2 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_805D352C_2;   /* ((S_805D352C_1 *)D_80016000)->unk_1C in func_805D352C */


typedef struct S_805D352C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_805D352C_0;   /* D_80016000 in func_805D352C */


M2C_UNK func_800174CC();                            /* extern */
extern S_805D352C_0 *D_80016000;
extern M2C_UNK D_80019814;
extern M2C_UNK D_80019884;
extern s32 D_80019AF8;
extern M2C_UNK *D_80019B90;

void func_805D352C(void) {
    func_800174CC();
    D_80019B90 = &D_80019814;
    D_80019AF8 = D_80016000->unk_40 + (D_80016000->unk_08 * 8);
    ((S_805D352C_2 *)(((S_805D352C_1 *)D_80016000)->unk_1C))->unk_40 = &D_80019884;
}
