#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8008F664();              /* extern */
extern s32 D_80083788[];
extern M2C_UNK D_8009B8E8;
extern s32 D_800D0428[];



typedef struct S_8009C148_2 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_8009C148_2;   /* arg0 in func_8009C148 */

void func_8009C148(S_8009C148_2 *arg0, Rec_D_800CFCB4 *arg1, Rec_D_800E3D7C *arg2) {
    s32 sum;

    arg1->unk_15 = 0;
    sum = D_80083788[0] + D_800D0428[0];
    arg2->unk_0C.as_s32 = 0;
    arg2->unk_10.at00_s32.v = 0;
    arg2->unk_14.as_s32 = 0;
    arg2->unk_08.at00_s32.v = sum;
    func_8008F664(arg1, arg2);
    arg0->unk_50 = &D_8009B8E8;
    arg0->unk_6C = 4;
}

/* MECHANISM: The 0x18 frame and lone s0 save arise from holding arg0 across the call.
   Incomplete extern arrays force the two hi/lo global loads used by retail.
   Computing their sum before the arg2 stores covers load latency and removes the extra nop. */
