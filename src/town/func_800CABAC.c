#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C830C_0 {
    u8 pad_00[0x74];
    s32 unk_74;
} S_800C830C_0;   /* D_80082674 in func_800C830C */


extern S_800C830C_0 *D_80082674;
extern s32 D_800D61F8[];

void func_800C830C(s32 arg0) {
    D_80082674->unk_74 = D_800D61F8[arg0];
}
