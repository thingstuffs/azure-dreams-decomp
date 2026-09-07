#include "common.h"
#include "m2c_compat.h"

typedef struct S_8051FCE8_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8051FCE8_0;   /* D_80016000 in func_8051FCE8 */

typedef struct S_8051FCE8_1 {
    u8 pad_00[0x280];
    M2C_UNK (*unk_280)(s32);
} S_8051FCE8_1;   /* ((S_8051FCE8_0 *)D_80016000)->unk_20 in func_8051FCE8 */




extern S_8051FCE8_0 *D_80016000;


void func_8051FCE8(s32 arg0) {
    ((S_8051FCE8_1 *)(D_80016000->unk_20))->unk_280(arg0 | 0x8000);
}
