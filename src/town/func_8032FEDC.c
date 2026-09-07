#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A6DC_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8001A6DC_0;   /* D_80016000 in func_8001A6DC */

typedef struct S_8001A6DC_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8001A6DC_1;   /* ((S_8001A6DC_0 *)D_80016000)->unk_1C in func_8001A6DC */




extern S_8001A6DC_0 *D_80016000;


void func_8001A6DC(M2C_UNK arg0, s32 arg1, s32 arg2) {
    ((S_8001A6DC_1 *)(D_80016000->unk_1C))->unk_04 = (s32) (arg1 << 5);
    ((S_8001A6DC_1 *)(D_80016000->unk_1C))->unk_08 = (s32) (arg2 << 5);
}
