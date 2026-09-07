#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016F1C_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016F1C_0;   /* D_80016000 in func_80016F1C */

typedef struct S_80016F1C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80016F1C_1;   /* ((S_80016F1C_0 *)D_80016000)->unk_1C in func_80016F1C */




extern S_80016F1C_0 *D_80016000;


void func_80016F1C(void) {
    ((S_80016F1C_1 *)(D_80016000->unk_1C))->unk_04 = 0x4E0;
    ((S_80016F1C_1 *)(D_80016000->unk_1C))->unk_08 = 0x4E0;
}
